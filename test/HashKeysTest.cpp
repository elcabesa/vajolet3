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

#include "gtest/gtest.h"
#include "./../HashKeys.h"


using namespace libChess;


namespace {
	
	TEST(HashKeys, constructor)
	{
		HashKey x;	
		ASSERT_EQ( 0, x.getKey());
	}
	
	TEST(HashKeys, constructor2)
	{
		HashKey x;
		HashKey ex = x.exclusion();
		ASSERT_NE( 0, ex.getKey());
		
		ASSERT_EQ( 0, ex.exclusion().getKey());
	}
	
	TEST(HashKeys, assign)
	{
		HashKey x;
		x.movePiece(3,tSquare::A1,tSquare::F3);
		
		HashKey y;
		y = x;
		
		ASSERT_EQ( y.getKey(), x.getKey());
	}
	
	TEST(HashKeys, MovePiece)
	{
		HashKey x;
		HashKey y = x;
		ASSERT_EQ( y.getKey(), x.getKey());
		
		// todo change to number of pieces to constant
		for( int i = 0; i < 30; i++)
		{
			for(auto from: tSquareRange())
			{
				for(auto to: tSquareRange())
				{
					x.movePiece(i,from,to);
					if( from == to )
					{
						ASSERT_EQ(y.getKey(), x.getKey());
					}
					else
					{
						ASSERT_NE(y.getKey(), x.getKey());
					}
					y = x;
				}
			}
		}
	}
	
	TEST(HashKeys, AddRemovePiece)
	{
		HashKey x;
		HashKey y = x;
		HashKey z = x;
		ASSERT_EQ( y.getKey(), x.getKey());
		ASSERT_EQ( z.getKey(), x.getKey());
		
		// todo change to number of pieces to constant
		for( int i = 0; i < 30; i++)
		{
			for(auto from: tSquareRange())
			{
				for(auto to: tSquareRange())
				{
					z = x;
					x.addPiece(i,from);
					
					ASSERT_NE(z.getKey(), x.getKey());
					x.removePiece(i,to);
					
					if( from == to )
					{
						ASSERT_EQ(y.getKey(), x.getKey());
					}
					else
					{
						ASSERT_NE(y.getKey(), x.getKey());
					}
					y = x;
				}
			}
		}
	}
	
	TEST(HashKeys, changeSide)
	{
		HashKey x;
		x.movePiece(3,tSquare::A1,tSquare::F3);
		
		HashKey y = x;
		x.changeSide();
		
		ASSERT_NE( y.getKey(), x.getKey());
	}
	
	TEST(HashKeys, AddEp)
	{
		HashKey x;
		HashKey y = x;
		ASSERT_EQ( y.getKey(), x.getKey());
		

		for(auto ep: tSquareRange())
		{
			y = x;
			x.addEp(ep);	
			ASSERT_NE(y.getKey(), x.getKey());
		}		
	}
	
	TEST(HashKeys, RemoveEp)
	{
		HashKey x;
		HashKey y = x;
		ASSERT_EQ( y.getKey(), x.getKey());
		

		for(auto ep: tSquareRange())
		{
			y = x;
			x.removeEp(ep);	
			ASSERT_NE(y.getKey(), x.getKey());
		}		
	}
	
	TEST(HashKeys, AddRemoveEp)
	{
		HashKey x;
		HashKey y = x;
		ASSERT_EQ( y.getKey(), x.getKey());
		

		for(auto ep: tSquareRange())
		{
			y = x;
			x.addEp(ep);	
			ASSERT_NE(y.getKey(), x.getKey());
		}
		
		for(auto ep: tSquareRange())
		{
			y = x;
			x.removeEp(ep);	
			ASSERT_NE(y.getKey(), x.getKey());
		}
		
		ASSERT_EQ( 0, x.getKey());
		
		
	}
	
	TEST(HashKeys, ChangeCastlingRight)
	{
		HashKey x;
		HashKey y = x;
		HashKey z = x;
		
		ASSERT_EQ( y.getKey(), x.getKey());
		ASSERT_EQ( z.getKey(), z.getKey());
		
		for( int i = 0 ;i < 16; i++ )
		{
			y = x;
			z = x;
			y.changeCastlingRight(i);
			
			if( i != 0 ){ ASSERT_NE(y.getKey(), x.getKey()); }
			else{ ASSERT_EQ(y.getKey(), x.getKey()); }
			
			if( i & 1 ){ z.changeCastlingRight( 1 ); }
			if( i & 2 ){ z.changeCastlingRight( 2 ); }
			if( i & 4 ){ z.changeCastlingRight( 4 ); }
			if( i & 8 ){ z.changeCastlingRight( 8 ); }
			
			ASSERT_EQ(y.getKey(), z.getKey());
		}
		
		for(auto ep: tSquareRange())
		{
			y = x;
			x.removeEp(ep);	
			ASSERT_NE(y.getKey(), x.getKey());
		}		
	}
}