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
#include "MoveSelector.h"
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
	unsigned long long tot = 0;
	libChess::MoveSelector ms( pos );
	if (depth == 1)
	{
		return ms.getNumberOfLegalMoves();
	}
	libChess::Move m;
	while( libChess::Move::NOMOVE != ( m = ms.getNextMove() ) )
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
	libChess::MoveSelector ms( pos );

	libChess::Move m;
	while( libChess::Move::NOMOVE != ( m = ms.getNextMove() ) )
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
	pos.setupFromFen();
	int i = 1;
	while(true)
	{
		long long int start = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
		long long int tot = 0;
		tot = perft(pos,i++);
		long long int end = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
		std::cout<<(tot)<<" " <<(end-start) <<"ms "<<((end-start) !=0 ? (tot/(end-start)): 0 )<<" mps "<< std::endl;
	}
	
	
	
	return 0;
}




