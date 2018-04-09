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
#include <iostream>

#include "Move.h"
#include "Position.h"


namespace libChess
{
	const Move Move::NOMOVE(0);
	
	std::string Move::to_string( const bool chess960 ) const
	{
		std::string s;

		if( _u._packed == 0 )
		{
			s = "0000";
			return s;
		}
		// from
		s += libChess::baseTypes::to_string( getFrom() );
		
		if( isCastleMove() )
		{
			// todo manage chess frc with uci option
			// to
			if( chess960 )
			{
				// chess 960
				s += libChess::baseTypes::to_string( getTo() );
			}
			else
			{
				// standard chess
				baseTypes::tSquare to = getTo();
				const baseTypes::tSquare from = getFrom();
				const bool kingSide = isKingsideCastle( from, to );
				if( kingSide )
				{
					to += baseTypes::ovest;
				}
				else
				{
					to += baseTypes::east + baseTypes::east;
				}
				s += libChess::baseTypes::to_string( to );
			}
		}
		else
		{
			// to
			s += libChess::baseTypes::to_string( getTo() );
		}
		//promotion
		if( isPromotionMove() )
		{
			s += getPieceName( baseTypes::blackQueens + getPromotionType() );
		}
		
		return s;
	}
	
}