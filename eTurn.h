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

#ifndef ETURN_H_
#define ETURN_H_

#include "BitBoardIndex.h"
#include "tSquare.h"

namespace libChess
{
	namespace baseTypes
	{
		
		/*	\brief enum for turn, also used as offset to access bitmap by index
			\author Marco Belli
			\version 1.0
			\date 17/08/2017
		*/
		enum eTurn
		{
			whiteTurn = 0,
			blackTurn = 1,
			turnNumber = 2
		};
		
		/*	\brief return the switched turn
			\author Marco Belli
			\version 1.0
			\date 17/08/2017
		*/
		inline eTurn getSwitchedTurn( const eTurn t )
		{
			return ( eTurn )( blackTurn - t );
		}
		
		/*	\brief return true if it's white turn
			\author Marco Belli
			\version 1.0
			\date 17/08/2017
		*/
		inline bool isWhiteTurn( const eTurn t )
		{
			return !t;
		}
		
		/*	\brief return true if it's black turn
			\author Marco Belli
			\version 1.0
			\date 17/08/2017
		*/
		inline bool isBlackTurn( const eTurn t )
		{
			return t;
		}
		
		/*	\brief return the offset in bitboard based on turn
			\author Marco Belli
			\version 1.0
			\date 13/08/2018
		*/
		inline bitboardIndex getBiboardIndexOffset( const eTurn t )
		{
			return (bitboardIndex)( baseTypes::separationBitmap * t );
		}
		
		inline bitboardIndex getPiece(const eTurn t, const bitboardIndex b)
		{
			return (bitboardIndex)(getBiboardIndexOffset( t ) + b);
		}
		
		static inline eTurn getColor(const tSquare n)
		{
			extern eTurn SQUARE_COLOR[ tSquare::squareNumber ];
			assert( n < tSquare::squareNumber );
			return SQUARE_COLOR[ n ];
		}
		
		
		
		
	}

}
#endif