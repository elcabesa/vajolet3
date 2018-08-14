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
	
	*Copyright (C) 2007 Pradyumna Kannan.
	*
	*This code is provided 'as-is', without any expressed or implied warranty.
	*In no event will the authors be held liable for any damages arising from
	*the use of this code. Permission is granted to anyone to use this
	*code for any purpose, including commercial applications, and to alter
	*it and redistribute it freely, subject to the following restrictions:
	*
	*1. The origin of this code must not be misrepresented; you must not
	*claim that you wrote the original code. If you use this code in a
	*product, an acknowledgment in the product documentation would be
	*appreciated but is not required.
	*
	*2. Altered source versions must be plainly marked as such, and must not be
	*misrepresented as being the original code.
	*
	*3. This notice may not be removed or altered from any source distribution.
*/

#include "BitMapMoveGenerator.h"

namespace libChess
{
	/*	\brief init the magic bitmap move generator
		\author Marco Belli
		\version 1.0
		\date 15/06/2018
	*/
	void BitMapMoveGenerator::init(void)
	{
		/*********************************************
		* Define the list of pieces bitboard to be filled , and the move associated with each piece
		**********************************************/
		struct initializer{
			baseTypes::BitMap (&piece)[ baseTypes::squareNumber ];	// array of bitmap to be filled
			const std::list<std::pair<int,int>> moves;				// list of piece moves
		};
		
		const std::list<struct initializer> initializerList =
		{
			{ _kingMoveBitmap,   { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} } }, 	// king
			{ _knightMoveBitmap, { {-2,1}, {-2,-1}, {2,1}, {2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} } },	// knight
			{ _pawnsAttackBitmap[ baseTypes::whiteTurn ], { {-1,1}, {1,1} } },							// white pawn capture
			{ _pawnsAttackBitmap[ baseTypes::blackTurn ], { {-1,-1}, {1,-1} } }							// black pawn capture
		};
		
		/*********************************************
		* initialize the standard bitboards
		**********************************************/
		for( const auto& it: initializerList )
		{
			_initHelper( it.piece, it.moves );
		}
		
		/*********************************************
		* initialize the magic bitboards
		**********************************************/
		_initializeMagic<_getBishopMoves,_generateBishopMoveBitMap>(_magicMovesBmask);
		_initializeMagic<_getRookMoves,_generateRookMoveBitMap>(_magicMovesRmask);
	}
	
	/*	\brief helper function to populate the magic bibtboards
		\author Marco Belli
		\version 1.0
		\date 15/06/2018
	*/
	template <baseTypes::BitMap& (*get)( const baseTypes::tSquare, const baseTypes::BitMap&), baseTypes::BitMap (*gen)( baseTypes::tSquare,  const baseTypes::BitMap& )>
	void BitMapMoveGenerator::_initializeMagic( const baseTypes::BitMap (&bitMask)[ baseTypes::squareNumber ] )
	{
		// populate every square
		for ( const auto square : baseTypes::tSquareRange() )
		{
			// get the mask
			baseTypes::BitMap mask = bitMask[ square ];
			
			// iterate all the possibile configuration of the occupancy
			const int maxOcc = 1 << mask.bitCnt();
			for( int linearOcc = 0; linearOcc < maxOcc; ++linearOcc )
			{
				baseTypes::BitMap occ = _mapLinearOccToBitmap( mask, baseTypes::BitMap( linearOcc ) );
				// get the index of the bitmap to populate...
				baseTypes::BitMap& moves = get( square, occ );
				// ... and populate it
				moves = gen( square, occ );
			}
		}
	}
	
	
	/*	\brief helper function that map a linear occupation to the mask to generate a real board occupation
		\author Marco Belli
		\version 1.0
		\date 15/06/2018
	*/
	baseTypes::BitMap BitMapMoveGenerator::_mapLinearOccToBitmap( const baseTypes::BitMap& mask, const baseTypes::BitMap& linOcc )
	{

		baseTypes::BitMap occ(0);
		baseTypes::tSquare i = baseTypes::A1;
		
		// for every bit of the mask ...
		for( const auto sq : mask )
		{
			// ... if the relevant bit of the linear occupancy is set
			if( linOcc.isSquareSet( i ) )
			{
				// set the equivalente bit of the mask
				occ += sq;
			}
			++i;
		}
		return occ;
	}
	
	/*	\brief helper function that map a linear occupation to the mask to generate a real board occupation
		\author Marco Belli
		\version 1.0
		\date 15/06/2018
	*/
	baseTypes::BitMap BitMapMoveGenerator::_generateMoveBitMapHelper( const baseTypes::tSquare sq, const baseTypes::BitMap& occ, const int fileIncrement, const int rankIncrement)
	{
		baseTypes::BitMap moves(0);
		const baseTypes::tFile file = getFile( sq );
		const baseTypes::tRank rank = getRank( sq );
		
		baseTypes::tRank toRank = rank;
		baseTypes::tFile toFile = file;
		baseTypes::tSquare toSquare;
		
		do
		{
			toRank += fileIncrement;
			toFile += rankIncrement;
			if ( isValidRank( toRank ) && isValidFile( toFile ) )
			{
				toSquare = getSquareFromFileRank( toFile, toRank );
				moves += toSquare;
			}
		}
		while ( isValidRank( toRank ) && isValidFile( toFile ) && !occ.isSquareSet(toSquare) );
		
		return moves;
		
	}
	
	baseTypes::BitMap BitMapMoveGenerator::_generateRookMoveBitMap( const baseTypes::tSquare sq, const baseTypes::BitMap& occ )
	{
		baseTypes::BitMap moves(0);
		
		moves +=_generateMoveBitMapHelper( sq, occ, 1, 0 );
		moves +=_generateMoveBitMapHelper( sq, occ, -1, 0 );
		moves +=_generateMoveBitMapHelper( sq, occ, 0, 1 );
		moves +=_generateMoveBitMapHelper( sq, occ, 0, -1 );
		
		return moves;
	}
	
	baseTypes::BitMap BitMapMoveGenerator::_generateBishopMoveBitMap( const baseTypes::tSquare sq,  const baseTypes::BitMap& occ )
	{
		baseTypes::BitMap moves(0);
		
		moves +=_generateMoveBitMapHelper( sq, occ, 1, 1 );
		moves +=_generateMoveBitMapHelper( sq, occ, 1, -1 );
		moves +=_generateMoveBitMapHelper( sq, occ, -1, 1 );
		moves +=_generateMoveBitMapHelper( sq, occ, -1, -1 );
		
		return moves;
	}

	void BitMapMoveGenerator::_initHelper( baseTypes::BitMap * const b, const std::list<std::pair<int,int>> directions )
	{
		for ( const auto square : baseTypes::tSquareRange() )
		{
			for( auto dir :directions )
			{
				const baseTypes::tFile toFile = getFile( square ) + dir.first;
				const baseTypes::tRank toRank = getRank( square ) + dir.second;
						
				
				if( isValidFile( toFile ) && isValidRank( toRank ) )
				{
					b[square] += getSquareFromFileRank( toFile, toRank );
				}
			}
		}
	}
	
	baseTypes::BitMap BitMapMoveGenerator::_kingMoveBitmap[ baseTypes::squareNumber ] = { baseTypes::BitMap(0) };
	baseTypes::BitMap BitMapMoveGenerator::_knightMoveBitmap[ baseTypes::squareNumber ] = { baseTypes::BitMap(0) };
	baseTypes::BitMap BitMapMoveGenerator::_pawnsAttackBitmap[ baseTypes::turnNumber ][ baseTypes::squareNumber ] = { { baseTypes::BitMap(0) } };
	
	const unsigned int BitMapMoveGenerator::_magicMovesRshift[ baseTypes::squareNumber ] = 
	{
		52, 53, 53, 53, 53, 53, 53, 52,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 54, 54, 54, 54, 53,
		53, 54, 54, 53, 53, 53, 53, 53
	};
	
	const uint64_t BitMapMoveGenerator::_magicMovesRmagics[ baseTypes::squareNumber ] =
	{
		uint64_t(0x0080001020400080), uint64_t(0x0040001000200040), uint64_t(0x0080081000200080), uint64_t(0x0080040800100080),
		uint64_t(0x0080020400080080), uint64_t(0x0080010200040080), uint64_t(0x0080008001000200), uint64_t(0x0080002040800100),
		uint64_t(0x0000800020400080), uint64_t(0x0000400020005000), uint64_t(0x0000801000200080), uint64_t(0x0000800800100080),
		uint64_t(0x0000800400080080), uint64_t(0x0000800200040080), uint64_t(0x0000800100020080), uint64_t(0x0000800040800100),
		uint64_t(0x0000208000400080), uint64_t(0x0000404000201000), uint64_t(0x0000808010002000), uint64_t(0x0000808008001000),
		uint64_t(0x0000808004000800), uint64_t(0x0000808002000400), uint64_t(0x0000010100020004), uint64_t(0x0000020000408104),
		uint64_t(0x0000208080004000), uint64_t(0x0000200040005000), uint64_t(0x0000100080200080), uint64_t(0x0000080080100080),
		uint64_t(0x0000040080080080), uint64_t(0x0000020080040080), uint64_t(0x0000010080800200), uint64_t(0x0000800080004100),
		uint64_t(0x0000204000800080), uint64_t(0x0000200040401000), uint64_t(0x0000100080802000), uint64_t(0x0000080080801000),
		uint64_t(0x0000040080800800), uint64_t(0x0000020080800400), uint64_t(0x0000020001010004), uint64_t(0x0000800040800100),
		uint64_t(0x0000204000808000), uint64_t(0x0000200040008080), uint64_t(0x0000100020008080), uint64_t(0x0000080010008080),
		uint64_t(0x0000040008008080), uint64_t(0x0000020004008080), uint64_t(0x0000010002008080), uint64_t(0x0000004081020004),
		uint64_t(0x0000204000800080), uint64_t(0x0000200040008080), uint64_t(0x0000100020008080), uint64_t(0x0000080010008080),
		uint64_t(0x0000040008008080), uint64_t(0x0000020004008080), uint64_t(0x0000800100020080), uint64_t(0x0000800041000080),
		uint64_t(0x00FFFCDDFCED714A), uint64_t(0x007FFCDDFCED714A), uint64_t(0x003FFFCDFFD88096), uint64_t(0x0000040810002101),
		uint64_t(0x0001000204080011), uint64_t(0x0001000204000801), uint64_t(0x0001000082000401), uint64_t(0x0001FFFAABFAD1A2)
	};
	
	const baseTypes::BitMap BitMapMoveGenerator::_magicMovesRmask[ baseTypes::squareNumber ] =
	{	
		baseTypes::BitMap(0x000101010101017E), baseTypes::BitMap(0x000202020202027C), baseTypes::BitMap(0x000404040404047A), baseTypes::BitMap(0x0008080808080876),
		baseTypes::BitMap(0x001010101010106E), baseTypes::BitMap(0x002020202020205E), baseTypes::BitMap(0x004040404040403E), baseTypes::BitMap(0x008080808080807E),
		baseTypes::BitMap(0x0001010101017E00), baseTypes::BitMap(0x0002020202027C00), baseTypes::BitMap(0x0004040404047A00), baseTypes::BitMap(0x0008080808087600),
		baseTypes::BitMap(0x0010101010106E00), baseTypes::BitMap(0x0020202020205E00), baseTypes::BitMap(0x0040404040403E00), baseTypes::BitMap(0x0080808080807E00),
		baseTypes::BitMap(0x00010101017E0100), baseTypes::BitMap(0x00020202027C0200), baseTypes::BitMap(0x00040404047A0400), baseTypes::BitMap(0x0008080808760800),
		baseTypes::BitMap(0x00101010106E1000), baseTypes::BitMap(0x00202020205E2000), baseTypes::BitMap(0x00404040403E4000), baseTypes::BitMap(0x00808080807E8000),
		baseTypes::BitMap(0x000101017E010100), baseTypes::BitMap(0x000202027C020200), baseTypes::BitMap(0x000404047A040400), baseTypes::BitMap(0x0008080876080800),
		baseTypes::BitMap(0x001010106E101000), baseTypes::BitMap(0x002020205E202000), baseTypes::BitMap(0x004040403E404000), baseTypes::BitMap(0x008080807E808000),
		baseTypes::BitMap(0x0001017E01010100), baseTypes::BitMap(0x0002027C02020200), baseTypes::BitMap(0x0004047A04040400), baseTypes::BitMap(0x0008087608080800),
		baseTypes::BitMap(0x0010106E10101000), baseTypes::BitMap(0x0020205E20202000), baseTypes::BitMap(0x0040403E40404000), baseTypes::BitMap(0x0080807E80808000),
		baseTypes::BitMap(0x00017E0101010100), baseTypes::BitMap(0x00027C0202020200), baseTypes::BitMap(0x00047A0404040400), baseTypes::BitMap(0x0008760808080800),
		baseTypes::BitMap(0x00106E1010101000), baseTypes::BitMap(0x00205E2020202000), baseTypes::BitMap(0x00403E4040404000), baseTypes::BitMap(0x00807E8080808000),
		baseTypes::BitMap(0x007E010101010100), baseTypes::BitMap(0x007C020202020200), baseTypes::BitMap(0x007A040404040400), baseTypes::BitMap(0x0076080808080800),
		baseTypes::BitMap(0x006E101010101000), baseTypes::BitMap(0x005E202020202000), baseTypes::BitMap(0x003E404040404000), baseTypes::BitMap(0x007E808080808000),
		baseTypes::BitMap(0x7E01010101010100), baseTypes::BitMap(0x7C02020202020200), baseTypes::BitMap(0x7A04040404040400), baseTypes::BitMap(0x7608080808080800),
		baseTypes::BitMap(0x6E10101010101000), baseTypes::BitMap(0x5E20202020202000), baseTypes::BitMap(0x3E40404040404000), baseTypes::BitMap(0x7E80808080808000)
	};
	
	
	const unsigned int BitMapMoveGenerator::_magicMovesBshift[ baseTypes::squareNumber ] =
	{
		58, 59, 59, 59, 59, 59, 59, 58,
		59, 59, 59, 59, 59, 59, 59, 59,
		59, 59, 57, 57, 57, 57, 59, 59,
		59, 59, 57, 55, 55, 57, 59, 59,
		59, 59, 57, 55, 55, 57, 59, 59,
		59, 59, 57, 57, 57, 57, 59, 59,
		59, 59, 59, 59, 59, 59, 59, 59,
		58, 59, 59, 59, 59, 59, 59, 58
	};

	const uint64_t BitMapMoveGenerator::_magicMovesBmagics[ baseTypes::squareNumber ] =
	{
		uint64_t(0x0002020202020200), uint64_t(0x0002020202020000), uint64_t(0x0004010202000000), uint64_t(0x0004040080000000),
		uint64_t(0x0001104000000000), uint64_t(0x0000821040000000), uint64_t(0x0000410410400000), uint64_t(0x0000104104104000),
		uint64_t(0x0000040404040400), uint64_t(0x0000020202020200), uint64_t(0x0000040102020000), uint64_t(0x0000040400800000),
		uint64_t(0x0000011040000000), uint64_t(0x0000008210400000), uint64_t(0x0000004104104000), uint64_t(0x0000002082082000),
		uint64_t(0x0004000808080800), uint64_t(0x0002000404040400), uint64_t(0x0001000202020200), uint64_t(0x0000800802004000),
		uint64_t(0x0000800400A00000), uint64_t(0x0000200100884000), uint64_t(0x0000400082082000), uint64_t(0x0000200041041000),
		uint64_t(0x0002080010101000), uint64_t(0x0001040008080800), uint64_t(0x0000208004010400), uint64_t(0x0000404004010200),
		uint64_t(0x0000840000802000), uint64_t(0x0000404002011000), uint64_t(0x0000808001041000), uint64_t(0x0000404000820800),
		uint64_t(0x0001041000202000), uint64_t(0x0000820800101000), uint64_t(0x0000104400080800), uint64_t(0x0000020080080080),
		uint64_t(0x0000404040040100), uint64_t(0x0000808100020100), uint64_t(0x0001010100020800), uint64_t(0x0000808080010400),
		uint64_t(0x0000820820004000), uint64_t(0x0000410410002000), uint64_t(0x0000082088001000), uint64_t(0x0000002011000800),
		uint64_t(0x0000080100400400), uint64_t(0x0001010101000200), uint64_t(0x0002020202000400), uint64_t(0x0001010101000200),
		uint64_t(0x0000410410400000), uint64_t(0x0000208208200000), uint64_t(0x0000002084100000), uint64_t(0x0000000020880000),
		uint64_t(0x0000001002020000), uint64_t(0x0000040408020000), uint64_t(0x0004040404040000), uint64_t(0x0002020202020000),
		uint64_t(0x0000104104104000), uint64_t(0x0000002082082000), uint64_t(0x0000000020841000), uint64_t(0x0000000000208800),
		uint64_t(0x0000000010020200), uint64_t(0x0000000404080200), uint64_t(0x0000040404040400), uint64_t(0x0002020202020200)
	};


	const baseTypes::BitMap BitMapMoveGenerator::_magicMovesBmask[ baseTypes::squareNumber ] =
	{
		baseTypes::BitMap(0x0040201008040200), baseTypes::BitMap(0x0000402010080400), baseTypes::BitMap(0x0000004020100A00), baseTypes::BitMap(0x0000000040221400),
		baseTypes::BitMap(0x0000000002442800), baseTypes::BitMap(0x0000000204085000), baseTypes::BitMap(0x0000020408102000), baseTypes::BitMap(0x0002040810204000),
		baseTypes::BitMap(0x0020100804020000), baseTypes::BitMap(0x0040201008040000), baseTypes::BitMap(0x00004020100A0000), baseTypes::BitMap(0x0000004022140000),
		baseTypes::BitMap(0x0000000244280000), baseTypes::BitMap(0x0000020408500000), baseTypes::BitMap(0x0002040810200000), baseTypes::BitMap(0x0004081020400000),
		baseTypes::BitMap(0x0010080402000200), baseTypes::BitMap(0x0020100804000400), baseTypes::BitMap(0x004020100A000A00), baseTypes::BitMap(0x0000402214001400),
		baseTypes::BitMap(0x0000024428002800), baseTypes::BitMap(0x0002040850005000), baseTypes::BitMap(0x0004081020002000), baseTypes::BitMap(0x0008102040004000),
		baseTypes::BitMap(0x0008040200020400), baseTypes::BitMap(0x0010080400040800), baseTypes::BitMap(0x0020100A000A1000), baseTypes::BitMap(0x0040221400142200),
		baseTypes::BitMap(0x0002442800284400), baseTypes::BitMap(0x0004085000500800), baseTypes::BitMap(0x0008102000201000), baseTypes::BitMap(0x0010204000402000),
		baseTypes::BitMap(0x0004020002040800), baseTypes::BitMap(0x0008040004081000), baseTypes::BitMap(0x00100A000A102000), baseTypes::BitMap(0x0022140014224000),
		baseTypes::BitMap(0x0044280028440200), baseTypes::BitMap(0x0008500050080400), baseTypes::BitMap(0x0010200020100800), baseTypes::BitMap(0x0020400040201000),
		baseTypes::BitMap(0x0002000204081000), baseTypes::BitMap(0x0004000408102000), baseTypes::BitMap(0x000A000A10204000), baseTypes::BitMap(0x0014001422400000),
		baseTypes::BitMap(0x0028002844020000), baseTypes::BitMap(0x0050005008040200), baseTypes::BitMap(0x0020002010080400), baseTypes::BitMap(0x0040004020100800),
		baseTypes::BitMap(0x0000020408102000), baseTypes::BitMap(0x0000040810204000), baseTypes::BitMap(0x00000A1020400000), baseTypes::BitMap(0x0000142240000000),
		baseTypes::BitMap(0x0000284402000000), baseTypes::BitMap(0x0000500804020000), baseTypes::BitMap(0x0000201008040200), baseTypes::BitMap(0x0000402010080400),
		baseTypes::BitMap(0x0002040810204000), baseTypes::BitMap(0x0004081020400000), baseTypes::BitMap(0x000A102040000000), baseTypes::BitMap(0x0014224000000000),
		baseTypes::BitMap(0x0028440200000000), baseTypes::BitMap(0x0050080402000000), baseTypes::BitMap(0x0020100804020000), baseTypes::BitMap(0x0040201008040200)
	};
	
	baseTypes::BitMap BitMapMoveGenerator::_magicMovesBdb[ 5248 ];
	baseTypes::BitMap* BitMapMoveGenerator::_magicMovesBindices[ baseTypes::squareNumber ] =
	{
		_magicMovesBdb+4992, _magicMovesBdb+2624, _magicMovesBdb+256,  _magicMovesBdb+896,
		_magicMovesBdb+1280, _magicMovesBdb+1664, _magicMovesBdb+4800, _magicMovesBdb+5120,
		_magicMovesBdb+2560, _magicMovesBdb+2656, _magicMovesBdb+288,  _magicMovesBdb+928,
		_magicMovesBdb+1312, _magicMovesBdb+1696, _magicMovesBdb+4832, _magicMovesBdb+4928,
		_magicMovesBdb+0,    _magicMovesBdb+128,  _magicMovesBdb+320,  _magicMovesBdb+960,
		_magicMovesBdb+1344, _magicMovesBdb+1728, _magicMovesBdb+2304, _magicMovesBdb+2432,
		_magicMovesBdb+32,   _magicMovesBdb+160,  _magicMovesBdb+448,  _magicMovesBdb+2752,
		_magicMovesBdb+3776, _magicMovesBdb+1856, _magicMovesBdb+2336, _magicMovesBdb+2464,
		_magicMovesBdb+64,   _magicMovesBdb+192,  _magicMovesBdb+576,  _magicMovesBdb+3264,
		_magicMovesBdb+4288, _magicMovesBdb+1984, _magicMovesBdb+2368, _magicMovesBdb+2496,
		_magicMovesBdb+96,   _magicMovesBdb+224,  _magicMovesBdb+704,  _magicMovesBdb+1088,
		_magicMovesBdb+1472, _magicMovesBdb+2112, _magicMovesBdb+2400, _magicMovesBdb+2528,
		_magicMovesBdb+2592, _magicMovesBdb+2688, _magicMovesBdb+832,  _magicMovesBdb+1216,
		_magicMovesBdb+1600, _magicMovesBdb+2240, _magicMovesBdb+4864, _magicMovesBdb+4960,
		_magicMovesBdb+5056, _magicMovesBdb+2720, _magicMovesBdb+864,  _magicMovesBdb+1248,
		_magicMovesBdb+1632, _magicMovesBdb+2272, _magicMovesBdb+4896, _magicMovesBdb+5184
	};


	baseTypes::BitMap BitMapMoveGenerator::_magicMovesRdb[ 102400 ];
	baseTypes::BitMap* BitMapMoveGenerator::_magicMovesRindices[ baseTypes::squareNumber ] =
	{
		_magicMovesRdb+86016, _magicMovesRdb+73728, _magicMovesRdb+36864, _magicMovesRdb+43008,
		_magicMovesRdb+47104, _magicMovesRdb+51200, _magicMovesRdb+77824, _magicMovesRdb+94208,
		_magicMovesRdb+69632, _magicMovesRdb+32768, _magicMovesRdb+38912, _magicMovesRdb+10240,
		_magicMovesRdb+14336, _magicMovesRdb+53248, _magicMovesRdb+57344, _magicMovesRdb+81920,
		_magicMovesRdb+24576, _magicMovesRdb+33792, _magicMovesRdb+6144,  _magicMovesRdb+11264,
		_magicMovesRdb+15360, _magicMovesRdb+18432, _magicMovesRdb+58368, _magicMovesRdb+61440,
		_magicMovesRdb+26624, _magicMovesRdb+4096,  _magicMovesRdb+7168,  _magicMovesRdb+0,
		_magicMovesRdb+2048,  _magicMovesRdb+19456, _magicMovesRdb+22528, _magicMovesRdb+63488,
		_magicMovesRdb+28672, _magicMovesRdb+5120,  _magicMovesRdb+8192,  _magicMovesRdb+1024,
		_magicMovesRdb+3072,  _magicMovesRdb+20480, _magicMovesRdb+23552, _magicMovesRdb+65536,
		_magicMovesRdb+30720, _magicMovesRdb+34816, _magicMovesRdb+9216,  _magicMovesRdb+12288,
		_magicMovesRdb+16384, _magicMovesRdb+21504, _magicMovesRdb+59392, _magicMovesRdb+67584,
		_magicMovesRdb+71680, _magicMovesRdb+35840, _magicMovesRdb+39936, _magicMovesRdb+13312,
		_magicMovesRdb+17408, _magicMovesRdb+54272, _magicMovesRdb+60416, _magicMovesRdb+83968,
		_magicMovesRdb+90112, _magicMovesRdb+75776, _magicMovesRdb+40960, _magicMovesRdb+45056,
		_magicMovesRdb+49152, _magicMovesRdb+55296, _magicMovesRdb+79872, _magicMovesRdb+98304
	};
	
}


