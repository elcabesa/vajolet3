
//---------------------------------
//	includes
//---------------------------------

#include <random>
#include "hashKeys.h"

namespace libChess
{
//---------------------------------
//	global static hashKeys
//---------------------------------

uint64_t  HashKeys::_keys[tSquare::squareNumber][_KeyNum];	// position, piece (not all the keys are used)
uint64_t  HashKeys::_side;          							// side to move (black)
uint64_t  HashKeys::_ep[tSquare::squareNumber];        		// ep targets (only 16 used)
uint64_t  HashKeys::_castlingRight[_CastlingRightSize];		// white king-side castling right
uint64_t  HashKeys::_exclusion;								// position with an exluded move

/*!	\brief init the hashkeys
    \author Marco Belli
	\version 1.0
	\date 27/10/2013
 */
void HashKeys::init()
{
	// initialize all random 64-bit numbers
	unsigned int i,j;
	uint64_t temp[_CastlingRightBit];
	std::mt19937_64 rnd;
	std::uniform_int_distribution<uint64_t> uint_dist;

	// use current time (in seconds) as random seed:
	rnd.seed(19091979);

	for (auto & val :_ep)
	{
		val = uint_dist(rnd);
	}

	for(auto & outerArray :_keys)
	{
		for(auto & val :outerArray)
		{
			val = uint_dist(rnd);
		}

	}

	_side = uint_dist(rnd);
	_exclusion=uint_dist(rnd);

	for(auto & val :_castlingRight )
	{
		val = 0;
	}


	for(auto & val :temp)
	{
		val=uint_dist(rnd);
	}

	for( i = 0; i<_CastlingRightSize; i++ )
	{
		for( j = 0; j < _CastlingRightBit; j++ )
		{
			if(i&(1<<j))
			{
				_castlingRight[i] ^= temp[j];
			}
		}
	}

}

}

