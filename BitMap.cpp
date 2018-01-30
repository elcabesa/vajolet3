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
#include <iostream>

#include "vajolet.h"
#include "BitMap.h"

namespace libChess
{
	
BitMap BitMap::RANKMASK[ tSquare::squareNumber ];			//!< bitmask of a rank given a square on the rank
BitMap BitMap::FILEMASK[ tSquare::squareNumber ];			//!< bitmask of a file given a square on the rank
BitMap BitMap::SQUARECOLOR[ 2 ] = { 0ull, 0ull };
BitMap BitMap::SQUARES_BETWEEN[ tSquare::squareNumber ][ tSquare::squareNumber ];
BitMap BitMap::LINES[ tSquare::squareNumber ][ tSquare::squareNumber ];

/*	\brief return a string representing a bitmap
	\author Marco Belli
	\version 1.0
	\date 17/06/2017
*/
std::string BitMap::to_string() const
{

	std::string s;
	for (tRank rank = tRank::eight ; rank >= tRank::one; rank--)
	{
		s += std::to_string( (int)rank + 1) + " ";
		for (tFile file = tFile::A ; file <= tFile::H; file++)
		{

			if ( this->isSquareSet( file, rank ) )
			{
				s += '1';
			}
			else
			{
				s += '.';
			}

		}
		s += "\n";
	}
	s +=  "  abcdefgh";
	return (s);
}

void BitMap::_initRankMask(void)
{
	for( auto sq: tSquareRange() )
	{
		
		tRank rank = getRank( sq );
		
		//===========================================================================
		//initialize 8-bit rank mask
		//===========================================================================
		
		RANKMASK[ sq ] = 0ull;
		
		for( auto file: tFileRange() )
		{
			RANKMASK[ sq ] += getSquareFromFileRank( file, rank );
		}
	}	
}

void BitMap::_initFileMask(void)
{
	for( auto sq: tSquareRange() )
	{
		tFile file = getFile( sq );
		
		//===========================================================================
		//initialize 8-bit file mask
		//===========================================================================
		
		FILEMASK[ sq ] = 0ull;
		
		for( auto rank: tRankRange() )
		{
			FILEMASK[ sq ] += getSquareFromFileRank( file, rank );
		}
	}
}

void BitMap::_initSquareColor(void)
{
	SQUARECOLOR[0] = 0ull;
	SQUARECOLOR[1] = 0ull;
	
	for( auto sq: tSquareRange() )
	{
		//===========================================================================
		//initialize SQUARECOLOR
		//===========================================================================
		SQUARECOLOR[ getColor(sq) ] += sq;
		
	}
}



/*	\brief initalize help data
	\author Marco Belli
	\version 1.0
	\date 17/06/2017
*/
void BitMap::init(void)
{
	BitMap DIAGA1H8MASK[ tSquare::squareNumber ];
	BitMap DIAGA8H1MASK[ tSquare::squareNumber ];
	
	
	_initRankMask();
	_initFileMask();
	_initSquareColor();
	
	for( auto sq: tSquareRange() )
	{
		tFile file = getFile( sq );
		tRank rank = getRank( sq );
		
		
		//===========================================================================
		//Initialize 8-bit diagonal mask
		//===========================================================================
		
		DIAGA1H8MASK[ sq ] = 0ull;
		DIAGA8H1MASK[ sq ] = 0ull;
		
		
		int diaga8h1 = file + rank; // from 0 to 14, longest diagonal = 7
		if (diaga8h1 < 8)  // lower half, diagonals 0 to 7
		{
			for (int square = 0 ; square <= diaga8h1 ; square ++)
			{
				DIAGA8H1MASK[ sq ] += getSquareFromFileRank( tFile( square ), tRank( diaga8h1 - square ) ) ;
			}
		}
		else  // upper half, diagonals 8 to 14
		{
			for (int square = 0 ; square < 15 - diaga8h1 ; square ++)
			{
				DIAGA8H1MASK[ sq ] += getSquareFromFileRank( tFile( diaga8h1 + square - 7 ), tRank( 7 - square ) );
			}
		}

		int diaga1h8 = file - rank; // from -7 to +7, longest diagonal = 0
		if (diaga1h8 > -1)  // lower half, diagonals 0 to 7
		{
			for (int square = 0 ; square <= 7 - diaga1h8 ; square ++)
			{
				DIAGA1H8MASK[ sq ] += getSquareFromFileRank( tFile( diaga1h8 + square ), tRank( square ) );
			}
		}
		else
		{
			for (int square = 0 ; square <= 7 + diaga1h8 ; square ++)
			{
				DIAGA1H8MASK[ sq ] += getSquareFromFileRank( tFile(square), tRank( square - diaga1h8 ) );
			}
		}
	}
	
	for( auto sq1: tSquareRange() )
	{
		for( auto sq2: tSquareRange() )
		{
			LINES[ sq1 ][ sq2 ] = 0ull;
			SQUARES_BETWEEN[ sq1 ][ sq2 ] = 0ull;
			
			if( sq1 != sq2 )
			{
				if( getFile( sq1 ) == getFile( sq2 ) )
				{
					// stessa colonna

					LINES[ sq1 ][ sq2 ] = FILEMASK[ sq1 ];
					if( getRank( sq2 ) > getRank( sq1 ) ) // in salita
					{
						tRank temp = getRank( sq1 ) + 1;
						while( temp < getRank( sq2 ) )
						{
							SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( getFile( sq1 ), temp );
							temp++;
						}
					}
					if( getRank( sq2 ) < getRank( sq1 ) ) // in discesa
					{
						tRank temp = getRank( sq1 ) - 1;
						while( temp > getRank( sq2 ) )
						{
							SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( getFile( sq1 ), temp );
							temp--;
						}
					}
				}
				if( getRank( sq1 ) == getRank( sq2 ) )
				{
					LINES[ sq1 ][ sq2 ] = RANKMASK[ sq1 ];
					if( getFile( sq2 ) > getFile( sq1 ) ) // in salita
					{
						tFile temp = getFile( sq1 ) + 1;
						while( temp < getFile( sq2 ) )
						{
							SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, getRank( sq1 ) );
							temp++;
						}
					}
					if( getFile( sq2 ) < getFile( sq1 ) ) // in discesa
					{
						tFile temp = getFile( sq1 ) - 1;
						while( temp > getFile( sq2 ) )
						{
							SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, getRank( sq1 ) );
							temp--;
						}
					}
				}
				if( DIAGA1H8MASK[ sq1 ].isSquareSet( sq2 ) )
				{
					LINES[ sq1 ][ sq2 ] = DIAGA1H8MASK[ sq1 ];
					if( getFile( sq2 ) > getFile( sq1 ) ) // in salita
					{
						tFile temp = getFile( sq1 ) + 1;
						tRank temp2 = getRank( sq1 ) + 1;
						while( temp < getFile( sq2 ) )
						{
							SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, temp2 );
							temp++;
							temp2++;
						}
					}
					if( getFile( sq2 ) < getFile( sq1 ) ) // in discesa
					{
						tFile temp = getFile( sq1 ) - 1;
						tRank temp2 = getRank( sq1 ) - 1;
						while( temp > getFile( sq2 ) )
						{
							SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, temp2 );
							temp--;
							temp2--;
						}
					}
				}
				if(DIAGA8H1MASK[ sq1 ].isSquareSet( sq2 ) )
				{
					LINES[ sq1 ][ sq2 ] = DIAGA8H1MASK[ sq1 ];
					if( getFile( sq2 ) > getFile( sq1 ) ) // in salita
					{
						tFile temp = getFile( sq1 ) + 1;
						tRank temp2 = getRank( sq1 ) - 1;
						while( temp < getFile( sq2 ) )
						{
							SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, temp2 );
							temp++;
							temp2--;
						}
					}
					if( getFile( sq2 ) < getFile( sq1 ) ) // in discesa
					{
						tFile temp = getFile( sq1 ) - 1;
						tRank temp2 = getRank( sq1 ) + 1;
						while( temp > getFile( sq2 ) )
						{
							SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, temp2 );
							temp--;
							temp2++;
						}
					}
				}
				
			}
		}
	}
	
	
}

}
