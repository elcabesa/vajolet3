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

#include <algorithm>
#include "gtest/gtest.h"
#include "./../BitMap.h"

using namespace libChess::baseTypes;


namespace {
	
	TEST(BitMap, constructor1)
	{
		BitMap x = BitMap(5);
		ASSERT_TRUE( x.isSquareSet(tSquare::A1));
		ASSERT_FALSE( x.isSquareSet(tSquare::B1));
		ASSERT_TRUE( x.isSquareSet(tSquare::C1));
		ASSERT_FALSE( x.isSquareSet(tSquare::E5));
	}
	
	TEST(BitMap, constructor2)
	{
		BitMap x = BitMap(7);
		ASSERT_TRUE( x.isSquareSet(tSquare::A1));
		ASSERT_TRUE( x.isSquareSet(tSquare::B1));
		ASSERT_TRUE( x.isSquareSet(tSquare::C1));
		ASSERT_FALSE( x.isSquareSet(tSquare::E5));
	}
	
	TEST(BitMap, constructor3)
	{
		BitMap x = BitMap(7);
		BitMap y(x);
		ASSERT_TRUE( y.isSquareSet(tSquare::A1));
		ASSERT_TRUE( y.isSquareSet(tSquare::B1));
		ASSERT_TRUE( y.isSquareSet(tSquare::C1));
		ASSERT_FALSE( y.isSquareSet(tSquare::E5));
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
		//ASSERT_EQ( BitMap(0).firstOne(), tSquare::A1); // sure?? machine dependant??
		ASSERT_EQ( BitMap(1).firstOne(), tSquare::A1);
		ASSERT_EQ( BitMap(0x803000100C803008ull).firstOne(), tSquare::D1);
		ASSERT_EQ( BitMap(3458769736543240192ull).firstOne(), tSquare::D3);
		ASSERT_EQ( BitMap(0xFFFFFFFFFFFFFFFFull).firstOne(), tSquare::A1);
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
		ASSERT_EQ( BitMap::getBitmapFromSquare( tSquare::A3 ), BitMap(0x10000ull));
		ASSERT_EQ( BitMap::getBitmapFromSquare( tSquare::H8 ), BitMap(0x8000000000000000ull));
		ASSERT_EQ( BitMap::getBitmapFromSquare( tSquare::A1 ), BitMap(0x0000000000000001ull));

	}

	TEST(BitMap, getBitmapFromSquare2)
	{
		ASSERT_EQ( BitMap::getBitmapFromSquare( tFile::A, tRank::three ), BitMap(0x10000ull));
		ASSERT_EQ( BitMap::getBitmapFromSquare( tFile::H, tRank::eight ), BitMap(0x8000000000000000ull));
		ASSERT_EQ( BitMap::getBitmapFromSquare( tFile::A, tRank::one ), BitMap(0x0000000000000001ull));
	}

	TEST(BitMap, isSquareSet)
	{
		BitMap b(3458769736543240192ull);
		ASSERT_FALSE( b.isSquareSet( tSquare::A1 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::C3 ) );
		ASSERT_TRUE( b.isSquareSet( tSquare::D3 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::E3 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::A5 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::F5 ) );
		ASSERT_TRUE( b.isSquareSet( tSquare::G5 ) );
		ASSERT_TRUE( b.isSquareSet( tSquare::H5 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::B6 ) );
		ASSERT_TRUE( b.isSquareSet( tSquare::C6 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::D6 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::E7 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::B8 ) );
		ASSERT_TRUE( b.isSquareSet( tSquare::E8 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::H8 ) );


	}

	TEST(BitMap, isSquareSet2)
	{
		BitMap b(3458769736543240192ull);
		ASSERT_FALSE( b.isSquareSet( tFile::A, tRank::one ) );
		ASSERT_FALSE( b.isSquareSet( tFile::C, tRank::three ) );
		ASSERT_TRUE( b.isSquareSet( tFile::D, tRank::three ) );
		ASSERT_FALSE( b.isSquareSet( tFile::E, tRank::three ) );
		ASSERT_FALSE( b.isSquareSet( tFile::A, tRank::five ) );
		ASSERT_FALSE( b.isSquareSet( tFile::F, tRank::five ) );
		ASSERT_TRUE( b.isSquareSet( tFile::G, tRank::five ) );
		ASSERT_TRUE( b.isSquareSet( tFile::H, tRank::five ) );
		ASSERT_FALSE( b.isSquareSet( tFile::B, tRank::six ) );
		ASSERT_TRUE( b.isSquareSet( tFile::C, tRank::six ) );
		ASSERT_FALSE( b.isSquareSet( tFile::D, tRank::six ) );
		ASSERT_FALSE( b.isSquareSet( tFile::E, tRank::seven ) );
		ASSERT_FALSE( b.isSquareSet( tFile::B, tRank::eight ) );
		ASSERT_TRUE( b.isSquareSet( tFile::E, tRank::eight ) );
		ASSERT_FALSE( b.isSquareSet( tFile::H, tRank::eight ) );


	}

	TEST(BitMap, iterator)
	{
		std::vector<tSquare>v;
		BitMap b(3458769736543240192ull);
		for(const auto& t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 8u );
		ASSERT_EQ( v[0], tSquare::D3 );
		ASSERT_EQ( v[1], tSquare::H3 );
		ASSERT_EQ( v[2], tSquare::B4 );
		ASSERT_EQ( v[3], tSquare::G5 );
		ASSERT_EQ( v[4], tSquare::H5 );
		ASSERT_EQ( v[5], tSquare::C6 );
		ASSERT_EQ( v[6], tSquare::E8 );
		ASSERT_EQ( v[7], tSquare::F8 );


	}

	TEST(BitMap, getRankMask)
	{
		for (tFile file = tFile::A; file <= tFile::H; file++)
		{
			for (tRank rank = tRank::one; rank <= tRank::eight; rank++)
			{
				std::vector<tSquare>v;
				BitMap b = BitMap::getRankMask( getSquareFromFileRank( file, rank) );
				for(const auto t : b)
				{
					v.push_back(t);

				}
				ASSERT_EQ( v.size(), 8u );
				ASSERT_EQ( v[0], getSquareFromFileRank( tFile::A, rank) );
				ASSERT_EQ( v[1], getSquareFromFileRank( tFile::B, rank) );
				ASSERT_EQ( v[2], getSquareFromFileRank( tFile::C, rank) );
				ASSERT_EQ( v[3], getSquareFromFileRank( tFile::D, rank) );
				ASSERT_EQ( v[4], getSquareFromFileRank( tFile::E, rank) );
				ASSERT_EQ( v[5], getSquareFromFileRank( tFile::F, rank) );
				ASSERT_EQ( v[6], getSquareFromFileRank( tFile::G, rank) );
				ASSERT_EQ( v[7], getSquareFromFileRank( tFile::H, rank) );
			}
		}
	}

	TEST(BitMap, getFileMask)
	{
		for (tFile file = tFile::A; file <= tFile::H; file++)
		{
			for (tRank rank = tRank::one; rank <= tRank::eight; rank++)
			{
				std::vector<tSquare>v;
				BitMap b = BitMap::getFileMask( getSquareFromFileRank( file, rank) );
				for(const auto t : b)
				{
					v.push_back(t);

				}
				ASSERT_EQ( v.size(), 8u );
				ASSERT_EQ( v[0], getSquareFromFileRank( file, tRank::one) );
				ASSERT_EQ( v[1], getSquareFromFileRank( file, tRank::two) );
				ASSERT_EQ( v[2], getSquareFromFileRank( file, tRank::three) );
				ASSERT_EQ( v[3], getSquareFromFileRank( file, tRank::four) );
				ASSERT_EQ( v[4], getSquareFromFileRank( file, tRank::five) );
				ASSERT_EQ( v[5], getSquareFromFileRank( file, tRank::six) );
				ASSERT_EQ( v[6], getSquareFromFileRank( file, tRank::seven) );
				ASSERT_EQ( v[7], getSquareFromFileRank( file, tRank::eight) );
			}
		}
	}
	
	TEST(BitMap, getColorBitMap)
	{	
		ASSERT_EQ( BitMap::getColorBitMap(tColor::black), BitMap(0xAA55AA55AA55AA55ull) );
		ASSERT_EQ( BitMap::getColorBitMap(tColor::white), BitMap(0x55AA55AA55AA55AAull) );
		
	}
	
	TEST(BitMap, areSquaresAligned)
	{
		ASSERT_TRUE( BitMap::areSquaresAligned( tSquare::D3, tSquare::F5, tSquare::B1 ) );
		ASSERT_FALSE( BitMap::areSquaresAligned( tSquare::C1, tSquare::C7, tSquare::B4 ) );
	}
	
	TEST(BitMap, getSquaresBetween)
	{
		BitMap b = BitMap::getSquaresBetween( tSquare::B7, tSquare::D5);
		ASSERT_TRUE( b.isSquareSet( tSquare::C6 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::B7 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::D5 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::A8 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::F3 ) );
		ASSERT_FALSE( b.isSquareSet( tSquare::G7 ) );
		
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
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D4;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], tSquare::D4 );
		ASSERT_EQ( v[1], tSquare::F6 );
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
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		BitMap b2(0);
		b2+= tSquare::A2;
		b2+= tSquare::F8;
		b2+= tSquare::D5;
		
		b += b2;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 5u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::D4 );
		ASSERT_EQ( v[2], tSquare::D5 );
		ASSERT_EQ( v[3], tSquare::F6 );
		ASSERT_EQ( v[4], tSquare::F8 );
	}
	
	TEST(BitMap, operatorandEqual)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		BitMap b2(0);
		b2+= tSquare::A2;
		b2+= tSquare::F6;
		b2+= tSquare::D5;
		b2+= tSquare::E8;
		
		b &= b2;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], tSquare::D5 );
		ASSERT_EQ( v[1], tSquare::F6 );

	}
	
	TEST(BitMap, operatorEqual)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b = tSquare::F6;
		
		

		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 1u );
		ASSERT_EQ( v[0], tSquare::F6 );
	}
	
	TEST(BitMap, operatorEqual2)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D4;
		
		BitMap b2;
		b2 = b;
		for(const auto t : b2)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], tSquare::D4 );
		ASSERT_EQ( v[1], tSquare::F6 );
	}
	
	TEST(BitMap, operatorPlus)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		BitMap b2(0);
		b2+= tSquare::A2;
		b2+= tSquare::F8;
		b2+= tSquare::D5;
		
		BitMap b3 = b + b2;
		for(const auto t : b3)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 5u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::D4 );
		ASSERT_EQ( v[2], tSquare::D5 );
		ASSERT_EQ( v[3], tSquare::F6 );
		ASSERT_EQ( v[4], tSquare::F8 );
	}
	
	TEST(BitMap, operatorPlus2)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		BitMap b2(0);
		b2 = b + tSquare::A2;
		b2 = b2 + tSquare::F8;
		b2 = b2 + tSquare::D5;
		
		
		for(const auto t : b2)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 5u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::D4 );
		ASSERT_EQ( v[2], tSquare::D5 );
		ASSERT_EQ( v[3], tSquare::F6 );
		ASSERT_EQ( v[4], tSquare::F8 );
	}
	
	TEST(BitMap, operatorAnd)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		BitMap b2(0);
		b2+= tSquare::A2;
		b2+= tSquare::F6;
		b2+= tSquare::D5;
		b2+= tSquare::E8;
		
		BitMap b3 = b & b2;
		for(const auto t : b3)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], tSquare::D5 );
		ASSERT_EQ( v[1], tSquare::F6 );

	}
	
	TEST(BitMap, operatorXor)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		BitMap b2(0);
		b2+= tSquare::A2;
		b2+= tSquare::F6;
		b2+= tSquare::D5;
		b2+= tSquare::E8;
		
		BitMap b3 = b ^ b2;
		for(const auto t : b3)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::D4 );
		ASSERT_EQ( v[2], tSquare::E8 );

	}
	
	TEST(BitMap, operatorXor2)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		BitMap b3 = b ^ tSquare::A2;
		b3 = b3 ^ tSquare::F6;
		b3 = b3 ^ tSquare::D5;
		b3 = b3 ^ tSquare::E8;
		for(const auto t : b3)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::D4 );
		ASSERT_EQ( v[2], tSquare::E8 );

	}
	
	TEST(BitMap, operatorXorEqual)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		BitMap b2(0);
		b2+= tSquare::A2;
		b2+= tSquare::F6;
		b2+= tSquare::D5;
		b2+= tSquare::E8;
		
		 b ^= b2;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::D4 );
		ASSERT_EQ( v[2], tSquare::E8 );

	}
	
	TEST(BitMap, operatorXorEqual2)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::F6;
		b+= tSquare::D4;
		b+= tSquare::D5;
		
		b ^= tSquare::A2;
		b ^= tSquare::F6;
		b ^= tSquare::D5;
		b ^= tSquare::E8;
		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::D4 );
		ASSERT_EQ( v[2], tSquare::E8 );

	}
	
	TEST(BitMap, operatorLeftShift)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::H8;
		
		BitMap r = b << 1;
		

		for(const auto t : r)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::B1 );
		ASSERT_EQ( v[1], tSquare::A2 );
		ASSERT_EQ( v[2], tSquare::F6 );

	}
	
	TEST(BitMap, operatorRightShift)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::H8;
		
		BitMap r = b >> 1;
		

		for(const auto t : r)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::G1 );
		ASSERT_EQ( v[1], tSquare::D6 );
		ASSERT_EQ( v[2], tSquare::G8 );

	}
	
	TEST(BitMap, operatorLeftShift2)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::H8;
		
		BitMap r = b << 8;
		

		for(const auto t : r)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::H2 );
		ASSERT_EQ( v[2], tSquare::E7 );

	}
	
	TEST(BitMap, operatorRightShift2)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::H8;
		
		BitMap r = b >> 8;
		

		for(const auto t : r)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], tSquare::E5 );
		ASSERT_EQ( v[1], tSquare::H7 );

	}
	
	TEST(BitMap, operatorLeftShift3)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::B1;
		b+= tSquare::H8;
		
		BitMap r = b << 63;
		

		for(const auto t : r)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 0u );

	}
	
	TEST(BitMap, operatorRightShift3)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::F8;

		BitMap r = b >> 63;
		

		for(const auto t : r)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 0u );

	}
	
	
	TEST(BitMap, operatorLeftShiftEqual)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::H8;
		
		b <<= 1;
		

		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::B1 );
		ASSERT_EQ( v[1], tSquare::A2 );
		ASSERT_EQ( v[2], tSquare::F6 );

	}
	
	TEST(BitMap, operatorRightShiftEqual)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::H8;
		
		b >>= 1;
		

		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::G1 );
		ASSERT_EQ( v[1], tSquare::D6 );
		ASSERT_EQ( v[2], tSquare::G8 );

	}
	
	TEST(BitMap, operatorLeftShiftEqual2)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::H8;
		
		b <<= 8;
		

		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 3u );
		ASSERT_EQ( v[0], tSquare::A2 );
		ASSERT_EQ( v[1], tSquare::H2 );
		ASSERT_EQ( v[2], tSquare::E7 );

	}
	
	TEST(BitMap, operatorRightShiftEqual2)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::H8;
		
		b >>= 8;
		

		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 2u );
		ASSERT_EQ( v[0], tSquare::E5 );
		ASSERT_EQ( v[1], tSquare::H7 );

	}
	
	TEST(BitMap, operatorLeftShiftEqual3)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::B1;
		b+= tSquare::H8;
		
		b <<= 63;
		

		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 0u );

	}
	
	TEST(BitMap, operatorRightShiftEqual3)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b+= tSquare::E6;
		b+= tSquare::H1;
		b+= tSquare::A1;
		b+= tSquare::F8;

		b >>= 63;
		

		for(const auto t : b)
		{
			v.push_back(t);
		}

		ASSERT_EQ( v.size(), 0u );

	}
	TEST(BitMap, operatorInvert)
	{
		std::vector<tSquare>v;
		BitMap b(0);
		b += tSquare::A5;
		b += tSquare::D3;
		b += tSquare::C7;
		
		BitMap d = ~b;
		
		for(const auto t : d)
		{
			v.push_back(t);
		}
		ASSERT_EQ( v.size(), 61u );
		for( auto t : tSquareRange() )
		{
			if( t == tSquare::A5 || t == tSquare::D3 || t == tSquare::C7 )
			{
				ASSERT_EQ( v.end(), std::find( v.begin(), v.end(),t ) );
			}
			else
			{
				ASSERT_NE( v.end(), std::find( v.begin(), v.end(),t ) );
			}
			
		}
		
	}
	
	
}