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




using namespace libChess;

namespace {
	
	TEST(Position, constructor)
	{
		Position p;
		Position p2(p);
		ASSERT_EQ( 1, p2.getStateSize() );
	}
	
	TEST(Position, test)
	{
		Position p;
		p.setupFromFen();
		Move m1(baseTypes::tSquare::E2, baseTypes::tSquare::E4);
		Move m2(baseTypes::tSquare::D7, baseTypes::tSquare::D5);
		Move m3(baseTypes::tSquare::E4, baseTypes::tSquare::D5);
		p.doMove(m1);
		ASSERT_STREQ( "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1", p.getFen().c_str() );
		p.doMove(m2);
		ASSERT_STREQ( "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", p.getFen().c_str() );
		p.doMove(m3);
		ASSERT_STREQ( "rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2", p.getFen().c_str() );
	}
	
	
}
