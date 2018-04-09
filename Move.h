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

#ifndef MOVE_H_
#define MOVE_H_

#include <string>
#include "Score.h"
#include "tSquare.h"

namespace libChess
{
	
	/*!	\brief class move
		\author Marco Belli
		\version 1.0
		\date 22/02/2018
	 */
	class Move
	{
	public:
		enum eflags
		{
			fnone,
			fpromotion,
			fenpassant,
			fcastle,
		};

		enum epromotion
		{
			promQueen,
			promRook,
			promBishop,
			promKnight,
		};
		
		/*****************************************************************
		*	constructors
		******************************************************************/
		Move(){}
		Move(const Move& m): _u( m._u._packed ){}
		explicit Move( const unsigned short i ):_u(i){}
		Move( const baseTypes::tSquare _from, const baseTypes::tSquare _to, const eflags _flag=fnone, const epromotion _prom=promQueen ):_u(_from, _to, _flag, _prom){}
		
		/*****************************************************************
		*	Operators
		******************************************************************/
		inline bool operator == (const Move& d1) const { return _u._packed == d1._u._packed; }
		inline bool operator != (const Move& d1) const { return _u._packed != d1._u._packed; }
		inline Move& operator = (const unsigned short b) { _u._packed = b; return *this; }
		inline Move& operator = (const Move&m){ _u._packed = m._u._packed; return *this; }

		/*****************************************************************
		*	setter methods
		******************************************************************/
		void setFrom( baseTypes::tSquare from );
		void setTo( baseTypes::tSquare to );
		void setFlag( eflags fl );
		void clearFlag();
		void setPromotion( epromotion pr );
		
		/*****************************************************************
		*	getter methods
		******************************************************************/
		epromotion getPromotionType() const;
		baseTypes::tSquare getFrom() const;
		baseTypes::tSquare getTo() const;
		unsigned short getPacked() const;
		
		/*****************************************************************
		*	other methods
		******************************************************************/
		bool isPromotionMove() const;
		bool isCastleMove() const;
		bool isEnPassantMove() const;
		bool isStandardMove() const;
		std::string to_string( const bool chess960 = false ) const;
		
		/*****************************************************************
		*	static methods
		******************************************************************/
		static bool isKingsideCastle( const baseTypes::tSquare from, const baseTypes::tSquare to);
		static const Move NOMOVE;
		
		/*****************************************************************
		*	private members
		******************************************************************/

	protected:
		union t_u
		{
			t_u(){};
			t_u( unsigned short packed ):_packed(packed){}
			t_u( const baseTypes::tSquare _from, const baseTypes::tSquare _to, const eflags _flag=fnone, const epromotion _prom=promQueen ):_bit{(unsigned int)_from,(unsigned int)_to,_prom, _flag}{}
			struct
			{
				unsigned _from		:6;
				unsigned _to		:6;
				unsigned _promotion	:2;
				unsigned _flags		:2;
			}_bit;
			unsigned short _packed;
		}_u;


	};
	
	inline void Move::setFrom( baseTypes::tSquare from ){ _u._bit._from = from; }
	inline void Move::setTo( baseTypes::tSquare to ){ _u._bit._to = to; }
	inline void Move::setFlag( eflags fl ){ _u._bit._flags = fl; }
	inline void Move::clearFlag(){ _u._bit._flags = fnone; }
	inline void Move::setPromotion(epromotion pr){ _u._bit._promotion = pr; }
	
	inline Move::epromotion Move::getPromotionType() const
	{
		return (epromotion)( _u._bit._promotion );
	}
	
	inline bool Move::isPromotionMove() const
	{
		return _u._bit._flags == Move::fpromotion;
	}
	
	inline bool Move::isCastleMove() const
	{
		return _u._bit._flags == Move::fcastle;
	}
	
	inline bool Move::isEnPassantMove() const
	{
		return _u._bit._flags == Move::fenpassant;
	}
	
	inline bool Move::isStandardMove() const
	{
		return _u._bit._flags == Move::fnone;
	}
	
	inline baseTypes::tSquare Move::getFrom()const
	{
		return baseTypes::tSquare( _u._bit._from );
	
	}
	inline baseTypes::tSquare Move::getTo()const
	{
		return baseTypes::tSquare( _u._bit._to );
	}
	
	inline unsigned short Move::getPacked()const
	{
		return _u._packed;
	}
	inline bool Move::isKingsideCastle( const baseTypes::tSquare from, const baseTypes::tSquare to)
	{
		return to > from;
	}

	

	/*!	\brief struct extMove
		\author Marco Belli
		\version 1.0
		\date 22/02/2018
	 */
	class extMove: public Move
	{
	
	public:
		
		
		/*****************************************************************
		*	constructors
		******************************************************************/
		extMove(){};
		explicit extMove( const Move& m ): Move(m){}
		explicit extMove( const unsigned short i ): Move(i){}
		extMove( const baseTypes::tSquare _from, const baseTypes::tSquare _to, const eflags _flag=fnone, const epromotion _prom=promQueen): Move( _from, _to, _flag, _prom ){}
		
		/*****************************************************************
		*	Operators
		******************************************************************/
		inline bool operator < ( const extMove& d1 ) const { return _score < d1._score;}
		inline extMove& operator = ( const Move& m ){ _u._packed = m.getPacked(); return *this; }
		
		/*Score inline getScore() const { return _score;}*/
		
		/*****************************************************************
		*	setter methods
		******************************************************************/
		void setScore( const Score s );
		
	private:
		Score _score;
	};
	
	void inline extMove::setScore( const Score  s){ _score = s;}

}


#endif /* MOVE_H_ */
