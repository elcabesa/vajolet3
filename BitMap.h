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

#ifndef BITMAP_H_
#define BITMAP_H_

#include <assert.h>
#include "tSquare.h"

namespace libChess
{	
	namespace baseTypes
	{
		/*	\brief this class implement a 64bit representation of a board containing pieces
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		class BitMap
		{
			
		public:
			/*****************************************************************
			*	constructors
			******************************************************************/
			BitMap(){};
			BitMap ( const BitMap & ) = default;	
			explicit BitMap(uint64_t b): _b(b){}
			
			/*****************************************************************
			*	Operators
			******************************************************************/
			
			inline bool operator ==(const BitMap& rhs) const { return _b == rhs._b;}
			
			inline BitMap& operator += (const tSquare sq) { _b |= getBitmapFromSquare(sq)._b; return (*this); }
			inline BitMap& operator +=(const BitMap& x) { _b |= x._b; return (*this); }
			
			inline BitMap& operator &=(const BitMap& x) { _b &= x._b; return (*this); }
			
			inline BitMap& operator = (const tSquare sq) { _b = getBitmapFromSquare(sq)._b; return (*this); }
			inline BitMap& operator = (const BitMap& x) { _b = x._b; return (*this); }
			
			inline BitMap operator +(const BitMap& rhs) const { return BitMap(_b | rhs._b); }
			
			inline BitMap operator &(const BitMap& rhs) const { return BitMap(_b & rhs._b); }
			
			inline BitMap operator ^(const tSquare sq) const { return BitMap(_b ^ getBitmapFromSquare(sq)._b); }
			inline BitMap operator ^(const BitMap& rhs) const { return BitMap(_b ^ rhs._b); }
			
			inline BitMap& operator ^=(const tSquare sq) { _b ^= getBitmapFromSquare(sq)._b; return (*this); }
			inline BitMap& operator ^=(const BitMap& x) { _b ^= x._b; return (*this); }
			
			inline BitMap operator <<(const unsigned int shift) const { return BitMap(_b << shift);}
			inline BitMap operator >>(const unsigned int shift) const { return BitMap(_b >> shift);}
			
			inline BitMap& operator <<=(const unsigned int shift) { _b <<= shift; return (*this);}
			inline BitMap& operator >>=(const unsigned int shift) { _b >>= shift; return (*this);}
			
			inline BitMap operator~() const { return BitMap(~_b ); }
			
			/*****************************************************************
			*	Iterator
			******************************************************************/
			class iterator: public std::iterator<
									std::input_iterator_tag,	// iterator_category
									tSquare
									>{
				public:
					explicit iterator(const uint64_t b = 0ull) : _b(b) {}
					iterator& operator++() { _b &= ( _b - 1 ); return *this;}
					bool operator!=(iterator other) const { return _b != other._b; }
					value_type operator*() const {return (tSquare)__builtin_ctzll(_b);}
				private:
					uint64_t _b;
			};
			iterator begin() const {return iterator(_b);}
			iterator end() const {return iterator(0);}
			
			/*****************************************************************
			*	methods
			******************************************************************/

			uint64_t getInternalRepresentation() const ;
			/*	\brief clear the state of the bitboard and empty it
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			void clear();
			
			/*	\brief count the number of 1 bits in a 64 bit variable
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			int bitCnt() const;
			
			/*	\brief tell whether the bitboard is empty or not
				\author Marco Belli
				\version 1.0
				\date 28/11/2017
			*/
			bool isEmpty() const;

			/*	\brief get the index of the rightmost one bit
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			tSquare firstOne() const;

			/*	\brief return true if the bitmap has more than one bit set
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			bool moreThanOneBit() const;

			/*	\brief convert bitmpap to string
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			std::string to_string() const;

			/*	\brief return true if the square is set in the bitmap
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			bool isSquareSet(const tSquare sq) const;

			/*	\brief return true if the square is set in the bitmap
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			bool isSquareSet(const tFile f, const tRank r) const;
			
		private:
		
			uint64_t _b; /*internal board representation*/
			
		public:

			/*****************************************************************
			*	static methods
			******************************************************************/

			/*	\brief return a BitMap with the nth bit set
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			static BitMap getBitmapFromSquare(const tSquare n);

			/*	\brief return a BitMap with the nth bit set
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			static BitMap getBitmapFromSquare( const tFile f, const tRank r );

			/*	\brief return a bitmap used to mask rank
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			static BitMap getRankMask(const tSquare n);

			/*	\brief return a bitmap used to mask file
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			static BitMap getFileMask(const tSquare n);
			
			/*	\brief return a bitmap used to mask light or dark square
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			static BitMap getColorBitMap(const tColor c);
			
			/*	\brief get a bitmap with the squares between 2 squares
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			static BitMap getSquaresBetween(const tSquare n1, const tSquare n2);
			
			/*	\brief tell whether 3 squares are aligned or not
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			static bool areSquaresAligned(const tSquare s1, const tSquare s2, const tSquare s3);
			
			/*	\brief init the static variables used to speed up bitmap manipulations
				\author Marco Belli
				\version 1.0
				\date 17/08/2017
			*/
			static void init(void);
		
		private:		
			/*****************************************************************
			*	static members
			******************************************************************/
		
			static BitMap _RANKMASK[ tSquare::squareNumber ];
			static BitMap _FILEMASK[ tSquare::squareNumber ];
			static BitMap _SQUARECOLOR[ tColor::colorNumber ];
			static BitMap _SQUARES_BETWEEN[ tSquare::squareNumber ][ tSquare::squareNumber ];
			static BitMap _LINES[ tSquare::squareNumber ][ tSquare::squareNumber ];
			
			static void _initRankMask(void);
			static void _initFileMask(void);
			static void _initSquareColor(void);
		};
		
		inline uint64_t BitMap::getInternalRepresentation() const
		{
			return _b;
		}
		
		inline void BitMap::clear()
		{
			_b = 0ull;
		}
		
		inline int BitMap::bitCnt() const
		{
			return __builtin_popcountll( _b );
		}
		
		inline bool BitMap::isEmpty() const
		{
			return _b == 0ull;
		}

		inline tSquare BitMap::firstOne() const
		{
			assert(_b !=0);
			return (tSquare)__builtin_ctzll( _b ) ;
		}

		inline bool BitMap::moreThanOneBit() const
		{
			return bitCnt() > 1;
		}

		inline bool BitMap::isSquareSet(const tSquare sq) const
		{
			return (_b & getBitmapFromSquare(sq)._b);
		}

		inline bool BitMap::isSquareSet(const tFile f, const tRank r) const
		{
			return (_b & getBitmapFromSquare( f, r )._b);
		}
		
		
		inline BitMap BitMap::getBitmapFromSquare(const tSquare n)
		{
			assert( n < tSquare::squareNumber );
			return BitMap( 1ull << n );
		}

		inline BitMap BitMap::getBitmapFromSquare( const tFile f, const tRank r )
		{
			assert( f <= tFile::H );
			assert( r <= tRank::eight );
			assert( f >= tFile::A );
			assert( r >= tRank::one );
			return BitMap(1ull << getSquareFromFileRank( f, r ) );
		}
		
		inline BitMap BitMap::getRankMask(const tSquare n)
		{
			assert( n < squareNumber );
			return (_RANKMASK[ n ]);
		}
		
		inline BitMap BitMap::getFileMask(const tSquare n)
		{
			assert( n < squareNumber );
			return (_FILEMASK[ n ]);
		}
		
		inline BitMap BitMap::getColorBitMap(const tColor c)
		{
			return _SQUARECOLOR[ c ];
		}
		
		inline BitMap BitMap::getSquaresBetween(const tSquare n1, const tSquare n2)
		{
			assert( n1 < squareNumber );
			assert( n2 < squareNumber );
			return _SQUARES_BETWEEN[ n1 ][ n2 ];
		}

		inline bool BitMap::areSquaresAligned(const tSquare s1, const tSquare s2, const tSquare s3)
		{
			assert( s1 < squareNumber );
			assert( s2 < squareNumber );
			assert( s3 < squareNumber );
			return _LINES[ s1 ][ s2 ].isSquareSet( s3 );
		}
	
	}
}



#endif /* BITMAP_H_ */
