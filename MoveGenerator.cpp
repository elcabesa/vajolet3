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
	/*! \brief check whether a move is allowed or not
	*
	*  check whether a move is allowed or not because of pin against the king
	*  return true if the move is legal, false otherwise
	*/
	inline bool MoveGenerator::_checkAllowedMove( const baseTypes::tSquare from, const baseTypes::tSquare to, const baseTypes::tSquare kingSquare, const GameState& st )
	{
		return 																	// the move is allowed 
			!( st.getPinned().isSquareSet( from ) )								// if the piece is not pinned
			|| baseTypes::BitMap::areSquaresAligned( from, to, kingSquare );	// or if the move is along the pinning direction
	}
	
	/*! \brief generate the moves of a piece type and add it to the movelist
	*

	*/
	template< baseTypes::bitboardIndex pieceType, MoveGenerator::genType mgType > inline void MoveGenerator::_generatePieceMoves( const Position& pos, const baseTypes::bitboardIndex piece, const baseTypes::tSquare kingSquare, const baseTypes::BitMap& occupiedSquares, const baseTypes::BitMap& target, const GameState& st, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		Move m(Move::NOMOVE);
		
		/*
		 get the piece bitmap
		*/
		const baseTypes::BitMap& bFrom = pos.getBitmap( piece );
		
		/*
		 iterate for all the pieces
		*/
		for( const auto& from : bFrom )
		{
			m.setFrom( from );
			
			/*
			 generate the moves depending on the piece type
			*/
			baseTypes::BitMap moveBitMap = target;
			if( pieceType == baseTypes::Queens )
			{
				moveBitMap &= BitMapMoveGenerator::getQueenMoves( from, occupiedSquares );
			}
			else if( pieceType == baseTypes::Rooks )
			{
				moveBitMap &= BitMapMoveGenerator::getRookMoves( from, occupiedSquares );
			}
			else if( pieceType == baseTypes::Bishops )
			{
				moveBitMap &= BitMapMoveGenerator::getBishopMoves( from, occupiedSquares );
			}
			else if( pieceType == baseTypes::Knights )
			{
				// todo confrontare con vajolet2 e controllare se è molto più lento, in vajolet2 faccio un controllo diverso di inchiodatura
				moveBitMap &= BitMapMoveGenerator::getKnightMoves( from );
			}
			else
			{
				/*piece type not managed*/
				assert(false);
				return;
			}

			/*
				iterate the bitmap and add the moves to the list
			*/
			for( const auto& to : moveBitMap )
			{
				
				if( _checkAllowedMove( from, to, kingSquare, st ) )
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
	
	/*! \brief generate the moves of the king piece tpye and add it to the movelist
	*

	*/
	template< MoveGenerator::genType mgType > inline void MoveGenerator::_generateKingMoves( const Position& pos, const baseTypes::tSquare kingSquare, const baseTypes::BitMap& target, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		Move m(Move::NOMOVE);
		
		m.setFrom( kingSquare );
		/*
		generate the moves
		*/
		baseTypes::BitMap moveBitMap = BitMapMoveGenerator::getKingMoves( kingSquare ) & target;

		/*
		 iterate the bitmap and add the moves to the list
		*/
		for( const auto& to : moveBitMap )
		{
			if( pos.checkKingAllowedMove( to) )
			{
				// todo fare funzione comune??
				if( mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
				{
					m.setTo( to );
					ml.insert(m);
				}
			}
		}
	}
	
	/*! \brief insert pawns move on the move list besed on move delta
	*

	*/
	template< MoveGenerator::genType mgType > inline void MoveGenerator::_insertPawn( const baseTypes::BitMap& movesBitmap, const baseTypes::tSquare delta, const baseTypes::tSquare kingSquare, const Position& pos, const GameState& st, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		Move m(Move::NOMOVE);
		
		/*
		 iterate the bitmap and add the moves to the list
		*/
		for( const auto& to : movesBitmap )
		{
			baseTypes::tSquare from = to - delta;
			
			if( _checkAllowedMove( from, to, kingSquare, st ) )
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
	
	/*! \brief insert promoting pawns move on the move list besed on move delta
	*

	*/
	template< MoveGenerator::genType mgType > inline void MoveGenerator::_insertPromotionPawn( const baseTypes::BitMap& movesBitmap, const baseTypes::tSquare delta, const baseTypes::tSquare kingSquare, const GameState& st, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		Move m(Move::NOMOVE);
		m.setFlag(Move::fpromotion);
				
		/*
		 iterate the bitmap and add the moves to the list
		*/
		for( const auto& to : movesBitmap )
		{
			baseTypes::tSquare from = to - delta;
			
			if( _checkAllowedMove( from, to, kingSquare, st ) )
			{
				m.setFrom( from );
				m.setTo( to );
						
				/*
				iterate all the promotion types
				*/
				for( Move::epromotion prom = Move::promQueen; prom <= Move::promKnight; prom = (Move::epromotion)( prom + 1 ) )
				{
					m.setPromotion( prom );
					ml.insert(m);
				}
			}
		}		
	}
	
	/*! \brief generate and insert en passant pawns move on the move list
	*

	*/
	inline void MoveGenerator::_generateEnPassantMoves( const Position& pos, const GameState& st, const baseTypes::BitMap& occupiedSquares, const baseTypes::BitMap& nonPromotingPawns, const baseTypes::tSquare kingSquare, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		/*
		if en passant square is iset
		*/
		if( st.hasEpSquareSet() )
		{
			const baseTypes::tSquare epSquare = st.getEpSquare();
			const baseTypes::tColor color = pos.isBlackTurn() ? baseTypes::white : baseTypes::black;
			const baseTypes::BitMap epAttackerBitMap = nonPromotingPawns & BitMapMoveGenerator::getPawnAttack( epSquare, color );
			
			/*
			for every attacker
			*/
			for( const auto& from : epAttackerBitMap )
			{
				
				const baseTypes::tSquare captureSquare = baseTypes::getSquareFromFileRank( baseTypes::getFile( epSquare ), baseTypes::getRank( from ) );
				const baseTypes::BitMap occ = ( ( occupiedSquares ^ from ) ^ epSquare ) ^ captureSquare;
				
				/*
				check whether the ep is forbidden because of discovery check
				*/
				if( 
					(
						/* test for horizontal/vertical discovery*/
						( BitMapMoveGenerator::getRookMoves( kingSquare, occ ) & pos.getTheirQRSlidingBitMap() )
						+
						/* test for diagonal discovery*/
						( BitMapMoveGenerator::getBishopMoves( kingSquare, occ ) & pos.getTheirQBSlidingBitMap() ) 
					).isEmpty()
				)
				{
					/* finally insert the move*/
					Move m( Move::NOMOVE );
					m.setFlag( Move::fenpassant );
					m.setFrom( from );
					m.setTo( epSquare );
					ml.insert( m ); 
				}
			}
		}
	}
	
	
	/*! \brief generate and insert a castling moves on the move list
	*

	*/
	template< MoveGenerator::genType mgType > inline void MoveGenerator::_generateCastleMove( const Position& pos, const GameState& st, const baseTypes::eCastle castleType, const bool isKingSideCastle, const baseTypes::tColor color, const baseTypes::tSquare kingSquare, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		/*
		check wheter the king has the castle right and the paths are free
		*/
		if( st.hasCastleRight( castleType, color ) && !( pos.getCastleOccupancyPath( color, isKingSideCastle ).isIntersecting( pos.getOccupationBitMap() ) ) )
		{
			const baseTypes::tSquare rookSq = pos.getCastleRookInvolved( color, isKingSideCastle );
			/*
			check whether the castling is denied by a check in the castle path
			*/
			for( auto sq: pos.getKingCastlePath( color, isKingSideCastle ) )
			{
				if( pos.getAttackersTo( sq, pos.getOccupationBitMap() ^ rookSq ).isIntersecting( pos.getTheirBitMap() ) )
				{
					return;
				}
			}
			
			/* if the castle is allowed insert the move*/
			Move m( Move::NOMOVE ); 
			m.setFlag( Move::fcastle );
			m.setFrom( kingSquare );
			m.setTo( rookSq );
			
			if( mgType != MoveGenerator::quietChecksMg || pos.moveGivesCheck( m ) )
			{
				ml.insert(m);
			}
		}
	}
	
	/*! \brief movegenerator template
	*

	*/
	template< MoveGenerator::genType mgType > void MoveGenerator::generateMoves( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		// initialize constants
		const GameState& st = pos.getActualStateConst();
		
		const baseTypes::eTurn turn = st.getTurn();
			
		const baseTypes::BitMap& opponent = pos.getTheirBitMap();
		const baseTypes::BitMap& occupiedSquares = pos.getOccupationBitMap();

		const baseTypes::tSquare kingSquare = pos.getSquareOfMyKing();
		
		// populate the target squares bitmaps
		baseTypes::BitMap kingTarget;
		baseTypes::BitMap target;
		const baseTypes::BitMap& checkers = st.getCheckers();
		
		if( mgType == MoveGenerator::allEvasionMg )
		{
			assert( checkers.isEmpty() == false );
			target = ( checkers + baseTypes::BitMap::getSquaresBetween( kingSquare, checkers.firstOne() ) ) & ~pos.getOurBitMap();
			kingTarget = ~pos.getOurBitMap();
		}
		else if( mgType == MoveGenerator::captureEvasionMg )
		{
			assert( checkers.isEmpty() == false );
			target = ( checkers ) & ~pos.getOurBitMap();
			kingTarget = target + opponent;
		}
		else if( mgType == MoveGenerator::quietEvasionMg )
		{
			assert( checkers.isEmpty() == false );
			target = baseTypes::BitMap::getSquaresBetween( kingSquare, checkers.firstOne() ) & ~pos.getOurBitMap();
			kingTarget = ~occupiedSquares;
		}
		else if( mgType == MoveGenerator::allNonEvasionMg )
		{
			target= ~pos.getOurBitMap();
			kingTarget = target;
		}
		else if( mgType == MoveGenerator::captureMg )
		{
			target = opponent;
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
		
		//------------------------------------------------------
		// king
		//------------------------------------------------------
		
		baseTypes::bitboardIndex piece = pos.getMyPiece( baseTypes::King );
		_generateKingMoves< mgType >( pos, kingSquare, kingTarget, ml );
		
		//-----------------------------------------------------------------------------------------------
		// if the king is in check from 2 enemy, it can only run away, we should not search any other move
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
		_generatePieceMoves< baseTypes::Queens, mgType >( pos, ++piece, kingSquare, occupiedSquares, target, st, ml );
		
		//------------------------------------------------------
		// rook
		//------------------------------------------------------
		_generatePieceMoves< baseTypes::Rooks, mgType >( pos, ++piece, kingSquare, occupiedSquares, target, st, ml );
		
		//------------------------------------------------------
		// bishop
		//------------------------------------------------------
		_generatePieceMoves< baseTypes::Bishops, mgType >( pos, ++piece, kingSquare, occupiedSquares, target, st, ml );
		
		//------------------------------------------------------
		// knight
		//------------------------------------------------------
		_generatePieceMoves< baseTypes::Knights, mgType >( pos, ++piece, kingSquare, occupiedSquares, target, st, ml );
		
		//------------------------------------------------------
		// pawns
		//------------------------------------------------------

		// pawns bitmaps
		const baseTypes::BitMap& thirdRankMask = baseTypes::BitMap::getRankMask( turn == baseTypes::whiteTurn ? baseTypes::A3 : baseTypes::A6 );
		const baseTypes::BitMap& seventhRankMask = baseTypes::BitMap::getRankMask( turn == baseTypes::whiteTurn ? baseTypes::A7 : baseTypes::A2 );

		const baseTypes::BitMap promotingPawns = pos.getOurBitMap( baseTypes::Pawns ) & seventhRankMask ;
		const baseTypes::BitMap nonPromotingPawns = pos.getOurBitMap( baseTypes::Pawns ) ^ promotingPawns;
		
		if( mgType != MoveGenerator::captureMg && mgType != MoveGenerator::captureEvasionMg )
		{
			//--------------------------------------------------
			// pawn push
			//--------------------------------------------------
			
			baseTypes::BitMap movesBitMap = BitMapMoveGenerator::getPawnGroupAdvance( nonPromotingPawns, turn, occupiedSquares );
			// save it for double push
			baseTypes::BitMap pawnPushed = movesBitMap;
			movesBitMap &= target;
			_insertPawn< mgType >( movesBitMap, pawnPush( turn ) , kingSquare, pos, st, ml );

			//--------------------------------------------------
			// double pawn push
			//--------------------------------------------------
			
			movesBitMap = BitMapMoveGenerator::getPawnGroupAdvance( (pawnPushed & thirdRankMask), turn, occupiedSquares ) & target;
			_insertPawn< mgType >( movesBitMap, pawnDoublePush( turn ) , kingSquare, pos, st, ml );
		}
		
		//--------------------------------------------------
		// pawn capture
		//--------------------------------------------------
		if( mgType != MoveGenerator::quietMg && mgType != MoveGenerator::quietChecksMg && mgType != MoveGenerator::quietEvasionMg )
		{
			
			//left capture
			baseTypes::BitMap movesBitMap = BitMapMoveGenerator::getPawnGroupCaptureLeft( nonPromotingPawns, turn, opponent & target );
			_insertPawn< mgType >( movesBitMap, pawnLeftCapture( turn ) , kingSquare, pos, st, ml );
			
			//right capture
			movesBitMap = BitMapMoveGenerator::getPawnGroupCaptureRight( nonPromotingPawns, turn, opponent & target );
			_insertPawn< mgType >( movesBitMap, pawnRightCapture( turn ) , kingSquare, pos, st, ml );
		}
		
		//------------------------------------------------------
		// pawns promotions
		//------------------------------------------------------
		if( mgType != MoveGenerator::captureMg && mgType != MoveGenerator::captureEvasionMg )
		{
			//--------------------------------------------------
			// pawn push promotion
			//--------------------------------------------------
			baseTypes::BitMap movesBitMap = BitMapMoveGenerator::getPawnGroupAdvance( promotingPawns, turn, occupiedSquares ) & target;
			_insertPromotionPawn< mgType >( movesBitMap, pawnPush( turn ) , kingSquare, st, ml );
		}
		
		if( mgType != MoveGenerator::quietMg && mgType != MoveGenerator::quietChecksMg && mgType != MoveGenerator::quietEvasionMg )
		{
			//left capture promotion
			baseTypes::BitMap movesBitMap = BitMapMoveGenerator::getPawnGroupCaptureLeft( promotingPawns, turn, opponent & target );
			_insertPromotionPawn< mgType >( movesBitMap, pawnLeftCapture( turn ) , kingSquare, st, ml );
			
			//right capture promotion
			movesBitMap = BitMapMoveGenerator::getPawnGroupCaptureRight( promotingPawns, turn, opponent & target );
			_insertPromotionPawn< mgType >( movesBitMap, pawnRightCapture( turn ) , kingSquare, st, ml );
			
			//------------------------------------------------------
			// en passant capture
			//------------------------------------------------------
			_generateEnPassantMoves( pos, st, occupiedSquares, nonPromotingPawns, kingSquare, ml );
			
		}
		
		//------------------------------------------------------
		// king castle
		//------------------------------------------------------
		if( mgType != MoveGenerator::allEvasionMg && mgType != MoveGenerator::captureEvasionMg && mgType != MoveGenerator::quietEvasionMg && mgType!= MoveGenerator::captureMg)
		{
			if( checkers.isEmpty() )
			{
				const baseTypes::tColor color = pos.isBlackTurn() ?  baseTypes::black : baseTypes::white;
				
				// kingSquare
				_generateCastleMove< mgType >( pos, st, baseTypes::wCastleOO, true, color, kingSquare, ml );
				
				// queenSquare
				_generateCastleMove< mgType >( pos, st, baseTypes::wCastleOOO, false, color, kingSquare, ml );
			}	
		}
	}

	/*! \brief generate all the legal moves
	*

	*/
	template<> void MoveGenerator::generateMoves< MoveGenerator::allMg >( const Position& pos, MoveList< MoveGenerator::maxMovePerPosition >& ml )
	{
		/* if in check generate evasion */
		if( pos.isInCheck() )
		{
			generateMoves< MoveGenerator::captureEvasionMg >( pos, ml );
			generateMoves< MoveGenerator::quietEvasionMg >( pos, ml );
		}
		/* otherwise generate all moves */
		else
		{
			generateMoves< MoveGenerator::captureMg >( pos, ml );
			generateMoves< MoveGenerator::quietMg >( pos, ml );
		}
	}
}
