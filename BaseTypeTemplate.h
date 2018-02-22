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

#ifndef BASETYPETEMPLATE_H_
#define BASETYPETEMPLATE_H_

namespace libChess
{
	namespace baseTypes
	{
	
		/*	\brief operator++ for tFile/tRank/tSquare
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		template <typename myType>
		static inline myType& operator++(myType& r)
		{
			return r = (myType)( (int)r + 1 );
		}
		
		/*	\brief operator-- for tFile/tRank/tSquare
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		template <typename myType>
		static inline myType& operator--(myType& r)
		{
			return r = (myType)( (int)r - 1 );
		}
		
		/*	\brief operator++ for tFile/tRank/tSquare
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		template <typename myType>
		static inline myType operator++(myType& r,int)
		{
			myType n = r;
			++r;
			return n;
		}
		
		/*	\brief operator-- for tFile/tRank/tSquare
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		template <typename myType>
		static inline myType operator--(myType& r,int)
		{
			myType n = r;
			--r;
			return n;
		}
		
		/*	\brief operator+ for tFile/tRank/tSquare
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		template <typename myType>
		static inline myType operator+(const myType d1, const int d2) { return myType( (int)d1 + d2 ); }
		
		/*	\brief operator- for tFile/tRank/tSquare
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		template <typename myType>
		static inline myType operator-(const myType d1, const int d2) { return myType( (int)d1 - d2 ); }

		/*	\brief operator+= for tFile/tRank/tSquare
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		template <class myType>
		static inline myType& operator+=(myType& d1, const int d2) { d1 = d1 + d2; return d1; }
		
		/*	\brief operator-= for tFile/tRank/tSquare
			\author Marco Belli
			\version 1.0
			\date 20/02/2018
		*/
		template <class myType>
		static inline myType& operator-=(myType& d1, const int d2) { d1 = d1 - d2; return d1; }
		
		
		/*	\brief range class used to iterate in for(auto a: range())
			\author Marco Belli
			\version 1.0
			\date 22/02/2018
		*/
		template<typename type, type minValue, type maxValue> class baseTypeRange
		{

		public:
			baseTypeRange(type min = minValue, type Max = maxValue): _min(min), _Max( Max + 1 ){ if(_Max < _min) _Max = _min; }

			class iterator: public std::iterator<std::input_iterator_tag,type>
			{
				public:
					explicit iterator(type t = minValue) : _t(t){}
					iterator& operator++() { _t += 1; return *this;}
					bool operator!=(iterator other) const { return _t != other._t; }
					const type& operator*() const {return _t;}
				private:
					type _t;
			};

			iterator begin() {return iterator(_min);}
			iterator end() {return iterator(_Max);}
		
		private:
			type _min;
			type _Max;

		};
		
		/*	\brief range class used to backward iterate in for(auto a: range())
			\author Marco Belli
			\version 1.0
			\date 22/02/2018
		*/
		template<typename type, type minValue, type maxValue> class baseTypeNegativeRange
		{

		
		public:
			baseTypeNegativeRange(type min = minValue, type Max = maxValue): _min(min -1 ), _Max( Max  ){ if(_Max < _min) _Max = _min; }

			class iterator: public std::iterator<std::input_iterator_tag,type>
			{
				public:
					explicit iterator(type t = minValue) : _t(t){}
					iterator& operator++() { _t -= 1; return *this;}
					bool operator!=(iterator other) const { return _t != other._t; }
					const type& operator*() const {return _t;}
				private:
					type _t;
			};

			iterator begin() {return iterator(_Max);}
			iterator end() {return iterator(_min);}
		
		private:
			type _min;
			type _Max;

		};
		
		
	
	}
}
#endif