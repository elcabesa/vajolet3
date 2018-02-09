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
#include "./../Position.h"






namespace libChess
{
	// Google-test:
	class GameStateFixture: public GameState
	{
		public:

		void setEpSquare( const tSquare sq){ GameState::setEpSquare(sq);}

	
	};
}

using namespace libChess;

namespace {
	
	
	
	TEST(GameState, setEpSquare)
	{
		GameStateFixture st;
		st.setEpSquare(tSquare::E3);
		ASSERT_EQ( tSquare::E3, st.getEpSquare() );
	}
	
}
