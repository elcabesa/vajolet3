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

#ifndef HASHKEYS_H_
#define HASHKEYS_H_


//---------------------------------
//	includes
//---------------------------------
#include "vajolet.h"
#include "tSquare.h"

namespace libChess
{
//---------------------------------
//	class
//---------------------------------
class HashKeys
{
private:
	static const unsigned int _CastlingRightBit = 4;
	static const unsigned int _CastlingRightSize = 1<<_CastlingRightBit;
	static const unsigned int _KeyNum = 30;
	static uint64_t _keys[tSquare::squareNumber][_KeyNum];	// position, piece (not all the keys are used)
	static uint64_t _side;									// side to move (black)
	static uint64_t _ep[tSquare::squareNumber];				// ep targets (only 16 used)
	static uint64_t _castlingRight[_CastlingRightSize];		// white king-side castling right
	static uint64_t _exclusion;

public:

	static void init();       // initialize the random data
	static inline uint64_t getKeys(const tSquare sq,const /*piece*/ unsigned int p){ return _keys[sq][p];};
	static inline uint64_t getSide(){ return _side;};
	static inline uint64_t getEp(const tSquare sq){ return _ep[sq];};
	static inline uint64_t getCastlingRight(const unsigned int cr){ return _castlingRight[cr];};
	static inline uint64_t getExclusion(){ return _exclusion;};
};

}

#endif /* HASHKEYS_H_ */
