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

#ifndef BITBOARD_INDEX_H_
#define BITBOARD_INDEX_H_


#include "BaseTypeTemplate.h"

namespace libChess
{
	namespace baseTypes
	{
	
	
	
		enum bitboardIndex
		{
			occupiedSquares = 0,			//0		00000000
			whiteKing = 1,					//1		00000001
			whiteQueens = 2,				//2		00000010
			whiteRooks = 3,					//3		00000011
			whiteBishops = 4,				//4		00000100
			whiteKnights = 5,				//5		00000101
			whitePawns = 6,					//6		00000110
			whitePieces = 7,				//7		00000111

			separationBitmap = 8,
			blackKing = 9,					//9		00001001
			blackQueens = 10,				//10	00001010
			blackRooks = 11,				//11	00001011
			blackBishops = 12,				//12	00001100
			blackKnights = 13,				//13	00001101
			blackPawns = 14,				//14	00001110
			blackPieces = 15,				//15	00001111




			bitboardNumber = 16,

			King = whiteKing,
			Queens,
			Rooks,
			Bishops,
			Knights,
			Pawns,
			Pieces,

			empty = occupiedSquares

		};
		
		static inline std::string getPieceName( bitboardIndex in )
		{
			static std::string PIECE_NAMES_FEN[] = {" ","K","Q","R","B","N","P"," "," ","k","q","r","b","n","p"," "};
			
			assert( in < bitboardNumber );
			return std::string(PIECE_NAMES_FEN[ in ]);
		}
		
		static inline bitboardIndex getPieceFromUci( char token )
		{
			switch(token)
			{
			case 'P':
				return whitePawns;
				break;
			case 'N':
				return whiteKnights;
				break;
			case 'B':
				return whiteBishops;
				break;
			case 'R':
				return whiteRooks;
				break;
			case 'Q':
				return whiteQueens;
				break;
			case 'K':
				return whiteKing;
				break;
			case 'p':
				return blackPawns;
				break;
			case 'n':
				return blackKnights;
				break;
			case 'b':
				return blackBishops;
				break;
			case 'r':
				return blackRooks;
				break;
			case 'q':
				return blackQueens;
				break;
			case 'k':
				return blackKing;
				break;
			default:
				return empty;
			
			}
			return empty;
		}
		
		static inline bitboardIndex getMyPiecesfromPiece(const bitboardIndex& piece)
		{
			return  piece > separationBitmap ? blackPieces : whitePieces;
		}
		
		static inline bool isValidPiece(const bitboardIndex& piece)
		{
			return  (piece != occupiedSquares) && (piece != whitePieces) && (piece != separationBitmap) && (piece != blackPieces);
		}
		
		/*! \brief tell if the piece is a pawn
			\author Marco Belli
			\version 1.0
			\date 27/10/2013
		*/
		inline static bool isPawn(bitboardIndex piece)
		{
			return (piece&7) == Pawns;
		}
		/*! \brief tell if the piece is a king
			\author Marco Belli
			\version 1.0
			\date 27/10/2013
		*/
		inline static bool isKing(bitboardIndex piece)
		{
			return (piece&7) == King;
		}
		/*! \brief tell if the piece is a queen
			\author Marco Belli
			\version 1.0
			\date 04/11/2013
		*/
		inline static bool isQueen(bitboardIndex piece)
		{
			return (piece&7) == Queens;
		}
		/*! \brief tell if the piece is a rook
			\author Marco Belli
			\version 1.0
			\date 04/11/2013
		*/
		inline static bool isRook(bitboardIndex piece)
		{
			return (piece&7) == Rooks;
		}
		/*! \brief tell if the piece is a bishop
			\author Marco Belli
			\version 1.0
			\date 04/11/2013
		*/
		inline static bool isBishop(bitboardIndex piece)
		{
			return (piece&7) == Bishops;
		}
		
		static inline bool isBlackPiece(const bitboardIndex& piece)
		{
			return  piece & 8;
		}
		
		static inline bool isWhitePiece(const bitboardIndex& piece)
		{
			return  piece < separationBitmap;
		}

		/*	\brief operators for bitboardIndex
			\author Marco Belli
			\version 1.0
			\date 17/08/2017
		*/
		template static bitboardIndex& operator++<bitboardIndex>(bitboardIndex& r);
		template static bitboardIndex& operator--<bitboardIndex>(bitboardIndex& r);
		template static bitboardIndex operator++<bitboardIndex>(bitboardIndex& r,int);
		template static bitboardIndex operator--<bitboardIndex>(bitboardIndex& r,int);
		
		template static bitboardIndex operator+<bitboardIndex>(const bitboardIndex d1, const int d2);
		template static bitboardIndex operator-<bitboardIndex>(const bitboardIndex d1, const int d2);

		template static bitboardIndex& operator+=<bitboardIndex>(bitboardIndex& d1, const int d2);
		template static bitboardIndex& operator-=<bitboardIndex>(bitboardIndex& d1, const int d2);

		
		/*	\brief class used to iterate over a range of tFile
			\author Marco Belli
			\version 1.0
			\date 17/08/2017
		*/
		template class baseTypeRange<bitboardIndex, bitboardIndex::occupiedSquares, bitboardIndex::blackPieces>;
		using bitboardIndexRange = baseTypeRange<bitboardIndex, bitboardIndex::occupiedSquares, bitboardIndex::blackPieces>;
			
		enum eTurn	// color turn. ( it's also used as offset to access bitmaps by index)
		{
			whiteTurn = 0,
			blackTurn = (int)blackKing - (int)whiteKing
		};
		
		inline eTurn getSwitchedTurn(eTurn t)
		{
			return (eTurn)(blackTurn - t);
		}

		enum eCastle	// castleRights
		{
			wCastleOO=1,
			wCastleOOO=2,
			bCastleOO=4,
			bCastleOOO=8,
		};
	}

}
#endif