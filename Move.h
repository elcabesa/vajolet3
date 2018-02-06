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

#ifndef MOVE_H_
#define MOVE_H_

#include <string>
#include "Vajolet.h"
#include "tSquare.h"

namespace libChess
{

/*!	\brief struct move
    \author Marco Belli
	\version 1.0
	\date 08/11/2013
 */
class Move
{
protected:
	union
	{
		struct
		{
			unsigned _from		:6;
			unsigned _to		:6;
			unsigned _promotion	:2;
			unsigned _flags		:2;
		}_bit;
		unsigned short _packed;
	};
	
public:

	enum eflags{
		fnone,
		fpromotion,
		fenpassant,
		fcastle,
	};

	enum epromotion{
		promQueen,
		promRook,
		promBishop,
		promKnight,
	};
	
	Move(){}
	Move(const Move& m): _packed(m._packed){}
	explicit Move(const unsigned short i):_packed(i){}
	Move(const tSquare _from, const tSquare _to, const eflags _flag=fnone, const epromotion _prom=promQueen):_bit{(unsigned int)_from,(unsigned int)_to,_prom, _flag}{}
	
	


	inline bool operator == (const Move& d1) const { return _packed == d1._packed;}
	inline bool operator != (const Move& d1) const { return _packed != d1._packed;}
	inline Move& operator = (const unsigned short b) { _packed = b; return *this;}
	inline Move& operator = (const Move&m){ _packed = m._packed; return *this;}

	
	inline void setFrom(tSquare from){ _bit._from = from; }
	inline void setTo(tSquare to){ _bit._to = to; }
	inline void setFlag(eflags fl){ _bit._flags = fl; }
	inline void clearFlag(){ _bit._flags = fnone; }
	inline void setPromotion(epromotion pr){ _bit._promotion = pr; }
	
	inline epromotion getPromotionType() const
	{
		return (epromotion)(_bit._promotion);
	}
	
	inline bool isPromotionMove() const
	{
		return _bit._flags == Move::fpromotion;
	}
	
	inline bool isCastleMove() const
	{
		return _bit._flags == Move::fcastle;
	}
	inline bool isEnPassantMove() const
	{
		return _bit._flags == Move::fenpassant;
	}
	inline tSquare getFrom()const {return tSquare(_bit._from);}
	inline tSquare getTo()const {return tSquare(_bit._to);}
	inline unsigned short getPacked()const {return _packed;}
	
	std::string to_string(void) const;



};



class extMove: public Move
{
private:
	Score _score;
public:
	/*Score inline getScore() const { return _score;}*/
	void inline setScore(const Score s){ _score = s;}
	
	extMove(){};
	explicit extMove(const Move& m): Move(m){}
	explicit extMove(const unsigned short i): Move(i){}
	extMove(const tSquare _from, const tSquare _to, const eflags _flag=fnone, const epromotion _prom=promQueen): Move(_from,_to,_flag,_prom){}
	
	inline bool operator < (const extMove& d1) const { return _score < d1._score;}
};


}


#endif /* MOVE_H_ */
