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
namespace {

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
		for(const auto t : b)
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

	TEST(BitMap, getRankMask)
	{
		for (tFile file = tFile::A; file <= tFile::H; file++)
		{
			for (tRank rank = tRank::one; rank <= tRank::eight; rank++)
			{
				std::vector<tSquare>v;
				BitMap b = BitMap::getRankMask( getFromFileRank( file, rank) );
				for(const auto t : b)
				{
					v.push_back(t);

				}
				ASSERT_EQ( v.size(), 8u );
				ASSERT_EQ( v[0], getFromFileRank( tFile::A, rank) );
				ASSERT_EQ( v[1], getFromFileRank( tFile::B, rank) );
				ASSERT_EQ( v[2], getFromFileRank( tFile::C, rank) );
				ASSERT_EQ( v[3], getFromFileRank( tFile::D, rank) );
				ASSERT_EQ( v[4], getFromFileRank( tFile::E, rank) );
				ASSERT_EQ( v[5], getFromFileRank( tFile::F, rank) );
				ASSERT_EQ( v[6], getFromFileRank( tFile::G, rank) );
				ASSERT_EQ( v[7], getFromFileRank( tFile::H, rank) );
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
				BitMap b = BitMap::getFileMask( getFromFileRank( file, rank) );
				for(const auto t : b)
				{
					v.push_back(t);

				}
				ASSERT_EQ( v.size(), 8u );
				ASSERT_EQ( v[0], getFromFileRank( file, tRank::one) );
				ASSERT_EQ( v[1], getFromFileRank( file, tRank::two) );
				ASSERT_EQ( v[2], getFromFileRank( file, tRank::three) );
				ASSERT_EQ( v[3], getFromFileRank( file, tRank::four) );
				ASSERT_EQ( v[4], getFromFileRank( file, tRank::five) );
				ASSERT_EQ( v[5], getFromFileRank( file, tRank::six) );
				ASSERT_EQ( v[6], getFromFileRank( file, tRank::seven) );
				ASSERT_EQ( v[7], getFromFileRank( file, tRank::eight) );
			}
		}
	}

}




