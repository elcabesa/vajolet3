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
#include "./../BitMap.h"

using namespace libChess;


namespace {
	
	TEST(BitMap, constructor1)
	{
		BitMap x = BitMap(5);
		ASSERT_TRUE( x.isSquareSet(baseTypes::tSquare::A1));
		ASSERT_FALSE( x.isSquareSet(baseTypes::tSquare::B1));
		ASSERT_TRUE( x.isSquareSet(baseTypes::tSquare::C1));
		ASSERT_FALSE( x.isSquareSet(baseTypes::tSquare::E5));
	}
	
	TEST(BitMap, constructor2)
	{
		BitMap x = BitMap(7);
		ASSERT_TRUE( x.isSquareSet(baseTypes::tSquare::A1));
		ASSERT_TRUE( x.isSquareSet(baseTypes::tSquare::B1));
		ASSERT_TRUE( x.isSquareSet(baseTypes::tSquare::C1));
		ASSERT_FALSE( x.isSquareSet(baseTypes::tSquare::E5));
	}
	
	TEST(BitMap, clear)
	{
		BitMap x = BitMap(7);
		
		ASSERT_NE( 0, x.bitCnt() );
		x.clear();
		ASSERT_EQ( 0, x.bitCnt() );
		ASSERT_TRUE( x.isEmpty() );
	}
	

	TEST(BitMap, bitCnt)
	{
		ASSERT_EQ( BitMap(0).bitCnt(), 0);
		ASSERT_EQ( BitMap(1).bitCnt(), 1);
		ASSERT_EQ( BitMap(0x803000100C803008ull).bitCnt(), 10);
		ASSERT_EQ( BitMap(3458769736543240192ull).bitCnt(), 8);
		ASSERT_EQ( BitMap(0xFFFFFFFFFFFFFFFFull).bitCnt(), 64);

	}

	TEST(BitMap, FirstOne)
	{
		//ASSERT_EQ( BitMap(0).firstOne(), baseTypes::tSquare::A1); // sure?? machine dependant??
		ASSERT_EQ( BitMap(1).firstOne(), baseTypes::tSquare::A1);
		ASSERT_EQ( BitMap(0x803000100C803008ull).firstOne(), baseTypes::tSquare::D1);
		ASSERT_EQ( BitMap(3458769736543240192ull).firstOne(), baseTypes::tSquare::D3);
		ASSERT_EQ( BitMap(0xFFFFFFFFFFFFFFFFull).firstOne(), baseTypes::tSquare::A1);
	}

	TEST(BitMap, moreThanOneBit)
	{
		ASSERT_FALSE( BitMap(0).moreThanOneBit());
		ASSERT_FALSE( BitMap(1).moreThanOneBit());
		ASSERT_TRUE( BitMap(3).moreThanOneBit());
		ASSERT_TRUE( BitMap(0x803000100C803008ull).moreThanOneBit());
		ASSERT_TRUE( BitMap(3458769736543240192ull).moreThanOneBit());
		ASSERT_TRUE( BitMap(0xFFFFFFFFFFFFFFFFull).moreThanOneBit());
		ASSERT_TRUE( BitMap(0x0000001000010000ull).moreThanOneBit());
		ASSERT_FALSE( BitMap(0x0000004000000000ull).moreThanOneBit());
	}

	TEST(BitMap, getBitmapFromSquare)
	{
		ASSERT_EQ( BitMap::getBitmapFromSquare( baseTypes::tSquare::A3 ), BitMap(0x10000ull));
		ASSERT_EQ( BitMap::getBitmapFromSquare( baseTypes::tSquare::H8 ), BitMap(0x8000000000000000ull));
		ASSERT_EQ( BitMap::getBitmapFromSquare( baseTypes::tSquare::A1 ), BitMap(0x0000000000000001ull));

	}

	TEST(BitMap, getBitmapFromSquare2)
	{
		ASSERT_EQ( BitMap::getBitmapFromSquare( baseTypes::tFile::A, baseTypes::tRank::three ), BitMap(0x10000ull));
		ASSERT_EQ( BitMap::getBitmapFromSquare( baseTypes::tFile::H, baseTypes::tRank::eight ), BitMap(0x8000000000000000ull));
		ASSERT_EQ( BitMap::getBitmapFromSquare( baseTypes::tFile::A, baseTypes::tRank::one ), BitMap(0x0000000000000001ull));
	}

	TEST(BitMap, isSquareSet)
	{
		BitMap b(3458769736543240192ull);
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::A1 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::C3 ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tSquare::D3 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::E3 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::A5 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::F5 ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tSquare::G5 ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tSquare::H5 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::B6 ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tSquare::C6 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::D6 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::E7 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::B8 ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tSquare::E8 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::H8 ) );


	}

	TEST(BitMap, isSquareSet2)
	{
		BitMap b(3458769736543240192ull);
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::A, baseTypes::tRank::one ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::C, baseTypes::tRank::three ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tFile::D, baseTypes::tRank::three ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::E, baseTypes::tRank::three ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::A, baseTypes::tRank::five ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::F, baseTypes::tRank::five ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tFile::G, baseTypes::tRank::five ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tFile::H, baseTypes::tRank::five ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::B, baseTypes::tRank::six ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tFile::C, baseTypes::tRank::six ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::D, baseTypes::tRank::six ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::E, baseTypes::tRank::seven ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::B, baseTypes::tRank::eight ) );
		ASSERT_TRUE( b.isSquareSet( baseTypes::tFile::E, baseTypes::tRank::eight ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tFile::H, baseTypes::tRank::eight ) );


	}

	TEST(BitMap, iterator)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(3458769736543240192ull);
		for(const auto& t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 8u );
		ASSERT_EQ( v[0], baseTypes::tSquare::D3 );
		ASSERT_EQ( v[1], baseTypes::tSquare::H3 );
		ASSERT_EQ( v[2], baseTypes::tSquare::B4 );
		ASSERT_EQ( v[3], baseTypes::tSquare::G5 );
		ASSERT_EQ( v[4], baseTypes::tSquare::H5 );
		ASSERT_EQ( v[5], baseTypes::tSquare::C6 );
		ASSERT_EQ( v[6], baseTypes::tSquare::E8 );
		ASSERT_EQ( v[7], baseTypes::tSquare::F8 );


	}

	TEST(BitMap, getRankMask)
	{
		for (baseTypes::tFile file = baseTypes::tFile::A; file <= baseTypes::tFile::H; file++)
		{
			for (baseTypes::tRank rank = baseTypes::tRank::one; rank <= baseTypes::tRank::eight; rank++)
			{
				std::vector<baseTypes::tSquare>v;
				BitMap b = BitMap::getRankMask( getSquareFromFileRank( file, rank) );
				for(const auto t : b)
				{
					v.push_back(t);

				}
				ASSERT_EQ( v.size(), 8u );
				ASSERT_EQ( v[0], getSquareFromFileRank( baseTypes::tFile::A, rank) );
				ASSERT_EQ( v[1], getSquareFromFileRank( baseTypes::tFile::B, rank) );
				ASSERT_EQ( v[2], getSquareFromFileRank( baseTypes::tFile::C, rank) );
				ASSERT_EQ( v[3], getSquareFromFileRank( baseTypes::tFile::D, rank) );
				ASSERT_EQ( v[4], getSquareFromFileRank( baseTypes::tFile::E, rank) );
				ASSERT_EQ( v[5], getSquareFromFileRank( baseTypes::tFile::F, rank) );
				ASSERT_EQ( v[6], getSquareFromFileRank( baseTypes::tFile::G, rank) );
				ASSERT_EQ( v[7], getSquareFromFileRank( baseTypes::tFile::H, rank) );
			}
		}
	}

	TEST(BitMap, getFileMask)
	{
		for (baseTypes::tFile file = baseTypes::tFile::A; file <= baseTypes::tFile::H; file++)
		{
			for (baseTypes::tRank rank = baseTypes::tRank::one; rank <= baseTypes::tRank::eight; rank++)
			{
				std::vector<baseTypes::tSquare>v;
				BitMap b = BitMap::getFileMask( getSquareFromFileRank( file, rank) );
				for(const auto t : b)
				{
					v.push_back(t);

				}
				ASSERT_EQ( v.size(), 8u );
				ASSERT_EQ( v[0], getSquareFromFileRank( file, baseTypes::tRank::one) );
				ASSERT_EQ( v[1], getSquareFromFileRank( file, baseTypes::tRank::two) );
				ASSERT_EQ( v[2], getSquareFromFileRank( file, baseTypes::tRank::three) );
				ASSERT_EQ( v[3], getSquareFromFileRank( file, baseTypes::tRank::four) );
				ASSERT_EQ( v[4], getSquareFromFileRank( file, baseTypes::tRank::five) );
				ASSERT_EQ( v[5], getSquareFromFileRank( file, baseTypes::tRank::six) );
				ASSERT_EQ( v[6], getSquareFromFileRank( file, baseTypes::tRank::seven) );
				ASSERT_EQ( v[7], getSquareFromFileRank( file, baseTypes::tRank::eight) );
			}
		}
	}
	
	TEST(BitMap, getColorBitMap)
	{	
		ASSERT_EQ( BitMap::getColorBitMap(baseTypes::tColor::black), BitMap(0xAA55AA55AA55AA55ull) );
		ASSERT_EQ( BitMap::getColorBitMap(baseTypes::tColor::white), BitMap(0x55AA55AA55AA55AAull) );
		
	}
	
	TEST(BitMap, areSquaresAligned)
	{
		ASSERT_TRUE( BitMap::areSquaresAligned( baseTypes::tSquare::D3, baseTypes::tSquare::F5, baseTypes::tSquare::B1 ) );
		ASSERT_FALSE( BitMap::areSquaresAligned( baseTypes::tSquare::C1, baseTypes::tSquare::C7, baseTypes::tSquare::B4 ) );
	}
	
	TEST(BitMap, getSquaresBetween)
	{
		BitMap b = BitMap::getSquaresBetween( baseTypes::tSquare::B7, baseTypes::tSquare::D5);
		ASSERT_TRUE( b.isSquareSet( baseTypes::tSquare::C6 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::B7 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::D5 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::A8 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::F3 ) );
		ASSERT_FALSE( b.isSquareSet( baseTypes::tSquare::G7 ) );
		
	}
	
	TEST(BitMap, to_string)
	{
		BitMap b(64382);
		std::string s = "8 ........\n7 ........\n6 ........\n5 ........\n4 ........\n3 ........\n2 11.11111\n1 .111111.\n  abcdefgh";
		ASSERT_STREQ( s.c_str(), b.to_string().c_str() );
	}
	
	TEST(BitMap, isEmpty)
	{
		BitMap b(64382);
		ASSERT_FALSE( b.isEmpty() );
		BitMap b2(0);
		ASSERT_TRUE( b2.isEmpty() );
		
	}
	
	TEST(BitMap, operatorPlusEqual)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D4;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], baseTypes::tSquare::D4 );
		ASSERT_EQ( v[1], baseTypes::tSquare::F6 );
	}
	
	TEST(BitMap, operatorComparison)
	{
		BitMap b(12692365593);
		BitMap b2(12692365593);
		BitMap b3(1243780067094);
		
		ASSERT_TRUE( b == b2 );
		ASSERT_FALSE( b == b3 );
		ASSERT_FALSE( b2 == b3 );
		ASSERT_TRUE( b == b );
		ASSERT_TRUE( b2 == b2 );
		ASSERT_TRUE( b3 == b3 );
		ASSERT_FALSE( b3 == b2 );
		ASSERT_FALSE( b3 == b );
	}
	
	TEST(BitMap, operatorPlusEqual2)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D5;
		
		BitMap b2(0);
		b2+= baseTypes::tSquare::A2;
		b2+= baseTypes::tSquare::F8;
		b2+= baseTypes::tSquare::D5;
		
		b += b2;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 5u );
		ASSERT_EQ( v[0], baseTypes::tSquare::A2 );
		ASSERT_EQ( v[1], baseTypes::tSquare::D4 );
		ASSERT_EQ( v[2], baseTypes::tSquare::D5 );
		ASSERT_EQ( v[3], baseTypes::tSquare::F6 );
		ASSERT_EQ( v[4], baseTypes::tSquare::F8 );
	}
	
	TEST(BitMap, operatorandEqual)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D5;
		
		BitMap b2(0);
		b2+= baseTypes::tSquare::A2;
		b2+= baseTypes::tSquare::F6;
		b2+= baseTypes::tSquare::D5;
		b2+= baseTypes::tSquare::E8;
		
		b &= b2;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], baseTypes::tSquare::D5 );
		ASSERT_EQ( v[1], baseTypes::tSquare::F6 );

	}
	
	TEST(BitMap, operatorEqual)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b = baseTypes::tSquare::F6;
		
		

		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 1u );
		ASSERT_EQ( v[0], baseTypes::tSquare::F6 );
	}
	
	TEST(BitMap, operatorEqual2)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D4;
		
		BitMap b2;
		b2 = b;
		for(const auto t : b2)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], baseTypes::tSquare::D4 );
		ASSERT_EQ( v[1], baseTypes::tSquare::F6 );
	}
	
	TEST(BitMap, operatorPlus)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D5;
		
		BitMap b2(0);
		b2+= baseTypes::tSquare::A2;
		b2+= baseTypes::tSquare::F8;
		b2+= baseTypes::tSquare::D5;
		
		BitMap b3 = b + b2;
		for(const auto t : b3)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 5u );
		ASSERT_EQ( v[0], baseTypes::tSquare::A2 );
		ASSERT_EQ( v[1], baseTypes::tSquare::D4 );
		ASSERT_EQ( v[2], baseTypes::tSquare::D5 );
		ASSERT_EQ( v[3], baseTypes::tSquare::F6 );
		ASSERT_EQ( v[4], baseTypes::tSquare::F8 );
	}
	
	TEST(BitMap, operatorAnd)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D5;
		
		BitMap b2(0);
		b2+= baseTypes::tSquare::A2;
		b2+= baseTypes::tSquare::F6;
		b2+= baseTypes::tSquare::D5;
		b2+= baseTypes::tSquare::E8;
		
		BitMap b3 = b & b2;
		for(const auto t : b3)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], baseTypes::tSquare::D5 );
		ASSERT_EQ( v[1], baseTypes::tSquare::F6 );

	}
	
	TEST(BitMap, operatorXor)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D5;
		
		BitMap b2(0);
		b2+= baseTypes::tSquare::A2;
		b2+= baseTypes::tSquare::F6;
		b2+= baseTypes::tSquare::D5;
		b2+= baseTypes::tSquare::E8;
		
		BitMap b3 = b ^ b2;
		for(const auto t : b3)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], baseTypes::tSquare::A2 );
		ASSERT_EQ( v[1], baseTypes::tSquare::D4 );
		ASSERT_EQ( v[2], baseTypes::tSquare::E8 );

	}
	
	TEST(BitMap, operatorXor2)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D5;
		
		BitMap b3 = b ^ baseTypes::tSquare::A2;
		b3 = b3 ^ baseTypes::tSquare::F6;
		b3 = b3 ^ baseTypes::tSquare::D5;
		b3 = b3 ^ baseTypes::tSquare::E8;
		for(const auto t : b3)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], baseTypes::tSquare::A2 );
		ASSERT_EQ( v[1], baseTypes::tSquare::D4 );
		ASSERT_EQ( v[2], baseTypes::tSquare::E8 );

	}
	
	TEST(BitMap, operatorXorEqual)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D5;
		
		BitMap b2(0);
		b2+= baseTypes::tSquare::A2;
		b2+= baseTypes::tSquare::F6;
		b2+= baseTypes::tSquare::D5;
		b2+= baseTypes::tSquare::E8;
		
		 b ^= b2;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], baseTypes::tSquare::A2 );
		ASSERT_EQ( v[1], baseTypes::tSquare::D4 );
		ASSERT_EQ( v[2], baseTypes::tSquare::E8 );

	}
	
	TEST(BitMap, operatorXorEqual2)
	{
		std::vector<baseTypes::tSquare>v;
		BitMap b(0);
		b+= baseTypes::tSquare::F6;
		b+= baseTypes::tSquare::D4;
		b+= baseTypes::tSquare::D5;
		
		b ^= baseTypes::tSquare::A2;
		b ^= baseTypes::tSquare::F6;
		b ^= baseTypes::tSquare::D5;
		b ^= baseTypes::tSquare::E8;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], baseTypes::tSquare::A2 );
		ASSERT_EQ( v[1], baseTypes::tSquare::D4 );
		ASSERT_EQ( v[2], baseTypes::tSquare::E8 );

	}
	
}