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
#include <iostream>

#include "Vajolet.h"
#include "tSquare.h"
#include "BitMap.h"
#include "HashKeys.h"
#include "Position.h"

static void setIoBuffers()
{
	std::cout.rdbuf()->pubsetbuf( nullptr, 0 );
	std::cin.rdbuf()->pubsetbuf( nullptr, 0 );
}

static void init(void)
{
	libChess::inittSquare();
	libChess::BitMap::init();
	libChess::HashKey::init();
}

int main(void)
{
	setIoBuffers();
	init();
	libChess::Position p;
	p.setupFromFen("8/5p1k/6p1/1p5p/1P1Q3P/2P2PP1/5K2/3q4 b - - 6 59");
	std::cout<<p.display()<<std::endl;

	return 0;
}




