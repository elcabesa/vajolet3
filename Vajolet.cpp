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

	/*if (depth == 0) {
		return 1;
	}*/

	unsigned long long tot = 0;
	libChess::MoveSelector ms( pos );
	if (depth == 1)
	{
		return ms.getMoveList().size();
	}
	
	for( auto& m: ms.getMoveList() )
	{	
		/*for( unsigned int i=0;i< pos.getStateSize();i++)
		{
			std::cout<<(pos.getState(i).getCurrentMove().to_string())<<std::endl;
		}*/

		//std::cout<<"do move "<<m.to_string()<<std::endl;
		//std::cout<<"do"<<std::endl;
		pos.doMove(m);
		tot += perft( pos, depth - 1);
		//std::cout<<"undo move "<<m.to_string()<<std::endl;
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
	/*if (depth == 1) {
		std::cout<<pos.display()<<std::endl;
		for( auto m: ms.getMoveList())
		{
			std::cout<<m.to_string()<<std::endl;
		}
		return ms.getMoveList().size();
	}
	*/
	for( auto& m: ms.getMoveList() )
	{
		std::cout<<"un move "<<m.to_string()<<std::endl;
		pos.doMove(m);
		unsigned long long int n = perft( pos, depth - 1);
		tot += n;
		std::cout<<"undo move "<<m.to_string()<<std::endl;
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
	int i = 0;
	while(true)
	{
		long long int start = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
		unsigned long long res = perft(pos, i+1);
		long long int end = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
		std::cout<<(++i)<<": "<<res<<" ("<<res/1000.0/(end-start) <<"Mnps)"<<std::endl;
		
	}
	/*pos.setupFromFen("r1k1r2q/p1ppp1pp/8/8/8/8/P1PPP1PP/R1K1R2Q w KQkq - 0 1");
	std::cout<<perft(pos, 1)<<std::endl;
	std::cout<<perft(pos, 2)<<std::endl;
	std::cout<<perft(pos, 3)<<std::endl;
	std::cout<<perft(pos, 4)<<std::endl;
	std::cout<<perft(pos, 5)<<std::endl;
	std::cout<<perft(pos, 6)<<std::endl;
	std::cout<<perft(pos, 7)<<std::endl;
	
	pos.setupFromFen("r1k2r1q/p1ppp1pp/8/8/8/8/P1PPP1PP/R1K2R1Q w KQkq - 0 1 ");
	
	std::cout<<perft(pos, 1)<<std::endl;
	std::cout<<perft(pos, 2)<<std::endl;
	std::cout<<perft(pos, 3)<<std::endl;
	std::cout<<perft(pos, 4)<<std::endl;
	std::cout<<perft(pos, 5)<<std::endl;
	std::cout<<perft(pos, 6)<<std::endl;
	std::cout<<perft(pos, 7)<<std::endl;
	
	pos.setupFromFen("8/8/8/4B2b/6nN/8/5P2/2R1K2k w Q - 0 1");
	
	std::cout<<perft(pos, 1)<<std::endl;
	std::cout<<perft(pos, 2)<<std::endl;
	std::cout<<perft(pos, 3)<<std::endl;
	std::cout<<perft(pos, 4)<<std::endl;
	std::cout<<perft(pos, 5)<<std::endl;
	std::cout<<perft(pos, 6)<<std::endl;
	std::cout<<perft(pos, 7)<<std::endl;
	
	pos.setupFromFen("2r5/8/8/8/8/8/6PP/k2KR3 w K - 0 1");
	
	std::cout<<perft(pos, 1)<<std::endl;
	std::cout<<perft(pos, 2)<<std::endl;
	std::cout<<perft(pos, 3)<<std::endl;
	std::cout<<perft(pos, 4)<<std::endl;
	std::cout<<perft(pos, 5)<<std::endl;
	std::cout<<perft(pos, 6)<<std::endl;
	std::cout<<perft(pos, 7)<<std::endl;
	
	pos.setupFromFen("4r3/3k4/8/8/8/8/6PP/qR1K1R2 w KQ - 0 1");
	
	std::cout<<perft(pos, 1)<<std::endl;
	std::cout<<perft(pos, 2)<<std::endl;
	std::cout<<perft(pos, 3)<<std::endl;
	std::cout<<perft(pos, 4)<<std::endl;
	std::cout<<perft(pos, 5)<<std::endl;
	std::cout<<perft(pos, 6)<<std::endl;
	std::cout<<perft(pos, 7)<<std::endl;*/
	
	return 0;
}




