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

#include <list>
#include <utility>
#include "BitMapMoveGenerator.h"

namespace libChess
{
	void BitMapMoveGenerator::init(void)
	{
		
		// KING attacks;
		for ( const auto square : baseTypes::tSquareRange() )
		{
			std::list<std::pair<int,int>> directions = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
			for( auto dir :directions )
			{
				const baseTypes::tFile toFile = getFile( square ) + dir.first;
				const baseTypes::tRank toRank = getRank( square ) + dir.second;
						
				
				if( isValidFile( toFile ) && isValidRank( toRank ) )
				{
					_kingMoveBitmap[square] += getSquareFromFileRank( toFile, toRank );
				}
			}
		}
		
		for ( const auto square : baseTypes::tSquareRange() )
		{
			std::list<std::pair<int,int>> directions = { {-2,1}, {-2,-1}, {2,1}, {2,-1}, {1,2}, {1,-2}, {-1,2}, {-1,-2} };
			for( auto dir :directions )
			{
				const baseTypes::tFile toFile = getFile( square ) + dir.first;
				const baseTypes::tRank toRank = getRank( square ) + dir.second;
						
				
				if( isValidFile( toFile ) && isValidRank( toRank ) )
				{
					_knightMoveBitmap[square] += getSquareFromFileRank( toFile, toRank );
				}
			}
		}

	}
	
	baseTypes::BitMap BitMapMoveGenerator::_kingMoveBitmap[ baseTypes::squareNumber ] = { baseTypes::BitMap(0) };
	baseTypes::BitMap BitMapMoveGenerator::_knightMoveBitmap[ baseTypes::squareNumber ] = { baseTypes::BitMap(0) };
	
}


