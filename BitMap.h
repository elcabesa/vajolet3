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

#ifndef BITMAP_H_
#define BITMAP_H_

#include <cstdint>
#include <string>
#include "tSquare.h"

class BitMap
{
private:
	uint64_t b;
public:

	BitMap(){};
	BitMap(uint64_t _b): b(_b){}
	BitMap(const BitMap& x): b(x.b){}

	/*	\brief count the number of 1 bits in a 64 bit variable
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	inline int bitCnt() const
	{
		return __builtin_popcountll( b );
	}


	/*	\brief get the index of the rightmost one bit
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	inline tSquare firstOne() const
	{
		assert(b !=0);
		return (tSquare)__builtin_ctzll( b ) ;
	}

	/*	\brief return true if the bitmap has more than one bit set
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	inline bool moreThanOneBit() const
	{
		return bitCnt() > 1;
	}


	std::string to_string() const;

	/*	\brief return a BitMap with the nth bit set
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline BitMap getBitmapFromSquare(const tSquare n)
	{
		assert( n < tSquare::squareNumber );
		return BitMap(1ull << (int)n);
		//return (BITSET[n]);
	}

	/*	\brief return a BitMap with the nth bit set
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline BitMap getBitmapFromSquare( const tFile f, const tRank r )
	{
		assert( f <= tFile::H );
		assert( r <= tRank::eight );
		assert( f >= tFile::A );
		assert( r >= tRank::one );
		return BitMap(1ull << (int)gettSquareFromFileRank( f, r ) );
	}

	/*	\brief return true if the square is set in the bitmap
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	inline bool isSquareSet(const tSquare sq) const
	{
		return (b & getBitmapFromSquare(sq).b);
	}

	/*	\brief return true if the square is set in the bitmap
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	inline bool isSquareSet(const tFile f, const tRank r) const
	{
		return (b & getBitmapFromSquare( f, r ).b);
	}

	/* iterator */
	class iterator: public std::iterator<
	                        std::input_iterator_tag,   // iterator_category
							tSquare,                      // value_type
							tSquare,
							const tSquare*,
							tSquare
							>{
		unsigned long long b;
		public:
			explicit iterator(unsigned long long _b = 0ull) : b(_b) {}
			iterator& operator++() { b &= ( b - 1 ); return *this;}
			iterator operator++(int) { iterator retval = *this; ++(*this); return retval;}
			bool operator==(iterator other) const { return b == other.b; }
			bool operator!=(iterator other) const { return b != other.b; }
			reference operator*() const {return (tSquare)__builtin_ctzll(b);}
	};
	iterator begin() {return iterator(b);}
	iterator end() {return iterator(0);}

	/* operators */
	inline bool operator ==(const BitMap& rhs) const { return b == rhs.b;}
/*	//inline bitmap2 operator += (const tSquare sq) { b |= bitHelper::getBitmapFromSquare(sq); return *this; }
	inline bitmap2& operator=(const bitmap2& other){ b = other.b; return *this;}

	inline bool operator=(const bitmap2& other){ return other.b;}
	inline bitmap2& operator|=(const bitmap2& other){ b |= other.b; return *this;}
	inline bitmap2& operator&=(const bitmap2& other){ b &= other.b; return *this;}
	inline bitmap2& operator^=(const bitmap2& other){ b ^= other.b; return *this;}
	inline bitmap2 operator|(const bitmap2& other) const { return bitmap2(b | other.b); }
	inline bitmap2 operator&(const bitmap2& other) const { return bitmap2(b & other.b); }
	inline bitmap2 operator^(const bitmap2& other) const { return bitmap2(b ^ other.b); }
	inline bitmap2 operator&&(const bitmap2& other) const { return bitmap2(b && other.b); }

	inline bitmap2& operator|=(const bitMap& other){ b |= other; return *this;} // todo remove
	inline bitmap2& operator&=(const bitMap& other){ b &= other; return *this;} // todo remove
	inline bitmap2 operator|(const bitMap& other) const { return bitmap2(b | other); } // todo remove
	inline bitmap2 operator&(const bitMap& other) const { return bitmap2(b & other); } // todo remove
	inline bitmap2& operator^=(const bitMap& other){ b ^= other; return *this;} // todo remove
	inline bitMap getBitmap(void)const { return b;} // TODO remove
	inline bitmap2& operator=(const bitMap& other){ b = other; return *this;} // todo remove

	inline operator !() const { return b==0;}
	inline operator bool() const { return b!=0;}
	inline operator bitMap() const { return b;}

*/
};







#endif /* BITMAP_H_ */
