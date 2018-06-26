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



static unsigned long long perft(libChess::Position& pos, unsigned int depth)
{
/*
    if (depth == 0) {
        return 1;
    }
*/
    unsigned long long tot = 0;
    
    if (depth == 1)
    {	
        return pos.getNumberOfLegalMoves();
    }
    
    libChess::MoveSelector ms( pos );
    libChess::Move m;
    while( libChess::Move::NOMOVE != ( m = ms.getNextMove() ) )
    {
        pos.doMove(m);
        tot += perft( pos, depth - 1);
        pos.undoMove();
    }
    return tot;

}


int main(void)
{
	setIoBuffers();	
	init();
	
	libChess::Position pos;
    pos.setupFromFen();
    /*//pos.setupFromFen("r2n3r/1bNk2pp/6P1/pP3p2/3pPqnP/1P1P1p1R/2P3B1/Q1B1bKN1 b - e3 0 1");
	//pos.setupFromFen("rn1q1bnr/3kppp1/2pp3p/pp6/1P2b3/2PQ1N1P/P2PPPB1/RNB1K2R w KQ - 0 1");
    std::cout<<pos.display()<<std::endl;
    libChess::MoveList< libChess::MoveGenerator::maxMovePerPosition > ml;
	libChess::MoveGenerator::generateMoves< libChess::MoveGenerator::allMg >( pos, ml );
    for( auto m : ml )
    {
        std::cout<<m.to_string(true)<<std::endl;
    }
    std::cout<<"move is valid " <<pos.isMoveLegal(libChess::Move(libChess::baseTypes::D4, libChess::baseTypes::E3, libChess::Move::fenpassant))<<std::endl;*/
    
    
    
	int i = 1;
	while(true)
	{
		long long int start = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
		long long int tot = 0;
		tot = perft(pos,/*i++*/6);
		long long int end = std::chrono::duration_cast<std::chrono::milliseconds >(std::chrono::steady_clock::now().time_since_epoch()).count();
		std::cout<<(tot)<<" " <<(end-start) <<"ms "<<((end-start) !=0 ? (tot/(end-start)): 0 )<<" mps "<< std::endl;
	}
	
	
	
	return 0;
}




