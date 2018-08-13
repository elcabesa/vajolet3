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

#ifndef ECASTLE_H_
#define ECASTLE_H_


namespace libChess
{
	namespace baseTypes
	{
		/*	\brief enum with the castle rights definitions
			\author Marco Belli
			\version 1.0
			\date 17/08/2017
		*/
		enum eCastle	// castleRights
		{
			noCastleRights = 0,
			wCastleOO=1,
			wCastleOOO=2,
			bCastleOO=4,
			bCastleOOO=8,
		};
		
		inline void addCastleRightTo( eCastle& cr, const eCastle r )
		{
			cr = (eCastle)( cr | r ) ;
		}
		
		inline eCastle operator|( const eCastle rhs, const eCastle lhs ){ return eCastle( (int)rhs | (int)lhs ); }
	}

}
#endif