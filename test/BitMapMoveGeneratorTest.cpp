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
#include "./../BitMapMoveGenerator.h"
using namespace libChess;
using namespace libChess::baseTypes;

namespace {
		
	TEST(BitMapMoveGenerator,getKingMoves)
	{
		BitMap k = BitMapMoveGenerator::getKingMoves( tSquare::E4 );
		
		BitMap ref(0);
		ref += E5;
		ref += F5;
		ref += F4;
		ref += F3;
		ref += E3;
		ref += D3;
		ref += D4;
		ref += D5;
		
		ASSERT_EQ( ref, k );
		
		k = BitMapMoveGenerator::getKingMoves( tSquare::A1 );
		
		BitMap ref1(0);
		ref1 += A2;
		ref1 += B2;
		ref1 += B1;

		
		ASSERT_EQ( ref1, k );
		
		
	}
}