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
	libChess::baseTypes::inittSquare();
	libChess::baseTypes::BitMap::init();
	libChess::HashKey::init();
}

int main(void)
{
	setIoBuffers();
	init();
	
	libChess::Position p;
	p.setupFromFen("bnrqb1k1/pppppp1p/6p1/6N1/2BBP3/2Q5/PPP5/1K5R w - - 0 13");
	std::cout<<p.display()<<std::endl;

	return 0;
}




