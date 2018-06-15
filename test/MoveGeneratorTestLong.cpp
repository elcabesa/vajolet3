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

#include <fstream>
#include "gtest/gtest.h"
#include "./../MoveGenerator.h"
#include "./../Position.h"




using namespace libChess;


namespace {
	
	unsigned long long perft(libChess::Position& pos, unsigned int depth)
	{
	/*
		if (depth == 0) {
			return 1;
		}
	*/
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

	TEST(MoveGenerator,perft)
	{
		
		std::ifstream infile("perft.txt");
		
		ASSERT_FALSE(infile.fail());
		
		Position pos;
		
		std::string line;
		
		while (std::getline(infile, line))
		{
			std::size_t found = line.find_first_of(",");
			std::string fen = line.substr(0, found);
			pos.setupFromFen( fen ); 

			unsigned int i = 0;
			while (found != std::string::npos )
			{	
				std::size_t start = found+1;
				found=line.find_first_of(",",found + 1 );
				
				unsigned long long ull = std::stoull (line.substr(start, found-start));
				unsigned long long int res = perft( pos, ++i);
				std::cout<<res<<std::endl;
				ASSERT_EQ(ull, res);
			}

		}
	}

	
}