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
#include "./../bitboardIndex.h"

using namespace libChess;

namespace {
		
	TEST(bitboardIndex,assign)
	{
		bitboardIndex b;
		b = bitboardIndex::whiteRooks;
		
		ASSERT_EQ( bitboardIndex::whiteRooks, b );
		
		bitboardIndex g = b;
		ASSERT_EQ( bitboardIndex::whiteRooks, g );
		g = bitboardIndex::blackPieces;
		ASSERT_EQ( bitboardIndex::blackPieces, g );
	}
	
	TEST(bitboardIndex, Increment)
	{
		bitboardIndex f = bitboardIndex::whiteRooks;
		ASSERT_EQ( bitboardIndex::whiteRooks, f++ );
		ASSERT_EQ( bitboardIndex::whiteBishops, f );
		ASSERT_EQ( bitboardIndex::whiteKnights, ++f );
		ASSERT_EQ( bitboardIndex::whiteKnights, f );
		
	}
	
	TEST(bitboardIndex, Decrement)
	{
		bitboardIndex f = bitboardIndex::blackPawns;
		ASSERT_EQ( bitboardIndex::blackPawns, f-- );
		ASSERT_EQ( bitboardIndex::blackKnights, f );
		ASSERT_EQ( bitboardIndex::blackBishops, --f );
		ASSERT_EQ( bitboardIndex::blackBishops, f );
		
	}
	
	TEST(bitboardIndex, Sum)
	{
		bitboardIndex f = bitboardIndex::whitePieces;
		ASSERT_EQ( bitboardIndex::blackKing, f + 2 );
	}
	
	TEST(bitboardIndex, Sub)
	{
		bitboardIndex f = bitboardIndex::whiteRooks;
		ASSERT_EQ( bitboardIndex::occupiedSquares, f - 3 );
	}
	
	TEST(bitboardIndex, Sum2)
	{
		bitboardIndex f = bitboardIndex::whitePieces;
		ASSERT_EQ( bitboardIndex::blackKing, f += 2 );
	}
	
	TEST(bitboardIndex, Sub2)
	{
		bitboardIndex f = bitboardIndex::whiteRooks;
		ASSERT_EQ( bitboardIndex::occupiedSquares, f -= 3 );
	}
	
	TEST(bitboardIndex, iterate)
	{
		unsigned int i = 0;

		for(auto t: bitboardIndexRange())
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			if(i>1000) break;
		}
		ASSERT_EQ(i, 16u);
	}
	
	TEST(bitboardIndex, iterateRange0)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::blackKing);

		for(auto t: bitboardIndexRange(bitboardIndex::blackKing,bitboardIndex::blackPawns))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 6u);
	}

	TEST(bitboardIndex, iterateRange1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::Queens);

		for(auto t: bitboardIndexRange(bitboardIndex::Queens,bitboardIndex::Rooks))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 2u);
	}

	TEST(bitboardIndex, iterateRange2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::Rooks);

		for(auto t: bitboardIndexRange(bitboardIndex::Rooks,bitboardIndex::Rooks))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 1u);
	}

	TEST(bitboardIndex, iterateRangeNeg1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::Rooks);

		for(auto t: bitboardIndexRange(bitboardIndex::Rooks,bitboardIndex::King))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}

	TEST(bitboardIndex, iterateRangeNeg2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::blackPawns);

		for(auto t: bitboardIndexRange(bitboardIndex::blackPawns,bitboardIndex::whiteKing))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}
}