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
#include "./../MoveSelector.h"
#include "./../Position.h"




using namespace libChess;


namespace {
	
	TEST(MoveGenerator,mg0)
	{
		Position pos;
		pos.setupFromFen();
		
		MoveList< MoveSelector::maxMovePerPosition > ml;
		MoveGenerator::generateMoves< MoveGenerator::allMg >( pos, ml );

		ASSERT_EQ( 20, ml.size() );
	}
	
	TEST(MoveGenerator,mg1)
	{
		Position pos;
		pos.setupFromFen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
		
		MoveList< MoveSelector::maxMovePerPosition > ml;
		MoveGenerator::generateMoves< MoveGenerator::allMg >( pos, ml );

		ASSERT_EQ( 48, ml.size() );
	}
	
	TEST(MoveGenerator,mg2)
	{
		Position pos;
		pos.setupFromFen("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
		
		MoveList< MoveSelector::maxMovePerPosition > ml;
		MoveGenerator::generateMoves< MoveGenerator::allMg >( pos, ml );

		ASSERT_EQ( 14, ml.size() );
	}
	
	TEST(MoveGenerator,mg3)
	{
		Position pos;
		pos.setupFromFen("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
		
		MoveList< MoveSelector::maxMovePerPosition > ml;
		MoveGenerator::generateMoves< MoveGenerator::allMg >( pos, ml );

		ASSERT_EQ( 6, ml.size() );
	}
	
	TEST(MoveGenerator,mg4)
	{
		Position pos;
		pos.setupFromFen("r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1");
		
		MoveList< MoveSelector::maxMovePerPosition > ml;
		MoveGenerator::generateMoves< MoveGenerator::allMg >( pos, ml );

		ASSERT_EQ( 6, ml.size() );
	}
	
	TEST(MoveGenerator,mg5)
	{
		Position pos;
		pos.setupFromFen("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
		
		MoveList< MoveSelector::maxMovePerPosition > ml;
		MoveGenerator::generateMoves< MoveGenerator::allMg >( pos, ml );

		ASSERT_EQ( 44, ml.size() );
	}
	
	TEST(MoveGenerator,mg6)
	{
		Position pos;
		pos.setupFromFen("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
		
		MoveList< MoveSelector::maxMovePerPosition > ml;
		MoveGenerator::generateMoves< MoveGenerator::allMg >( pos, ml );

		ASSERT_EQ( 46, ml.size() );
	}
	
typedef struct _positions
{
     const std::string Fen;
     const std::vector<unsigned long long> PerftValue;
}positions;

static const std::vector<positions> perftPos ={
	{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", {20ull, 400ull, 8902ull, 197281ull, 4865609ull, 119060324ull}},
	{"r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1", {48ull, 2039ull, 97862ull, 4085603ull, 193690690ull, 8031647685ull}},
	{"8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1", {14ull, 191ull, 2812ull, 43238ull, 674624ull, 11030083ull, 178633661ull}},
	{"r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1", {6ull, 264ull, 9467ull, 422333ull, 15833292ull, 706045033ull }},
	{"r2q1rk1/pP1p2pp/Q4n2/bbp1p3/Np6/1B3NBn/pPPP1PPP/R3K2R b KQ - 0 1", {6ull, 264ull, 9467ull, 422333ull, 15833292ull, 706045033ull }},
	{"rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8", {44ull, 1486ull, 62379ull, 2103487ull, 89941194ull }},
	{"r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10", {46ull, 2079ull, 89890ull, 3894594ull, 164075551ull, 6923051137ull }}
	
};
	unsigned long long perft(Position& pos, unsigned int depth)
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
        while( Move::NOMOVE != ( m = ms.getNextMove() ) )
		{
			pos.doMove(m);
			tot += perft( pos, depth - 1);
			pos.undoMove();
		}
		return tot;

	}
	
	TEST(MoveGenerator,perft)
	{
		
		Position pos;
		
		for (auto & p : perftPos)
		{
			pos.setupFromFen( p.Fen ); 
			for( unsigned int i = 0; i < p.PerftValue.size() && i<2; i++)
			{
				unsigned long long int res = perft( pos, i+1);
				EXPECT_EQ( p.PerftValue[i], res);
			}
		}
	}
	

	
	TEST(MoveGenerator,perft2)
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
			while (found != std::string::npos && i < 2 )
			{	
				std::size_t start = found+1;
				found=line.find_first_of(",",found + 1 );
				
				unsigned long long ull = std::stoull (line.substr(start, found-start));
				unsigned long long int res = perft( pos, ++i);
				ASSERT_EQ(ull, res);
			}

		}
	}

	
}