/*
	This file is part of Vajolet.
	Copyright (C) 2013-2018 Marco Belli
	
    Vajolet is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Vajolet is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Vajolet.  If not, see <http://www.gnu.org/licenses/>
*/

#include "MoveGenerator.h"
#include "BitMapMoveGenerator.h"

namespace libChess
{
	
	inline bool MoveGenerator::_checkAllowedMove( const baseTypes::tSquare from, const baseTypes::tSquare to, const baseTypes::tSquare kingSquare, const GameState& s )
	{
		return !( ( s.getPinned() & from ).isEmpty() ) || baseTypes::BitMap::areSquaresAligned( from, to, kingSquare );
	}
	
	inline bool MoveGenerator::_checkKingAllowedMove( const Position& pos, const baseTypes::tSquare to, const baseTypes::BitMap& occupiedSquares, const baseTypes::BitMap& opponent )
	{
		return ( ( pos.getAttackersTo( to, occupiedSquares & ~pos.getOurBitmap( baseTypes::King ) ) & opponent ).isEmpty() == false );
	}
	
	template< baseTypes::bitboardIndex pieceType, MoveGenerator::genType mgType > inline void MoveGenerator::_generatePieceMoves( const Position& pos, const baseTypes::bitboardIndex piece, const baseTypes::tSquare kingSquare, const baseTypes::BitMap& occupiedSquares, const baseTypes::BitMap& target, const GameState& s, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		Move m(Move::NOMOVE);
		const baseTypes::BitMap bFrom = pos.getBitmap( piece );
		
		for( const auto& from : bFrom )
		{
			
			m.setFrom( from );
			baseTypes::BitMap moveBitMap;
			
			if( pieceType == baseTypes::Queens )
			{
				moveBitMap = BitMapMoveGenerator::getQueenMoves( from, occupiedSquares ) & target;
			}
			else if( pieceType == baseTypes::Rooks )
			{
				moveBitMap = BitMapMoveGenerator::getRookMoves( from, occupiedSquares ) & target;
			}
			else if( pieceType == baseTypes::Bishops )
			{
				moveBitMap = BitMapMoveGenerator::getBishopMoves( from, occupiedSquares ) & target;
			}
			else if( pieceType == baseTypes::Knights )
			{
				// todo confrontare con vajolet2 e controllare se è molto più lento
				moveBitMap = BitMapMoveGenerator::getKnightMoves( from ) & target;
			}

			for( const auto& to : moveBitMap )
			{
				if( _checkAllowedMove( from, to, kingSquare, s ) )
				{
					m.setTo( to );
					if( mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
					{
						ml.insert(m);
					}
				}
			}
		}
		
	}
	
	template< MoveGenerator::genType mgType > inline void MoveGenerator::_generateKingMoves( const Position& pos, const baseTypes::tSquare kingSquare, const baseTypes::BitMap& occupiedSquares, const baseTypes::BitMap& target, const baseTypes::BitMap& opponent, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		Move m(Move::NOMOVE);
		
		m.setFrom( kingSquare );
		
		baseTypes::BitMap moveBitMap = BitMapMoveGenerator::getKingMoves( kingSquare ) & target;

		for( const auto& to : moveBitMap )
		{
			if( _checkKingAllowedMove( pos, to, occupiedSquares, opponent ) )
			{
				m.setTo( to );
				// todo fare funzione comune??
				if(mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
				{
					ml.insert(m);
				}
			}
		}
	}
	
	template< MoveGenerator::genType mgType > void MoveGenerator::generateMoves( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		// initialize constants
		const GameState& s = pos.getActualStateConst();
		
		//todo mettere baseTypes::Pieces come parametro di default?
		const baseTypes::BitMap& opponent = pos.getTheirBitmap( baseTypes::Pieces );
		const baseTypes::BitMap& occupiedSquares = pos.getOccupationBitmap();

		// pawns bitmaps
		const baseTypes::BitMap& thirdRankMask = baseTypes::BitMap::getRankMask( s.getTurn() == baseTypes::whiteTurn ? baseTypes::A3 : baseTypes::A6 );
		const baseTypes::BitMap& seventhRankMask = baseTypes::BitMap::getRankMask( s.getTurn() == baseTypes::whiteTurn ? baseTypes::A7 : baseTypes::A2 );

		const baseTypes::BitMap promotionPawns = pos.getOurBitmap( baseTypes::Pawns ) & seventhRankMask ;
		const baseTypes::BitMap nonPromotionPawns = pos.getOurBitmap( baseTypes::Pawns ) ^ promotionPawns;

		const baseTypes::tSquare kingSquare = pos.getSquareOfThePiece( pos.getMyPiece( baseTypes::King ) );
		
		// populate the target squares bitmaps
		baseTypes::BitMap kingTarget;
		baseTypes::BitMap target;
		const baseTypes::BitMap checkers = s.getCheckers();
		
		if( mgType == MoveGenerator::allEvasionMg )
		{
			assert( checkers.isEmpty() == false );
			target = ( checkers + baseTypes::BitMap::getSquaresBetween( kingSquare, checkers.firstOne() ) ) & ~pos.getOurBitmap( baseTypes::Pieces );
			kingTarget = ~pos.getOurBitmap( baseTypes::Pieces );
		}
		else if( mgType == MoveGenerator::captureEvasionMg )
		{
			assert( checkers.isEmpty() == false );
			target = ( checkers ) & ~pos.getOurBitmap( baseTypes::Pieces );
			kingTarget = target + pos.getTheirBitmap( baseTypes::Pieces );
		}
		else if( mgType == MoveGenerator::quietEvasionMg )
		{
			assert( checkers.isEmpty() == false );
			target = baseTypes::BitMap::getSquaresBetween( kingSquare, checkers.firstOne() ) & ~pos.getOurBitmap( baseTypes::Pieces );
			kingTarget = ~occupiedSquares;
		}
		else if( mgType == MoveGenerator::allNonEvasionMg )
		{
			target= ~pos.getOurBitmap( baseTypes::Pieces );
			kingTarget = target;
		}
		else if( mgType == MoveGenerator::captureMg )
		{
			target = pos.getTheirBitmap( baseTypes::Pieces );
			kingTarget = target;
		}
		else if( mgType == MoveGenerator::quietMg )
		{
			target = ~occupiedSquares;
			kingTarget = target;
		}
		else if( mgType == MoveGenerator::quietChecksMg )
		{
			target = ~occupiedSquares;
			kingTarget = target;
		}
		else
		{
			assert(false);
			assert( checkers.isEmpty() == false );
			target = baseTypes::BitMap(0);
			kingTarget = baseTypes::BitMap(0);
		}
		
		baseTypes::BitMap moveBitMap;
		Move m( Move::NOMOVE );
		//------------------------------------------------------
		// king
		//------------------------------------------------------
		
		baseTypes::bitboardIndex piece = pos.getMyPiece( baseTypes::King );
		_generateKingMoves< mgType >( pos, kingSquare, occupiedSquares, kingTarget, opponent, ml );
		
		//-----------------------------------------------------------------------------------------------
		// if the king is in check from 2 enemy, it can only run away, we sohld not search any other move
		//-----------------------------------------------------------------------------------------------
		if( ( 
				mgType == MoveGenerator::allEvasionMg 
				|| mgType == MoveGenerator::captureEvasionMg 
				|| mgType == MoveGenerator::quietEvasionMg
			)
			&& checkers.moreThanOneBit()
		)
		{
			return;
		}
		
		//------------------------------------------------------
		// queen
		//------------------------------------------------------
		_generatePieceMoves< baseTypes::Queens, mgType >( pos, ++piece, kingSquare, occupiedSquares, target, s, ml );
		
		//------------------------------------------------------
		// rook
		//------------------------------------------------------
		_generatePieceMoves< baseTypes::Rooks, mgType >( pos, ++piece, kingSquare, occupiedSquares, target, s, ml );
		
		//------------------------------------------------------
		// bishop
		//------------------------------------------------------
		_generatePieceMoves< baseTypes::Bishops, mgType >( pos, ++piece, kingSquare, occupiedSquares, target, s, ml );
		
		//------------------------------------------------------
		// knight
		//------------------------------------------------------
		_generatePieceMoves< baseTypes::Knights, mgType >( pos, ++piece, kingSquare, occupiedSquares, target, s, ml );
		
		
	}
	
	template void MoveGenerator::generateMoves< MoveGenerator::captureMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml );
	template void MoveGenerator::generateMoves< MoveGenerator::quietMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml );
	template void MoveGenerator::generateMoves< MoveGenerator::quietChecksMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml );
	
	template<> void MoveGenerator::generateMoves< MoveGenerator::allMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		// todo add this code
		if( pos.isInCheck() )
		{
			generateMoves< MoveGenerator::captureEvasionMg >( pos, ml );
			generateMoves< MoveGenerator::quietEvasionMg >( pos, ml );
		}
		else
		{
			generateMoves< MoveGenerator::captureMg >( pos, ml );
			generateMoves< MoveGenerator::quietMg >( pos, ml );
		}
	}
}
