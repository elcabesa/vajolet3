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

BitMap BitMap::RANKMASK[ static_cast<typename std::underlying_type<tSquare>::type>(tSquare::squareNumber) ];			//!< bitmask of a rank given a square on the rank
BitMap BitMap::FILEMASK[ static_cast<typename std::underlying_type<tSquare>::type>(tSquare::squareNumber) ];			//!< bitmask of a file given a square on the rank

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

			RANKMASK[ (int)getFromFileRank( file, rank ) ] = getFromFileRank(tFile::A, rank);
			RANKMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(tFile::B, rank);
			RANKMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(tFile::C, rank);
			RANKMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(tFile::D, rank);
			RANKMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(tFile::E, rank);
			RANKMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(tFile::F, rank);
			RANKMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(tFile::G, rank);
			RANKMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(tFile::H, rank);

			//===========================================================================
			//initialize 8-bit file mask
			//===========================================================================
			FILEMASK[ (int)getFromFileRank( file, rank ) ] = getFromFileRank(file, tRank::one);
			FILEMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(file, tRank::two);
			FILEMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(file, tRank::three);
			FILEMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(file, tRank::four);
			FILEMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(file, tRank::five);
			FILEMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(file, tRank::six);
			FILEMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(file, tRank::seven);
			FILEMASK[ (int)getFromFileRank( file, rank ) ] += getFromFileRank(file, tRank::eight);

		}
	}
}
