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

namespace libChess
{

	//-----------------------------------------------------
	// tFile
	//-----------------------------------------------------
	/*	\brief enum rapresenting a file
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	enum class tFile : int
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

	/*	\brief operators for tFile
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline tFile& operator++(tFile& r)
	{
		return r = (tFile)( static_cast<int>(r) + 1 );
	}

	static inline tFile& operator--(tFile& r)
	{
		return r = (tFile)( static_cast<int>(r) - 1 );
	}

	static inline tFile operator++(tFile& r,int)
	{
		tFile n = r;
		++r;
		return n;
	}

	static inline tFile operator--(tFile& r,int)
	{
		tFile n = r;
		--r;
		return n;
	}

	static inline tFile operator+(const tFile d1, const int d2) { return tFile( static_cast<int>(d1) + d2 ); }
	static inline tFile operator-(const tFile d1, const int d2) { return tFile( static_cast<int>(d1) - d2 ); }

	inline tFile& operator+=(tFile& d1, const int d2) { d1 = d1 + d2; return d1; }
	inline tFile& operator-=(tFile& d1, const int d2) { d1 = d1 - d2; return d1; }

	/*	\brief class used to iterate over a range of tFile
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	class tFileRange{

	tFile min;
	tFile Max;
	public:
	tFileRange(tFile _min=tFile::A, tFile _Max= tFile::H): min(_min), Max( _Max + 1 ){if(Max < min) Max = min;}

	class iterator: public std::iterator<
														std::input_iterator_tag,	// iterator_category
								tFile,					// value_type
								tFile,
								const tFile*,
								tFile
								>{
			tFile t;
			public:
				explicit iterator(tFile _t = tFile::A) : t(_t) {}
				iterator& operator++() { t += 1; return *this;}
				iterator operator++(int) { iterator retval = *this; ++(*this); return retval;}
				bool operator==(iterator other) const { return t == other.t; }
				bool operator!=(iterator other) const { return t != other.t; }
				reference operator*() const {return t;}
		};

	iterator begin() {return iterator(min);}
	iterator end() {return iterator(Max);}

	};


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
	
	static inline int distance(const tFile d1, const tFile d2) { return std::abs(static_cast<int>(d1) - static_cast<int>(d2)); }


	//-----------------------------------------------------
	// tRank
	//-----------------------------------------------------

	/*	\brief enum rapresenting a rank
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	enum class tRank : int
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

	static inline tRank& operator++(tRank& r)
	{
		return r = (tRank)( static_cast<int>(r) + 1 );
	}

	static inline tRank& operator--(tRank& r)
	{
		return r = (tRank)( static_cast<int>(r) - 1 );
	}


	static inline tRank operator++(tRank& r,int)
	{
		tRank n = r;
		++r;
		return n;
	}

	static inline tRank operator--(tRank& r,int)
	{
		tRank n = r;
		--r;
		return n;
	}

	static inline tRank operator+(const tRank d1, const int d2) { return tRank( static_cast<int>(d1) + d2 ); }
	static inline tRank operator-(const tRank d1, const int d2) { return tRank( static_cast<int>(d1) - d2 ); }



	inline tRank& operator+=(tRank& d1, const int d2) { d1 = d1 + d2; return d1; }
	inline tRank& operator-=(tRank& d1, const int d2) { d1 = d1 - d2; return d1; }


	/*	\brief class used to iterate over a range of tRank
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	class tRankRange{

	tRank min;
	tRank Max;
	public:
	tRankRange(tRank _min=tRank::one, tRank _Max= tRank::eight): min(_min), Max( _Max + 1 ){if(Max < min) Max = min;}

	class iterator: public std::iterator<
														std::input_iterator_tag,	// iterator_category
								tRank,					// value_type
								tRank,
								const tRank*,
								tRank
								>{
			tRank t;
			public:
				explicit iterator(tRank _t = tRank::one) : t(_t) {}
				iterator& operator++() { t += 1; return *this;}
				iterator operator++(int) { iterator retval = *this; ++(*this); return retval;}
				bool operator==(iterator other) const { return t == other.t; }
				bool operator!=(iterator other) const { return t != other.t; }
				reference operator*() const {return t;}
		};

	iterator begin() {return iterator(min);}
	iterator end() {return iterator(Max);}

	};

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
	
	static inline int distance(const tRank d1, const tRank d2) { return std::abs(static_cast<int>(d1) - static_cast<int>(d2)); }


	//-----------------------------------------------------
	// tSquare
	//-----------------------------------------------------

	/*	\brief enum rapresenting a square
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	enum class tSquare : int
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

	inline tSquare operator+(const tSquare d1, const tSquare d2) { return tSquare( static_cast<int>(d1) + static_cast<int>(d2) ); }
	inline tSquare operator-(const tSquare d1, const tSquare d2) { return tSquare( static_cast<int>(d1) - static_cast<int>(d2) ); }
	inline tSquare operator*(int i, const tSquare d) { return tSquare( i * static_cast<int>(d) ); }
	inline tSquare operator*(const tSquare d, int i) { return tSquare(static_cast<int>(d) * i); }
	inline tSquare& operator+=(tSquare& d1, const tSquare d2) { d1 = d1 + d2; return d1; }
	inline tSquare& operator-=(tSquare& d1, const tSquare d2) { d1 = d1 - d2; return d1; }


		/*	\brief operators for tRank
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/

	static inline tSquare& operator++(tSquare& r)
	{
		return r = (tSquare)( static_cast<int>(r) + 1 );
	}

	static inline tSquare& operator--(tSquare& r)
	{
		return r = (tSquare)( static_cast<int>(r) - 1 );
	}


	static inline tSquare operator++(tSquare& r,int)
	{
		tSquare n = r;
		++r;
		return n;
	}

	static inline tSquare operator--(tSquare& r,int)
	{
		tSquare n = r;
		--r;
		return n;
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
		return (tFile)( static_cast<int>(n) % 8u );
	}

	/*	\brief get rank of a square
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline tRank getRank(const tSquare n)
	{
		assert( n < tSquare::squareNumber );
		return (tRank)( static_cast<int>(n) / 8 );
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
		t = (tSquare)( static_cast<int>(r) *8 + static_cast<int>(f) );
		return t;
	}

	/*	\brief get distance between 2 squares
		\author Marco Belli
		\version 1.0
		\date 18/08/2017
	*/
	static inline unsigned int distance(const tSquare s1, const tSquare s2)
	{
		extern unsigned int SQUARE_DISTANCE[ static_cast<int>(tSquare::squareNumber) ][ static_cast<int>(tSquare::squareNumber) ];
		assert( s1 < static_cast<int>(squareNumber) );
		assert( s2 < static_cast<int>(squareNumber) );
		return (SQUARE_DISTANCE[ static_cast<int>(s1) ][ static_cast<int>(s2) ]);
	}

	//-----------------------------------------------------
	// tSquare
	//-----------------------------------------------------

	/*	\brief enum rapresenting a square color
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	enum class tColor : unsigned int
	{
		white = 0,
		black = 1
	};

	/*	\brief get color of a square
		\author Marco Belli
		\version 1.0
		\date 17/08/2017
	*/
	static inline tColor getColor(const tSquare n)
	{
		extern tColor SQUARE_COLOR[ static_cast<int>(tSquare::squareNumber) ];
		assert( n < static_cast<int>(tSquare::squareNumber) );
		return SQUARE_COLOR[static_cast<int>(n)];
	}

	/*	\brief initTsquares help data
		\author Marco Belli
		\version 1.0
		\date 18/08/2017
	*/
	void inittSquare(void);

}


#endif /* TSQUARE_H_ */
