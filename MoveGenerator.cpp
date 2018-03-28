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
		return ( ( s.getPinned() & from ).isEmpty() ) || baseTypes::BitMap::areSquaresAligned( from, to, kingSquare );
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
				// todo confrontare con vajolet2 e controllare se è molto più lento, in vajolet2 faccio un controllo diverso di inchiodatura
				moveBitMap = BitMapMoveGenerator::getKnightMoves( from ) & target;
			}

			for( const auto& to : moveBitMap )
			{
				
				if( _checkAllowedMove( from, to, kingSquare, s ) )
				{
					if( mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
					{
						m.setTo( to );
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
				// todo fare funzione comune??
				if(mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
				{
					m.setTo( to );
					ml.insert(m);
				}
			}
		}
	}
	
	template< MoveGenerator::genType mgType > inline void MoveGenerator::_insertPawn( const baseTypes::BitMap& movesBitmap, const baseTypes::tSquare delta, const baseTypes::tSquare kingSquare, const Position& pos, const GameState& s, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		Move m(Move::NOMOVE);
		
		for( const auto& to : movesBitmap )
		{
			baseTypes::tSquare from = to - delta;
			
			if( _checkAllowedMove( from, to, kingSquare, s ) )
			{
				if( mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
				{
					m.setFrom( from );
					m.setTo( to );
					ml.insert(m);
				}
			}
		}		
	}
	
	template< MoveGenerator::genType mgType > inline void MoveGenerator::_insertPromotionPawn( const baseTypes::BitMap& movesBitmap, const baseTypes::tSquare delta, const baseTypes::tSquare kingSquare, const GameState& s, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		Move m(Move::NOMOVE);
		m.setFlag(Move::fpromotion);
		
		for( const auto& to : movesBitmap )
		{
			baseTypes::tSquare from = to - delta;
			
			if( _checkAllowedMove( from, to, kingSquare, s ) )
			{
				m.setFrom( from );
				m.setTo( to );
				for( Move::epromotion prom = Move::promQueen; prom <= Move::promKnight; prom = (Move::epromotion)( prom + 1 ) )
				{
					m.setPromotion( prom );
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

		const baseTypes::BitMap promotingPawns = pos.getOurBitmap( baseTypes::Pawns ) & seventhRankMask ;
		const baseTypes::BitMap nonPromotingPawns = pos.getOurBitmap( baseTypes::Pawns ) ^ promotingPawns;

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
		//Move m( Move::NOMOVE );
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
		
		//------------------------------------------------------
		// pawns
		//------------------------------------------------------

		if( mgType != MoveGenerator::captureMg && mgType != MoveGenerator::captureEvasionMg )
		{
			//--------------------------------------------------
			// pawn push
			//--------------------------------------------------
			
			baseTypes::BitMap movesBitMap = BitMapMoveGenerator::getPawnGroupAdvance( nonPromotingPawns, s.getTurn(), occupiedSquares );
			// save it for double push
			baseTypes::BitMap pawnPushed = movesBitMap;
			movesBitMap &= target;
			_insertPawn< mgType >( movesBitMap, pawnPush( s.getTurn() ) , kingSquare, pos, s, ml );

			//--------------------------------------------------
			// double pawn push
			//--------------------------------------------------
			
			movesBitMap = BitMapMoveGenerator::getPawnGroupAdvance( (pawnPushed & thirdRankMask), s.getTurn(), occupiedSquares ) & target;
			_insertPawn< mgType >( movesBitMap, pawnDoublePush( s.getTurn() ) , kingSquare, pos, s, ml );
		}
		
		//--------------------------------------------------
		// pawn capture
		//--------------------------------------------------
		if( mgType != MoveGenerator::quietMg && mgType != MoveGenerator::quietChecksMg && mgType != MoveGenerator::quietEvasionMg )
		{
			
			//left capture
			baseTypes::BitMap movesBitMap = BitMapMoveGenerator::getPawnGroupCaptureLeft( nonPromotingPawns, s.getTurn(), opponent & target );
			_insertPawn< mgType >( movesBitMap, pawnLeftCapture( s.getTurn() ) , kingSquare, pos, s, ml );
			
			//right capture
			movesBitMap = BitMapMoveGenerator::getPawnGroupCaptureRight( nonPromotingPawns, s.getTurn(), opponent & target );
			_insertPawn< mgType >( movesBitMap, pawnRightCapture( s.getTurn() ) , kingSquare, pos, s, ml );
		}
		
		//------------------------------------------------------
		// pawns promotions
		//------------------------------------------------------
		if( mgType != MoveGenerator::captureMg && mgType != MoveGenerator::captureEvasionMg )
		{
			//--------------------------------------------------
			// pawn push promotion
			//--------------------------------------------------
			baseTypes::BitMap movesBitMap = BitMapMoveGenerator::getPawnGroupAdvance( promotingPawns, s.getTurn(), occupiedSquares ) & target;
			_insertPromotionPawn< mgType >( movesBitMap, pawnPush( s.getTurn() ) , kingSquare, s, ml );
		}
		
		if( mgType != MoveGenerator::quietMg && mgType != MoveGenerator::quietChecksMg && mgType != MoveGenerator::quietEvasionMg )
		{
			//left capture promotion
			baseTypes::BitMap movesBitMap = BitMapMoveGenerator::getPawnGroupCaptureLeft( promotingPawns, s.getTurn(), opponent & target );
			_insertPawn< mgType >( movesBitMap, pawnLeftCapture( s.getTurn() ) , kingSquare, pos, s, ml );
			
			//right capture promotion
			movesBitMap = BitMapMoveGenerator::getPawnGroupCaptureRight( promotingPawns, s.getTurn(), opponent & target );
			_insertPawn< mgType >( movesBitMap, pawnRightCapture( s.getTurn() ) , kingSquare, pos, s, ml );
			
			//------------------------------------------------------
			// en passant capture
			//------------------------------------------------------
			
			
			
			if( s.getEpSquare() != baseTypes::squareNone )
			{
				Move m( Move::NOMOVE );
				m.setFlag( Move::fenpassant );
				const baseTypes::tColor color = pos.isBlackTurn() ?  baseTypes::white : baseTypes::black;
				
				const baseTypes::BitMap epAttackerBitMap = nonPromotingPawns & BitMapMoveGenerator::getPawnAttack( s.getEpSquare(), color );
				
				for( const auto& from : epAttackerBitMap )
				{
					const baseTypes::tSquare captureSquare = baseTypes::getSquareFromFileRank( baseTypes::getFile( s.getEpSquare() ), baseTypes::getRank( from ) );
					const baseTypes::BitMap occ = ( ( occupiedSquares ^ from ) ^ s.getEpSquare() ) ^ captureSquare;
					
					// check ep discovery
					if( 
						(
							( BitMapMoveGenerator::getRookMoves( kingSquare, occ ) & ( pos.getTheirBitmap( baseTypes::Queens ) + pos.getTheirBitmap( baseTypes::Rooks ) ) )
							+
							( BitMapMoveGenerator::getBishopMoves( kingSquare, occ ) & (pos.getTheirBitmap( baseTypes::Queens ) + pos.getTheirBitmap( baseTypes::Bishops ) ) ) 
						).isEmpty()
					)
					{
						m.setFrom( from );
						m.setTo( s.getEpSquare() );
						ml.insert( m ); 
					}
				}
			}
		}
		
		//------------------------------------------------------
		// king castle
		//------------------------------------------------------
		if( mgType != MoveGenerator::allEvasionMg && mgType != MoveGenerator::captureEvasionMg && mgType != MoveGenerator::quietEvasionMg && mgType!= MoveGenerator::captureMg)
		{
			if( s.getCheckers().isEmpty() )
			{
				const baseTypes::tColor color = pos.isBlackTurn() ?  baseTypes::black : baseTypes::white;
				
				// kingSquare
				if( s.hasCastleRight( baseTypes::wCastleOO, color ) && ( pos.getCastleOccupancyPath( color, true ) & pos.getOccupationBitmap() ).isEmpty() )
				{
					bool castleDenied = false;
					for( auto sq: pos.getKingCastlePath( color, true ) )
					{

						if( ( pos.getAttackersTo( sq, pos.getOccupationBitmap() ^ pos.getCastleRookInvolved( color, true ) ) & pos.getTheirBitmap( baseTypes::Pieces ) ).isEmpty() == false )
						{
							castleDenied = true;
							break;
						}
					}
					
					if( !castleDenied )
					{
						Move m( Move::NOMOVE ); 
						m.setFlag( Move::fcastle );
						m.setFrom( kingSquare );
						m.setTo( color == baseTypes::white ? baseTypes::G1: baseTypes::G8 );
						if( mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
						{
							ml.insert(m);
						}
					}
				}
				// queenSquare
				if( s.hasCastleRight( baseTypes::wCastleOOO, color ) && ( pos.getCastleOccupancyPath( color, false ) & pos.getOccupationBitmap() ).isEmpty() )
				{
					bool castleDenied = false;
					for( auto sq: pos.getKingCastlePath( color, false ) )
					{
						if( ( pos.getAttackersTo( sq, pos.getOccupationBitmap() ^ pos.getCastleRookInvolved( color, false )) & pos.getTheirBitmap( baseTypes::Pieces ) ).isEmpty() == false )
						{
							castleDenied = true;
							break;
						}
					}
					if( !castleDenied )
					{
						Move m( Move::NOMOVE ); 
						m.setFlag( Move::fcastle );
						m.setFrom( kingSquare );
						m.setTo( color == baseTypes::white ? baseTypes::C1: baseTypes::C8 );
						if( mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
						{
							ml.insert(m);
						}
					}
				}
			}
			
		}
	}
	
	template void MoveGenerator::generateMoves< MoveGenerator::captureMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml );
	template void MoveGenerator::generateMoves< MoveGenerator::quietMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml );
	template void MoveGenerator::generateMoves< MoveGenerator::quietChecksMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml );
	
	template<> void MoveGenerator::generateMoves< MoveGenerator::allMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
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
