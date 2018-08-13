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

#ifndef HASHKEYS_H_
#define HASHKEYS_H_


//---------------------------------
//	includes
//---------------------------------
#include "tSquare.h"
#include "BitBoardIndex.h"
#include "eCastle.h"

namespace libChess
{
//---------------------------------
//	class
//---------------------------------
class HashKey
{
public:

	/*****************************************************************
	*	constructors
	******************************************************************/
	HashKey():_key(0){};
	explicit HashKey(const uint64_t key):_key(key){};
	HashKey ( const HashKey & ) = default;
	
	/*****************************************************************
	*	Operators
	******************************************************************/
	HashKey& operator=(const HashKey & other){_key = other._key; return *this;}
	bool operator==(const HashKey & other)const {return (_key == other._key);}
	bool operator!=(const HashKey & other)const {return (_key != other._key);}
	
	/*****************************************************************
	*	methods
	******************************************************************/
	
	//uint64_t inline getKey(void)const{ return _key; } 
	
	HashKey exclusion(void) const;
	
	HashKey& movePiece( const baseTypes::bitboardIndex p, const baseTypes::tSquare fromSq, const baseTypes::tSquare toSq );
	HashKey& addPiece( const baseTypes::bitboardIndex p, const baseTypes::tSquare sq );
	HashKey& removePiece( const baseTypes::bitboardIndex p, const baseTypes::tSquare sq );
	HashKey& changeSide( void );
	HashKey& addEp( const baseTypes::tSquare sq );
	HashKey& removeEp( const baseTypes::tSquare sq );
	HashKey& changeCastlingRight( const baseTypes::eCastle cr );
	
private:
	uint64_t _key;

public:

	/*****************************************************************
	*	static methods
	******************************************************************/
	
	static void init();       // initialize the random data
	//static inline uint64_t getKeys(const baseTypes::tSquare sq,const /*piece*/ unsigned int p){ return _keys[sq][p];};
	//static inline uint64_t getSide(){ return _side;};
	//static inline uint64_t getEp(const baseTypes::tSquare sq){ return _ep[sq];};
	//static inline uint64_t getCastlingRight(const unsigned int cr){ return _castlingRight[cr];};
	//static inline uint64_t getExclusion(){ return _exclusion;};
	
private:
	/*****************************************************************
	*	static members
	******************************************************************/
	static const unsigned int _CastlingRightBit = 4;
	static const unsigned int _CastlingRightSize = 1<<_CastlingRightBit;
	static const unsigned int _KeyNum = baseTypes::bitboardNumber;
	static uint64_t _keys[baseTypes::tSquare::squareNumber][_KeyNum];	// position, piece (not all the keys are used)
	static uint64_t _side;									// side to move (black)
	static uint64_t _ep[baseTypes::tSquare::squareNumber];				// ep targets (only 16 used)
	static uint64_t _castlingRight[_CastlingRightSize];		// white king-side castling right
	static uint64_t _exclusion;


};

inline HashKey HashKey::exclusion(void)const{ return HashKey(_key ^ _exclusion); }
	
inline HashKey& HashKey::movePiece(const baseTypes::bitboardIndex p , const baseTypes::tSquare fromSq, const baseTypes::tSquare toSq)
{
	_key ^= _keys[fromSq][p] ^ _keys[toSq][p];
	return *this;
}

inline HashKey& HashKey::addPiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare sq)
{
	_key ^= _keys[sq][p];
	return *this;
}

inline HashKey& HashKey::removePiece(const baseTypes::bitboardIndex p, const baseTypes::tSquare sq)
{
	_key ^= _keys[sq][p];
	return *this;
}

inline HashKey& HashKey::changeSide(void)
{
	_key ^= _side;
	return *this;
}

inline HashKey& HashKey::addEp(const baseTypes::tSquare sq)
{
	_key ^= _ep[sq];
	return *this;
}

inline HashKey& HashKey::removeEp(const baseTypes::tSquare sq)
{
	_key ^= _ep[sq];
	return *this;

	}
inline HashKey& HashKey::changeCastlingRight(const baseTypes::eCastle cr)
{
	_key ^= _castlingRight[cr];
	return *this;
}



}

#endif /* HASHKEYS_H_ */
