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
		
	static BitMap createBitMap( const std::vector< tSquare >& list )
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
			{ A7, { { A1, A2, A3, A4, A5, A6, A8, B7, C7, D7, E7, F7, G7, H7 }, { E2, F3, A8 } } },
			{ H3, { { H1, H2, H4, H5, H6, H7, H8, A3, B3, C3, D3, E3, F3, G3 }, { A1, H3, D2 } } },
			{ H7, { { H1, H2, H3, H4, H5, H6, H8, A7, B7, C7, D7, E7, F7, G7 }, { E2, B3, C4 } } },
			{ A5, { { A1, A2, A3, A4, A6, A7, A8, B5, C5, D5, E5, F5, G5, H5 }, { A1, A8, H5 } } },
			{ F7, { { F1, F2, F3, F4, F5, F6, F8, A7, B7, C7, D7, E7, G7, H7 }, { E2 } } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap occupancy = createBitMap(it.second[1]);
			const BitMap k = BitMapMoveGenerator::getRookMoves( it.first, occupancy );
			const BitMap ref = createBitMap(it.second[0]);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getRookMoves2)
	{
		// occupancy changing movement respect to 0 occupancy
		std::vector< std::pair< tSquare, std::vector<std::vector< tSquare > > > > testList = 
		{ 
			{ E4, { { E1, E2, E3, E5, E6, A4, B4, C4, D4, F4, G4, H4 }, { E6, F7, C6 } } },
			{ G2, { { G1, G3, F2, H2 }, { E3, F2, G3 } } },
			{ A2, { { A1, A3, A4, A5, B2, C2, D2, E2, F2, G2, H2 }, { H1, A5, F6 } } },
			{ A7, { { A4, A5, A6, A8, B7, C7, D7, E7, F7, G7, H7 }, { E2, F3, A4 } } },
			{ H3, { { H2, H4, G3 }, { G3, H2, H4 } } },
			{ H7, { { H1, H2, H3, H4, H5, H6, H8, B7, C7, D7, E7, F7, G7 }, { B7, B3, C4 } } },
			{ A5, { { A2, A3, A4, A6, A7, A8, B5, C5, D5, E5, F5, G5 }, { A2, A8, G5 } } },
			{ F7, { { F3, F4, F5, F6, F8, A7, B7, C7, D7, E7, G7, H7 }, { F3 } } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap occupancy = createBitMap(it.second[1]);
			const BitMap k = BitMapMoveGenerator::getRookMoves( it.first, occupancy );
			const BitMap ref = createBitMap(it.second[0]);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getRookPseudoMoves0)
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
			const BitMap k = BitMapMoveGenerator::getRookPseudoMoves( it.first );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getRookPseudoMoves1)
	{
		for( const auto sq : tSquareRange() )
		{
			ASSERT_EQ( BitMapMoveGenerator::getRookPseudoMoves( sq ) , BitMapMoveGenerator::getRookMoves( sq, BitMap(0) ) );
		}
	}
	
	TEST(BitMapMoveGenerator,getBishopMoves0)
	{
		// empy occupancy test
		std::vector< std::pair< tSquare, std::vector< tSquare > > > testList = 
		{ 
			{ E4, { D3, C2, B1, F5, G6, H7, D5, C6, B7, A8, F3, G2, H1 } },
			{ F1, { G2, H3, E2, D3, C4, B5, A6 } },
			{ D6, { C7, B8, C5, B4, A3, E7, F8, E5, F4, G3, H2 } },
			{ C2, { B1, B3, A4, D3, E4, F5, G6, H7, D1 } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap k = BitMapMoveGenerator::getBishopMoves( it.first, BitMap(0) );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getBishopMoves1)
	{
		// occupancy not changing movement respect to 0 occupancy
		std::vector< std::pair< tSquare, std::vector<std::vector< tSquare > > > > testList = 
		{ 
			{ E4, { { D3, C2, B1, F5, G6, H7, D5, C6, B7, A8, F3, G2, H1 }, { F4, G3, D4, E5 } } },
			{ F1, { { G2, H3, E2, D3, C4, B5, A6 }, { E8, H3 } } },
			{ D6, { { C7, B8, C5, B4, A3, E7, F8, E5, F4, G3, H2 }, { B8, B7, B6, F2 } } },
			{ C2, { { B1, B3, A4, D3, E4, F5, G6, H7, D1 }, { D4, E5 } } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap occupancy = createBitMap(it.second[1]);
			const BitMap k = BitMapMoveGenerator::getBishopMoves( it.first, occupancy );
			const BitMap ref = createBitMap(it.second[0]);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getBishopMoves2)
	{
		// occupancy changing movement respect to 0 occupancy
		std::vector< std::pair< tSquare, std::vector<std::vector< tSquare > > > > testList = 
		{ 
			{ E4, { { D3, C2, F5, G6, H7, D5, C6, F3, G2, H1 }, { F4, G3, D4, E5, C2, C6 } } },
			{ F1, { { G2, H3, E2, D3, C4 }, { E8, H3 ,C4 } } },
			{ D6, { { C7, C5, E7, E5 }, { B8, B7, B6, F2, C7, C5, E7, E5,} } },
			{ C2, { { B1, B3, D3, E4, F5, G6, H7, D1 }, { D4, E5, B3 } } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap occupancy = createBitMap(it.second[1]);
			const BitMap k = BitMapMoveGenerator::getBishopMoves( it.first, occupancy );
			const BitMap ref = createBitMap(it.second[0]);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getBishopPseudoMoves0)
	{
		// empy occupancy test
		std::vector< std::pair< tSquare, std::vector< tSquare > > > testList = 
		{ 
			{ E4, { D3, C2, B1, F5, G6, H7, D5, C6, B7, A8, F3, G2, H1 } },
			{ F1, { G2, H3, E2, D3, C4, B5, A6 } },
			{ D6, { C7, B8, C5, B4, A3, E7, F8, E5, F4, G3, H2 } },
			{ C2, { B1, B3, A4, D3, E4, F5, G6, H7, D1 } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap k = BitMapMoveGenerator::getBishopPseudoMoves( it.first );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getBishopPseudoMoves1)
	{
		for( const auto sq : tSquareRange() )
		{
			ASSERT_EQ( BitMapMoveGenerator::getBishopPseudoMoves( sq ) , BitMapMoveGenerator::getBishopMoves( sq, BitMap(0) ) );
		}
	}
	
	TEST(BitMapMoveGenerator,getQueenMoves0)
	{
		// empy occupancy test
		std::vector< std::pair< tSquare, std::vector< tSquare > > > testList = 
		{ 
			{ E4, { D3, C2, B1, F5, G6, H7, D5, C6, B7, A8, F3, G2, H1, E1, E2, E3, E5, E6, E7, E8, A4, B4, C4, D4, F4, G4, H4} },
			{ F1, { G2, H3, E2, D3, C4, B5, A6, F2, F3, F4, F5, F6, F7, F8, A1, B1, C1, D1, E1, G1, H1 } },
			{ D6, { C7, B8, C5, B4, A3, E7, F8, E5, F4, G3, H2, A6, B6, C6, E6, F6, G6, H6, D1, D2, D3, D4, D5, D7, D8 } },
			{ C2, { B1, B3, A4, D3, E4, F5, G6, H7, D1, A2, B2, D2, E2, F2, G2, H2, C1, C3, C4, C5, C6, C7, C8 } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap k = BitMapMoveGenerator::getQueenMoves( it.first, BitMap(0) );
			const BitMap ref = createBitMap(it.second);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getQueenMoves1)
	{
		// occupancy not changing movement respect to 0 occupancy
		std::vector< std::pair< tSquare, std::vector<std::vector< tSquare > > > > testList = 
		{ 
			{ E4, { { D3, C2, B1, F5, G6, H7, D5, C6, B7, A8, F3, G2, H1, E1, E2, E3, E5, E6, E7, E8, A4, B4, C4, D4, F4, G4, H4}, { F7, G3, D6, E8 } } },
			{ F1, { { G2, H3, E2, D3, C4, B5, A6, F2, F3, F4, F5, F6, F7, F8, A1, B1, C1, D1, E1, G1, H1 }, { E8, H2 } } },
			{ D6, { { C7, B8, C5, B4, A3, E7, F8, E5, F4, G3, H2, A6, B6, C6, E6, F6, G6, H6, D1, D2, D3, D4, D5, D7, D8 }, { B8, B7, B5, F2 } } },
			{ C2, { { B1, B3, A4, D3, E4, F5, G6, H7, D1, A2, B2, D2, E2, F2, G2, H2, C1, C3, C4, C5, C6, C7, C8 }, { D4, E5 } } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap occupancy = createBitMap(it.second[1]);
			const BitMap k = BitMapMoveGenerator::getQueenMoves( it.first, occupancy );
			const BitMap ref = createBitMap(it.second[0]);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getQueenMoves2)
	{
		// occupancy changing movement respect to 0 occupancy
		std::vector< std::pair< tSquare, std::vector<std::vector< tSquare > > > > testList = 
		{ 
			{ E4, { { D3, C2, F5, G6, H7, D5, C6, F3, G2, H1, E1, E2, E3, E5, D4, F4,}, { F4, G3, D4, E5, C2, C6 } } },
			{ F1, { { G2, H3, E2, D3, C4, F2, F3, F4, F5, F6, F7, F8, A1, B1, C1, D1, E1, G1, H1 }, { E8, H3 ,C4 } } },
			{ D6, { { C7, C5, E7, E5, B6, C6, E6, F6, G6, H6, D2, D3, D4, D5, D7, D8 }, { B8, B7, B6, F2, C7, C5, E7, E5, D2} } },
			{ C2, { { B1, B3, D3, E4, F5, G6, H7, D1, A2, B2, D2, E2, F2, G2, H2, C1, C3, C4, C5, C6, C7, C8 }, { D4, E5, B3 } } }
		};
		
		for( const auto& it : testList )
		{
			const BitMap occupancy = createBitMap(it.second[1]);
			const BitMap k = BitMapMoveGenerator::getQueenMoves( it.first, occupancy );
			const BitMap ref = createBitMap(it.second[0]);
			ASSERT_EQ( ref, k );
		}
		
	}
	
	TEST(BitMapMoveGenerator,getPawnGroupAdvance0)
	{
		std::vector< tSquare > PawnSqList = { A3, B4, C4, E2, F2, G3, H2 };
		std::vector< tSquare > ExpectedPawnSqList = { A4, B5, C5, E3, F3, G4, H3 };
		const BitMap Pawns = createBitMap(PawnSqList);
		const BitMap Pawns2 = createBitMap(ExpectedPawnSqList);

		ASSERT_EQ( Pawns2, BitMapMoveGenerator::getPawnGroupAdvance( Pawns, white, BitMap(0) ) );
		
		
	}
	
	TEST(BitMapMoveGenerator,getPawnGroupAdvance1)
	{
		std::vector< tSquare > PawnSqList = { A3, B4, C4, E2, F2, G3, H2 };
		std::vector< tSquare > ExpectedPawnSqList = { A4, C5, E3, G4, H3 };
		std::vector< tSquare > OccupancyList = { A7, B5, C7, D7, E7, F3, G7, H7 };
		const BitMap Pawns = createBitMap(PawnSqList);
		const BitMap Pawns2 = createBitMap(ExpectedPawnSqList);
		const BitMap Occupancy = createBitMap(OccupancyList);

		ASSERT_EQ( Pawns2, BitMapMoveGenerator::getPawnGroupAdvance( Pawns, white, Occupancy ) );
		
		
	}
	
	TEST(BitMapMoveGenerator,getPawnGroupAdvance2)
	{
		std::vector< tSquare > PawnSqList = { A6, B5, C5, E7, F7, G6, H7 };
		std::vector< tSquare > ExpectedPawnSqList = { A5, B4, C4, E6, F6, G5, H6 };
		const BitMap Pawns = createBitMap(PawnSqList);
		const BitMap Pawns2 = createBitMap(ExpectedPawnSqList);

		ASSERT_EQ( Pawns2, BitMapMoveGenerator::getPawnGroupAdvance( Pawns, black, BitMap(0) ) );
		
		
	}
	
	TEST(BitMapMoveGenerator,getPawnGroupAdvance3)
	{
		std::vector< tSquare > PawnSqList = { A6, B5, C5, E7, F7, G6, H7 };
		std::vector< tSquare > ExpectedPawnSqList = { A5, C4, E6, G5, H6 };
		std::vector< tSquare > OccupancyList = { A2, B4, C2, D2, E2, F6, G2, H2 };
		const BitMap Pawns = createBitMap(PawnSqList);
		const BitMap Pawns2 = createBitMap(ExpectedPawnSqList);
		const BitMap Occupancy = createBitMap(OccupancyList);

		ASSERT_EQ( Pawns2, BitMapMoveGenerator::getPawnGroupAdvance( Pawns, black, Occupancy ) );
		
	}
	
	TEST(BitMapMoveGenerator,getPawnGroupCaptureLeft0)
	{
		std::vector< tSquare > PawnSqList = { A3, B4, C4, E2, F2, G3, H2 };
		std::vector< tSquare > ExpectedPawnSqList = { A5, F4 };
		std::vector< tSquare > TargetList = { A4, A5, F7, F4, G4, D5 };
		const BitMap Pawns = createBitMap(PawnSqList);
		const BitMap Pawns2 = createBitMap(ExpectedPawnSqList);
		const BitMap Target = createBitMap(TargetList);

		ASSERT_EQ( Pawns2, BitMapMoveGenerator::getPawnGroupCaptureLeft( Pawns, white, Target ) );
		
	}
	
	TEST(BitMapMoveGenerator,getPawnGroupCaptureRight0)
	{
		std::vector< tSquare > PawnSqList = { A3, B4, C4, E2, F2, G3, H2 };
		std::vector< tSquare > ExpectedPawnSqList = { F3, D5 };
		std::vector< tSquare > TargetList = { A4, A5, F7, F3, G4, D5 };
		const BitMap Pawns = createBitMap(PawnSqList);
		const BitMap Pawns2 = createBitMap(ExpectedPawnSqList);
		const BitMap Target = createBitMap(TargetList);

		ASSERT_EQ( Pawns2, BitMapMoveGenerator::getPawnGroupCaptureRight( Pawns, white, Target ) );
		
	}
	
	TEST(BitMapMoveGenerator,getPawnGroupCaptureLeft1)
	{
		std::vector< tSquare > PawnSqList = { A6, B5, C5, E7, F7, G6, H7 };
		std::vector< tSquare > ExpectedPawnSqList = { A4, F5 };
		std::vector< tSquare > TargetList = { A5, A4, F2, F5, G5, D4 };
		const BitMap Pawns = createBitMap(PawnSqList);
		const BitMap Pawns2 = createBitMap(ExpectedPawnSqList);
		const BitMap Target = createBitMap(TargetList);

		ASSERT_EQ( Pawns2, BitMapMoveGenerator::getPawnGroupCaptureLeft( Pawns, black, Target ) );
		
	}
	
	TEST(BitMapMoveGenerator,getPawnGroupCaptureRight1)
	{
		std::vector< tSquare > PawnSqList = { A6, B5, C5, E7, F7, G6, H7 };
		std::vector< tSquare > ExpectedPawnSqList = { F6, D4 };
		std::vector< tSquare > TargetList = { A5, A4, F2, F6, G5, D4 };
		const BitMap Pawns = createBitMap(PawnSqList);
		const BitMap Pawns2 = createBitMap(ExpectedPawnSqList);
		const BitMap Target = createBitMap(TargetList);

		ASSERT_EQ( Pawns2, BitMapMoveGenerator::getPawnGroupCaptureRight( Pawns, black, Target ) );
		
	}
	
}