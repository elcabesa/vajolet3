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
	
	*Copyright (C) 2007 Pradyumna Kannan.
	*
	*This code is provided 'as-is', without any expressed or implied warranty.
	*In no event will the authors be held liable for any damages arising from
	*the use of this code. Permission is granted to anyone to use this
	*code for any purpose, including commercial applications, and to alter
	*it and redistribute it freely, subject to the following restrictions:
	*
	*1. The origin of this code must not be misrepresented; you must not
	*claim that you wrote the original code. If you use this code in a
	*product, an acknowledgment in the product documentation would be
	*appreciated but is not required.
	*
	*2. Altered source versions must be plainly marked as such, and must not be
	*misrepresented as being the original code.
	*
	*3. This notice may not be removed or altered from any source distribution.
*/

#ifndef BITMAPMOVEGENERATOR_H_
#define BITMAPMOVEGENERATOR_H_

#include <list>
#include <utility>
#include "BitMap.h"

namespace libChess
{
	
	class BitMapMoveGenerator
	{
		
	public:

		/*****************************************************************
		*	static methods
		******************************************************************/
		
		static const baseTypes::BitMap& getBitMapMovesFromKing( const baseTypes::tSquare& from );
		static const baseTypes::BitMap& getBitMapMovesFromKnight( const baseTypes::tSquare& from );
		static const baseTypes::BitMap& getBitMapAttacksFromPawn( const baseTypes::tSquare& from, const baseTypes::tColor color );
	
		static void init(void);
	
	private:
		/*****************************************************************
		*	static members
		******************************************************************/
		static baseTypes::BitMap _knightMoveBitmap[ baseTypes::squareNumber ];
		static baseTypes::BitMap _kingMoveBitmap[ baseTypes::squareNumber ];
		static baseTypes::BitMap _pawnsAttackBitmap[ baseTypes::colorNumber ][ baseTypes::squareNumber ];
		
		static const unsigned int _magicmovesRshift[ baseTypes::squareNumber ];
		static const baseTypes::BitMap _magicmovesRmagics[ baseTypes::squareNumber ];
		static const baseTypes::BitMap _magicmovesRmask[ baseTypes::squareNumber ];
		
		static const unsigned int _magicmovesBshift[ baseTypes::squareNumber ];
		static const baseTypes::BitMap _magicmovesBmagics[ baseTypes::squareNumber ];
		static const baseTypes::BitMap _magicmovesBmask[ baseTypes::squareNumber ];
		
		static baseTypes::BitMap _magicmovesBdb[ 5248 ];
		static const baseTypes::BitMap* _magicmovesBindices[ baseTypes::squareNumber ];
		static baseTypes::BitMap _magicmovesRdb[ 102400 ];
		static const baseTypes::BitMap* _magicmovesRindices[ baseTypes::squareNumber ];

		/*****************************************************************
		*	static methods
		******************************************************************/
		static void _initHelper( baseTypes::BitMap * const b, std::list<std::pair<int,int>> directions );
		static baseTypes::BitMap _mapLinearOccToBitmap( const baseTypes::BitMap& moves, const baseTypes::BitMap& linOcc );
		
	};
	
	inline const baseTypes::BitMap& BitMapMoveGenerator::getBitMapMovesFromKing( const baseTypes::tSquare& from )
	{
		assert(from < baseTypes::squareNumber);
		return _kingMoveBitmap[ from ];
	}
	
	inline const baseTypes::BitMap& BitMapMoveGenerator::getBitMapMovesFromKnight( const baseTypes::tSquare& from )
	{
		assert(from < baseTypes::squareNumber);
		return _knightMoveBitmap[ from ];
	}
	
	inline const baseTypes::BitMap& BitMapMoveGenerator::getBitMapAttacksFromPawn( const baseTypes::tSquare& from, const baseTypes::tColor color )
	{
		assert(from < baseTypes::squareNumber);
		assert(color < baseTypes::colorNumber);
		return _pawnsAttackBitmap[ color ][ from ];
	}
	
}




#endif /* BITMAPMOVEGENERATOR_H_ */
