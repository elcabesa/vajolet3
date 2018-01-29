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

using namespace libChess;

namespace {
	
	TEST(tFile,assign)
	{
		tFile f;
		f = tFile::B;
		ASSERT_EQ( tFile::B, f );
		
		tFile g = f;
		ASSERT_EQ( tFile::B, g );
		g = tFile::F;
		ASSERT_EQ( tFile::F, g );
	}
	
	TEST(tFile, tFileIncrement)
	{
		tFile f = tFile::B;
		ASSERT_EQ( tFile::B, f++ );
		ASSERT_EQ( tFile::C, f );
		ASSERT_EQ( tFile::D, ++f );
		ASSERT_EQ( tFile::D, f );
		
	}
	
	TEST(tFile, tFileDecrement)
	{
		tFile f = tFile::E;
		ASSERT_EQ( tFile::E, f-- );
		ASSERT_EQ( tFile::D, f );
		ASSERT_EQ( tFile::C, --f );
		ASSERT_EQ( tFile::C, f );
		
	}
	
	TEST(tFile, tFileSum)
	{
		tFile f = tFile::E;
		ASSERT_EQ( tFile::G, f + 2 );
	}
	
	TEST(tFile, tFileSub)
	{
		tFile f = tFile::E;
		ASSERT_EQ( tFile::B, f - 3 );
	}
	
	TEST(tFile, tFileDistance)
	{
		tFile f = tFile::E;
		tFile g = tFile::E;
		ASSERT_EQ( 0, distance( f, g ) );
		
		f = tFile::A;
		g = tFile::D;
		ASSERT_EQ( 3, distance( f, g ) );
		
		f = tFile::D;
		g = tFile::A;
		ASSERT_EQ( 3, distance( f, g ) );
	}
	
	TEST(tFile, tFileSum2)
	{
		tFile f = tFile::E;
		ASSERT_EQ( tFile::G, f+= 2 );
	}
	
	TEST(tFile, tFileSub2)
	{
		tFile f = tFile::E;
		ASSERT_EQ( tFile::B, f-= 3 );
	}
	
	TEST(tFile, iterate)
	{
		unsigned int i = 0;

		for(auto t: tFileRange())
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			if(i>1000) break;
		}
		ASSERT_EQ(i, 8u);
	}
	
	TEST(tFile, iterateRange0)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tFile::B);

		for(auto t: tFileRange(tFile::B,tFile::E))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 4u);
	}

	TEST(tFile, iterateRange1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tFile::A);

		for(auto t: tFileRange(tFile::A,tFile::B))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 2u);
	}

	TEST(tFile, iterateRange2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tFile::E);

		for(auto t: tFileRange(tFile::E,tFile::E))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 1u);
	}

	TEST(tFile, iterateRangeNeg1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tFile::E);

		for(auto t: tFileRange(tFile::E,tFile::D))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}

	TEST(tFile, iterateRangeNeg2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tFile::E);

		for(auto t: tFileRange(tFile::E,tFile::A))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}
	
	TEST(tFile, to_string)
	{
		tFile f = tFile::E;
		ASSERT_STREQ( "e", to_string(f).c_str() );
	}
	
	TEST(tFile, distance)
	{
		tFile f = tFile::E;
		tFile g = tFile::E;
		ASSERT_EQ( 0, distance( f,g ));
		
		f = tFile::A;
		g = tFile::D;
		ASSERT_EQ( 3, distance( f,g ));
		
		f = tFile::D;
		g = tFile::A;
		ASSERT_EQ( 3, distance( f,g ));
	}
	
	
		
	TEST(tRank,assign)
	{
		tRank f;
		f = tRank::two;
		ASSERT_EQ( tRank::two, f );
		
		tRank g = f;
		ASSERT_EQ( tRank::two, g );
		g = tRank::four;
		ASSERT_EQ( tRank::four, g );
	}
	
	TEST(tRank, tRankIncrement)
	{
		tRank f = tRank::two;
		ASSERT_EQ( tRank::two, f++ );
		ASSERT_EQ( tRank::three, f );
		ASSERT_EQ( tRank::four, ++f );
		ASSERT_EQ( tRank::four, f );
		
	}
	
	TEST(tRank, tRankDecrement)
	{
		tRank f = tRank::seven;
		ASSERT_EQ( tRank::seven, f-- );
		ASSERT_EQ( tRank::six, f );
		ASSERT_EQ( tRank::five, --f );
		ASSERT_EQ( tRank::five, f );
		
	}
	
	TEST(tRank, tRankSum)
	{
		tRank f = tRank::four;
		ASSERT_EQ( tRank::six, f + 2 );
	}
	
	TEST(tRank, tRankSub)
	{
		tRank f = tRank::eight;
		ASSERT_EQ( tRank::five, f - 3 );
	}
	
	TEST(tRank, tRankDistance)
	{
		tRank f = tRank::four;
		tRank g = tRank::four;
		ASSERT_EQ( 0, distance( f, g ) );
		
		f = tRank::four;
		g = tRank::one;
		ASSERT_EQ( 3, distance( f, g ) );
		
		f = tRank::one;
		g = tRank::four;
		ASSERT_EQ( 3, distance( f, g ) );
	}
	
	TEST(tRank, tRankSum2)
	{
		tRank f = tRank::five;
		ASSERT_EQ( tRank::seven, f+= 2 );
	}
	
	TEST(tRank, tRankSub2)
	{
		tRank f = tRank::four;
		ASSERT_EQ( tRank::one, f-= 3 );
	}
	
	TEST(tRank, iterate)
	{
		unsigned int i = 0;

		for(auto t: tRankRange())
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			if(i>1000) break;
		}
		ASSERT_EQ(i, 8u);
	}
	
	TEST(tRank, iterateRange0)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tRank::two);

		for(auto t: tRankRange(tRank::two,tRank::five))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 4u);
	}

	TEST(tRank, iterateRange1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tRank::one);

		for(auto t: tRankRange(tRank::one,tRank::two))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 2u);
	}

	TEST(tRank, iterateRange2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tRank::seven);

		for(auto t: tRankRange(tRank::seven,tRank::seven))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 1u);
	}

	TEST(tRank, iterateRangeNeg1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tRank::seven);

		for(auto t: tRankRange(tRank::seven,tRank::six))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}

	TEST(tRank, iterateRangeNeg2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(tRank::eight);

		for(auto t: tRankRange(tRank::eight,tRank::one))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}
	
	TEST(tRank, to_string)
	{
		tRank f = tRank::two;
		ASSERT_STREQ( "2", to_string(f).c_str() );
	}
	
	TEST(tRank, distance)
	{
		tRank f = tRank::seven;
		tRank g = tRank::seven;
		ASSERT_EQ( 0, distance( f,g ));
		
		f = tRank::one;
		g = tRank::four;
		ASSERT_EQ( 3, distance( f,g ));
		
		f = tRank::four;
		g = tRank::one;
		ASSERT_EQ( 3, distance( f,g ));
	}

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

	
	TEST(tSquare, sum)
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
	
	TEST(tSquare, sum2)
	{
		tSquare t;
		t = tSquare::C3;
		t += tSquare::north;
		ASSERT_EQ(tSquare::C4, t );
	}
	
	TEST(tSquare, subtracion)
	{
		tSquare t= tSquare::F6;
		ASSERT_EQ(tSquare::F5, t - tSquare::north );
	}

	TEST(tSquare, subtracion2)
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
	
	TEST(tSquare, multiply2)
	{
		tSquare t= tSquare::A1;
		t += tSquare::north * 5;
		ASSERT_EQ(t, tSquare::A6);
	}
	
	TEST(tSquare, tSquareIncrement)
	{
		tSquare f = tSquare::E4;
		ASSERT_EQ( tSquare::E4, f++ );
		ASSERT_EQ( tSquare::F4, f );
		ASSERT_EQ( tSquare::G4, ++f );
		ASSERT_EQ( tSquare::G4, f );
		
	}
	
	TEST(tSquare, tSquareDecrement)
	{
		tSquare f = tSquare::E4;
		ASSERT_EQ( tSquare::E4, f-- );
		ASSERT_EQ( tSquare::D4, f );
		ASSERT_EQ( tSquare::C4, --f );
		ASSERT_EQ( tSquare::C4, f );
		
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
			
		t = tSquare::G8;
		ASSERT_EQ(getFile(t),tFile::G);
		ASSERT_EQ(getRank(t),tRank::eight);
		ASSERT_EQ(getColor(t),tColor::white);
		
		t = tSquare::D4;
		ASSERT_EQ(getFile(t),tFile::D);
		ASSERT_EQ(getRank(t),tRank::four);
		ASSERT_EQ(getColor(t),tColor::black);
		
		t = tSquare::D5;
		ASSERT_EQ(getFile(t),tFile::D);
		ASSERT_EQ(getRank(t),tRank::five);
		ASSERT_EQ(getColor(t),tColor::white);
		
		t = tSquare::E4;
		ASSERT_EQ(getFile(t),tFile::E);
		ASSERT_EQ(getRank(t),tRank::four);
		ASSERT_EQ(getColor(t),tColor::white);
		
		t = tSquare::E5;
		ASSERT_EQ(getFile(t),tFile::E);
		ASSERT_EQ(getRank(t),tRank::five);
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

	TEST(tSquare, distance)
	{
		ASSERT_EQ( distance( tSquare::A1, tSquare::H8 ), 7u );
		ASSERT_EQ( distance( tSquare::H8, tSquare::A1 ), 7u );
		ASSERT_EQ( distance( tSquare::F6, tSquare::F6 ), 0u );
		ASSERT_EQ( distance( tSquare::F4, tSquare::F7 ), 3u );
		ASSERT_EQ( distance( tSquare::D4, tSquare::F7 ), 3u );
		ASSERT_EQ( distance( tSquare::F7, tSquare::D4 ), 3u );
		ASSERT_EQ( distance( tSquare::D4, tSquare::D5 ), 1u );
		ASSERT_EQ( distance( tSquare::D4, tSquare::E4 ), 1u );
	}
	
	TEST(tColor, assign)
	{
		tColor c = tColor::white;
		ASSERT_EQ(tColor::white, c);
		
		c = tColor::black;
		ASSERT_EQ(tColor::black, c);
	}
	
}


