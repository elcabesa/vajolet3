/*
	This file is part of Vajolet.

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

#include "gtest/gtest.h"
#include "./../State.h"






namespace libChess
{
	// Google-test:
	class GameStateFixture: public GameState
	{
		public:
		
		using GameState::setKeys;

		using GameState::setMaterialValues;

		using GameState::setTurn;
		
		using GameState::setCastleRights;
		using GameState::setCastleRight;
		using GameState::resetAllCastleRights;
		
		using GameState::setFiftyMoveCnt;
		using GameState::setPliesCnt;
		
		using GameState::setCurrentMove;
		using GameState::setEpSquare;
		
		using GameState::setCapturedPiece;
		using GameState::resetCapturedPiece;
		
		using GameState::setCheckingSquare;
		using GameState::setDiscoveryChechers;
		using GameState::setPinned;
		using GameState::setCheckers;
			
		/*****************************************************************
		*	update method, if necessary update keys
		******************************************************************/
		
		using GameState::changeTurn;
		
		using GameState::incrementCounters;
		using GameState::incrementCountersNullMove;
		using GameState::resetCountersNullMove;
		using GameState::resetFiftyMoveCnt;
		
		using GameState::clearEpSquare;
		using GameState::addEpSquare;
		
		using GameState::clearCastleRight;
		
		using GameState::keyMovePiece;
		using GameState::keyRemovePiece;
		using GameState::keyPromotePiece;
		
		using GameState::pawnKeyMovePiece;
		using GameState::pawnKeyRemovePiece;
		
		using GameState::materialKeyRemovePiece;
		using GameState::materialKeyPromovePiece;
		
		using GameState::materialMovePiece;
		using GameState::materialCapturePiece;
		using GameState::materialPromotePiece;
		
		/*****************************************************************
		*	other methods
		******************************************************************/
		using GameState::hasCastleRight;
		using GameState::hasEpSquareSet;


	
	};
}

using namespace libChess;

namespace {
	
	TEST(GameState, getKey)
	{
		GameState g;
		ASSERT_EQ( g.getKey(), g.getKey());
	}
	
	TEST(GameState, getPawnKey)
	{
		GameState g;
		ASSERT_EQ( g.getPawnKey(), g.getPawnKey());
	}
	
	TEST(GameState, getMaterialKey)
	{
		GameState g;
		ASSERT_EQ( g.getMaterialKey(), g.getMaterialKey());
	}
	
	TEST(GameState,MaterialValueGetSet)
	{
		GameStateFixture g;
		simdScore mv = { 450, 245, 0, 0 };
		simdScore npmv = { 38350, -392, 0, 0 };
		g.setMaterialValues( mv, npmv );
		simdScore readNpmv= g.getNonPawnMaterialValue();
		simdScore readMv= g.getMaterialValue();
		ASSERT_EQ( npmv[0], readNpmv[0]);
		ASSERT_EQ( npmv[1], readNpmv[1]);
		ASSERT_EQ( mv[0], readMv[0]);
		ASSERT_EQ( mv[1], readMv[1]);
		
	}
	
	TEST(GameState, KeysValuesGetSet)
	{
		GameStateFixture g;
		HashKey k(473829258338);
		HashKey pk(947828127461);
		HashKey mk(4832976592067);
		g.setKeys( k, pk, mk );
		
		ASSERT_EQ( k, g.getKey() );
		ASSERT_EQ( pk, g.getPawnKey() );
		ASSERT_EQ( mk, g.getMaterialKey() );
	
	}
	
	TEST(GameState, TurnGetSet)
	{
		GameStateFixture g;
		
		g.setTurn( baseTypes::whiteTurn );
		ASSERT_EQ( baseTypes::whiteTurn, g.getTurn() );
		
		g.setTurn( baseTypes::blackTurn );
		ASSERT_EQ( baseTypes::blackTurn, g.getTurn() );
	
	}
	
	TEST(GameState, CastleRightsGetSet)
	{
		GameStateFixture g;
		
		for( int i = 0; i < 16; i++ )
		{
			g.setCastleRights( (baseTypes::eCastle)i );
			ASSERT_EQ( (baseTypes::eCastle)i, g.getCastleRights() );
		}
	}
	
	TEST(GameState, resetAllCastleRights)
	{
		GameStateFixture g;
		
		g.setCastleRights( (baseTypes::eCastle)12 );
		ASSERT_EQ( (baseTypes::eCastle)12, g.getCastleRights() );
		
		g.resetAllCastleRights();
		
		ASSERT_EQ( (baseTypes::eCastle)0, g.getCastleRights() );
			
	}
	
	TEST(GameState, setCastleRight)
	{
		GameStateFixture g;
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::wCastleOO );
		ASSERT_EQ( baseTypes::wCastleOO, g.getCastleRights() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::wCastleOOO );
		ASSERT_EQ( baseTypes::wCastleOOO, g.getCastleRights() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::bCastleOO );
		ASSERT_EQ( baseTypes::bCastleOO, g.getCastleRights() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::bCastleOOO );
		ASSERT_EQ( baseTypes::bCastleOOO, g.getCastleRights() );

		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::bCastleOOO );
		g.setCastleRight( baseTypes::wCastleOO );
		ASSERT_EQ( baseTypes::wCastleOO | baseTypes::bCastleOOO, g.getCastleRights() );

			
	}
	
	
	TEST(GameState, EpSquareSetGet)
	{
		GameStateFixture st;
		st.setEpSquare(baseTypes::tSquare::E3);
		ASSERT_EQ( baseTypes::tSquare::E3, st.getEpSquare() );
		
		st.setEpSquare(baseTypes::tSquare::C6);
		ASSERT_EQ( baseTypes::tSquare::C6, st.getEpSquare() );
		
		st.setEpSquare(baseTypes::tSquare::H3);
		ASSERT_EQ( baseTypes::tSquare::H3, st.getEpSquare() );
		
		st.setEpSquare(baseTypes::tSquare::A6);
		ASSERT_EQ( baseTypes::tSquare::A6, st.getEpSquare() );
	}
	
	// todo moved to position, rewrite this test if possibile
	/*TEST(GameState, getCastleRightsString)
	{
		GameStateFixture g;
		
		g.resetAllCastleRights();
		ASSERT_STREQ( "-", g.getCastleRightsString().c_str() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::wCastleOO );
		ASSERT_STREQ( "K", g.getCastleRightsString().c_str() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::wCastleOOO );
		ASSERT_STREQ( "Q", g.getCastleRightsString().c_str() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::bCastleOO );
		ASSERT_STREQ( "k", g.getCastleRightsString().c_str() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::bCastleOOO );
		ASSERT_STREQ( "q", g.getCastleRightsString().c_str() );

		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::bCastleOOO );
		g.setCastleRight( baseTypes::wCastleOO );
		ASSERT_STREQ( "Kq", g.getCastleRightsString().c_str() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::wCastleOOO );
		g.setCastleRight( baseTypes::wCastleOO );
		ASSERT_STREQ( "KQ", g.getCastleRightsString().c_str() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::bCastleOOO );
		g.setCastleRight( baseTypes::bCastleOO );
		ASSERT_STREQ( "kq", g.getCastleRightsString().c_str() );
		
		g.resetAllCastleRights();
		g.setCastleRight( baseTypes::wCastleOOO );
		g.setCastleRight( baseTypes::wCastleOO );
		g.setCastleRight( baseTypes::bCastleOOO );
		g.setCastleRight( baseTypes::bCastleOO );
		ASSERT_STREQ( "KQkq", g.getCastleRightsString().c_str() );

			
	}*/
	
	TEST(GameState, getEpSquareString)
	{
		GameStateFixture st;
		st.setEpSquare(baseTypes::tSquare::E3);
		ASSERT_STREQ( "e3", st.getEpSquareString().c_str() );
		
		st.setEpSquare(baseTypes::tSquare::C6);
		ASSERT_STREQ( "c6", st.getEpSquareString().c_str() );
		
		st.setEpSquare(baseTypes::tSquare::H3);
		ASSERT_STREQ( "h3", st.getEpSquareString().c_str() );
		
		st.setEpSquare(baseTypes::tSquare::A6);
		ASSERT_STREQ( "a6", st.getEpSquareString().c_str() );
		
		st.setEpSquare(baseTypes::tSquare::squareNone);
		ASSERT_STREQ( "-", st.getEpSquareString().c_str() );
	}
	
	TEST(GameState, FiftyMoveCntSetGet)
	{
		GameStateFixture st;
		
		for( unsigned int i = 0 ; i < 300; ++i )
		{
			st.setFiftyMoveCnt( i );
			ASSERT_EQ( i, st.getFiftyMoveCnt() );
		}
		
	}
	
	TEST(GameState, PliesCntSetGet)
	{
		GameStateFixture st;
		
		for( unsigned int i = 0 ; i < 2000; ++i )
		{
			st.setPliesCnt( i );
			ASSERT_EQ( i, st.getPliesCnt() );
		}
		
	}
	
	TEST(GameState, getFullMoveCounter)
	{
		GameStateFixture st;
		
		st.setTurn( baseTypes::whiteTurn );
		st.setPliesCnt( 0 );

		ASSERT_EQ( 1, st.getFullMoveCounter() );
		
		st.setTurn( baseTypes::blackTurn );
		st.setPliesCnt( 1 );
		ASSERT_EQ( 1, st.getFullMoveCounter() );
		
		
		st.setTurn( baseTypes::whiteTurn );
		st.setPliesCnt( 100 );
		ASSERT_EQ( 51, st.getFullMoveCounter() );
		
		st.setTurn( baseTypes::blackTurn );
		st.setPliesCnt( 101 );
		ASSERT_EQ( 51, st.getFullMoveCounter() );
		
	}
	
	TEST(GameState, CurrentMoveSetGet)
	{
		GameStateFixture st;
		
		for( int i = 0; i < 65536; ++i )
		{
			st.setCurrentMove( Move(0) );
			ASSERT_EQ( Move(0), st.getCurrentMove() );
		}
	}
	
	TEST(GameState, CapturedPieceSetGet)
	{
		GameStateFixture st;
		
		for( auto idx: baseTypes::bitboardIndexRange() )
		{
			st.setCapturedPiece( idx );
			ASSERT_EQ( idx, st.getCapturedPiece() );
		}
	}
	
	TEST(GameState, resetCapturedPiece)
	{
		GameStateFixture st;
		
		for( auto idx: baseTypes::bitboardIndexRange() )
		{
			st.setCapturedPiece( idx );
			st.resetCapturedPiece();
			ASSERT_EQ( baseTypes::empty, st.getCapturedPiece() );
		}
	}
	
	TEST(GameState, checkingSquareSetGet)
	{
		GameStateFixture st;
		
		st.setCheckingSquare( baseTypes::whiteQueens, baseTypes::BitMap(34535) );
		st.setCheckingSquare( baseTypes::blackQueens, baseTypes::BitMap(5347274) );
		st.setCheckingSquare( baseTypes::whitePawns, baseTypes::BitMap(23) );
		st.setCheckingSquare( baseTypes::blackRooks, baseTypes::BitMap(6549598769) );
		
		ASSERT_EQ( baseTypes::BitMap(34535), st.getCheckingSquare(baseTypes::whiteQueens) );
		ASSERT_EQ( baseTypes::BitMap(5347274), st.getCheckingSquare(baseTypes::blackQueens) );
		ASSERT_EQ( baseTypes::BitMap(23), st.getCheckingSquare(baseTypes::whitePawns) );
		ASSERT_EQ( baseTypes::BitMap(6549598769), st.getCheckingSquare(baseTypes::blackRooks) );
		
	}
	
	TEST(GameState, DiscoveryCheckersSetGet)
	{
		GameStateFixture st;
		
		st.setDiscoveryChechers( baseTypes::BitMap(34535) );
		ASSERT_EQ( baseTypes::BitMap(34535), st.getDiscoveryCheckers() );
		st.setDiscoveryChechers( baseTypes::BitMap(5347274) );
		ASSERT_EQ( baseTypes::BitMap(5347274), st.getDiscoveryCheckers() );
		st.setDiscoveryChechers( baseTypes::BitMap(23) );
		ASSERT_EQ( baseTypes::BitMap(23), st.getDiscoveryCheckers() );
		st.setDiscoveryChechers( baseTypes::BitMap(6549598769) );
		ASSERT_EQ( baseTypes::BitMap(6549598769), st.getDiscoveryCheckers() );
		
	}
	
	TEST(GameState, PinnedSetGet)
	{
		GameStateFixture st;
		
		st.setPinned( baseTypes::BitMap(34535) );
		ASSERT_EQ( baseTypes::BitMap(34535), st.getPinned() );
		st.setPinned( baseTypes::BitMap(5347274) );
		ASSERT_EQ( baseTypes::BitMap(5347274), st.getPinned() );
		st.setPinned( baseTypes::BitMap(23) );
		ASSERT_EQ( baseTypes::BitMap(23), st.getPinned() );
		st.setPinned( baseTypes::BitMap(6549598769) );
		ASSERT_EQ( baseTypes::BitMap(6549598769), st.getPinned() );
		
	}
	
	TEST(GameState, CheckersSetGet)
	{
		GameStateFixture st;
		
		st.setCheckers( baseTypes::BitMap(34535) );
		ASSERT_EQ( baseTypes::BitMap(34535), st.getCheckers() );
		st.setCheckers( baseTypes::BitMap(5347274) );
		ASSERT_EQ( baseTypes::BitMap(5347274), st.getCheckers() );
		st.setCheckers( baseTypes::BitMap(23) );
		ASSERT_EQ( baseTypes::BitMap(23), st.getCheckers() );
		st.setCheckers( baseTypes::BitMap(6549598769) );
		ASSERT_EQ( baseTypes::BitMap(6549598769), st.getCheckers() );
		
	}
	
	TEST(GameState, BitmapIndipendence)
	{
		GameStateFixture st;
		
		st.setDiscoveryChechers( baseTypes::BitMap(34535) );
		st.setPinned( baseTypes::BitMap(23) );
		st.setCheckers( baseTypes::BitMap(6549598769) );
		
		ASSERT_EQ( baseTypes::BitMap(23), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(34535), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(6549598769), st.getCheckers() );
		
	}
	
	void setCommonData( GameStateFixture& st )
	{

		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };

		
		st.setKeys( HashKey(1454), HashKey(54832), HashKey(390864398026) );
		st.setMaterialValues( mv, npmv );
		st.setTurn( baseTypes::whiteTurn);
		st.setCastleRights( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO) );
		
		st.setFiftyMoveCnt( 32 );
		st.setPliesCnt( 135 );
		st.resetCountersNullMove();
		st.setEpSquare( baseTypes::squareNone );
		st.setCurrentMove( Move( baseTypes::E2, baseTypes::E4 ) );
		st.setCapturedPiece( baseTypes::blackBishops );
		
		st.setCheckingSquare( baseTypes::whiteKing, baseTypes::BitMap(1) );
		st.setCheckingSquare( baseTypes::whiteQueens, baseTypes::BitMap(2) );
		st.setCheckingSquare( baseTypes::whiteRooks, baseTypes::BitMap(3) );
		st.setCheckingSquare( baseTypes::whiteBishops, baseTypes::BitMap(4) );
		st.setCheckingSquare( baseTypes::whiteKnights, baseTypes::BitMap(5) );
		st.setCheckingSquare( baseTypes::whitePawns, baseTypes::BitMap(6) );
		st.setCheckingSquare( baseTypes::blackKing, baseTypes::BitMap(7) );
		st.setCheckingSquare( baseTypes::blackQueens, baseTypes::BitMap(8) );
		st.setCheckingSquare( baseTypes::blackRooks, baseTypes::BitMap(9) );
		st.setCheckingSquare( baseTypes::blackBishops, baseTypes::BitMap(10) );
		st.setCheckingSquare( baseTypes::blackKnights, baseTypes::BitMap(11) );
		st.setCheckingSquare( baseTypes::blackPawns, baseTypes::BitMap(12) );
		
		st.setDiscoveryChechers( baseTypes::BitMap(435) );
		st.setPinned( baseTypes::BitMap(1435) );
		st.setCheckers( baseTypes::BitMap(732) );
	}
	
	TEST(GameState, StateFullSet)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */

		
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( HashKey(1454), st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, changeTurn)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */
		HashKey newKey = st.getKey();
		newKey.changeSide();
	
		st.changeTurn();
		
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( newKey, st.getKey() );
		ASSERT_NE( HashKey(1454), st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::blackTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, countersUpdate)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */
		st.incrementCounters();
		
		ASSERT_EQ( 33, st.getFiftyMoveCnt() );
		ASSERT_EQ( 1, st.getPliesFromNullCnt() );
		ASSERT_EQ( 136, st.getPliesCnt() );
		
		st.incrementCounters();
		
		ASSERT_EQ( 34, st.getFiftyMoveCnt() );
		ASSERT_EQ( 2, st.getPliesFromNullCnt() );
		ASSERT_EQ( 137, st.getPliesCnt() );
		
		st.resetCountersNullMove();
		
		ASSERT_EQ( 34, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 137, st.getPliesCnt() );
		
		st.incrementCounters();
		st.incrementCounters();
		st.incrementCounters();
		
		ASSERT_EQ( 37, st.getFiftyMoveCnt() );
		ASSERT_EQ( 3, st.getPliesFromNullCnt() );
		ASSERT_EQ( 140, st.getPliesCnt() );
		
		st.incrementCounters();
		st.incrementCountersNullMove();
		st.incrementCounters();
		
		ASSERT_EQ( 40, st.getFiftyMoveCnt() );
		ASSERT_EQ( 1, st.getPliesFromNullCnt() );
		ASSERT_EQ( 143, st.getPliesCnt() );
		
		st.resetFiftyMoveCnt();
		st.incrementCounters();
		st.incrementCounters();
		st.incrementCounters();
		
		ASSERT_EQ( 3, st.getFiftyMoveCnt() );
		ASSERT_EQ( 4, st.getPliesFromNullCnt() );
		ASSERT_EQ( 146, st.getPliesCnt() );
		
		
		
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( HashKey(1454), st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 3, st.getFiftyMoveCnt() );
		ASSERT_EQ( 4, st.getPliesFromNullCnt() );
		ASSERT_EQ( 146, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, EpSquare)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */
		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		
		ASSERT_FALSE( st.hasEpSquareSet() );
		
		st.clearEpSquare();
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		ASSERT_FALSE( st.hasEpSquareSet() );
		
		st.addEpSquare( baseTypes::E3 );
		ASSERT_NE( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		ASSERT_EQ( baseTypes::E3, st.getEpSquare() );
		ASSERT_TRUE( st.hasEpSquareSet() );
		
		st.clearEpSquare(  );
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		ASSERT_FALSE( st.hasEpSquareSet() );
		
		
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( HashKey(1454), st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	
	TEST(GameState, clearCastleRight)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */
		//st.setCastleRights( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO) );
		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		baseTypes::eCastle cr = st.getCastleRights();
		ASSERT_FALSE( st.hasCastleRight( baseTypes::wCastleOO) );
		ASSERT_TRUE( st.hasCastleRight( baseTypes::wCastleOOO) );
		ASSERT_TRUE( st.hasCastleRight( baseTypes::bCastleOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::bCastleOOO) );
		
		st.clearCastleRight( baseTypes::wCastleOO );
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		ASSERT_EQ( cr, st.getCastleRights() );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::wCastleOO) );
		ASSERT_TRUE( st.hasCastleRight( baseTypes::wCastleOOO) );
		ASSERT_TRUE( st.hasCastleRight( baseTypes::bCastleOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::bCastleOOO) );
		
		st.clearCastleRight( baseTypes::wCastleOOO );
		ASSERT_NE( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		ASSERT_NE( cr, st.getCastleRights() );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::wCastleOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::wCastleOOO) );
		ASSERT_TRUE( st.hasCastleRight( baseTypes::bCastleOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::bCastleOOO) );
		
		k = st.getKey();
		pk = st.getPawnKey();
		mk = st.getMaterialKey();
		cr = st.getCastleRights();
		
		st.clearCastleRight( baseTypes::bCastleOO );
		ASSERT_NE( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		ASSERT_NE( cr, st.getCastleRights() );
		
		ASSERT_FALSE( st.hasCastleRight( baseTypes::wCastleOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::wCastleOOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::bCastleOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::bCastleOOO) );
		
		k = st.getKey();
		pk = st.getPawnKey();
		mk = st.getMaterialKey();
		cr = st.getCastleRights();
		
		st.clearCastleRight( baseTypes::bCastleOOO );
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		ASSERT_EQ( cr, st.getCastleRights() );
		
		ASSERT_FALSE( st.hasCastleRight( baseTypes::wCastleOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::wCastleOOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::bCastleOO) );
		ASSERT_FALSE( st.hasCastleRight( baseTypes::bCastleOOO) );
		
		
		
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(0), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
	}
	
	TEST(GameState, keyMovePiece)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */

		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		
		st.keyMovePiece( baseTypes::whiteRooks, baseTypes::E3, baseTypes::E7);
		st.keyMovePiece( baseTypes::whiteRooks, baseTypes::E7, baseTypes::D3);
		
		st.keyMovePiece( baseTypes::blackBishops, baseTypes::F1, baseTypes::G4);
		
		
		ASSERT_NE( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		
		st.keyMovePiece( baseTypes::whiteRooks, baseTypes::D3, baseTypes::E3);
		st.keyMovePiece( baseTypes::blackBishops, baseTypes::G4, baseTypes::F1);
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( HashKey(1454), st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, keyRemovePiece)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */

		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		
		st.keyRemovePiece( baseTypes::whiteRooks, baseTypes::E3);
		
		ASSERT_NE( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		
	
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_NE( k, st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, keyPromotePiece)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */

		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		
		st.keyPromotePiece( baseTypes::whitePawns, baseTypes::whiteQueens, baseTypes::E8);
		
		ASSERT_NE( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		
	
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_NE( k, st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, pawnKeyMovePiece)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */

		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		
		st.pawnKeyMovePiece( baseTypes::whitePawns, baseTypes::E3, baseTypes::E7);
		st.pawnKeyMovePiece( baseTypes::whitePawns, baseTypes::E7, baseTypes::D3);
		
		st.pawnKeyMovePiece( baseTypes::blackPawns, baseTypes::F1, baseTypes::G4);
		
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_NE( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		
		st.pawnKeyMovePiece( baseTypes::whitePawns, baseTypes::D3, baseTypes::E3);
		st.pawnKeyMovePiece( baseTypes::blackPawns, baseTypes::G4, baseTypes::F1);
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( HashKey(1454), st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, pawnKeyRemovePiece)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */

		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		
		st.pawnKeyRemovePiece( baseTypes::whiteRooks, baseTypes::E3);
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_NE( pk, st.getPawnKey() );
		ASSERT_EQ( mk, st.getMaterialKey() );
		
	
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_NE( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, materialKeyRemovePiece)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */

		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		
		st.materialKeyRemovePiece( baseTypes::whiteRooks, 1);
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_NE( mk, st.getMaterialKey() );
		
	
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_NE( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	TEST(GameState, materialKeyPromotePiece)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */

		HashKey k = st.getKey();
		HashKey pk = st.getPawnKey();
		HashKey mk = st.getMaterialKey();
		
		st.materialKeyPromovePiece( baseTypes::whitePawns, 3, baseTypes::whiteQueens, 1 );
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( pk, st.getPawnKey() );
		ASSERT_NE( mk, st.getMaterialKey() );
		
	
		// final check
		
		const simdScore mv = { 127, 4532, 0, 0};
		const simdScore npmv = { -3427, 56432, 0, 0 };
		
		ASSERT_EQ( k, st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_NE( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( mv[0], st.getMaterialValue()[0] );
		ASSERT_EQ( mv[1], st.getMaterialValue()[1] );
		ASSERT_EQ( npmv[0], st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( npmv[1], st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	
	TEST(GameState, materialValuesUpdate)
	{
		GameStateFixture st;
		
		/* set common data */
		setCommonData( st );
		
		/* function to be tested */
		
		st.materialMovePiece( simdScore{100,80,0,0}, simdScore{60,40,0,0} ) ;
		
		ASSERT_EQ( 87, st.getMaterialValue()[0] );
		ASSERT_EQ( 4492, st.getMaterialValue()[1] );
		ASSERT_EQ( -3427, st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( 56432, st.getNonPawnMaterialValue()[1] );
		
		
		st.materialCapturePiece( simdScore{1000,800,0,0}, simdScore{200,400,0,0} );
		
		ASSERT_EQ( -913, st.getMaterialValue()[0] );
		ASSERT_EQ( 3692, st.getMaterialValue()[1] );
		ASSERT_EQ( -3627, st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( 56032, st.getNonPawnMaterialValue()[1] );
		
		st.materialPromotePiece( simdScore{10000,8000,0,0}, simdScore{30000,35000,0,0}, simdScore{12000,9000,0,0} );
		
		ASSERT_EQ( 19087, st.getMaterialValue()[0] );
		ASSERT_EQ( 30692, st.getMaterialValue()[1] );
		ASSERT_EQ( 8373, st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( 65032, st.getNonPawnMaterialValue()[1] );
		

		
		// final check
		
		ASSERT_EQ( HashKey(1454), st.getKey() );
		ASSERT_EQ( HashKey(54832), st.getPawnKey() );
		ASSERT_EQ( HashKey(390864398026), st.getMaterialKey() );
		
		ASSERT_EQ( 19087, st.getMaterialValue()[0] );
		ASSERT_EQ( 30692, st.getMaterialValue()[1] );
		ASSERT_EQ( 8373, st.getNonPawnMaterialValue()[0] );
		ASSERT_EQ( 65032, st.getNonPawnMaterialValue()[1] );
		
		ASSERT_EQ( baseTypes::whiteTurn, st.getTurn() );
		ASSERT_EQ( (baseTypes::eCastle)(baseTypes::wCastleOOO | baseTypes::bCastleOO), st.getCastleRights() );
		ASSERT_EQ( baseTypes::squareNone, st.getEpSquare() );
		
		ASSERT_EQ( 32, st.getFiftyMoveCnt() );
		ASSERT_EQ( 0, st.getPliesFromNullCnt() );
		ASSERT_EQ( 135, st.getPliesCnt() );
		
		ASSERT_EQ( Move( baseTypes::E2, baseTypes::E4 ), st.getCurrentMove() );
		ASSERT_EQ( baseTypes::blackBishops, st.getCapturedPiece() );
		
		ASSERT_EQ( baseTypes::BitMap(1), st.getCheckingSquare( baseTypes::whiteKing ) );
		ASSERT_EQ( baseTypes::BitMap(2), st.getCheckingSquare( baseTypes::whiteQueens ) );
		ASSERT_EQ( baseTypes::BitMap(3), st.getCheckingSquare( baseTypes::whiteRooks ) );
		ASSERT_EQ( baseTypes::BitMap(4), st.getCheckingSquare( baseTypes::whiteBishops ) );
		ASSERT_EQ( baseTypes::BitMap(5), st.getCheckingSquare( baseTypes::whiteKnights ) );
		ASSERT_EQ( baseTypes::BitMap(6), st.getCheckingSquare( baseTypes::whitePawns ) );
		ASSERT_EQ( baseTypes::BitMap(7), st.getCheckingSquare( baseTypes::blackKing ) );
		ASSERT_EQ( baseTypes::BitMap(8), st.getCheckingSquare( baseTypes::blackQueens ) );
		ASSERT_EQ( baseTypes::BitMap(9), st.getCheckingSquare( baseTypes::blackRooks ) );
		ASSERT_EQ( baseTypes::BitMap(10), st.getCheckingSquare( baseTypes::blackBishops ) );
		ASSERT_EQ( baseTypes::BitMap(11), st.getCheckingSquare( baseTypes::blackKnights ) );
		ASSERT_EQ( baseTypes::BitMap(12), st.getCheckingSquare( baseTypes::blackPawns ) );
		
		ASSERT_EQ( baseTypes::BitMap(435), st.getDiscoveryCheckers() );
		ASSERT_EQ( baseTypes::BitMap(1435), st.getPinned() );
		ASSERT_EQ( baseTypes::BitMap(732), st.getCheckers() );
		
		

	}
	
	

}
