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

#ifndef MOVEGENERATOR_H_
#define MOVEGENERATOR_H_


#include "tSquare.h"
#include "Position.h"
#include "MoveList.h"


namespace libChess
{
	
	class MoveGenerator
	{
	public:
		// todo remove from here, he belong to movepicker
		static const unsigned int maxMovePerPosition = 250;
		// todo remove from here, he belong to movepicker
		static const unsigned int maxBadMovePerPosition = 32;
		
	public:
		enum genType
		{
			captureMg,			// generate capture moves
			quietMg,			// generate quiet moves
			quietChecksMg,		// generate quiet moves giving check
			allNonEvasionMg,	// generate all moves while not in check
			allEvasionMg,		// generate all moves while in check
			allMg,				// general generate all move
			captureEvasionMg,	// generate capture while in check
			quietEvasionMg		// generate quiet moves while in check


		};

		/*****************************************************************
		*	static methods
		******************************************************************/
		
		static baseTypes::tSquare pawnPush( const baseTypes::eTurn turn );
		static baseTypes::tSquare pawnDoublePush( const baseTypes::eTurn turn );
		static baseTypes::tSquare pawnLeftCapture( const baseTypes::eTurn turn );
		static baseTypes::tSquare pawnRightCapture( const baseTypes::eTurn turn );
		static bool isPawnPush( const baseTypes::tSquare from, const baseTypes::tSquare to );
		static bool isPawnDoublePush( const baseTypes::tSquare from, const baseTypes::tSquare to );
		
		template< genType mgType > static void generateMoves( const Position& pos, MoveList< maxMovePerPosition >& ml );
	
	private:
		static bool _checkAllowedMove( const baseTypes::tSquare from, const baseTypes::tSquare to, const baseTypes::tSquare kingSquare, const GameState& s );
		static bool _checkKingAllowedMove( const Position& pos, const baseTypes::tSquare to, const baseTypes::BitMap& occupiedSquares, const baseTypes::BitMap& opponent );
		template< baseTypes::bitboardIndex pieceType, genType mgType > static void _generatePieceMoves( const Position& pos, const baseTypes::bitboardIndex piece, const baseTypes::tSquare kingSquare, const baseTypes::BitMap& occupiedSquares, const baseTypes::BitMap& target, const GameState& s, MoveList< MoveGenerator::maxMovePerPosition >& ml );
		template< MoveGenerator::genType mgType > static void _generateKingMoves( const Position& pos, const baseTypes::tSquare kingSquare, const baseTypes::BitMap& occupiedSquares, const baseTypes::BitMap& target, const baseTypes::BitMap& opponent, MoveList< MoveGenerator::maxMovePerPosition >& ml );
		template< MoveGenerator::genType mgType > static void _insertPawn( const baseTypes::BitMap& movesBitmap, const baseTypes::tSquare delta, const baseTypes::tSquare kingSquare, const Position& pos, const GameState& s, MoveList< MoveGenerator::maxMovePerPosition >& ml );
		template< MoveGenerator::genType mgType > static void _insertPromotionPawn( const baseTypes::BitMap& movesBitmap, const baseTypes::tSquare delta, const baseTypes::tSquare kingSquare, const GameState& s, MoveList< MoveGenerator::maxMovePerPosition >& ml );
		
	};
	
	
	
	/*!	\brief return the offset of a pawn push
		\author Marco Belli
		\version 1.0
		\date 08/11/2013
	 */
	inline baseTypes::tSquare MoveGenerator::pawnPush( const baseTypes::eTurn turn )
	{
		return turn ? baseTypes::sud : baseTypes::north;
	}
	
	inline baseTypes::tSquare MoveGenerator::pawnDoublePush( const baseTypes::eTurn turn )
	{
		return turn ? 2 * baseTypes::sud : 2 * baseTypes::north;
	}
	
	inline baseTypes::tSquare MoveGenerator::pawnLeftCapture( const baseTypes::eTurn turn )
	{
		return turn ? baseTypes::sud + baseTypes::ovest : baseTypes::north + baseTypes::ovest;
	}
	
	inline baseTypes::tSquare MoveGenerator::pawnRightCapture( const baseTypes::eTurn turn )
	{
		return turn ? baseTypes::sud + baseTypes::east : baseTypes::north + baseTypes::east;
	}
	
	inline bool MoveGenerator::isPawnPush( const baseTypes::tSquare from, const baseTypes::tSquare to )
	{
		return (std::abs( from - to ) == 8);
	}
	
	inline bool MoveGenerator::isPawnDoublePush( const baseTypes::tSquare from, const baseTypes::tSquare to )
	{
		return (std::abs( from - to ) == 16 );
	}
	
	
	
}




#endif /* MOVEGENERATOR_H_ */