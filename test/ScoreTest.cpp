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
#include "./../Score.h"

using namespace libChess;

namespace {
	
	TEST(Score,write_read1)
	{
		simdScore s = { 150, -65302 };
	    ASSERT_EQ( 150 ,s[0] );
		ASSERT_EQ( -65302 ,s[1] );
	}
	
	TEST(Score,write_read2)
	{
		simdScore s = { 2147483647, 2147483647 };
	    ASSERT_EQ( 2147483647 ,s[0] );
		ASSERT_EQ( 2147483647 ,s[1] );
	}
	
	TEST(Score,write_read3)
	{
		simdScore s = { -2147483648, -2147483648 };
	    ASSERT_EQ( -2147483648 ,s[0] );
		ASSERT_EQ( -2147483648 ,s[1] );
	}
	
	TEST(Score,write_read4)
	{
		simdScore s = { -2147483648, 2147483647 };
	    ASSERT_EQ( -2147483648 ,s[0] );
		ASSERT_EQ( 2147483647 ,s[1] );
	}
	
	TEST(Score,write_read5)
	{
		simdScore s = { 2147483647, -2147483648 };
	    ASSERT_EQ( 2147483647 ,s[0] );
		ASSERT_EQ( -2147483648 ,s[1] );
	}
	
	TEST(Score,sum)
	{
		simdScore s = { 32009, 45 };
		s += 100;
	    ASSERT_EQ( 32109 ,s[0] );
		ASSERT_EQ( 145 ,s[1] );
	}
	
	TEST(Score,sum2)
	{
		simdScore s = { 32009, 45 };
		simdScore s1 = { -34, 342 };
		s += s1;
	    ASSERT_EQ( 31975 ,s[0] );
		ASSERT_EQ( 387 ,s[1] );
	}
	
	TEST(Score,sub)
	{
		simdScore s = { 32009, 45 };
		s -= 1020;
	    ASSERT_EQ( 30989 ,s[0] );
		ASSERT_EQ( -975 ,s[1] );
	}
	
	TEST(Score,sub2)
	{
		simdScore s = { 32009, 45 };
		simdScore s1 = { 1020, 5045 };
		s -= s1;
	    ASSERT_EQ( 30989 ,s[0] );
		ASSERT_EQ( -5000 ,s[1] );
	}
	
	TEST(Score,overflow1)
	{
		simdScore s = { 32009, 2147483645 };
		simdScore s1 = { 0, 100 };
		s += s1;
	    ASSERT_EQ( 32009 ,s[0] );
		ASSERT_EQ( -2147483551 ,s[1] );
	}
	
	TEST(Score,overflow2)
	{
		simdScore s = { 2147483645, 32009  };
		simdScore s1 = { 100, 0 };
		s += s1;
	    ASSERT_EQ( 32009 ,s[1] );
		ASSERT_EQ( -2147483551 ,s[0] );
	}
	
	TEST(Score,multiply)
	{
		simdScore s = { 322, 277  };
		
		s = s * 8;
	    ASSERT_EQ( 2576 ,s[0] );
		ASSERT_EQ( 2216 ,s[1] );
	}
	
	TEST(Score,multiply2)
	{
		simdScore s = { 322, 277  };
		
		simdScore s1 = { 2, 3  };
		
		s = s * s1;
	    ASSERT_EQ( 644 ,s[0] );
		ASSERT_EQ( 831 ,s[1] );
	}
	
	// todo add sum che va fuori dai limiti
	
	
	
}