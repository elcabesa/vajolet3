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


enum class tSquare
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

inline tSquare operator+(const tSquare d1, const tSquare d2) { return tSquare(int(d1) + int(d2)); }
inline tSquare operator-(const tSquare d1, const tSquare d2) { return tSquare(int(d1) - int(d2)); }
inline tSquare operator*(int i, const tSquare d) { return tSquare(i * int(d)); }
inline tSquare operator*(const tSquare d, int i) { return tSquare(int(d) * i); }
inline tSquare& operator+=(tSquare& d1, const tSquare d2) { d1 = d1 + d2; return d1; }
inline tSquare& operator-=(tSquare& d1, const tSquare d2) { d1 = d1 - d2; return d1; }


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
			iterator& operator++() { t+=tSquare::east; return *this;}
			iterator operator++(int) { iterator retval = *this; ++(*this); return retval;}
			bool operator==(iterator other) const { return t == other.t; }
			bool operator!=(iterator other) const { return t != other.t; }
			reference operator*() const {return t;}
	};

iterator begin() {return iterator(min);}
iterator end() {return iterator(Max);}

};





#endif /* TSQUARE_H_ */
