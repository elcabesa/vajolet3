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
#include "./../tSquare.h"
#include "./../Position.h"
#include "./../MoveGenerator.h"





using namespace libChess;

namespace {
	
	TEST(Position, constructor)
	{
		Position p;
		Position p2(p);
		ASSERT_EQ( 1, p2.getStateSize() );
	}
	
	TEST(Position, test)
	{
		Position p;
		p.setupFromFen();
		Move m1(baseTypes::tSquare::E2, baseTypes::tSquare::E4);
		Move m2(baseTypes::tSquare::D7, baseTypes::tSquare::D5);
		Move m3(baseTypes::tSquare::E4, baseTypes::tSquare::D5);
		p.doMove(m1);
		ASSERT_STREQ( "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1", p.getFen().c_str() );
		p.doMove(m2);
		ASSERT_STREQ( "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2", p.getFen().c_str() );
		p.doMove(m3);
		ASSERT_STREQ( "rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2", p.getFen().c_str() );
	}
	
	TEST(Position, getMvvLvaScore)
	{
		Position p;
		p.setupFromFen();
		Score pxp = p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::A7 ) );
		Score pxn = p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::B8 ) );
		Score pxb = p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::C8 ) );
		Score pxr = p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::A8 ) );
		Score pxq = p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::D8 ) );
		Score pxk = p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::E8 ) );
		
		Score nxp = p.getMvvLvaScore( Move( baseTypes::B1, baseTypes::A7 ) );
		Score nxn = p.getMvvLvaScore( Move( baseTypes::B1, baseTypes::B8 ) );
		Score nxb = p.getMvvLvaScore( Move( baseTypes::B1, baseTypes::C8 ) );
		Score nxr = p.getMvvLvaScore( Move( baseTypes::B1, baseTypes::A8 ) );
		Score nxq = p.getMvvLvaScore( Move( baseTypes::B1, baseTypes::D8 ) );
		Score nxk = p.getMvvLvaScore( Move( baseTypes::B1, baseTypes::E8 ) );
		
		Score bxp = p.getMvvLvaScore( Move( baseTypes::C1, baseTypes::A7 ) );
		Score bxn = p.getMvvLvaScore( Move( baseTypes::C1, baseTypes::B8 ) );
		Score bxb = p.getMvvLvaScore( Move( baseTypes::C1, baseTypes::C8 ) );
		Score bxr = p.getMvvLvaScore( Move( baseTypes::C1, baseTypes::A8 ) );
		Score bxq = p.getMvvLvaScore( Move( baseTypes::C1, baseTypes::D8 ) );
		Score bxk = p.getMvvLvaScore( Move( baseTypes::C1, baseTypes::E8 ) );
		
		Score rxp = p.getMvvLvaScore( Move( baseTypes::A1, baseTypes::A7 ) );
		Score rxn = p.getMvvLvaScore( Move( baseTypes::A1, baseTypes::B8 ) );
		Score rxb = p.getMvvLvaScore( Move( baseTypes::A1, baseTypes::C8 ) );
		Score rxr = p.getMvvLvaScore( Move( baseTypes::A1, baseTypes::A8 ) );
		Score rxq = p.getMvvLvaScore( Move( baseTypes::A1, baseTypes::D8 ) );
		Score rxk = p.getMvvLvaScore( Move( baseTypes::A1, baseTypes::E8 ) );
		
		Score qxp = p.getMvvLvaScore( Move( baseTypes::D1, baseTypes::A7 ) );
		Score qxn = p.getMvvLvaScore( Move( baseTypes::D1, baseTypes::B8 ) );
		Score qxb = p.getMvvLvaScore( Move( baseTypes::D1, baseTypes::C8 ) );
		Score qxr = p.getMvvLvaScore( Move( baseTypes::D1, baseTypes::A8 ) );
		Score qxq = p.getMvvLvaScore( Move( baseTypes::D1, baseTypes::D8 ) );
		Score qxk = p.getMvvLvaScore( Move( baseTypes::D1, baseTypes::E8 ) );
		
		Score kxp = p.getMvvLvaScore( Move( baseTypes::E1, baseTypes::A7 ) );
		Score kxn = p.getMvvLvaScore( Move( baseTypes::E1, baseTypes::B8 ) );
		Score kxb = p.getMvvLvaScore( Move( baseTypes::E1, baseTypes::C8 ) );
		Score kxr = p.getMvvLvaScore( Move( baseTypes::E1, baseTypes::A8 ) );
		Score kxq = p.getMvvLvaScore( Move( baseTypes::E1, baseTypes::D8 ) );
		Score kxk = p.getMvvLvaScore( Move( baseTypes::E1, baseTypes::E8 ) );

		ASSERT_GT( pxk, nxk );
		ASSERT_GT( nxk, bxk );
		ASSERT_GT( bxk, rxk );
		ASSERT_GT( rxk, qxk );
		ASSERT_GT( qxk, kxk );
		
		ASSERT_GT( kxk, pxq );
		
		ASSERT_GT( pxq, nxq );
		ASSERT_GT( nxq, bxq );
		ASSERT_GT( bxq, rxq );
		ASSERT_GT( rxq, qxq );
		ASSERT_GT( qxq, kxq );
		
		ASSERT_GT( kxq, pxr );
		
		ASSERT_GT( pxr, nxr );
		ASSERT_GT( nxr, bxr );
		ASSERT_GT( bxr, rxr );
		ASSERT_GT( rxr, qxr );
		ASSERT_GT( qxr, kxr );
		
		ASSERT_GT( kxr, pxb );
		
		ASSERT_GT( pxb, nxb );
		ASSERT_GT( nxb, bxb );
		ASSERT_GT( bxb, rxb );
		ASSERT_GT( rxb, qxb );
		ASSERT_GT( qxb, kxb );
		
		ASSERT_GT( kxb, pxn );
		
		ASSERT_GT( pxn, nxn );
		ASSERT_GT( nxn, bxn );
		ASSERT_GT( bxn, rxn );
		ASSERT_GT( rxn, qxn );
		ASSERT_GT( qxn, kxn );
		
		ASSERT_GT( kxn, pxp );
		
		ASSERT_GT( pxp, nxp );
		ASSERT_GT( nxp, bxp );
		ASSERT_GT( bxp, rxp );
		ASSERT_GT( rxp, qxp );
		ASSERT_GT( qxp, kxp );
		
		// test equality
		ASSERT_EQ( p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::A7 ) ), p.getMvvLvaScore( Move( baseTypes::F2, baseTypes::G7 ) ) );
		ASSERT_EQ( p.getMvvLvaScore( Move( baseTypes::A1, baseTypes::G8 ) ), p.getMvvLvaScore( Move( baseTypes::H1, baseTypes::G8 ) ) );
		
		// test en passant
		ASSERT_EQ( p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::A7 ) ), p.getMvvLvaScore( Move( baseTypes::A2, baseTypes::G6, Move::fenpassant ) ) );
	
		
	}
	
	TEST(Position, getMvvLvaScore2)
	{
		Position p;
		p.setupFromFen();
		Score pxp = p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::A2 ) );
		Score pxn = p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::B1 ) );
		Score pxb = p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::C1 ) );
		Score pxr = p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::A1 ) );
		Score pxq = p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::D1 ) );
		Score pxk = p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::E1 ) );
		
		Score nxp = p.getMvvLvaScore( Move( baseTypes::B8, baseTypes::A2 ) );
		Score nxn = p.getMvvLvaScore( Move( baseTypes::B8, baseTypes::B1 ) );
		Score nxb = p.getMvvLvaScore( Move( baseTypes::B8, baseTypes::C1 ) );
		Score nxr = p.getMvvLvaScore( Move( baseTypes::B8, baseTypes::A1 ) );
		Score nxq = p.getMvvLvaScore( Move( baseTypes::B8, baseTypes::D1 ) );
		Score nxk = p.getMvvLvaScore( Move( baseTypes::B8, baseTypes::E1 ) );
		
		Score bxp = p.getMvvLvaScore( Move( baseTypes::C8, baseTypes::A2 ) );
		Score bxn = p.getMvvLvaScore( Move( baseTypes::C8, baseTypes::B1 ) );
		Score bxb = p.getMvvLvaScore( Move( baseTypes::C8, baseTypes::C1 ) );
		Score bxr = p.getMvvLvaScore( Move( baseTypes::C8, baseTypes::A1 ) );
		Score bxq = p.getMvvLvaScore( Move( baseTypes::C8, baseTypes::D1 ) );
		Score bxk = p.getMvvLvaScore( Move( baseTypes::C8, baseTypes::E1 ) );
		
		Score rxp = p.getMvvLvaScore( Move( baseTypes::A8, baseTypes::A2 ) );
		Score rxn = p.getMvvLvaScore( Move( baseTypes::A8, baseTypes::B1 ) );
		Score rxb = p.getMvvLvaScore( Move( baseTypes::A8, baseTypes::C1 ) );
		Score rxr = p.getMvvLvaScore( Move( baseTypes::A8, baseTypes::A1 ) );
		Score rxq = p.getMvvLvaScore( Move( baseTypes::A8, baseTypes::D1 ) );
		Score rxk = p.getMvvLvaScore( Move( baseTypes::A8, baseTypes::E1 ) );
		
		Score qxp = p.getMvvLvaScore( Move( baseTypes::D8, baseTypes::A2 ) );
		Score qxn = p.getMvvLvaScore( Move( baseTypes::D8, baseTypes::B1 ) );
		Score qxb = p.getMvvLvaScore( Move( baseTypes::D8, baseTypes::C1 ) );
		Score qxr = p.getMvvLvaScore( Move( baseTypes::D8, baseTypes::A1 ) );
		Score qxq = p.getMvvLvaScore( Move( baseTypes::D8, baseTypes::D1 ) );
		Score qxk = p.getMvvLvaScore( Move( baseTypes::D8, baseTypes::E1 ) );
		
		Score kxp = p.getMvvLvaScore( Move( baseTypes::E8, baseTypes::A2 ) );
		Score kxn = p.getMvvLvaScore( Move( baseTypes::E8, baseTypes::B1 ) );
		Score kxb = p.getMvvLvaScore( Move( baseTypes::E8, baseTypes::C1 ) );
		Score kxr = p.getMvvLvaScore( Move( baseTypes::E8, baseTypes::A1 ) );
		Score kxq = p.getMvvLvaScore( Move( baseTypes::E8, baseTypes::D1 ) );
		Score kxk = p.getMvvLvaScore( Move( baseTypes::E8, baseTypes::E1 ) );

		ASSERT_GT( pxk, nxk );
		ASSERT_GT( nxk, bxk );
		ASSERT_GT( bxk, rxk );
		ASSERT_GT( rxk, qxk );
		ASSERT_GT( qxk, kxk );
		
		ASSERT_GT( kxk, pxq );
		
		ASSERT_GT( pxq, nxq );
		ASSERT_GT( nxq, bxq );
		ASSERT_GT( bxq, rxq );
		ASSERT_GT( rxq, qxq );
		ASSERT_GT( qxq, kxq );
		
		ASSERT_GT( kxq, pxr );
		
		ASSERT_GT( pxr, nxr );
		ASSERT_GT( nxr, bxr );
		ASSERT_GT( bxr, rxr );
		ASSERT_GT( rxr, qxr );
		ASSERT_GT( qxr, kxr );
		
		ASSERT_GT( kxr, pxb );
		
		ASSERT_GT( pxb, nxb );
		ASSERT_GT( nxb, bxb );
		ASSERT_GT( bxb, rxb );
		ASSERT_GT( rxb, qxb );
		ASSERT_GT( qxb, kxb );
		
		ASSERT_GT( kxb, pxn );
		
		ASSERT_GT( pxn, nxn );
		ASSERT_GT( nxn, bxn );
		ASSERT_GT( bxn, rxn );
		ASSERT_GT( rxn, qxn );
		ASSERT_GT( qxn, kxn );
		
		ASSERT_GT( kxn, pxp );
		
		ASSERT_GT( pxp, nxp );
		ASSERT_GT( nxp, bxp );
		ASSERT_GT( bxp, rxp );
		ASSERT_GT( rxp, qxp );
		ASSERT_GT( qxp, kxp );
		
		// test equality
		ASSERT_EQ( p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::A2 ) ), p.getMvvLvaScore( Move( baseTypes::F7, baseTypes::G2 ) ) );
		ASSERT_EQ( p.getMvvLvaScore( Move( baseTypes::A8, baseTypes::G1 ) ), p.getMvvLvaScore( Move( baseTypes::H8, baseTypes::G1 ) ) );
		
		// test en passant
		ASSERT_EQ( p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::A2 ) ), p.getMvvLvaScore( Move( baseTypes::A7, baseTypes::G3, Move::fenpassant ) ) );
	
		
	}
    
    void testIsLegal( libChess::MoveList< libChess::MoveGenerator::maxMovePerPosition >& ml, const Move& m, const Position& pos)
    {
        if( std::find( ml.begin(), ml.end(), m ) != ml.end() )
        {
            if( !pos.isMoveLegal( m ) )
            {
                std::cout<< pos.display() <<std::endl;
                std::cout<< m.to_string(true) << std::endl;
            }
            ASSERT_TRUE( pos.isMoveLegal( m ) );
        }
        else
        {
            if( pos.isMoveLegal( m ) )
            {
                std::cout<< pos.display() <<std::endl;
                std::cout<< m.to_string(true) << std::endl;
            }
            ASSERT_FALSE( pos.isMoveLegal( m ) );
        }
    }

	TEST(Position, isMoveLegal)
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
			
			libChess::MoveList< libChess::MoveGenerator::maxMovePerPosition > ml;
			libChess::MoveGenerator::generateMoves< libChess::MoveGenerator::allMg >( pos, ml );

			for( auto from: baseTypes::tSquareRange() )
			{
				for( auto to: baseTypes::tSquareRange() )
				{
					
                    testIsLegal( ml, Move( from, to ), pos);
                    
                    testIsLegal( ml, Move( from, to, Move::fenpassant ), pos);
                    
                    testIsLegal( ml, Move( from, to, Move::fcastle ), pos);

                    Move m( from, to, Move::fpromotion);
                    for( int i = Move::promQueen; i <= Move::promKnight; ++i )
                    {
                        m.setPromotion( Move::epromotion( i ) );
                        testIsLegal( ml, m, pos);
                    }

				}
                
			}

		}
	}
}
