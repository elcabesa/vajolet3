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

#ifndef POSITION_H_
#define POSITION_H_

#include <vector>
#include <array>
#include "State.h"
#include "BitMap.h"
#include "BitBoardIndex.h"

namespace libChess
{
	class Position
	{
	private:
		std::vector<GameState> _stateList;
		// todo valutate the use of a iterator
		GameState* _actualState;
		std::array< bitboardIndex, squareNumber > _squares; // board square rapresentation to speed up, it contain pieces indexed by square
		std::array< BitMap, bitboardNumber > _bitBoard;     // bitboards indexed by bitboardIndex enum
		// todo valutate the use of a iterator
		BitMap *_Us,*_Them;	/*!< pointer to our & their pieces bitboard*/
		
		
	
	
		
	private:
		void _clearStateList( void );
		
		GameState& _getActualState( void );
		GameState& _pushState( void );
		void _popState( void );
		void _setUsThem( void );
		void _swapUsThem();
		void _addPiece( const bitboardIndex piece, const tSquare s );
		void _removePiece(const bitboardIndex piece,const tSquare s);
		void _movePiece(const bitboardIndex piece, const tSquare from, const tSquare to);
	
		
	public:
		const GameState& getActualStateConst(void)const;
		const GameState& getState(unsigned int n)const;
		unsigned int getStateSize() const;
		Position();
		Position(const Position& other);
		Position& operator=(const Position& other);
	
	
		
	};
	
	inline const GameState& Position::getActualStateConst(void)const
	{
		return *_actualState;
	}
	
	inline GameState& Position::_getActualState(void)
	{
		return *_actualState;
	}
	
}


#endif

