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

#include <chrono>
#include "MoveGenerator.h"
#include "Position.h"



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

/*! \brief calculate the perft result
	\author Marco Belli
	\version 1.0
	\date 08/11/2013
*/
unsigned long long perft(libChess::Position& pos, unsigned int depth)
{

	if (depth == 0) {
		return 1;
	}

	unsigned long long tot = 0;
	libChess::MoveList< libChess::MoveGenerator::maxMovePerPosition > ml;
	libChess::MoveGenerator::generateMoves< libChess::MoveGenerator::allMg >( pos, ml );
	if (depth == 1) {
		return ml.size();
	}
	
	for( auto& m: ml )
	{
		pos.doMove(m);
		tot += perft( pos, depth - 1);
		pos.undoMove();
	}
	return tot;

}

unsigned long long divide(libChess::Position& pos, unsigned int depth)
{

	if (depth == 0) {
		return 1;
	}

	unsigned long long tot = 0;
	libChess::MoveList< libChess::MoveGenerator::maxMovePerPosition > ml;
	libChess::MoveGenerator::generateMoves< libChess::MoveGenerator::allMg >( pos, ml );
	/*if (depth == 1) {
		std::cout<<pos.display()<<std::endl;
		for( auto m: ml)
		{
			std::cout<<m.to_string()<<std::endl;
		}
		return ml.size();
	}
	*/
	for( auto& m: ml )
	{
		pos.doMove(m);
		unsigned long long int n = perft( pos, depth - 1);
		tot += n;
		pos.undoMove();
		std::cout<<m.to_string()<<": "<<n<<std::endl;
	}
	return tot;

}



int main(void)
{
	setIoBuffers();
	init();
	
	libChess::Position pos;
	pos.setupFromFen("r2n3r/1bNk2pp/6P1/pP3p2/3pPqnP/1P1P1p1R/2P3B1/Q1B1bKN1 b - e3");
	
	
	std::cout<<divide(pos, 1)<<std::endl;
	
	return 0;
}




