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
		
		void setKeys( const HashKey& key, const HashKey& pawnKey, const HashKey& materialKey ){GameState::setKeys( key, pawnKey, materialKey );}
		
		void setMaterialValues( const simdScore MaterialValue, const simdScore nonPawnMaterialValue ){GameState::setMaterialValues( MaterialValue, nonPawnMaterialValue );}
		
		void setTurn( const baseTypes::eTurn turn){GameState::setTurn( turn );}
		
		void setCastleRights( const baseTypes::eCastle cr ){GameState::setCastleRights( cr );}
		void setCastleRight( const baseTypes::eCastle cr ){GameState::setCastleRight( cr );}
		void resetAllCastleRights(){GameState::resetAllCastleRights();}
		
		void setFiftyMoveCnt( const unsigned int fmc ){GameState::setFiftyMoveCnt( fmc );}
		void setPliesCnt( const unsigned int cnt ){GameState::setPliesCnt( cnt );}
		
		void setCurrentMove( const Move& m ){GameState::setCurrentMove( m );}
		void setEpSquare( const baseTypes::tSquare sq ){ GameState::setEpSquare(sq);}
		
		void setCapturedPiece( const baseTypes::bitboardIndex idx ){GameState::setCapturedPiece( idx );}
		void resetCapturedPiece(){GameState::resetCapturedPiece();}
		
		void setCheckingSquare( const baseTypes::bitboardIndex idx, const baseTypes::BitMap& b ){GameState::setCheckingSquare( idx, b );}
		void setHiddenChechers( const baseTypes::BitMap& b){GameState::setHiddenChechers( b );}
		void setPinned( const baseTypes::BitMap& b){GameState::setPinned( b );}
		void setCheckers( const baseTypes::BitMap& b ){GameState::setCheckers( b );}
			
		/*****************************************************************
		*	update method, if necessary update keys
		******************************************************************/
		
		void changeTurn(){GameState::changeTurn();}
		
		void incrementCounters(){GameState::incrementCounters();}
		void incrementCountersNullMove(){GameState::incrementCountersNullMove();}
		void resetCountersNullMove(){GameState::resetCountersNullMove();}
		void resetFiftyMoveCnt(){GameState::resetFiftyMoveCnt();}
		
		void clearEpSquare(){GameState::clearEpSquare();}
		void addEpSquare( const baseTypes::tSquare sq ){GameState::addEpSquare( sq );}
		
		void clearCastleRight( const int cr ){GameState::clearCastleRight( cr );}
		
		void keyMovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare fromSq, const baseTypes::tSquare toSq){GameState::keyMovePiece( p, fromSq, toSq);}
		void keyRemovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare sq){GameState::keyRemovePiece( p, sq );}
		void keyPromotePiece(const baseTypes::bitboardIndex piece, const baseTypes::bitboardIndex promotedPiece, const baseTypes::tSquare sq){GameState::keyPromotePiece( piece, promotedPiece, sq);}
		
		void pawnKeyMovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare fromSq, const baseTypes::tSquare toSq){GameState::pawnKeyMovePiece( p, fromSq, toSq);}
		void pawnKeyRemovePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare sq){GameState::pawnKeyRemovePiece( p , sq);}
		
		void materialKeyRemovePiece(const baseTypes::bitboardIndex p, unsigned int count){GameState::materialKeyRemovePiece( p , count );}
		void materialKeyPromovePiece(const baseTypes::bitboardIndex piece, const unsigned int count, const baseTypes::bitboardIndex promotedPiece, const unsigned int promotedCount){GameState::materialKeyPromovePiece( piece , count, promotedPiece, promotedCount);}
		
		void MaterialMovePiece( const simdScore from, const simdScore to ){ GameState::MaterialMovePiece(from,to);}
		void MaterialCapturePiece( const simdScore material, const simdScore nonPawnMaterial ){GameState::MaterialCapturePiece(material,nonPawnMaterial);}
		void MaterialPromotePiece( const simdScore material, const simdScore protmotedMaterial , const simdScore nonPawnPromotedMaterial ){GameState::MaterialPromotePiece(material,protmotedMaterial,nonPawnPromotedMaterial);}
		
		/*****************************************************************
		*	other methods
		******************************************************************/
		bool hasCastleRight( const baseTypes::eCastle cr) const{ return GameState::hasCastleRight(cr); }
		bool hasEpSquareSet(void)const{ return GameState::hasEpSquareSet(); }


	
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
	
	TEST(GameState, getCastleRightsString)
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

			
	}
	
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
	
	
	
	
	
	
	
}
