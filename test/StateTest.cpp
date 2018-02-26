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
	
	TEST(GameState, NonPawnMaterialValue)
	{
		GameStateFixture g;
		simdScore mv = { 450, 245, 0, 0 };
		simdScore nmv = { 38350, -392, 0, 0 };
		g.setMaterialValues( mv, nmv );
		simdScore read= g.getNonPawnMaterialValue();
		ASSERT_EQ( nmv[0], read[0]);
		ASSERT_EQ( nmv[1], read[1]);
	}
	
	
	TEST(GameState, setEpSquare)
	{
		GameStateFixture st;
		st.setEpSquare(baseTypes::tSquare::E3);
		ASSERT_EQ( baseTypes::tSquare::E3, st.getEpSquare() );
	}
	
}
