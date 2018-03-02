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
	
}


