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
*/
#include "tSquare.h"
#include "eTurn.h"

namespace libChess
{
	namespace baseTypes
	{
	unsigned int SQUARE_DISTANCE[ tSquare::squareNumber ][ tSquare::squareNumber ];
	eTurn SQUARE_COLOR[ tSquare::squareNumber ];

	void inittSquare(void)
	{
		for(auto square1 : tSquareRange())
		{
			for(auto square2 : tSquareRange())
			{
				SQUARE_DISTANCE[ square1 ][ square2 ] = 
					std::max(
						distance( getFile( square1 ) , getFile( square2 ) ) ,
						distance( getRank( square1 ) , getRank( square2 ) )
					);
			}
		}
		
		for(auto square : tSquareRange())
		{
			auto file = getFile(square);
			auto rank = getRank(square);
			SQUARE_COLOR[ square ] = (eTurn)( ( file + rank + 1 ) % 2 );
			
		}
		
	}
	}

}




