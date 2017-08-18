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

BitMap BitMap::RANKMASK[ tSquare::squareNumber ];			//!< bitmask of a rank given a square on the rank
BitMap BitMap::FILEMASK[ tSquare::squareNumber ];			//!< bitmask of a file given a square on the rank

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




void BitMap::init(void)
{
	for (tFile file = tFile::A; file <= tFile::H; file++)
	{
		for (tRank rank = tRank::one; rank <= tRank::eight; rank++)
		{
			//===========================================================================
			//initialize 8-bit rank mask
			//===========================================================================

			RANKMASK[ (int)getSquareFromFileRank( file, rank ) ] = getSquareFromFileRank(tFile::A, rank);
			RANKMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(tFile::B, rank);
			RANKMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(tFile::C, rank);
			RANKMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(tFile::D, rank);
			RANKMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(tFile::E, rank);
			RANKMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(tFile::F, rank);
			RANKMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(tFile::G, rank);
			RANKMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(tFile::H, rank);

			//===========================================================================
			//initialize 8-bit file mask
			//===========================================================================
			FILEMASK[ (int)getSquareFromFileRank( file, rank ) ] = getSquareFromFileRank(file, tRank::one);
			FILEMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(file, tRank::two);
			FILEMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(file, tRank::three);
			FILEMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(file, tRank::four);
			FILEMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(file, tRank::five);
			FILEMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(file, tRank::six);
			FILEMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(file, tRank::seven);
			FILEMASK[ (int)getSquareFromFileRank( file, rank ) ] += getSquareFromFileRank(file, tRank::eight);

		}
	}
}
