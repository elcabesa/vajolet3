/*
	This file is part of Vajolet.
	Copyright (C) 2013-2018 Marco Belli
	
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
#include "BitMap.h"
#include "HashKeys.h"
#include "BitMapMoveGenerator.h"


static void setIoBuffers()
{
	// todo why?? non ricordo perché e forse non serve
	std::cout.rdbuf()->pubsetbuf( nullptr, 0 );
	std::cin.rdbuf()->pubsetbuf( nullptr, 0 );
}

static void init(void)
{
	libChess::baseTypes::inittSquare();
	libChess::baseTypes::BitMap::init();
	libChess::HashKey::init();
	libChess::BitMapMoveGenerator::init();
}

int main(void)
{
	setIoBuffers();
	init();

	return 0;
}




