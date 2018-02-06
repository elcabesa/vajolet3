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
#include "Vajolet.h"
#include "tSquare.h"
#include "BitBoardIndex.h"

namespace libChess
{
//---------------------------------
//	class
//---------------------------------
class HashKey
{
	uint64_t _key;
public:
	HashKey():_key(0){};
	explicit HashKey(const uint64_t key):_key(key){};
	
	
	HashKey ( const HashKey & ) = default;
	
	HashKey& operator=(HashKey & other){_key = other._key; return *this;}
	bool operator==(const HashKey & other)const {return (_key == other._key);}
	bool operator!=(const HashKey & other)const {return (_key != other._key);}
	
	//uint64_t inline getKey(void)const{ return _key; } 
	
	HashKey inline exclusion(void)const{ return HashKey(_key ^ _exclusion); }
	
	void inline movePiece(const bitboardIndex p , const tSquare fromSq, const tSquare toSq){_key ^= _keys[fromSq][p] ^ _keys[toSq][p];};
	void inline addPiece(const bitboardIndex p, const tSquare sq){_key ^= _keys[sq][p];};
	void inline removePiece(const bitboardIndex p, const tSquare sq){_key ^= _keys[sq][p];};
	void inline changeSide(void){_key ^= _side;};
	void inline addEp(const tSquare sq){_key ^= _ep[sq];};
	void inline removeEp(const tSquare sq){_key ^= _ep[sq];};
	void inline changeCastlingRight(const unsigned int cr){_key ^= _castlingRight[cr];};
	
	
	
private:
	
	static const unsigned int _CastlingRightBit = 4;
	static const unsigned int _CastlingRightSize = 1<<_CastlingRightBit;
	static const unsigned int _KeyNum = bitboardNumber;
	static uint64_t _keys[tSquare::squareNumber][_KeyNum];	// position, piece (not all the keys are used)
	static uint64_t _side;									// side to move (black)
	static uint64_t _ep[tSquare::squareNumber];				// ep targets (only 16 used)
	static uint64_t _castlingRight[_CastlingRightSize];		// white king-side castling right
	static uint64_t _exclusion;

public:

	static void init();       // initialize the random data
	//static inline uint64_t getKeys(const tSquare sq,const /*piece*/ unsigned int p){ return _keys[sq][p];};
	//static inline uint64_t getSide(){ return _side;};
	//static inline uint64_t getEp(const tSquare sq){ return _ep[sq];};
	//static inline uint64_t getCastlingRight(const unsigned int cr){ return _castlingRight[cr];};
	//static inline uint64_t getExclusion(){ return _exclusion;};
};

}

#endif /* HASHKEYS_H_ */
