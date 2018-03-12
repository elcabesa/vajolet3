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
#include "BitBoardIndex.h"

namespace libChess
{
	
	class BitMapMoveGenerator
	{
		
	public:

		/*****************************************************************
		*	static methods
		******************************************************************/
		
		static const baseTypes::BitMap& getKingMoves( const baseTypes::tSquare& from );
		static const baseTypes::BitMap& getKnightMoves( const baseTypes::tSquare& from );
		static const baseTypes::BitMap& getPawnAttack( const baseTypes::tSquare& from, const baseTypes::tColor color );
		static const baseTypes::BitMap& getRookMoves( const baseTypes::tSquare& from, const baseTypes::BitMap& occupancy );
		static const baseTypes::BitMap& getBishopMoves( const baseTypes::tSquare& from, const baseTypes::BitMap& occupancy );
		static const baseTypes::BitMap getQueenMoves( const baseTypes::tSquare& from, const baseTypes::BitMap& occupancy );
		static const baseTypes::BitMap& getRookPseudoMoves( const baseTypes::tSquare& from);
		static const baseTypes::BitMap& getBishopPseudoMoves( const baseTypes::tSquare& from);
		
		static const baseTypes::BitMap getPawnGroupAdvance( const baseTypes::BitMap& b, const baseTypes::tColor col, const baseTypes::BitMap& occupancy );
		static const baseTypes::BitMap getPawnGroupCaptureLeft( const baseTypes::BitMap& b, const baseTypes::tColor col, const baseTypes::BitMap& target );
		static const baseTypes::BitMap getPawnGroupCaptureRight( const baseTypes::BitMap& b, const baseTypes::tColor col, const baseTypes::BitMap& target );
		
		static void init(void);
	
	private:
		/*****************************************************************
		*	static members
		******************************************************************/
		static baseTypes::BitMap _knightMoveBitmap[ baseTypes::squareNumber ];
		static baseTypes::BitMap _kingMoveBitmap[ baseTypes::squareNumber ];
		static baseTypes::BitMap _pawnsAttackBitmap[ baseTypes::colorNumber ][ baseTypes::squareNumber ];
		
		static const unsigned int _magicMovesRshift[ baseTypes::squareNumber ];
		static const uint64_t _magicMovesRmagics[ baseTypes::squareNumber ];
		static const baseTypes::BitMap _magicMovesRmask[ baseTypes::squareNumber ];
		
		static const unsigned int _magicMovesBshift[ baseTypes::squareNumber ];
		static const uint64_t _magicMovesBmagics[ baseTypes::squareNumber ];
		static const baseTypes::BitMap _magicMovesBmask[ baseTypes::squareNumber ];
		
		static baseTypes::BitMap _magicMovesBdb[ 5248 ];
		static baseTypes::BitMap* _magicMovesBindices[ baseTypes::squareNumber ];
		static baseTypes::BitMap _magicMovesRdb[ 102400 ];
		static baseTypes::BitMap* _magicMovesRindices[ baseTypes::squareNumber ];

		/*****************************************************************
		*	static methods
		******************************************************************/
		static void _initHelper( baseTypes::BitMap * const b, std::list<std::pair<int,int>> directions );
		static baseTypes::BitMap _mapLinearOccToBitmap( const baseTypes::BitMap& moves, const baseTypes::BitMap& linOcc );
		static baseTypes::BitMap _generateMoveBitMapHelper( baseTypes::tSquare sq, const baseTypes::BitMap& occ, const int fileIncrement, const int rankIncrement);
		static baseTypes::BitMap _generateRookMoveBitMap( baseTypes::tSquare sq,  const baseTypes::BitMap& occ );
		static baseTypes::BitMap _generateBishopMoveBitMap( baseTypes::tSquare sq,  const baseTypes::BitMap& occ );
		
		static baseTypes::BitMap& _getBishopMoves( const baseTypes::tSquare sq, const baseTypes::BitMap& occupancy );
		static baseTypes::BitMap& _getRookMoves( const baseTypes::tSquare sq, const baseTypes::BitMap& occupancy );		
	};
	
	inline const baseTypes::BitMap& BitMapMoveGenerator::getKingMoves( const baseTypes::tSquare& from )
	{
		assert(from < baseTypes::squareNumber);
		return _kingMoveBitmap[ from ];
	}
	
	inline const baseTypes::BitMap& BitMapMoveGenerator::getKnightMoves( const baseTypes::tSquare& from )
	{
		assert(from < baseTypes::squareNumber);
		return _knightMoveBitmap[ from ];
	}
	
	inline const baseTypes::BitMap& BitMapMoveGenerator::getPawnAttack( const baseTypes::tSquare& from, const baseTypes::tColor color )
	{
		assert(from < baseTypes::squareNumber);
		assert(color < baseTypes::colorNumber);
		return _pawnsAttackBitmap[ color ][ from ];
	}
	
	inline const baseTypes::BitMap& BitMapMoveGenerator::getRookMoves( const baseTypes::tSquare& from, const baseTypes::BitMap& occupancy )
	{
		return _getRookMoves( from, occupancy );
	}
	inline const baseTypes::BitMap& BitMapMoveGenerator::getBishopMoves( const baseTypes::tSquare& from, const baseTypes::BitMap& occupancy )
	{
		return _getBishopMoves( from, occupancy );
	}
	inline const baseTypes::BitMap BitMapMoveGenerator::getQueenMoves( const baseTypes::tSquare& from, const baseTypes::BitMap& occupancy )
	{
		return _getRookMoves( from, occupancy ) + _getBishopMoves( from, occupancy );
	}
	
	inline baseTypes::BitMap& BitMapMoveGenerator::_getBishopMoves( const baseTypes::tSquare sq, const baseTypes::BitMap& occupancy )
	{
		return *( _magicMovesBindices [ sq ] + ( ( ( occupancy & _magicMovesBmask[ sq ] ).getInternalRepresentation() * _magicMovesBmagics[ sq ] ) >> _magicMovesBshift[ sq ] ) );
	}
	inline baseTypes::BitMap& BitMapMoveGenerator::_getRookMoves( const baseTypes::tSquare sq, const baseTypes::BitMap& occupancy )
	{
		return *( _magicMovesRindices [ sq ] + ( ( ( occupancy & _magicMovesRmask[ sq ] ).getInternalRepresentation() * _magicMovesRmagics[ sq ] ) >> _magicMovesRshift[ sq ] ) );
	}
	
	inline const baseTypes::BitMap& BitMapMoveGenerator::getRookPseudoMoves( const baseTypes::tSquare& from)
	{
		return _getRookMoves( from, baseTypes::BitMap(0) );
	}
	inline const baseTypes::BitMap& BitMapMoveGenerator::getBishopPseudoMoves( const baseTypes::tSquare& from)
	{
		return _getBishopMoves( from, baseTypes::BitMap(0) );
	}
	
	inline const baseTypes::BitMap BitMapMoveGenerator::getPawnGroupAdvance( const baseTypes::BitMap& b, const baseTypes::tColor col, const baseTypes::BitMap& occupancy )
	{
		return ( (col == baseTypes::white) ? (b << 1) : (b >> 1) ) & ~occupancy ;
	}
	
	inline const baseTypes::BitMap BitMapMoveGenerator::getPawnGroupCaptureLeft( const baseTypes::BitMap& b, const baseTypes::tColor col, const baseTypes::BitMap& target )
	{
		return ( (col == baseTypes::white) ? ( ( b & ( ~baseTypes::BitMap::getFileMask(baseTypes::A1) ) ) << 7 ) : ( ( b & ( ~baseTypes::BitMap::getFileMask(baseTypes::A1) ) ) >> 9 ) ) & target;	
	}
	
	inline const baseTypes::BitMap BitMapMoveGenerator::getPawnGroupCaptureRight( const baseTypes::BitMap& b, const baseTypes::tColor col, const baseTypes::BitMap& target )
	{
		return ( (col == baseTypes::white) ? ( ( b & ( ~baseTypes::BitMap::getFileMask(baseTypes::H1) ) ) << 9 ) : ( ( b & ( ~baseTypes::BitMap::getFileMask(baseTypes::H1) ) ) >> 7 ) ) & target;	
	}
	
}




#endif /* BITMAPMOVEGENERATOR_H_ */
