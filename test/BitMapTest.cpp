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
		ASSERT_EQ( BitMap(0).firstOne(), tSquare::A1); // sure?? machine dependant??
		ASSERT_EQ( BitMap(1).firstOne(), tSquare::A1);
		ASSERT_EQ( BitMap(0x803000100C803008ull).firstOne(), tSquare::D1);
		ASSERT_EQ( BitMap(3458769736543240192ull).firstOne(), tSquare::D3);
		ASSERT_EQ( BitMap(0xFFFFFFFFFFFFFFFFull).firstOne(), tSquare::A1);

	}

}




