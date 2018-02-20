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
		baseTypes::tFile f;
		f = baseTypes::tFile::B;
		ASSERT_EQ( baseTypes::tFile::B, f );
		
		baseTypes::tFile g = f;
		ASSERT_EQ( baseTypes::tFile::B, g );
		g = baseTypes::tFile::F;
		ASSERT_EQ( baseTypes::tFile::F, g );
	}
	
	TEST(tFile, tFileIncrement)
	{
		baseTypes::tFile f = baseTypes::tFile::B;
		ASSERT_EQ( baseTypes::tFile::B, f++ );
		ASSERT_EQ( baseTypes::tFile::C, f );
		ASSERT_EQ( baseTypes::tFile::D, ++f );
		ASSERT_EQ( baseTypes::tFile::D, f );
		
	}
	
	TEST(tFile, tFileDecrement)
	{
		baseTypes::tFile f = baseTypes::tFile::E;
		ASSERT_EQ( baseTypes::tFile::E, f-- );
		ASSERT_EQ( baseTypes::tFile::D, f );
		ASSERT_EQ( baseTypes::tFile::C, --f );
		ASSERT_EQ( baseTypes::tFile::C, f );
		
	}
	
	TEST(tFile, tFileSum)
	{
		baseTypes::tFile f = baseTypes::tFile::E;
		ASSERT_EQ( baseTypes::tFile::G, f + 2 );
	}
	
	TEST(tFile, tFileSub)
	{
		baseTypes::tFile f = baseTypes::tFile::E;
		ASSERT_EQ( baseTypes::tFile::B, f - 3 );
	}
	
	TEST(tFile, tFileDistance)
	{
		baseTypes::tFile f = baseTypes::tFile::E;
		baseTypes::tFile g = baseTypes::tFile::E;
		ASSERT_EQ( 0, distance( f, g ) );
		
		f = baseTypes::tFile::A;
		g = baseTypes::tFile::D;
		ASSERT_EQ( 3, distance( f, g ) );
		
		f = baseTypes::tFile::D;
		g = baseTypes::tFile::A;
		ASSERT_EQ( 3, distance( f, g ) );
	}
	
	TEST(tFile, tFileSum2)
	{
		baseTypes::tFile f = baseTypes::tFile::E;
		ASSERT_EQ( baseTypes::tFile::G, f+= 2 );
	}
	
	TEST(tFile, tFileSub2)
	{
		baseTypes::tFile f = baseTypes::tFile::E;
		ASSERT_EQ( baseTypes::tFile::B, f-= 3 );
	}
	
	TEST(tFile, iterate)
	{
		unsigned int i = 0;

		for(auto t: baseTypes::tFileRange())
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
		unsigned int i = (int)(baseTypes::tFile::B);

		for(auto t: baseTypes::tFileRange(baseTypes::tFile::B,baseTypes::tFile::E))
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
		unsigned int i = (int)(baseTypes::tFile::A);

		for(auto t: baseTypes::tFileRange(baseTypes::tFile::A,baseTypes::tFile::B))
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
		unsigned int i = (int)(baseTypes::tFile::E);

		for(auto t: baseTypes::tFileRange(baseTypes::tFile::E,baseTypes::tFile::E))
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
		unsigned int i = (int)(baseTypes::tFile::E);

		for(auto t: baseTypes::tFileRange(baseTypes::tFile::E,baseTypes::tFile::D))
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
		unsigned int i = (int)(baseTypes::tFile::E);

		for(auto t: baseTypes::tFileRange(baseTypes::tFile::E,baseTypes::tFile::A))
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
		baseTypes::tFile f = baseTypes::tFile::E;
		ASSERT_STREQ( "e", to_string(f).c_str() );
	}
	
	TEST(tFile, distance)
	{
		baseTypes::tFile f = baseTypes::tFile::E;
		baseTypes::tFile g = baseTypes::tFile::E;
		ASSERT_EQ( 0, distance( f,g ));
		
		f = baseTypes::tFile::A;
		g = baseTypes::tFile::D;
		ASSERT_EQ( 3, distance( f,g ));
		
		f = baseTypes::tFile::D;
		g = baseTypes::tFile::A;
		ASSERT_EQ( 3, distance( f,g ));
	}
	
	
		
	TEST(tRank,assign)
	{
		baseTypes::tRank f;
		f = baseTypes::tRank::two;
		ASSERT_EQ( baseTypes::tRank::two, f );
		
		baseTypes::tRank g = f;
		ASSERT_EQ( baseTypes::tRank::two, g );
		g = baseTypes::tRank::four;
		ASSERT_EQ( baseTypes::tRank::four, g );
	}
	
	TEST(tRank, tRankIncrement)
	{
		baseTypes::tRank f = baseTypes::tRank::two;
		ASSERT_EQ( baseTypes::tRank::two, f++ );
		ASSERT_EQ( baseTypes::tRank::three, f );
		ASSERT_EQ( baseTypes::tRank::four, ++f );
		ASSERT_EQ( baseTypes::tRank::four, f );
		
	}
	
	TEST(tRank, tRankDecrement)
	{
		baseTypes::tRank f = baseTypes::tRank::seven;
		ASSERT_EQ( baseTypes::tRank::seven, f-- );
		ASSERT_EQ( baseTypes::tRank::six, f );
		ASSERT_EQ( baseTypes::tRank::five, --f );
		ASSERT_EQ( baseTypes::tRank::five, f );
		
	}
	
	TEST(tRank, tRankSum)
	{
		baseTypes::tRank f = baseTypes::tRank::four;
		ASSERT_EQ( baseTypes::tRank::six, f + 2 );
	}
	
	TEST(tRank, tRankSub)
	{
		baseTypes::tRank f = baseTypes::tRank::eight;
		ASSERT_EQ( baseTypes::tRank::five, f - 3 );
	}
	
	TEST(tRank, tRankDistance)
	{
		baseTypes::tRank f = baseTypes::tRank::four;
		baseTypes::tRank g = baseTypes::tRank::four;
		ASSERT_EQ( 0, distance( f, g ) );
		
		f = baseTypes::tRank::four;
		g = baseTypes::tRank::one;
		ASSERT_EQ( 3, distance( f, g ) );
		
		f = baseTypes::tRank::one;
		g = baseTypes::tRank::four;
		ASSERT_EQ( 3, distance( f, g ) );
	}
	
	TEST(tRank, tRankSum2)
	{
		baseTypes::tRank f = baseTypes::tRank::five;
		ASSERT_EQ( baseTypes::tRank::seven, f+= 2 );
	}
	
	TEST(tRank, tRankSub2)
	{
		baseTypes::tRank f = baseTypes::tRank::four;
		ASSERT_EQ( baseTypes::tRank::one, f-= 3 );
	}
	
	TEST(tRank, iterate)
	{
		unsigned int i = 0;

		for(auto t: baseTypes::tRankRange())
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
		unsigned int i = (int)(baseTypes::tRank::two);

		for(auto t: baseTypes::tRankRange(baseTypes::tRank::two,baseTypes::tRank::five))
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
		unsigned int i = (int)(baseTypes::tRank::one);

		for(auto t: baseTypes::tRankRange(baseTypes::tRank::one,baseTypes::tRank::two))
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
		unsigned int i = (int)(baseTypes::tRank::seven);

		for(auto t: baseTypes::tRankRange(baseTypes::tRank::seven,baseTypes::tRank::seven))
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
		unsigned int i = (int)(baseTypes::tRank::seven);

		for(auto t: baseTypes::tRankRange(baseTypes::tRank::seven,baseTypes::tRank::six))
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
		unsigned int i = (int)(baseTypes::tRank::eight);

		for(auto t: baseTypes::tRankRange(baseTypes::tRank::eight,baseTypes::tRank::one))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}
	
	
	
	TEST(tRank, iterateNeg)
	{
		int i = 7;
		unsigned int count = 0;

		for(auto t: baseTypes::tRankNegativeRange())
		{
			ASSERT_EQ((unsigned int)t, i );
			--i;
			++count;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 8u);
	}
	
	TEST(tRank, iterateNegRange0)
	{

		unsigned int count = 0;
		unsigned int i = (int)(baseTypes::tRank::five);

		for(auto t: baseTypes::tRankNegativeRange(baseTypes::tRank::two,baseTypes::tRank::five))
		{
			ASSERT_EQ((unsigned int)t, i );
			--i;
			++count;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 4u);
	}

	TEST(tRank, iterateNegRange1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(baseTypes::tRank::two);

		for(auto t: baseTypes::tRankNegativeRange(baseTypes::tRank::one,baseTypes::tRank::two))
		{
			ASSERT_EQ((unsigned int)t, i );
			--i;
			++count;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 2u);
	}

	
	TEST(tRank, iterateNegRange2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(baseTypes::tRank::seven);

		for(auto t: baseTypes::tRankNegativeRange(baseTypes::tRank::seven,baseTypes::tRank::seven))
		{
			ASSERT_EQ((unsigned int)t, i );
			--i;
			++count;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 1u);
	}

	TEST(tRank, iterateNegRangeNeg1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(baseTypes::tRank::seven);

		for(auto t: baseTypes::tRankNegativeRange(baseTypes::tRank::seven,baseTypes::tRank::six))
		{
			ASSERT_EQ((unsigned int)t, i );
			--i;
			++count;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}

	TEST(tRank, iterateNegRangeNeg2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(baseTypes::tRank::eight);

		for(auto t: baseTypes::tRankNegativeRange(baseTypes::tRank::eight,baseTypes::tRank::one))
		{
			ASSERT_EQ((unsigned int)t, i );
			--i;
			++count;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}
	
	
	
	TEST(tRank, to_string)
	{
		baseTypes::tRank f = baseTypes::tRank::two;
		ASSERT_STREQ( "2", to_string(f).c_str() );
	}
	
	TEST(tRank, distance)
	{
		baseTypes::tRank f = baseTypes::tRank::seven;
		baseTypes::tRank g = baseTypes::tRank::seven;
		ASSERT_EQ( 0, distance( f,g ));
		
		f = baseTypes::tRank::one;
		g = baseTypes::tRank::four;
		ASSERT_EQ( 3, distance( f,g ));
		
		f = baseTypes::tRank::four;
		g = baseTypes::tRank::one;
		ASSERT_EQ( 3, distance( f,g ));
	}

	TEST(tSquare, assign)
	{
		baseTypes::tSquare t;
		t = baseTypes::tSquare::C3;
		ASSERT_EQ(t, baseTypes::tSquare::C3);

		t = baseTypes::tSquare::A1;
		ASSERT_EQ(t, baseTypes::tSquare::A1);

		t = baseTypes::tSquare::F6;
		ASSERT_EQ(t, baseTypes::tSquare::F6);
	}

	
	TEST(tSquare, sum)
	{
		baseTypes::tSquare t1,t2;
		t1 = baseTypes::tSquare::C3;
		t2 = baseTypes::tSquare::north;
		ASSERT_EQ(t1+t2, baseTypes::tSquare::C4);

		t1 = baseTypes::tSquare::G7;
		t2 = baseTypes::tSquare::northEast;
		ASSERT_EQ(t1+t2, baseTypes::tSquare::H8);

		t1 = baseTypes::tSquare::E4;
		t2 = baseTypes::tSquare::east;
		ASSERT_EQ(t1+t2, baseTypes::tSquare::F4);

		t1 = baseTypes::tSquare::D2;
		t2 = baseTypes::tSquare::sudEast;
		ASSERT_EQ(t1+t2, baseTypes::tSquare::E1);

		t1 = baseTypes::tSquare::B2;
		t2 = baseTypes::tSquare::sud;
		ASSERT_EQ(t1+t2, baseTypes::tSquare::B1);

		t1 = baseTypes::tSquare::D2;
		t2 = baseTypes::tSquare::sudOvest;
		ASSERT_EQ(t1+t2, baseTypes::tSquare::C1);

		t1 = baseTypes::tSquare::B4;
		t2 = baseTypes::tSquare::ovest;
		ASSERT_EQ(t1+t2, baseTypes::tSquare::A4);

		t1 = baseTypes::tSquare::H5;
		t2 = baseTypes::tSquare::northOvest;
		ASSERT_EQ(t1+t2, baseTypes::tSquare::G6);
	}
	
	TEST(tSquare, sum2)
	{
		baseTypes::tSquare t;
		t = baseTypes::tSquare::C3;
		t += baseTypes::tSquare::north;
		ASSERT_EQ(baseTypes::tSquare::C4, t );
	}
	
	TEST(tSquare, subtracion)
	{
		baseTypes::tSquare t= baseTypes::tSquare::F6;
		ASSERT_EQ(baseTypes::tSquare::F5, t - baseTypes::tSquare::north );
	}

	TEST(tSquare, subtracion2)
	{
		baseTypes::tSquare t= baseTypes::tSquare::F6;
		t -= baseTypes::tSquare::north;
		ASSERT_EQ(t, baseTypes::tSquare::F5);
	}

	TEST(tSquare, multiply)
	{
		baseTypes::tSquare t= baseTypes::tSquare::A1;
		t += 5*baseTypes::tSquare::north;
		ASSERT_EQ(t, baseTypes::tSquare::A6);
	}
	
	TEST(tSquare, multiply2)
	{
		baseTypes::tSquare t= baseTypes::tSquare::A1;
		t += baseTypes::tSquare::north * 5;
		ASSERT_EQ(t, baseTypes::tSquare::A6);
	}
	
	TEST(tSquare, tSquareIncrement)
	{
		baseTypes::tSquare f = baseTypes::tSquare::E4;
		ASSERT_EQ( baseTypes::tSquare::E4, f++ );
		ASSERT_EQ( baseTypes::tSquare::F4, f );
		ASSERT_EQ( baseTypes::tSquare::G4, ++f );
		ASSERT_EQ( baseTypes::tSquare::G4, f );
		
	}
	
	TEST(tSquare, tSquareDecrement)
	{
		baseTypes::tSquare f = baseTypes::tSquare::E4;
		ASSERT_EQ( baseTypes::tSquare::E4, f-- );
		ASSERT_EQ( baseTypes::tSquare::D4, f );
		ASSERT_EQ( baseTypes::tSquare::C4, --f );
		ASSERT_EQ( baseTypes::tSquare::C4, f );
		
	}

	TEST(tSquare, iterate)
	{
		unsigned int i = 0;

		for(auto t: baseTypes::tSquareRange())
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
		unsigned int i = (int)(baseTypes::tSquare::E2);

		for(auto t: baseTypes::tSquareRange(baseTypes::tSquare::E2,baseTypes::tSquare::B6))
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
		unsigned int i = (int)(baseTypes::tSquare::E2);

		for(auto t: baseTypes::tSquareRange(baseTypes::tSquare::E2,baseTypes::tSquare::F2))
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
		unsigned int i = (int)(baseTypes::tSquare::E2);

		for(auto t: baseTypes::tSquareRange(baseTypes::tSquare::E2,baseTypes::tSquare::E2))
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
		unsigned int i = (int)(baseTypes::tSquare::E2);

		for(auto t: baseTypes::tSquareRange(baseTypes::tSquare::E2,baseTypes::tSquare::D2))
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
		unsigned int i = (int)(baseTypes::tSquare::E2);

		for(auto t: baseTypes::tSquareRange(baseTypes::tSquare::E2,baseTypes::tSquare::A1))
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
		baseTypes::tSquare t = baseTypes::tSquare::A2;
		ASSERT_EQ(getFile(t),baseTypes::tFile::A);
		ASSERT_EQ(getRank(t),baseTypes::tRank::two);
		ASSERT_EQ(getColor(t),baseTypes::tColor::white);

		t = baseTypes::tSquare::F6;
		ASSERT_EQ(getFile(t),baseTypes::tFile::F);
		ASSERT_EQ(getRank(t),baseTypes::tRank::six);
		ASSERT_EQ(getColor(t),baseTypes::tColor::black);
			
		t = baseTypes::tSquare::G8;
		ASSERT_EQ(getFile(t),baseTypes::tFile::G);
		ASSERT_EQ(getRank(t),baseTypes::tRank::eight);
		ASSERT_EQ(getColor(t),baseTypes::tColor::white);
		
		t = baseTypes::tSquare::D4;
		ASSERT_EQ(getFile(t),baseTypes::tFile::D);
		ASSERT_EQ(getRank(t),baseTypes::tRank::four);
		ASSERT_EQ(getColor(t),baseTypes::tColor::black);
		
		t = baseTypes::tSquare::D5;
		ASSERT_EQ(getFile(t),baseTypes::tFile::D);
		ASSERT_EQ(getRank(t),baseTypes::tRank::five);
		ASSERT_EQ(getColor(t),baseTypes::tColor::white);
		
		t = baseTypes::tSquare::E4;
		ASSERT_EQ(getFile(t),baseTypes::tFile::E);
		ASSERT_EQ(getRank(t),baseTypes::tRank::four);
		ASSERT_EQ(getColor(t),baseTypes::tColor::white);
		
		t = baseTypes::tSquare::E5;
		ASSERT_EQ(getFile(t),baseTypes::tFile::E);
		ASSERT_EQ(getRank(t),baseTypes::tRank::five);
		ASSERT_EQ(getColor(t),baseTypes::tColor::black);
		
		
	}

	TEST(tSquare, to_string)
	{
		baseTypes::tSquare t = baseTypes::tSquare::A2;

		ASSERT_EQ(to_string(getFile(t)),std::string("a"));
		ASSERT_EQ(to_string(getRank(t)),std::string("2"));
		ASSERT_EQ(to_string(t),std::string("a2"));

		t = baseTypes::tSquare::F6;
		ASSERT_EQ( to_string( getFile(t) ), std::string("f") );
		ASSERT_EQ( to_string( getRank(t) ), std::string("6") );
		ASSERT_EQ( to_string( t ),std::string("f6"));

	}

	TEST(tSquare, gettSquareFromFileRank)
	{
		ASSERT_EQ( getSquareFromFileRank( baseTypes::tFile::A, baseTypes::tRank::six ), baseTypes::tSquare::A6 );
		ASSERT_EQ( getSquareFromFileRank( baseTypes::tFile::F, baseTypes::tRank::two ), baseTypes::tSquare::F2 );
		ASSERT_EQ( getSquareFromFileRank( baseTypes::tFile::A, baseTypes::tRank::one ), baseTypes::tSquare::A1 );
		ASSERT_EQ( getSquareFromFileRank( baseTypes::tFile::H, baseTypes::tRank::eight ), baseTypes::tSquare::H8 );
		ASSERT_EQ( getSquareFromFileRank( baseTypes::tFile::G, baseTypes::tRank::three ), baseTypes::tSquare::G3 );
		ASSERT_EQ( getSquareFromFileRank( baseTypes::tFile::C, baseTypes::tRank::seven ), baseTypes::tSquare::C7 );

	}

	TEST(tSquare, distance)
	{
		ASSERT_EQ( distance( baseTypes::tSquare::A1, baseTypes::tSquare::H8 ), 7u );
		ASSERT_EQ( distance( baseTypes::tSquare::H8, baseTypes::tSquare::A1 ), 7u );
		ASSERT_EQ( distance( baseTypes::tSquare::F6, baseTypes::tSquare::F6 ), 0u );
		ASSERT_EQ( distance( baseTypes::tSquare::F4, baseTypes::tSquare::F7 ), 3u );
		ASSERT_EQ( distance( baseTypes::tSquare::D4, baseTypes::tSquare::F7 ), 3u );
		ASSERT_EQ( distance( baseTypes::tSquare::F7, baseTypes::tSquare::D4 ), 3u );
		ASSERT_EQ( distance( baseTypes::tSquare::D4, baseTypes::tSquare::D5 ), 1u );
		ASSERT_EQ( distance( baseTypes::tSquare::D4, baseTypes::tSquare::E4 ), 1u );
	}
	
	TEST(tColor, assign)
	{
		baseTypes::tColor c = baseTypes::tColor::white;
		ASSERT_EQ(baseTypes::tColor::white, c);
		
		c = baseTypes::tColor::black;
		ASSERT_EQ(baseTypes::tColor::black, c);
	}
	
}


