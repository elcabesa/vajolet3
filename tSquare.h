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

#ifndef TSQUARE_H_
#define TSQUARE_H_

#include <string>
#include "vajolet.h"

/*	\brief enum rapresenting a square color
	\author Marco Belli
	\version 1.0
	\date 17/08/2017
*/
enum tColor : int
{
	white = 0,
	black = 1
};

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
inline tSquare operator+(const tSquare d1, const tSquare d2) { return tSquare(int(d1) + int(d2)); }
inline tSquare operator-(const tSquare d1, const tSquare d2) { return tSquare(int(d1) - int(d2)); }
inline tSquare operator*(int i, const tSquare d) { return tSquare(i * int(d)); }
inline tSquare operator*(const tSquare d, int i) { return tSquare(int(d) * i); }
inline tSquare& operator+=(tSquare& d1, const tSquare d2) { d1 = d1 + d2; return d1; }
inline tSquare& operator-=(tSquare& d1, const tSquare d2) { d1 = d1 - d2; return d1; }

static inline tFile operator++(tFile& r,int)
{
	return r = (tFile)( r + 1 );
}

static inline tRank operator++(tRank& r,int)
{
	return r = (tRank)( r + 1 );
}

static inline tFile operator--(tFile& r,int)
{
	return r = (tFile)( r - 1 );
}

static inline tRank operator--(tRank& r,int)
{
	return r = (tRank)( r - 1 );
}
/*	\brief class used to iterate over a range of tSquare
	\author Marco Belli
	\version 1.0
	\date 17/08/2017
*/
class tSquareRange{

tSquare min;
tSquare Max;
public:
tSquareRange(tSquare _min=tSquare::A1, tSquare _Max= tSquare::H8): min(_min), Max( _Max + tSquare::east ){if(Max < min) Max = min;}

class iterator: public std::iterator<
	                        std::input_iterator_tag,	// iterator_category
							tSquare,					// value_type
							tSquare,
							const tSquare*,
							tSquare
							>{
		tSquare t;
		public:
			explicit iterator(tSquare _t = tSquare::A1) : t(_t) {}
			iterator& operator++() { t += tSquare::east; return *this;}
			iterator operator++(int) { iterator retval = *this; ++(*this); return retval;}
			bool operator==(iterator other) const { return t == other.t; }
			bool operator!=(iterator other) const { return t != other.t; }
			reference operator*() const {return t;}
	};

iterator begin() {return iterator(min);}
iterator end() {return iterator(Max);}

};

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


/*	\brief get color of a square
	\author Marco Belli
	\version 1.0
	\date 17/08/2017
*/
static inline tColor getColor(const tSquare n)
{
	extern tColor SQUARE_COLOR[ tSquare::squareNumber ];
	assert( n < tSquare::squareNumber );
	return SQUARE_COLOR[n];
}

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
	t = (tSquare)( r *8 + f );
	return t;
}

/*	\brief get distance between 2 squares
	\author Marco Belli
	\version 1.0
	\date 18/08/2017
*/
static inline unsigned int getSquareDistance(const tSquare s1, const tSquare s2)
{
	extern unsigned int SQUARE_DISTANCE[ tSquare::squareNumber ][ tSquare::squareNumber ];
	assert(s1 < squareNumber);
	assert(s2 < squareNumber);
	return (SQUARE_DISTANCE[ s1 ][ s2 ]);
}

/*	\brief initTsquares help data
	\author Marco Belli
	\version 1.0
	\date 18/08/2017
*/
void inittSquare(void);



#endif /* TSQUARE_H_ */
