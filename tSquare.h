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

#ifndef TSQUARE_H_
#define TSQUARE_H_

#include <assert.h>
#include <iostream>
#include <string>
#include "BaseTypeTemplate.h"

namespace libChess
{
	namespace baseTypes
	{
	
	
	

	//-----------------------------------------------------
	// tFile
	//-----------------------------------------------------
	/*	\brief enum rapresenting a file
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	enum tFile : int
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H
	};

	template tFile& operator++<tFile>(tFile& r);
	template tFile& operator--<tFile>(tFile& r);
	template tFile operator++<tFile>(tFile& r,int);
	template tFile operator--<tFile>(tFile& r,int);
	
	template tFile operator+<tFile>(const tFile d1, const int d2);
	template tFile operator-<tFile>(const tFile d1, const int d2);

	template tFile& operator+=<tFile>(tFile& d1, const int d2);
	template tFile& operator-=<tFile>(tFile& d1, const int d2);

	

	/*	\brief class used to iterate over a range of tFile
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	template class baseTypeRange<tFile, tFile::A, tFile::H>;
	using tFileRange = baseTypeRange<tFile, tFile::A, tFile::H>;
	


	/*	\brief convert file to string
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline std::string to_string(tFile f)
	{
		std::string s;
		s += char( 'a' + (char)f );
		return s;
	}
	
	static inline int distance(const tFile d1, const tFile d2) { return std::abs( (int)d1 - (int)d2 ); }
	
	static inline bool isValidFile( const tFile f ) { return (f >= A) & (f <= H); }


	//-----------------------------------------------------
	// tRank
	//-----------------------------------------------------

	/*	\brief enum rapresenting a rank
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	enum tRank : int
	{
		one,
		two,
		three,
		four,
		five,
		six,
		seven,
		eight
	};

	/*	\brief operators for tRank
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	template tRank& operator++<tRank>(tRank& r);
	template tRank& operator--<tRank>(tRank& r);
	template tRank operator++<tRank>(tRank& r,int);
	template tRank operator--<tRank>(tRank& r,int);
	
	template tRank operator+<tRank>(const tRank d1, const int d2);
	template tRank operator-<tRank>(const tRank d1, const int d2);

	template tRank& operator+=<tRank>(tRank& d1, const int d2);
	template tRank& operator-=<tRank>(tRank& d1, const int d2);


	/*	\brief class used to iterate over a range of tRank
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	template class baseTypeRange<tRank, tRank::one, tRank::eight>;
	using tRankRange = baseTypeRange<tRank, tRank::one, tRank::eight>;

	/*	\brief class used to iterate over a range of tRank
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	
	template class baseTypeNegativeRange<tRank, tRank::one, tRank::eight>;
	using tRankNegativeRange = baseTypeNegativeRange<tRank, tRank::one, tRank::eight>;


	/*	\brief convert rank to string
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline std::string to_string(tRank r)
	{
		std::string s;
		s += char( '1' + (char)r );
		return s;
	}
	
	static inline int distance(const tRank d1, const tRank d2) { return std::abs( (int)d1 - (int)d2 ); }
	
	static inline bool isValidRank( const tRank r ) { return (r >= one) & (r <= eight); }


	//-----------------------------------------------------
	// tSquare
	//-----------------------------------------------------

	/*	\brief enum rapresenting a square
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	enum tSquare : int
	{
		A1,	B1,	C1,	D1,	E1,	F1,	G1,	H1,
		A2,	B2,	C2,	D2,	E2,	F2,	G2,	H2,
		A3,	B3,	C3,	D3,	E3,	F3,	G3,	H3,
		A4,	B4,	C4,	D4,	E4,	F4,	G4,	H4,
		A5,	B5,	C5,	D5,	E5,	F5,	G5,	H5,
		A6,	B6,	C6,	D6,	E6,	F6,	G6,	H6,
		A7,	B7,	C7,	D7,	E7,	F7,	G7,	H7,
		A8,	B8,	C8,	D8,	E8,	F8,	G8,	H8,
		squareNone,
		squareNumber = 64,
		north = 8,
		northEast = 9,
		east = 1,
		sudEast = -7,
		sud = -8,
		sudOvest = -9,
		ovest = -1,
		northOvest = 7,



	};


	/*	\brief operators for tSquare
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	
	template tSquare& operator++<tSquare>(tSquare& r);
	template tSquare& operator--<tSquare>(tSquare& r);
	template tSquare operator++<tSquare>(tSquare& r,int);
	template tSquare operator--<tSquare>(tSquare& r,int);


	static inline tSquare operator+(const tSquare d1, const tSquare d2) { return tSquare( (int)d1 + (int)d2 ); }
	static inline tSquare operator-(const tSquare d1, const tSquare d2) { return tSquare( (int)d1 - (int)d2 ); }
	static inline tSquare operator*(int i, const tSquare d) { return tSquare( i * (int)d ); }
	static inline tSquare operator*(const tSquare d, int i) { return tSquare( (int)d * i ); }
	static inline tSquare& operator+=(tSquare& d1, const tSquare d2) { d1 = d1 + d2; return d1; }
	static inline tSquare& operator-=(tSquare& d1, const tSquare d2) { d1 = d1 - d2; return d1; }


	/*	\brief class used to iterate over a range of tSquare
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	template class baseTypeRange<tSquare, tSquare::A1, tSquare::H8>;
	using tSquareRange = baseTypeRange<tSquare, tSquare::A1, tSquare::H8>;
	
	/*	\brief class used to iterate over a range of tSquare
	\author Marco Belli
	\version 1.0
	\date 17/08/2017
	*/
	template class baseTypeNegativeRange<tSquare, tSquare::A1, tSquare::H8>;
	using tSquareNegativeRange = baseTypeNegativeRange<tSquare, tSquare::A1, tSquare::H8>;
	
	/*	\brief get file of a square
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline tFile getFile(const tSquare n)
	{
		assert( n < tSquare::squareNumber );
		return (tFile)( n % 8u );
	}

	/*	\brief get rank of a square
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline tRank getRank(const tSquare n)
	{
		assert( n < tSquare::squareNumber );
		return (tRank)( n / 8 );
	}



	/*	\brief convert square to string
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline std::string to_string(tSquare sq)
	{
		std::string s;
		s += to_string( getFile( sq ) );
		s += to_string( getRank( sq ) );
		return s;
	}

	/*	\brief create a tSquare from file rank definition
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline tSquare getSquareFromFileRank(tFile f, tRank r)
	{
		tSquare t;
		t = (tSquare)( (int)(r * 8) + (int)f );
		return t;
	}

	/*	\brief get distance between 2 squares
		\author Marco Belli
		\version 1.0
		\date 18/08/2017
	*/
	static inline unsigned int distance(const tSquare s1, const tSquare s2)
	{
		extern unsigned int SQUARE_DISTANCE[ tSquare::squareNumber ][ tSquare::squareNumber ];
		assert( s1 < tSquare::squareNumber );
		assert( s2 < tSquare::squareNumber );
		return (SQUARE_DISTANCE[ s1 ][ s2 ]);
	}

	//-----------------------------------------------------
	// tSquare
	//-----------------------------------------------------

	/*	\brief enum rapresenting a square color
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	enum tColor : unsigned int
	{
		white = 0,
		black = 1,
		colorNumber = 2
	};

	/*	\brief get color of a square
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline tColor getColor(const tSquare n)
	{
		extern tColor SQUARE_COLOR[ tSquare::squareNumber ];
		assert( n < tSquare::squareNumber );
		return SQUARE_COLOR[ n ];
	}

	/*	\brief initTsquares help data
		\author Marco Belli
		\version 1.0
		\date 18/08/2017
	*/
	void inittSquare(void);
	}

}


#endif /* TSQUARE_H_ */
