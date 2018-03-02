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
	void BitMapMoveGenerator::init(void)
	{
		// KING attacks;
		const std::list<std::pair<int,int>> kDirections = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
		_initHelper( _kingMoveBitmap, kDirections );
		
		// KNIGHT attacks;
		const std::list<std::pair<int,int>> nDirections = { {-2,1}, {-2,-1}, {2,1}, {2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };
		_initHelper( _knightMoveBitmap, nDirections );
		
		// PAWNS attacks
		const std::list<std::pair<int,int>> wpDirections = { {-1,1}, {1,1} };
		_initHelper( _pawnsAttackBitmap[ baseTypes::white ], wpDirections );
		const std::list<std::pair<int,int>> bpDirections = { {-1,-1}, {1,-1} };
		_initHelper( _pawnsAttackBitmap[ baseTypes::black ], bpDirections );
	
		
		
		// BISHOP attacks
		for ( const auto square : baseTypes::tSquareRange() )
		{
			baseTypes::BitMap mask = _magicmovesBmask[ square ];
			
			const int maxOcc = 1 << mask.bitCnt();
			
			for( int linearOcc = 0; linearOcc < maxOcc; ++linearOcc )
			{
				baseTypes::BitMap occ = _mapLinearOccToBitmap( mask, baseTypes::BitMap( linearOcc ) );
			}
		}
		
		// ROOK attacks
		for ( const auto square : baseTypes::tSquareRange() )
		{
			baseTypes::BitMap mask = _magicmovesRmask[ square ];
			
			const int maxOcc = 1 << mask.bitCnt();
			
			for( int linearOcc = 0; linearOcc < maxOcc; ++linearOcc )
			{
				baseTypes::BitMap occ = _mapLinearOccToBitmap( mask, baseTypes::BitMap( linearOcc ) );
			}
		}
		
	}
	
	baseTypes::BitMap BitMapMoveGenerator::_mapLinearOccToBitmap( const baseTypes::BitMap& moves, const baseTypes::BitMap& linOcc )
	{
		// map a a linear occupancy on the relevant bits of moves BitMap.
		
		baseTypes::BitMap occ(0);
		baseTypes::tSquare i = baseTypes::A1;
		for( const auto sq : moves )
		{
			if( linOcc.isSquareSet( i ) )
			{
				occ += sq;
			}
			++i;
		}
		return occ;
	}

	void BitMapMoveGenerator::_initHelper( baseTypes::BitMap * const b, std::list<std::pair<int,int>> directions )
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
	baseTypes::BitMap BitMapMoveGenerator::_pawnsAttackBitmap[ baseTypes::colorNumber ][ baseTypes::squareNumber ] = { baseTypes::BitMap(0) };
	
	const unsigned int BitMapMoveGenerator::_magicmovesRshift[ baseTypes::squareNumber ] = 
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
	
	const baseTypes::BitMap BitMapMoveGenerator::_magicmovesRmagics[ baseTypes::squareNumber ] =
	{
		baseTypes::BitMap(0x0080001020400080), baseTypes::BitMap(0x0040001000200040), baseTypes::BitMap(0x0080081000200080), baseTypes::BitMap(0x0080040800100080),
		baseTypes::BitMap(0x0080020400080080), baseTypes::BitMap(0x0080010200040080), baseTypes::BitMap(0x0080008001000200), baseTypes::BitMap(0x0080002040800100),
		baseTypes::BitMap(0x0000800020400080), baseTypes::BitMap(0x0000400020005000), baseTypes::BitMap(0x0000801000200080), baseTypes::BitMap(0x0000800800100080),
		baseTypes::BitMap(0x0000800400080080), baseTypes::BitMap(0x0000800200040080), baseTypes::BitMap(0x0000800100020080), baseTypes::BitMap(0x0000800040800100),
		baseTypes::BitMap(0x0000208000400080), baseTypes::BitMap(0x0000404000201000), baseTypes::BitMap(0x0000808010002000), baseTypes::BitMap(0x0000808008001000),
		baseTypes::BitMap(0x0000808004000800), baseTypes::BitMap(0x0000808002000400), baseTypes::BitMap(0x0000010100020004), baseTypes::BitMap(0x0000020000408104),
		baseTypes::BitMap(0x0000208080004000), baseTypes::BitMap(0x0000200040005000), baseTypes::BitMap(0x0000100080200080), baseTypes::BitMap(0x0000080080100080),
		baseTypes::BitMap(0x0000040080080080), baseTypes::BitMap(0x0000020080040080), baseTypes::BitMap(0x0000010080800200), baseTypes::BitMap(0x0000800080004100),
		baseTypes::BitMap(0x0000204000800080), baseTypes::BitMap(0x0000200040401000), baseTypes::BitMap(0x0000100080802000), baseTypes::BitMap(0x0000080080801000),
		baseTypes::BitMap(0x0000040080800800), baseTypes::BitMap(0x0000020080800400), baseTypes::BitMap(0x0000020001010004), baseTypes::BitMap(0x0000800040800100),
		baseTypes::BitMap(0x0000204000808000), baseTypes::BitMap(0x0000200040008080), baseTypes::BitMap(0x0000100020008080), baseTypes::BitMap(0x0000080010008080),
		baseTypes::BitMap(0x0000040008008080), baseTypes::BitMap(0x0000020004008080), baseTypes::BitMap(0x0000010002008080), baseTypes::BitMap(0x0000004081020004),
		baseTypes::BitMap(0x0000204000800080), baseTypes::BitMap(0x0000200040008080), baseTypes::BitMap(0x0000100020008080), baseTypes::BitMap(0x0000080010008080),
		baseTypes::BitMap(0x0000040008008080), baseTypes::BitMap(0x0000020004008080), baseTypes::BitMap(0x0000800100020080), baseTypes::BitMap(0x0000800041000080),
		baseTypes::BitMap(0x00FFFCDDFCED714A), baseTypes::BitMap(0x007FFCDDFCED714A), baseTypes::BitMap(0x003FFFCDFFD88096), baseTypes::BitMap(0x0000040810002101),
		baseTypes::BitMap(0x0001000204080011), baseTypes::BitMap(0x0001000204000801), baseTypes::BitMap(0x0001000082000401), baseTypes::BitMap(0x0001FFFAABFAD1A2)
	};
	
	const baseTypes::BitMap BitMapMoveGenerator::_magicmovesRmask[ baseTypes::squareNumber ] =
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
	
	
	const unsigned int BitMapMoveGenerator::_magicmovesBshift[ baseTypes::squareNumber ] =
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

	const baseTypes::BitMap BitMapMoveGenerator::_magicmovesBmagics[ baseTypes::squareNumber ] =
	{
		baseTypes::BitMap(0x0002020202020200), baseTypes::BitMap(0x0002020202020000), baseTypes::BitMap(0x0004010202000000), baseTypes::BitMap(0x0004040080000000),
		baseTypes::BitMap(0x0001104000000000), baseTypes::BitMap(0x0000821040000000), baseTypes::BitMap(0x0000410410400000), baseTypes::BitMap(0x0000104104104000),
		baseTypes::BitMap(0x0000040404040400), baseTypes::BitMap(0x0000020202020200), baseTypes::BitMap(0x0000040102020000), baseTypes::BitMap(0x0000040400800000),
		baseTypes::BitMap(0x0000011040000000), baseTypes::BitMap(0x0000008210400000), baseTypes::BitMap(0x0000004104104000), baseTypes::BitMap(0x0000002082082000),
		baseTypes::BitMap(0x0004000808080800), baseTypes::BitMap(0x0002000404040400), baseTypes::BitMap(0x0001000202020200), baseTypes::BitMap(0x0000800802004000),
		baseTypes::BitMap(0x0000800400A00000), baseTypes::BitMap(0x0000200100884000), baseTypes::BitMap(0x0000400082082000), baseTypes::BitMap(0x0000200041041000),
		baseTypes::BitMap(0x0002080010101000), baseTypes::BitMap(0x0001040008080800), baseTypes::BitMap(0x0000208004010400), baseTypes::BitMap(0x0000404004010200),
		baseTypes::BitMap(0x0000840000802000), baseTypes::BitMap(0x0000404002011000), baseTypes::BitMap(0x0000808001041000), baseTypes::BitMap(0x0000404000820800),
		baseTypes::BitMap(0x0001041000202000), baseTypes::BitMap(0x0000820800101000), baseTypes::BitMap(0x0000104400080800), baseTypes::BitMap(0x0000020080080080),
		baseTypes::BitMap(0x0000404040040100), baseTypes::BitMap(0x0000808100020100), baseTypes::BitMap(0x0001010100020800), baseTypes::BitMap(0x0000808080010400),
		baseTypes::BitMap(0x0000820820004000), baseTypes::BitMap(0x0000410410002000), baseTypes::BitMap(0x0000082088001000), baseTypes::BitMap(0x0000002011000800),
		baseTypes::BitMap(0x0000080100400400), baseTypes::BitMap(0x0001010101000200), baseTypes::BitMap(0x0002020202000400), baseTypes::BitMap(0x0001010101000200),
		baseTypes::BitMap(0x0000410410400000), baseTypes::BitMap(0x0000208208200000), baseTypes::BitMap(0x0000002084100000), baseTypes::BitMap(0x0000000020880000),
		baseTypes::BitMap(0x0000001002020000), baseTypes::BitMap(0x0000040408020000), baseTypes::BitMap(0x0004040404040000), baseTypes::BitMap(0x0002020202020000),
		baseTypes::BitMap(0x0000104104104000), baseTypes::BitMap(0x0000002082082000), baseTypes::BitMap(0x0000000020841000), baseTypes::BitMap(0x0000000000208800),
		baseTypes::BitMap(0x0000000010020200), baseTypes::BitMap(0x0000000404080200), baseTypes::BitMap(0x0000040404040400), baseTypes::BitMap(0x0002020202020200)
	};


	const baseTypes::BitMap BitMapMoveGenerator::_magicmovesBmask[ baseTypes::squareNumber ] =
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
	
	baseTypes::BitMap BitMapMoveGenerator::_magicmovesBdb[ 5248 ];
	const baseTypes::BitMap* BitMapMoveGenerator::_magicmovesBindices[ baseTypes::squareNumber ] =
	{
		_magicmovesBdb+4992, _magicmovesBdb+2624, _magicmovesBdb+256,  _magicmovesBdb+896,
		_magicmovesBdb+1280, _magicmovesBdb+1664, _magicmovesBdb+4800, _magicmovesBdb+5120,
		_magicmovesBdb+2560, _magicmovesBdb+2656, _magicmovesBdb+288,  _magicmovesBdb+928,
		_magicmovesBdb+1312, _magicmovesBdb+1696, _magicmovesBdb+4832, _magicmovesBdb+4928,
		_magicmovesBdb+0,    _magicmovesBdb+128,  _magicmovesBdb+320,  _magicmovesBdb+960,
		_magicmovesBdb+1344, _magicmovesBdb+1728, _magicmovesBdb+2304, _magicmovesBdb+2432,
		_magicmovesBdb+32,   _magicmovesBdb+160,  _magicmovesBdb+448,  _magicmovesBdb+2752,
		_magicmovesBdb+3776, _magicmovesBdb+1856, _magicmovesBdb+2336, _magicmovesBdb+2464,
		_magicmovesBdb+64,   _magicmovesBdb+192,  _magicmovesBdb+576,  _magicmovesBdb+3264,
		_magicmovesBdb+4288, _magicmovesBdb+1984, _magicmovesBdb+2368, _magicmovesBdb+2496,
		_magicmovesBdb+96,   _magicmovesBdb+224,  _magicmovesBdb+704,  _magicmovesBdb+1088,
		_magicmovesBdb+1472, _magicmovesBdb+2112, _magicmovesBdb+2400, _magicmovesBdb+2528,
		_magicmovesBdb+2592, _magicmovesBdb+2688, _magicmovesBdb+832,  _magicmovesBdb+1216,
		_magicmovesBdb+1600, _magicmovesBdb+2240, _magicmovesBdb+4864, _magicmovesBdb+4960,
		_magicmovesBdb+5056, _magicmovesBdb+2720, _magicmovesBdb+864,  _magicmovesBdb+1248,
		_magicmovesBdb+1632, _magicmovesBdb+2272, _magicmovesBdb+4896, _magicmovesBdb+5184
	};


	baseTypes::BitMap BitMapMoveGenerator::_magicmovesRdb[ 102400 ];
	const baseTypes::BitMap* BitMapMoveGenerator::_magicmovesRindices[ baseTypes::squareNumber ] =
	{
		_magicmovesRdb+86016, _magicmovesRdb+73728, _magicmovesRdb+36864, _magicmovesRdb+43008,
		_magicmovesRdb+47104, _magicmovesRdb+51200, _magicmovesRdb+77824, _magicmovesRdb+94208,
		_magicmovesRdb+69632, _magicmovesRdb+32768, _magicmovesRdb+38912, _magicmovesRdb+10240,
		_magicmovesRdb+14336, _magicmovesRdb+53248, _magicmovesRdb+57344, _magicmovesRdb+81920,
		_magicmovesRdb+24576, _magicmovesRdb+33792, _magicmovesRdb+6144,  _magicmovesRdb+11264,
		_magicmovesRdb+15360, _magicmovesRdb+18432, _magicmovesRdb+58368, _magicmovesRdb+61440,
		_magicmovesRdb+26624, _magicmovesRdb+4096,  _magicmovesRdb+7168,  _magicmovesRdb+0,
		_magicmovesRdb+2048,  _magicmovesRdb+19456, _magicmovesRdb+22528, _magicmovesRdb+63488,
		_magicmovesRdb+28672, _magicmovesRdb+5120,  _magicmovesRdb+8192,  _magicmovesRdb+1024,
		_magicmovesRdb+3072,  _magicmovesRdb+20480, _magicmovesRdb+23552, _magicmovesRdb+65536,
		_magicmovesRdb+30720, _magicmovesRdb+34816, _magicmovesRdb+9216,  _magicmovesRdb+12288,
		_magicmovesRdb+16384, _magicmovesRdb+21504, _magicmovesRdb+59392, _magicmovesRdb+67584,
		_magicmovesRdb+71680, _magicmovesRdb+35840, _magicmovesRdb+39936, _magicmovesRdb+13312,
		_magicmovesRdb+17408, _magicmovesRdb+54272, _magicmovesRdb+60416, _magicmovesRdb+83968,
		_magicmovesRdb+90112, _magicmovesRdb+75776, _magicmovesRdb+40960, _magicmovesRdb+45056,
		_magicmovesRdb+49152, _magicmovesRdb+55296, _magicmovesRdb+79872, _magicmovesRdb+98304
	};
	
}


