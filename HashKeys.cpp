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


//---------------------------------
//	includes
//---------------------------------

#include <random>
#include "HashKeys.h"

namespace libChess
{

/*!	\brief init the HashKey
    \author Marco Belli
	\version 1.0
	\date 27/10/2013
 */
void HashKey::init()
{
	// initialize all random 64-bit numbers
	unsigned int i,j;
	uint64_t temp[_CastlingRightBit] = {0};
	std::mt19937_64 rnd;
	std::uniform_int_distribution<uint64_t> uint_dist;

	// use current time (in seconds) as random seed:
	rnd.seed(19091979);

	/********************
	load ep keys
	*********************/
	for (auto & val :_ep)
	{
		val = uint_dist(rnd);
	}

	/********************
	load piece keys
	*********************/
	for(auto & outerArray :_keys)
	{
		for(auto & val :outerArray)
		{
			val = uint_dist(rnd);
		}

	}

	/********************
	load side and exclusion keys
	*********************/
	_side = uint_dist(rnd);
	_exclusion = uint_dist(rnd);

	
	/********************
	load castling keys
	*********************/
	
	//prepare temp keys
	for(auto & val :temp)
	{
		val = uint_dist(rnd);
	}

	// save precalculated castling keys 	
	for( i = 0; i<_CastlingRightSize; ++i )
	{
		_castlingRight[i] = 0;
		
		for( j = 0; j < _CastlingRightBit; ++j )
		{
			if( i & ( 1<<j ) )
			{
				_castlingRight[i] ^= temp[j];
			}
		}
	}

}

//---------------------------------
//	global static HashKey
//---------------------------------

uint64_t  HashKey::_keys[baseTypes::tSquare::squareNumber][_KeyNum];	// position, piece (not all the keys are used)
uint64_t  HashKey::_side;          							// side to move (black)
uint64_t  HashKey::_ep[baseTypes::tSquare::squareNumber];   // ep targets (only 16 used)
uint64_t  HashKey::_castlingRight[_CastlingRightSize];		// white king-side castling right
uint64_t  HashKey::_exclusion;								// position with an exluded move

}

