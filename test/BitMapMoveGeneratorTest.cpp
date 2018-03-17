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

#include <utility>
#include <vector>
#include "gtest/gtest.h"
#include "./../BitMapMoveGenerator.h"
using namespace libChess;
using namespace libChess::baseTypes;

namespace {
		
	static BitMap createBitMap(const std::vector< tSquare >& list)
	{
		BitMap ref;
		ref.clear();
		for (auto sq : list )
		{
			ref += sq;
		}
		return ref;
	}
	
	
	TEST(BitMapMoveGenerator,getKingMoves)
	{
		std::vector< std::pair< tSquare, std::vector< tSquare > > > testList = 
		{ 
			{ E4, { E5, F5, F4, F3, E3, D3, D4, D5 } },
			{ G2, { G3, H3, H2, H1, G1, F1, F2, F3 } },
			{ A1, { A2, B2, B1 } },
			{ A8, { A7, B7, B8 } },
			{ H1, { H2, G2, G1 } },
			{ H8, { H7, G7, G8 } },
			{ A5, { A6, B6, B5, B4, A4 } },
			{ F8, { E8, E7, F7, G7, G8 } }
		};
		
		
		for( const auto& it : testList )
		{
			const BitMap k = BitMapMoveGenerator::getKingMoves( it.first );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getKnightMoves)
	{
		std::vector< std::pair< tSquare, std::vector< tSquare > > > testList = 
		{ 
			{ E4, { D6, F6, G5, G3, D2, F2, C5, C3 } },
			{ G2, { F4, H4, E3, E1 } },
			{ A1, { B3, C2 } },
			{ A8, { B6, C7 } },
			{ H1, { G3, F2 } },
			{ H8, { G6, F7 } },
			{ A5, { B7, C6, C4, B3 } },
			{ F7, { H8, H6, G5, E5, D6, D8 } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap k = BitMapMoveGenerator::getKnightMoves( it.first );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getPawnAttackW)
	{
		std::vector< std::pair< tSquare, std::vector< tSquare > > > testList = 
		{ 
			{ E4, { D5, F5} },
			{ G2, { F3, H3} },
			{ A2, { B3 } },
			{ A7, { B8 } },
			{ H3, { G4 } },
			{ H7, { G8 } },
			{ A5, { B6 } },
			{ F7, { G8, E8 } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap k = BitMapMoveGenerator::getPawnAttack( it.first, tColor::white );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getPawnAttackB)
	{
		std::vector< std::pair< tSquare, std::vector< tSquare > > > testList = 
		{ 
			{ E4, { D3, F3} },
			{ G2, { F1, H1} },
			{ A2, { B1 } },
			{ A7, { B6 } },
			{ H3, { G2 } },
			{ H7, { G6 } },
			{ A5, { B4 } },
			{ F7, { G6, E6 } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap k = BitMapMoveGenerator::getPawnAttack( it.first, tColor::black );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getRookMoves0)
	{
		// empy occupancy test
		std::vector< std::pair< tSquare, std::vector< tSquare > > > testList = 
		{ 
			{ E4, { E1, E2, E3, E5, E6, E7, E8, A4, B4, C4, D4, F4, G4, H4 } },
			{ G2, { G1, G3, G4, G5, G6, G7, G8, A2, B2, C2, D2, E2, F2, H2 } },
			{ A2, { A1, A3, A4, A5, A6, A7, A8, B2, C2, D2, E2, F2, G2, H2 } },
			{ A7, { A1, A2, A3, A4, A5, A6, A8, B7, C7, D7, E7, F7, G7, H7 } },
			{ H3, { H1, H2, H4, H5, H6, H7, H8, A3, B3, C3, D3, E3, F3, G3 } },
			{ H7, { H1, H2, H3, H4, H5, H6, H8, A7, B7, C7, D7, E7, F7, G7 } },
			{ A5, { A1, A2, A3, A4, A6, A7, A8, B5, C5, D5, E5, F5, G5, H5 } },
			{ F7, { F1, F2, F3, F4, F5, F6, F8, A7, B7, C7, D7, E7, G7, H7 } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap k = BitMapMoveGenerator::getRookMoves( it.first, BitMap(0) );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getRookMoves1)
	{
		// occupancy not changing movement respect to 0 occupancy
		std::vector< std::pair< tSquare, std::vector<std::vector< tSquare > > > > testList = 
		{ 
			{ E4, { { E1, E2, E3, E5, E6, E7, E8, A4, B4, C4, D4, F4, G4, H4 }, { D3, F7, C6 } } },
			{ G2, { { G1, G3, G4, G5, G6, G7, G8, A2, B2, C2, D2, E2, F2, H2 }, { E3, A6, H4 } } },
			{ A2, { { A1, A3, A4, A5, A6, A7, A8, B2, C2, D2, E2, F2, G2, H2 }, { H1, H2, F6 } } },
			/*{ A7, { { A1, A2, A3, A4, A5, A6, A8, B7, C7, D7, E7, F7, G7, H7 }, { E2 } } },
			{ H3, { { H1, H2, H4, H5, H6, H7, H8, A3, B3, C3, D3, E3, F3, G3 }, { E2 } } },
			{ H7, { { H1, H2, H3, H4, H5, H6, H8, A7, B7, C7, D7, E7, F7, G7 }, { E2 } } },
			{ A5, { { A1, A2, A3, A4, A6, A7, A8, B5, C5, D5, E5, F5, G5, H5 }, { E2 } } },
			{ F7, { { F1, F2, F3, F4, F5, F6, F8, A7, B7, C7, D7, E7, G7, H7 }, { E2 } } }*/
		};
		
		for( const auto& it : testList )
		{
			const BitMap occupancy = createBitMap(it.second[1]);
			const BitMap k = BitMapMoveGenerator::getRookMoves( it.first, occupancy );
			const BitMap ref = createBitMap(it.second[0]);
			ASSERT_EQ( ref, k );
		}
		
	}
}