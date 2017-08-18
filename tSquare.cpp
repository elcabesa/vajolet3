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

unsigned int SQUARE_DISTANCE[ tSquare::squareNumber ][ tSquare::squareNumber ];

void inittSquare(void)
{
	for(auto square1 : tSquareRange())
	{
		for(auto square2 : tSquareRange())
		{
			SQUARE_DISTANCE[ square1 ][ square2 ] = std::max(std::abs( getFile( square1 ) - getFile( square2 ) ), std::abs( getRank( square1 ) - getRank( square2 ) ) );
		}
	}

}




