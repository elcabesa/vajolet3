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
#include "./../BitBoardIndex.h"
#include "./../eCastle.h"
#include "./../eTurn.h"

using namespace libChess::baseTypes;

namespace {
		
	TEST(bitboardIndex,assign)
	{
		bitboardIndex b;
		b = bitboardIndex::whiteRooks;
		
		ASSERT_EQ( bitboardIndex::whiteRooks, b );
		
		bitboardIndex g = b;
		ASSERT_EQ( bitboardIndex::whiteRooks, g );
		g = bitboardIndex::blackPieces;
		ASSERT_EQ( bitboardIndex::blackPieces, g );
	}
	
	TEST(bitboardIndex, getPieceName)
	{
		bitboardIndex b;
		b = bitboardIndex::occupiedSquares;
		ASSERT_STREQ( " ", getPieceName(b).c_str() );
		
		b = bitboardIndex::whiteKing;
		ASSERT_STREQ( "K", getPieceName(b).c_str() );
		
		b = bitboardIndex::whiteQueens;
		ASSERT_STREQ( "Q", getPieceName(b).c_str() );
		
		b = bitboardIndex::whiteRooks;
		ASSERT_STREQ( "R", getPieceName(b).c_str() );
		
		b = bitboardIndex::whiteBishops;
		ASSERT_STREQ( "B", getPieceName(b).c_str() );
		
		b = bitboardIndex::whiteKnights;
		ASSERT_STREQ( "N", getPieceName(b).c_str() );
		
		b = bitboardIndex::whitePawns;
		ASSERT_STREQ( "P", getPieceName(b).c_str() );
		
		b = bitboardIndex::whitePieces;
		ASSERT_STREQ( " ", getPieceName(b).c_str() );

		b = bitboardIndex::separationBitmap;
		ASSERT_STREQ( " ", getPieceName(b).c_str() );
		
		b = bitboardIndex::blackKing;
		ASSERT_STREQ( "k", getPieceName(b).c_str() );
		
		b = bitboardIndex::blackQueens;
		ASSERT_STREQ( "q", getPieceName(b).c_str() );
		
		b = bitboardIndex::blackRooks;
		ASSERT_STREQ( "r", getPieceName(b).c_str() );
		
		b = bitboardIndex::blackBishops;
		ASSERT_STREQ( "b", getPieceName(b).c_str() );
		
		b = bitboardIndex::blackKnights;
		ASSERT_STREQ( "n", getPieceName(b).c_str() );
		
		b = bitboardIndex::blackPawns;
		ASSERT_STREQ( "p", getPieceName(b).c_str() );
		
		b = bitboardIndex::blackPieces;
		ASSERT_STREQ( " ", getPieceName(b).c_str() );
		
	}
	
	TEST(bitboardIndex, getPieceFromUci)
	{
		ASSERT_EQ( bitboardIndex::whitePawns, getPieceFromUci('P') );
		ASSERT_EQ( bitboardIndex::whiteKnights, getPieceFromUci('N') );
		ASSERT_EQ( bitboardIndex::whiteBishops, getPieceFromUci('B') );
		ASSERT_EQ( bitboardIndex::whiteRooks, getPieceFromUci('R') );
		ASSERT_EQ( bitboardIndex::whiteQueens, getPieceFromUci('Q') );
		ASSERT_EQ( bitboardIndex::whiteKing, getPieceFromUci('K') );
		ASSERT_EQ( bitboardIndex::blackPawns, getPieceFromUci('p') );
		ASSERT_EQ( bitboardIndex::blackKnights, getPieceFromUci('n') );
		ASSERT_EQ( bitboardIndex::blackBishops, getPieceFromUci('b') );
		ASSERT_EQ( bitboardIndex::blackRooks, getPieceFromUci('r') );
		ASSERT_EQ( bitboardIndex::blackQueens, getPieceFromUci('q') );
		ASSERT_EQ( bitboardIndex::blackKing, getPieceFromUci('k') );
		
		ASSERT_EQ( bitboardIndex::empty, getPieceFromUci('M') );
		ASSERT_EQ( bitboardIndex::empty, getPieceFromUci('v') );
		ASSERT_EQ( bitboardIndex::empty, getPieceFromUci('5') );
	}
	
	TEST(bitboardIndex, Increment)
	{
		bitboardIndex f = bitboardIndex::whiteRooks;
		ASSERT_EQ( bitboardIndex::whiteRooks, f++ );
		ASSERT_EQ( bitboardIndex::whiteBishops, f );
		ASSERT_EQ( bitboardIndex::whiteKnights, ++f );
		ASSERT_EQ( bitboardIndex::whiteKnights, f );
		
	}
	
	TEST(bitboardIndex, Decrement)
	{
		bitboardIndex f = bitboardIndex::blackPawns;
		ASSERT_EQ( bitboardIndex::blackPawns, f-- );
		ASSERT_EQ( bitboardIndex::blackKnights, f );
		ASSERT_EQ( bitboardIndex::blackBishops, --f );
		ASSERT_EQ( bitboardIndex::blackBishops, f );
		
	}
	
	TEST(bitboardIndex, Sum)
	{
		bitboardIndex f = bitboardIndex::whitePieces;
		ASSERT_EQ( bitboardIndex::blackKing, f + 2 );
	}
	
	TEST(bitboardIndex, Sub)
	{
		bitboardIndex f = bitboardIndex::whiteRooks;
		ASSERT_EQ( bitboardIndex::occupiedSquares, f - 3 );
	}
	
	TEST(bitboardIndex, Sum2)
	{
		bitboardIndex f = bitboardIndex::whitePieces;
		ASSERT_EQ( bitboardIndex::blackKing, f += 2 );
	}
	
	TEST(bitboardIndex, Sub2)
	{
		bitboardIndex f = bitboardIndex::whiteRooks;
		ASSERT_EQ( bitboardIndex::occupiedSquares, f -= 3 );
	}
	
	TEST(bitboardIndex, iterate)
	{
		unsigned int i = 0;

		for(auto t: bitboardIndexRange())
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			if(i>1000) break;
		}
		ASSERT_EQ(i, 16u);
	}
	
	TEST(bitboardIndex, iterateRange0)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::blackKing);

		for(auto t: bitboardIndexRange(bitboardIndex::blackKing,bitboardIndex::blackPawns))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 6u);
	}

	TEST(bitboardIndex, iterateRange1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::Queens);

		for(auto t: bitboardIndexRange(bitboardIndex::Queens,bitboardIndex::Rooks))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 2u);
	}

	TEST(bitboardIndex, iterateRange2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::Rooks);

		for(auto t: bitboardIndexRange(bitboardIndex::Rooks,bitboardIndex::Rooks))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 1u);
	}

	TEST(bitboardIndex, iterateRangeNeg1)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::Rooks);

		for(auto t: bitboardIndexRange(bitboardIndex::Rooks,bitboardIndex::King))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}

	TEST(bitboardIndex, iterateRangeNeg2)
	{

		unsigned int count = 0;
		unsigned int i = (int)(bitboardIndex::blackPawns);

		for(auto t: bitboardIndexRange(bitboardIndex::blackPawns,bitboardIndex::whiteKing))
		{
			ASSERT_EQ((unsigned int)t,i);
			i++;
			count++;
			if(count>1000) break;
		}
		ASSERT_EQ(count, 0u);
	}
	
	TEST(bitboardIndex, getMyPiecesFromPiece)
	{
		ASSERT_EQ( bitboardIndex::whitePieces, getMyPiecesFromPiece( bitboardIndex::whiteKing ) );
		ASSERT_EQ( bitboardIndex::whitePieces, getMyPiecesFromPiece( bitboardIndex::whiteQueens ) );
		ASSERT_EQ( bitboardIndex::whitePieces, getMyPiecesFromPiece( bitboardIndex::whiteRooks ) );
		ASSERT_EQ( bitboardIndex::whitePieces, getMyPiecesFromPiece( bitboardIndex::whiteBishops ) );
		ASSERT_EQ( bitboardIndex::whitePieces, getMyPiecesFromPiece( bitboardIndex::whiteKnights ) );
		ASSERT_EQ( bitboardIndex::whitePieces, getMyPiecesFromPiece( bitboardIndex::whitePawns ) );
		
		ASSERT_EQ( bitboardIndex::blackPieces, getMyPiecesFromPiece( bitboardIndex::blackKing ) );
		ASSERT_EQ( bitboardIndex::blackPieces, getMyPiecesFromPiece( bitboardIndex::blackQueens ) );
		ASSERT_EQ( bitboardIndex::blackPieces, getMyPiecesFromPiece( bitboardIndex::blackRooks ) );
		ASSERT_EQ( bitboardIndex::blackPieces, getMyPiecesFromPiece( bitboardIndex::blackBishops ) );
		ASSERT_EQ( bitboardIndex::blackPieces, getMyPiecesFromPiece( bitboardIndex::blackKnights ) );
		ASSERT_EQ( bitboardIndex::blackPieces, getMyPiecesFromPiece( bitboardIndex::blackPawns ) );

	}
	
	TEST(bitboardIndex, isValidPiece)
	{
		ASSERT_TRUE(isValidPiece( bitboardIndex::whiteKing ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::whiteQueens ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::whiteRooks ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::whiteBishops ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::whiteKnights ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::whitePawns ) );
		
		ASSERT_TRUE(isValidPiece( bitboardIndex::blackKing ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::blackQueens ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::blackRooks ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::blackBishops ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::blackKnights ) );
		ASSERT_TRUE(isValidPiece( bitboardIndex::blackPawns ) );
		
		ASSERT_FALSE(isValidPiece( bitboardIndex::occupiedSquares ) );
		ASSERT_FALSE(isValidPiece( bitboardIndex::whitePieces ) );
		ASSERT_FALSE(isValidPiece( bitboardIndex::separationBitmap ) );
		ASSERT_FALSE(isValidPiece( bitboardIndex::blackPieces ) );

	}
	
	TEST(bitboardIndex, isPawn)
	{
		ASSERT_FALSE(isPawn( bitboardIndex::whiteKing ) );
		ASSERT_FALSE(isPawn( bitboardIndex::whiteQueens ) );
		ASSERT_FALSE(isPawn( bitboardIndex::whiteRooks ) );
		ASSERT_FALSE(isPawn( bitboardIndex::whiteBishops ) );
		ASSERT_FALSE(isPawn( bitboardIndex::whiteKnights ) );
		ASSERT_TRUE(isPawn( bitboardIndex::whitePawns ) );
		
		ASSERT_FALSE(isPawn( bitboardIndex::blackKing ) );
		ASSERT_FALSE(isPawn( bitboardIndex::blackQueens ) );
		ASSERT_FALSE(isPawn( bitboardIndex::blackRooks ) );
		ASSERT_FALSE(isPawn( bitboardIndex::blackBishops ) );
		ASSERT_FALSE(isPawn( bitboardIndex::blackKnights ) );
		ASSERT_TRUE(isPawn( bitboardIndex::blackPawns ) );
		
		ASSERT_FALSE(isPawn( bitboardIndex::occupiedSquares ) );
		ASSERT_FALSE(isPawn( bitboardIndex::whitePieces ) );
		ASSERT_FALSE(isPawn( bitboardIndex::separationBitmap ) );
		ASSERT_FALSE(isPawn( bitboardIndex::blackPieces ) );

	}
	
	TEST(bitboardIndex, isKing)
	{
		ASSERT_TRUE(isKing( bitboardIndex::whiteKing ) );
		ASSERT_FALSE(isKing( bitboardIndex::whiteQueens ) );
		ASSERT_FALSE(isKing( bitboardIndex::whiteRooks ) );
		ASSERT_FALSE(isKing( bitboardIndex::whiteBishops ) );
		ASSERT_FALSE(isKing( bitboardIndex::whiteKnights ) );
		ASSERT_FALSE(isKing( bitboardIndex::whitePawns ) );
		
		ASSERT_TRUE(isKing( bitboardIndex::blackKing ) );
		ASSERT_FALSE(isKing( bitboardIndex::blackQueens ) );
		ASSERT_FALSE(isKing( bitboardIndex::blackRooks ) );
		ASSERT_FALSE(isKing( bitboardIndex::blackBishops ) );
		ASSERT_FALSE(isKing( bitboardIndex::blackKnights ) );
		ASSERT_FALSE(isKing( bitboardIndex::blackPawns ) );
		
		ASSERT_FALSE(isKing( bitboardIndex::occupiedSquares ) );
		ASSERT_FALSE(isKing( bitboardIndex::whitePieces ) );
		ASSERT_FALSE(isKing( bitboardIndex::separationBitmap ) );
		ASSERT_FALSE(isKing( bitboardIndex::blackPieces ) );

	}
	
	TEST(bitboardIndex, isQueen)
	{
		ASSERT_FALSE(isQueen( bitboardIndex::whiteKing ) );
		ASSERT_TRUE(isQueen( bitboardIndex::whiteQueens ) );
		ASSERT_FALSE(isQueen( bitboardIndex::whiteRooks ) );
		ASSERT_FALSE(isQueen( bitboardIndex::whiteBishops ) );
		ASSERT_FALSE(isQueen( bitboardIndex::whiteKnights ) );
		ASSERT_FALSE(isQueen( bitboardIndex::whitePawns ) );
		
		ASSERT_FALSE(isQueen( bitboardIndex::blackKing ) );
		ASSERT_TRUE(isQueen( bitboardIndex::blackQueens ) );
		ASSERT_FALSE(isQueen( bitboardIndex::blackRooks ) );
		ASSERT_FALSE(isQueen( bitboardIndex::blackBishops ) );
		ASSERT_FALSE(isQueen( bitboardIndex::blackKnights ) );
		ASSERT_FALSE(isQueen( bitboardIndex::blackPawns ) );
		
		ASSERT_FALSE(isQueen( bitboardIndex::occupiedSquares ) );
		ASSERT_FALSE(isQueen( bitboardIndex::whitePieces ) );
		ASSERT_FALSE(isQueen( bitboardIndex::separationBitmap ) );
		ASSERT_FALSE(isQueen( bitboardIndex::blackPieces ) );

	}
	
	TEST(bitboardIndex, isRook)
	{
		ASSERT_FALSE(isRook( bitboardIndex::whiteKing ) );
		ASSERT_FALSE(isRook( bitboardIndex::whiteQueens ) );
		ASSERT_TRUE(isRook( bitboardIndex::whiteRooks ) );
		ASSERT_FALSE(isRook( bitboardIndex::whiteBishops ) );
		ASSERT_FALSE(isRook( bitboardIndex::whiteKnights ) );
		ASSERT_FALSE(isRook( bitboardIndex::whitePawns ) );
		
		ASSERT_FALSE(isRook( bitboardIndex::blackKing ) );
		ASSERT_FALSE(isRook( bitboardIndex::blackQueens ) );
		ASSERT_TRUE(isRook( bitboardIndex::blackRooks ) );
		ASSERT_FALSE(isRook( bitboardIndex::blackBishops ) );
		ASSERT_FALSE(isRook( bitboardIndex::blackKnights ) );
		ASSERT_FALSE(isRook( bitboardIndex::blackPawns ) );
		
		ASSERT_FALSE(isRook( bitboardIndex::occupiedSquares ) );
		ASSERT_FALSE(isRook( bitboardIndex::whitePieces ) );
		ASSERT_FALSE(isRook( bitboardIndex::separationBitmap ) );
		ASSERT_FALSE(isRook( bitboardIndex::blackPieces ) );

	}
	
	TEST(bitboardIndex, isBishop)
	{
		ASSERT_FALSE(isBishop( bitboardIndex::whiteKing ) );
		ASSERT_FALSE(isBishop( bitboardIndex::whiteQueens ) );
		ASSERT_FALSE(isBishop( bitboardIndex::whiteRooks ) );
		ASSERT_TRUE(isBishop( bitboardIndex::whiteBishops ) );
		ASSERT_FALSE(isBishop( bitboardIndex::whiteKnights ) );
		ASSERT_FALSE(isBishop( bitboardIndex::whitePawns ) );
		
		ASSERT_FALSE(isBishop( bitboardIndex::blackKing ) );
		ASSERT_FALSE(isBishop( bitboardIndex::blackQueens ) );
		ASSERT_FALSE(isBishop( bitboardIndex::blackRooks ) );
		ASSERT_TRUE(isBishop( bitboardIndex::blackBishops ) );
		ASSERT_FALSE(isBishop( bitboardIndex::blackKnights ) );
		ASSERT_FALSE(isBishop( bitboardIndex::blackPawns ) );
		
		ASSERT_FALSE(isBishop( bitboardIndex::occupiedSquares ) );
		ASSERT_FALSE(isBishop( bitboardIndex::whitePieces ) );
		ASSERT_FALSE(isBishop( bitboardIndex::separationBitmap ) );
		ASSERT_FALSE(isBishop( bitboardIndex::blackPieces ) );

	}
	
	TEST(bitboardIndex, isKnight)
	{
		ASSERT_FALSE(isKnight( bitboardIndex::whiteKing ) );
		ASSERT_FALSE(isKnight( bitboardIndex::whiteQueens ) );
		ASSERT_FALSE(isKnight( bitboardIndex::whiteRooks ) );
		ASSERT_FALSE(isKnight( bitboardIndex::whiteBishops ) );
		ASSERT_TRUE(isKnight( bitboardIndex::whiteKnights ) );
		ASSERT_FALSE(isKnight( bitboardIndex::whitePawns ) );
		
		ASSERT_FALSE(isKnight( bitboardIndex::blackKing ) );
		ASSERT_FALSE(isKnight( bitboardIndex::blackQueens ) );
		ASSERT_FALSE(isKnight( bitboardIndex::blackRooks ) );
		ASSERT_FALSE(isKnight( bitboardIndex::blackBishops ) );
		ASSERT_TRUE(isKnight( bitboardIndex::blackKnights ) );
		ASSERT_FALSE(isKnight( bitboardIndex::blackPawns ) );
		
		ASSERT_FALSE(isKnight( bitboardIndex::occupiedSquares ) );
		ASSERT_FALSE(isKnight( bitboardIndex::whitePieces ) );
		ASSERT_FALSE(isKnight( bitboardIndex::separationBitmap ) );
		ASSERT_FALSE(isKnight( bitboardIndex::blackPieces ) );

	}
	
	TEST(bitboardIndex, isBlackPiece)
	{
		ASSERT_FALSE(isBlackPiece( bitboardIndex::whiteKing ) );
		ASSERT_FALSE(isBlackPiece( bitboardIndex::whiteQueens ) );
		ASSERT_FALSE(isBlackPiece( bitboardIndex::whiteRooks ) );
		ASSERT_FALSE(isBlackPiece( bitboardIndex::whiteBishops ) );
		ASSERT_FALSE(isBlackPiece( bitboardIndex::whiteKnights ) );
		ASSERT_FALSE(isBlackPiece( bitboardIndex::whitePawns ) );
		
		ASSERT_TRUE(isBlackPiece( bitboardIndex::blackKing ) );
		ASSERT_TRUE(isBlackPiece( bitboardIndex::blackQueens ) );
		ASSERT_TRUE(isBlackPiece( bitboardIndex::blackRooks ) );
		ASSERT_TRUE(isBlackPiece( bitboardIndex::blackBishops ) );
		ASSERT_TRUE(isBlackPiece( bitboardIndex::blackKnights ) );
		ASSERT_TRUE(isBlackPiece( bitboardIndex::blackPawns ) );
		
		ASSERT_FALSE(isBlackPiece( bitboardIndex::occupiedSquares ) );
		ASSERT_FALSE(isBlackPiece( bitboardIndex::whitePieces ) );
		ASSERT_TRUE(isBlackPiece( bitboardIndex::separationBitmap ) );
		ASSERT_TRUE(isBlackPiece( bitboardIndex::blackPieces ) );

	}
	
	TEST(bitboardIndex, isWhitePiece)
	{
		ASSERT_TRUE(isWhitePiece( bitboardIndex::whiteKing ) );
		ASSERT_TRUE(isWhitePiece( bitboardIndex::whiteQueens ) );
		ASSERT_TRUE(isWhitePiece( bitboardIndex::whiteRooks ) );
		ASSERT_TRUE(isWhitePiece( bitboardIndex::whiteBishops ) );
		ASSERT_TRUE(isWhitePiece( bitboardIndex::whiteKnights ) );
		ASSERT_TRUE(isWhitePiece( bitboardIndex::whitePawns ) );
		
		ASSERT_FALSE(isWhitePiece( bitboardIndex::blackKing ) );
		ASSERT_FALSE(isWhitePiece( bitboardIndex::blackQueens ) );
		ASSERT_FALSE(isWhitePiece( bitboardIndex::blackRooks ) );
		ASSERT_FALSE(isWhitePiece( bitboardIndex::blackBishops ) );
		ASSERT_FALSE(isWhitePiece( bitboardIndex::blackKnights ) );
		ASSERT_FALSE(isWhitePiece( bitboardIndex::blackPawns ) );
		
		ASSERT_TRUE(isWhitePiece( bitboardIndex::occupiedSquares ) );
		ASSERT_TRUE(isWhitePiece( bitboardIndex::whitePieces ) );
		ASSERT_FALSE(isWhitePiece( bitboardIndex::separationBitmap ) );
		ASSERT_FALSE(isWhitePiece( bitboardIndex::blackPieces ) );

	}
	
	TEST(eTurn, assign)
	{
		eTurn x = whiteTurn;
		ASSERT_EQ( whiteTurn, x );
		x = blackTurn;
		ASSERT_EQ( blackTurn, x );
	}
	
	TEST(eTurn, getSwitchedTurn)
	{
		ASSERT_EQ( whiteTurn, getSwitchedTurn(blackTurn) );
		ASSERT_EQ( blackTurn, getSwitchedTurn(whiteTurn) );
	}
	
	TEST(eCastle, assign)
	{
		eCastle x = noCastleRights;
		ASSERT_EQ( noCastleRights, x );
		x = wCastleOO;
		ASSERT_EQ( wCastleOO, x );
		x = wCastleOOO;
		ASSERT_EQ( wCastleOOO, x );
		x = bCastleOO;
		ASSERT_EQ( bCastleOO, x );
		x = bCastleOOO;
		ASSERT_EQ( bCastleOOO, x );
	}
	
	TEST(eCastle, operatorOr)
	{
		eCastle x = noCastleRights;
		x = x | wCastleOO;
		x = x | bCastleOOO;
		
		ASSERT_EQ( 9, x );
		
	}
	
	TEST(eCastle, addCastleRightTo)
	{
		eCastle x = noCastleRights;
		addCastleRightTo( x, wCastleOOO );
		addCastleRightTo( x, bCastleOO );
		
		ASSERT_EQ( 6, x );
		
	}
	
	
	
}