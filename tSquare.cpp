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
#include "tSquare.h"

unsigned int SQUARE_DISTANCE[ static_cast<int>(tSquare::squareNumber) ][ static_cast<int>(tSquare::squareNumber) ];
tColor SQUARE_COLOR[ static_cast<int>(tSquare::squareNumber) ];

void inittSquare(void)
{
	for(auto square1 : tSquareRange())
	{
		for(auto square2 : tSquareRange())
		{
			SQUARE_DISTANCE[ static_cast<int>(square1) ][ static_cast<int>(square2) ] = 
				std::max(
					static_cast<int>(std::abs( static_cast<int>( (getFile( square1 ) - getFile( square2 ) ) ) ) ),
					static_cast<int>(std::abs( static_cast<int>( (getRank( square1 ) - getRank( square2 ) ) ) ) )
				);
		}
	}
	
	for(auto square : tSquareRange())
	{
		auto file = getFile(square);
		auto rank = getRank(square);
		SQUARE_COLOR[ static_cast<int>(square) ] = (tColor)( ( static_cast<int>(file) + static_cast<int>(rank) + 1 ) % 2 );
		
	}
	
}




