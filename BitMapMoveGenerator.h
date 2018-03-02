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
		
		/*****************************************************************
		*	static methods
		******************************************************************/
		static void _initHelper( baseTypes::BitMap * const b, std::list<std::pair<int,int>> directions );
		
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
