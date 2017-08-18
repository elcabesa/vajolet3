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
#include "./../tSquare.h"
namespace {

	TEST(tSquare, assign)
	{
		tSquare t;
		t = tSquare::C3;
		ASSERT_EQ(t, tSquare::C3);

		t = tSquare::A1;
		ASSERT_EQ(t, tSquare::A1);

		t = tSquare::F6;
		ASSERT_EQ(t, tSquare::F6);
	}

	TEST(tSquare, move)
	{
		tSquare t1,t2;
		t1 = tSquare::C3;
		t2 = tSquare::north;
		ASSERT_EQ(t1+t2, tSquare::C4);

		t1 = tSquare::G7;
		t2 = tSquare::northEast;
		ASSERT_EQ(t1+t2, tSquare::H8);

		t1 = tSquare::E4;
		t2 = tSquare::east;
		ASSERT_EQ(t1+t2, tSquare::F4);

		t1 = tSquare::D2;
		t2 = tSquare::sudEast;
		ASSERT_EQ(t1+t2, tSquare::E1);

		t1 = tSquare::B2;
		t2 = tSquare::sud;
		ASSERT_EQ(t1+t2, tSquare::B1);

		t1 = tSquare::D2;
		t2 = tSquare::sudOvest;
		ASSERT_EQ(t1+t2, tSquare::C1);

		t1 = tSquare::B4;
		t2 = tSquare::ovest;
		ASSERT_EQ(t1+t2, tSquare::A4);

		t1 = tSquare::H5;
		t2 = tSquare::northOvest;
		ASSERT_EQ(t1+t2, tSquare::G6);
	}

	TEST(tSquare, subtracion)
	{
		tSquare t= tSquare::F6;
		t -= tSquare::north;
		ASSERT_EQ(t, tSquare::F5);
	}

	TEST(tSquare, multiply)
	{
		tSquare t= tSquare::A1;
		t += 5*tSquare::north;
		ASSERT_EQ(t, tSquare::A6);
	}

	TEST(tSquare, iterate)
	{
		unsigned int i = 0;

		for(auto t: tSquareRange())
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			if(i>1000) break;
		}
		ASSERT_EQ(i, 64u);
	}
	TEST(tSquare, iterateRange0)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tSquare::E2);

		for(auto t: tSquareRange(tSquare::E2,tSquare::B6))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 30u);
	}

	TEST(tSquare, iterateRange2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tSquare::E2);

		for(auto t: tSquareRange(tSquare::E2,tSquare::F2))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 2u);
	}

	TEST(tSquare, iterateRange1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tSquare::E2);

		for(auto t: tSquareRange(tSquare::E2,tSquare::E2))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 1u);
	}

	TEST(tSquare, iterateRangeNeg1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tSquare::E2);

		for(auto t: tSquareRange(tSquare::E2,tSquare::D2))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}

	TEST(tSquare, iterateRangeNeg2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tSquare::E2);

		for(auto t: tSquareRange(tSquare::E2,tSquare::A1))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}

	TEST(tSquare, getFileRankColor)
	{
		tSquare t = tSquare::A2;
		ASSERT_EQ(getFile(t),tFile::A);
		ASSERT_EQ(getRank(t),tRank::two);
		ASSERT_EQ(getColor(t),tColor::white);

		t = tSquare::F6;
		ASSERT_EQ(getFile(t),tFile::F);
		ASSERT_EQ(getRank(t),tRank::six);
		ASSERT_EQ(getColor(t),tColor::black);
	}

	TEST(tSquare, to_string)
	{
		tSquare t = tSquare::A2;

		ASSERT_EQ(to_string(getFile(t)),std::string("a"));
		ASSERT_EQ(to_string(getRank(t)),std::string("2"));
		ASSERT_EQ(to_string(t),std::string("a2"));

		t = tSquare::F6;
		ASSERT_EQ( to_string( getFile(t) ), std::string("f") );
		ASSERT_EQ( to_string( getRank(t) ), std::string("6") );
		ASSERT_EQ( to_string( t ),std::string("f6"));

	}

	TEST(tSquare, gettSquareFromFileRank)
	{
		ASSERT_EQ( getSquareFromFileRank( tFile::A, tRank::six ), tSquare::A6 );
		ASSERT_EQ( getSquareFromFileRank( tFile::F, tRank::two ), tSquare::F2 );
		ASSERT_EQ( getSquareFromFileRank( tFile::A, tRank::one ), tSquare::A1 );
		ASSERT_EQ( getSquareFromFileRank( tFile::H, tRank::eight ), tSquare::H8 );
		ASSERT_EQ( getSquareFromFileRank( tFile::G, tRank::three ), tSquare::G3 );
		ASSERT_EQ( getSquareFromFileRank( tFile::C, tRank::seven ), tSquare::C7 );

	}

	TEST(tSquare, getSquareDistance)
	{
		ASSERT_EQ( getSquareDistance( tSquare::A1, tSquare::H8 ), 7u );
		ASSERT_EQ( getSquareDistance( tSquare::H8, tSquare::A1 ), 7u );
		ASSERT_EQ( getSquareDistance( tSquare::F6, tSquare::F6 ), 0u );
		ASSERT_EQ( getSquareDistance( tSquare::F4, tSquare::F7 ), 3u );
		ASSERT_EQ( getSquareDistance( tSquare::D4, tSquare::F7 ), 3u );
		ASSERT_EQ( getSquareDistance( tSquare::F7, tSquare::D4 ), 3u );
		ASSERT_EQ( getSquareDistance( tSquare::D4, tSquare::D5 ), 1u );
		ASSERT_EQ( getSquareDistance( tSquare::D4, tSquare::E4 ), 1u );
	}


}


