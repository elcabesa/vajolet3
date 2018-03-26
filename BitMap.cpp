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

#include <iostream>
#include "BitMap.h"

namespace libChess
{
	namespace baseTypes
	{
		
		/*	\brief return a string representing a bitmap
			\author Marco Belli
			\version 1.0
			\date 17/06/2017
		*/
		std::string BitMap::to_string() const
		{
			std::string s;
			
			for( auto rank : tRankNegativeRange() )
			{
				// rank names
				s += std::to_string( (int)rank + 1) + " ";
				
				//rank data
				for( auto file : tFileRange() )
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
			// file names
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
				
				_RANKMASK[ sq ] = BitMap(0ull);
				
				for( auto file: tFileRange() )
				{
					_RANKMASK[ sq ] += getSquareFromFileRank( file, rank );
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
				
				_FILEMASK[ sq ] = BitMap(0ull);
				
				for( auto rank: tRankRange() )
				{
					_FILEMASK[ sq ] += getSquareFromFileRank( file, rank );
				}
			}
		}

		void BitMap::_initSquareColor(void)
		{
			_SQUARECOLOR[0] = BitMap(0ull);
			_SQUARECOLOR[1] = BitMap(0ull);
			
			for( auto sq: tSquareRange() )
			{
				//===========================================================================
				//initialize SQUARECOLOR
				//===========================================================================
				_SQUARECOLOR[ getColor(sq) ] += sq;
				
			}
		}



		/*	\brief initalize help data
			\author Marco Belli
			\version 1.0
			\date 17/06/2017
		*/
		void BitMap::init(void)
		{
			BitMap _DIAGA1H8MASK[ tSquare::squareNumber ];
			BitMap _DIAGA8H1MASK[ tSquare::squareNumber ];
			
			
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
				
				_DIAGA1H8MASK[ sq ] = BitMap(0ull);
				_DIAGA8H1MASK[ sq ] = BitMap(0ull);
				
				
				int diaga8h1 = file + rank; // from 0 to 14, longest diagonal = 7
				if (diaga8h1 < 8)  // lower half, diagonals 0 to 7
				{
					for (int square = 0 ; square <= diaga8h1 ; square ++)
					{
						_DIAGA8H1MASK[ sq ] += getSquareFromFileRank( tFile( square ), tRank( diaga8h1 - square ) ) ;
					}
				}
				else  // upper half, diagonals 8 to 14
				{
					for (int square = 0 ; square < 15 - diaga8h1 ; square ++)
					{
						_DIAGA8H1MASK[ sq ] += getSquareFromFileRank( tFile( diaga8h1 + square - 7 ), tRank( 7 - square ) );
					}
				}

				int diaga1h8 = file - rank; // from -7 to +7, longest diagonal = 0
				if (diaga1h8 > -1)  // lower half, diagonals 0 to 7
				{
					for (int square = 0 ; square <= 7 - diaga1h8 ; square ++)
					{
						_DIAGA1H8MASK[ sq ] += getSquareFromFileRank( tFile( diaga1h8 + square ), tRank( square ) );
					}
				}
				else
				{
					for (int square = 0 ; square <= 7 + diaga1h8 ; square ++)
					{
						_DIAGA1H8MASK[ sq ] += getSquareFromFileRank( tFile(square), tRank( square - diaga1h8 ) );
					}
				}
			}
			
			for( auto sq1: tSquareRange() )
			{
				for( auto sq2: tSquareRange() )
				{
					_LINES[ sq1 ][ sq2 ] = BitMap(0ull);
					_SQUARES_BETWEEN[ sq1 ][ sq2 ] = BitMap(0ull);
					
					if( sq1 != sq2 )
					{
						if( getFile( sq1 ) == getFile( sq2 ) )
						{
							// stessa colonna

							_LINES[ sq1 ][ sq2 ] = _FILEMASK[ sq1 ];
							if( getRank( sq2 ) > getRank( sq1 ) ) // in salita
							{
								tRank temp = getRank( sq1 ) + 1;
								while( temp < getRank( sq2 ) )
								{
									_SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( getFile( sq1 ), temp );
									++temp;
								}
							}
							if( getRank( sq2 ) < getRank( sq1 ) ) // in discesa
							{
								tRank temp = getRank( sq1 ) - 1;
								while( temp > getRank( sq2 ) )
								{
									_SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( getFile( sq1 ), temp );
									--temp;
								}
							}
						}
						if( getRank( sq1 ) == getRank( sq2 ) )
						{
							_LINES[ sq1 ][ sq2 ] = _RANKMASK[ sq1 ];
							if( getFile( sq2 ) > getFile( sq1 ) ) // in salita
							{
								tFile temp = getFile( sq1 ) + 1;
								while( temp < getFile( sq2 ) )
								{
									_SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, getRank( sq1 ) );
									++temp;
								}
							}
							if( getFile( sq2 ) < getFile( sq1 ) ) // in discesa
							{
								tFile temp = getFile( sq1 ) - 1;
								while( temp > getFile( sq2 ) )
								{
									_SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, getRank( sq1 ) );
									--temp;
								}
							}
						}
						if( _DIAGA1H8MASK[ sq1 ].isSquareSet( sq2 ) )
						{
							_LINES[ sq1 ][ sq2 ] = _DIAGA1H8MASK[ sq1 ];
							if( getFile( sq2 ) > getFile( sq1 ) ) // in salita
							{
								tFile temp = getFile( sq1 ) + 1;
								tRank temp2 = getRank( sq1 ) + 1;
								while( temp < getFile( sq2 ) )
								{
									_SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, temp2 );
									++temp;
									++temp2;
								}
							}
							if( getFile( sq2 ) < getFile( sq1 ) ) // in discesa
							{
								tFile temp = getFile( sq1 ) - 1;
								tRank temp2 = getRank( sq1 ) - 1;
								while( temp > getFile( sq2 ) )
								{
									_SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, temp2 );
									--temp;
									--temp2;
								}
							}
						}
						if(_DIAGA8H1MASK[ sq1 ].isSquareSet( sq2 ) )
						{
							_LINES[ sq1 ][ sq2 ] = _DIAGA8H1MASK[ sq1 ];
							if( getFile( sq2 ) > getFile( sq1 ) ) // in salita
							{
								tFile temp = getFile( sq1 ) + 1;
								tRank temp2 = getRank( sq1 ) - 1;
								while( temp < getFile( sq2 ) )
								{
									_SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, temp2 );
									++temp;
									--temp2;
								}
							}
							if( getFile( sq2 ) < getFile( sq1 ) ) // in discesa
							{
								tFile temp = getFile( sq1 ) - 1;
								tRank temp2 = getRank( sq1 ) + 1;
								while( temp > getFile( sq2 ) )
								{
									_SQUARES_BETWEEN[ sq1 ][ sq2 ] += getSquareFromFileRank( temp, temp2 );
									--temp;
									++temp2;
								}
							}
						}					
					}
				}
			}	
		}
		
		BitMap BitMap::_RANKMASK[ tSquare::squareNumber ];			//!< bitmask of a rank given a square on the rank
		BitMap BitMap::_FILEMASK[ tSquare::squareNumber ];			//!< bitmask of a file given a square on the rank
		BitMap BitMap::_SQUARECOLOR[ tColor::colorNumber ] = { BitMap(0ull), BitMap(0ull) };
		BitMap BitMap::_SQUARES_BETWEEN[ tSquare::squareNumber ][ tSquare::squareNumber ];
		BitMap BitMap::_LINES[ tSquare::squareNumber ][ tSquare::squareNumber ];
	}
}
