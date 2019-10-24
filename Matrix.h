/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file Matrix.h
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include "Vector.h"

namespace v_crys
{

	template <class T>
	class Matrix;


	template <class T>
	std::ostream & operator<< ( std::ostream &OS, const Matrix<T> &src_r )
	{
		int i;

		for ( i = 0; i < src_r._size; i++ )
			OS << src_r._vectors[ i ] << std::endl;

		return OS;
	}

	template <class T>
	std::istream & operator>> ( std::istream &OS, Matrix<T> &src_r )
	{
		int i;
		OS >> src_r._size;
		src_r.set_size( src_r._size );

		for ( i = 0; i < src_r._size; i++ )
			OS >> src_r._vectors[ i ];

		return OS;
	}

	template <class T>
	std::ofstream & operator<< ( std::ofstream &OS, Matrix<T> &src_r )
	{
		OS << src_r._size << " " << src_r[ 0 ].get_size() << std::endl;
		int i, j;
		for ( i = 0; i < src_r._size; i++ )
		{
			for ( j = 0; j < src_r[ 0 ].get_size(); j++ )
				OS << src_r[ i ][ j ] << " ";

			OS << std::endl;
		}
		return OS;
	}

	template <class T>
	std::ifstream & operator>> ( std::ifstream &OS, Matrix<T> &src_r )
	{
		int _s, _v;
		OS >> _s >> _v;

		src_r.resize( _s, _v );
		int i, j;
		for ( i = 0; i < src_r._size; i++ )
			for ( j = 0; j < src_r._vectors[ 0 ].get_size(); j++ )
				OS >> src_r[ i ][ j ];

		return OS;
	}

	template <class T>
	class Matrix
	{
		public:
			Matrix() : _vectors( NULL ), _size( 0 ) {}
			Matrix( int N ) : _vectors( NULL ), _size( 0 ) { set_size( N ) ; }
			Matrix( int Vectors, int Len_vect );
			~Matrix();

		//------- constructor copy
			Matrix<T>( const Matrix<T> &src );

		//------- binary operators
			Matrix<T> & operator=( const Matrix<T> &src );
			Matrix<T> operator+( const Matrix<T> &src_r );
			Matrix<T> operator-( );
			Matrix<T> operator-( const Matrix<T> &src_r );
			Matrix<T> operator*( const Matrix<T> &src_r );
			Matrix<T> operator*( int );
			friend Matrix<T> operator*( int Val, const Matrix<T> &src_r )
			{
                Matrix<T> res( src_r._size, src_r._vectors[ 0 ].get_size() );

                for ( int i = 0; i < src_r._size; i++ )
                    res._vectors[ i ] = src_r._vectors[ i ] * Val;

                return res;
			}

			T &operator[]( int );

		//-------- thread operators
			friend std::ostream & operator<< <T> ( std::ostream &OS, const Matrix <T> &src_r );
			friend std::istream & operator>> <T> ( std::istream &OS, Matrix <T> &src_r );

			friend std::ofstream & operator<< <T> ( std::ofstream &OS, Matrix<T> &src_r );
			friend std::ifstream & operator>> <T> ( std::ifstream &OS, Matrix<T> &src_r );

		//-------------
			friend bool operator== ( const Matrix<T> &src_l, const Matrix<T> &src_r )
			{
                if ( src_l._size != src_r._size )
                    return false;

                for ( int i = 0; i < src_l._size; i++)
                    if ( src_l._vectors[ i ] != src_r._vectors[ i ] )
                            return false;

                return true;
			}

			friend bool operator!= ( const Matrix<T> &src_l, const Matrix<T> &src_r )
			{
			    return !( src_l == src_r );
			}


			Matrix<T> & operator+= ( const Matrix<T> &src_r );
			Matrix<T> & operator-= ( const Matrix<T> &src_r );
			Matrix<T> & operator*= ( const Matrix<T> &src_r );
			Matrix<T> & operator*= ( int src );

			Matrix<T> operator!( );

			Matrix<T> Minor( int x, int y );
			Matrix<T> ret_part( int x1, int y1, int x2, int y2 );
			int Determinant( );
			void rotate_matr( int ang );

			Matrix<Vector <int> > diagonal( bool left );
			bool matr_binary();

			void swap_column( int a, int b );

			void resize( int Vectors, int Len_vect );

			int get_size() { return _size; }
			int get_len_vect() { return _vectors[ 0 ].get_size(); }

			Matrix<T> join_right( Matrix<T> &src );
			Matrix<T> join_left( Matrix<T> &src );
			Matrix<T> join_down( Matrix<T> &src );

			void zeros();
			void ones();
			void binaris( void );

			Matrix<T> del_column( int col );
			Matrix<T> del_row( int row );
		private:
			T *_vectors;
			int _size;

			void set_size( int N );
	};

	//!-------------------------------------------------------------------------------

	template <class T>
	Matrix<T> Matrix<T>::del_row( int row )
	{
		Matrix<T> res(_size - 1, get_len_vect() );
		for ( int i = 0; i < _size; i++ )
		{
			if ( i == row ) continue;
			if ( i < row )
				res[ i ] = _vectors[ i ];
			else
				res[ i - 1 ] = _vectors[ i ];
		}

		return res;
	}

	template <class T>
	Matrix<T> Matrix<T>::del_column( int col )
	{
		Matrix<T> res( _size, get_len_vect() - 1 );
		for ( int i = 0; i < _size; i++ )
			for ( int j = 0; j < get_len_vect(); j++ )
			{
				if ( j == col ) continue;
				if ( j < col )
					res[ i ][ j ] = _vectors[ i ][ j ];
				else
					res[ i ][ j - 1 ] = _vectors[ i ][ j ];
			}

		return res;
	}

	template <class T>
	void Matrix<T>::binaris()
	{
		for ( int i = 0; i < get_len_vect(); i++ )
			_vectors[ 0 ][ i ] = ( _vectors[ 0 ][ i ] % 2 ) ? 1 : 0;
	}

	template <class T>
	void Matrix <T>::zeros()
	{
		int i, j;
		for ( i = 0; i < _size; i++ )
			for ( j = 0; j < get_len_vect(); j++ )
				_vectors[ i ][ j ] = 0;
	}

	template <class T>
	void Matrix <T>::ones()
	{
		if ( _size != get_len_vect() )
			throw( "Matrix::ones, non-square matrix" );

		zeros();

		int i;
		for ( i = 0; i < _size; i++ )
			_vectors[ i ][ i ] = 1;
	}

	template <class T>
	Matrix<T> Matrix <T>::join_right( Matrix<T> &src )
	{
		if ( _size != src.get_size() )
			throw( "Matrix::join_right, size don't correct" );

		Matrix <T>res( _size, get_len_vect() + src.get_len_vect() );
		int i, j;

		for ( i = 0; i < _size; i++ )
		{
			for ( j = 0; j < get_len_vect(); j++ )
				res[ i ][ j ] = _vectors[ i ][ j ];

			for ( j = 0; j < src.get_len_vect(); j++ )
				res[ i ][ j + get_len_vect() ] = src._vectors[ i ][ j ];
		}

		return res;
	}

	template <class T>
	Matrix<T> Matrix<T>::join_left( Matrix &src )
	{
		if ( _size != src.get_size() )
			throw( "Matrix::join_right, size don't correct" );

		Matrix res( _size, get_len_vect() + src.get_len_vect() );
		int i, j;

		for ( i = 0; i < _size; i++ )
		{
			for ( j = 0; j < src.get_len_vect(); j++ )
				res[ i ][ j ] = src._vectors[ i ][ j ];

			for ( j = 0; j < get_len_vect(); j++ )
				res[ i ][ j + src.get_len_vect() ] = _vectors[ i ][ j ];

		}

		return res;
	}

	template <class T>
	Matrix<T> Matrix<T>::join_down( Matrix<T> &src )
	{
		if ( get_len_vect() != src.get_len_vect() )
			throw( "Matrix::join_down, size don't correct" );

		Matrix <T> res( get_size() + src.get_size(), get_len_vect() );
		for ( int i = 0; i < get_len_vect(); i++ )
		{
			for ( int j = 0; j < get_size(); j++ )
				res[ j ][ i ] = _vectors[ j ][ i ];

			for ( int j = 0; j < src.get_size(); j++ )
				res[ j + get_size() ][ i ] = src[ j ][ i ];
		}

		return res;
	}

	template <class T>
	void Matrix<T>::resize( int Vectors, int Len_vect )
	{
        delete [] _vectors;
        //delete _vectors;
        _vectors = NULL;
		_size = 0;

		set_size( Vectors );
		for ( int i = 0; i < _size; i ++ )
			_vectors[ i ].set_size( Len_vect );
	}


	template <class T>
	Matrix<Vector <int> > Matrix<T>::diagonal( bool left )
	{
		if ( _size > _vectors[ 0 ].get_size() )
			throw( "diagonal:: rows > columns" );

		if ( matr_binary() == false )
			throw( "diagonal:: matrix don't binary" );

		int i, j;
		Matrix<Vector <int> > ret( 1, _vectors[ 0 ].get_size() );
		for ( i = 0; i < _vectors[ 0 ].get_size(); i++ )
			ret[ 0 ][ i ] = i;

		if ( left )
		for ( i = 0; i < _size; i++ )
		{
			if ( _vectors[ i ][ i ] == 0 )
			{
				for ( j = i + 1; j < _vectors[ 0 ].get_size(); j++ )
				{
					if ( _vectors[ i ][ j ] == 1 )
					{
						swap_column( i, j );
						std::swap( ret[ 0 ][ i ], ret[ 0 ][ j ] );
						break;
					}
				}
			}

			for ( j = 0; j < _size; j++ )
				if ( i != j )
					if ( _vectors[ j ][ i ] == 1 )
						_vectors[ j ] ^= _vectors[ i ];
		}
		else
		for ( i = _size - 1; i >= 0 ; i-- )
		{
			if ( _vectors[ i ][ i + get_len_vect() - get_size() ] == 0 )
			{
				for ( j = i + get_len_vect() - get_size() - 1; j >= 0; j-- )
				{
					if ( _vectors[ i ][ j ] == 1 )
					{
						swap_column( i + get_len_vect() - get_size(), j );
						std::swap( ret[ 0 ][ i + get_len_vect() - get_size() ], ret[ 0 ][ j ] );
						break;
					}
				}
			}

			for ( j = 0; j < _size; j++ )
				if ( i != j )
					if ( _vectors[ j ][ i + get_len_vect() - get_size() ] == 1 )
						_vectors[ j ] ^= _vectors[ i ];
		}

		return ret;
	}

	template <class T>
	bool Matrix<T>::matr_binary()
	{
		int i, j;
		for ( i = 0; i < _size; i++ )
			for ( j = 0; j < _vectors[ 0 ].get_size(); j++ )
				if ( ( (int)_vectors[ i ][ j ] != 0 ) && ( (int)_vectors[ i ][ j ] != 1 ) )
					return false;

		return true;
	}

	template <class T>
	void Matrix<T>::swap_column( int a, int b )
	{
		if ( ( ( a < 0 ) || ( a >= _vectors[ 0 ].get_size() ) ) ||
						( ( b < 0 ) || ( b >= _vectors[ 0 ].get_size() ) ) )
								throw( "Matrix::swap_column, don't correct index" );

		if ( a == b ) return;

		int i, buf;
		for ( i = 0; i < _size; i++ )
		{
			buf = _vectors[ i ][ a ];
			_vectors[ i ][ a ] = _vectors[ i ][ b ];
			_vectors[ i ][ b ] = buf;
		}
	}

	template <class T>
	Matrix<T>::Matrix( int Vectors, int Len_vect )
		: _vectors( NULL ), _size( 0 )
	{
		set_size( Vectors );
		for ( int i = 0; i < _size; i ++ )
			_vectors[ i ].set_size( Len_vect );

	}

	template <class T>
	Matrix<T>::~Matrix()
	{
        delete [] _vectors;
		_size = 0;
	}

	template <class T>
	void Matrix<T>::set_size( int N )
	{
		if ( _vectors != NULL )
		{
            delete [] _vectors;
			_vectors = NULL;
		}

		if ( N <= 0 )
		{
			_size = 0;
			return;
		}

		_size = N;
		_vectors = new T [ N ];

	}

	template <class T>
	T & Matrix<T>::operator[]( int Number )
	{
		if ( ( Number < 0) || ( Number >= _size ) )
			exit( EXIT_FAILURE );

		return _vectors[ Number ];
	}


	//------- constructor copy
	template <class T>
	Matrix<T>::Matrix( const Matrix<T> &src ) :
		_size( 0 ), _vectors( NULL )
	{
		set_size( src._size );
		for ( int i = 0; i < _size; i ++ )
		{
			_vectors[ i ].set_size( src._vectors[ i ].get_size() );
			_vectors[ i ] = src._vectors[ i ];
		}
	}

	//------- binary operators
	template <class T>
	Matrix<T> & Matrix<T>::operator=( const Matrix<T> &src )
	{
		if ( this == &src )
			return *this;

		set_size( src._size );
		for ( int i = 0; i < _size; i++ )
		{
			_vectors[ i ].set_size( src._vectors[ i ].get_size() ) ;
			_vectors[ i ] = src._vectors[ i ];
		}

		return *this;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator+( const Matrix<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		Matrix<T> res( src_r._size );
		for ( int i = 0; i < src_r._size; i++ )
		{
			res._vectors[ i ].set_size( _size );
			res._vectors[ i ] = _vectors[ i ] + src_r._vectors[ i ];
		}

		return res;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator-( )
	{
		Matrix<T> res( _size );
		for ( int i = 0; i < _size; i++ )
		{
			res._vectors[ i ].set_size( _size );
			res._vectors[ i ] = -_vectors[ i ];
		}

		return res;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator-( const Matrix<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		Matrix<T> res( _size, _vectors[ 0 ].get_size() );
		res = src_r;
		res = *this + ( -res );

		return res;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator*( const Matrix<T> &src_r )
	{
		int i, j, k;

		if ( _vectors[ 0 ].get_size() != src_r._size )
			exit( EXIT_FAILURE );

		Matrix<T> res( _size, src_r._vectors[ 0 ].get_size() );

		for ( i = 0; i < _size; i++ )
		{
			for ( j = 0; j < src_r._vectors[ 0 ].get_size(); j++ )
			{
				int sum = 0;
				for ( k = 0; k < _vectors[ 0 ].get_size(); k++ )
					sum += _vectors[ i ][ k ] * src_r._vectors[ k ][ j ];

				res[ i ][ j ] = sum;
			}
		}

		return res;
	}


	template <class T>
	Matrix<T> Matrix<T>::operator*( int Val )
	{
		int i;

		Matrix<T> res( _size, _vectors[ 0 ].get_size() );

		for ( i = 0; i < _size; i++ )
			res._vectors[ i ] = _vectors[ i ] * Val;

		return res;
	}


	//------------------------------
	template <class T>
	Matrix<T> & Matrix<T>::operator+= ( const Matrix<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		int i;
		for ( i = 0; i < _size; i++ )
			_vectors[ i ] += src_r._vectors[ i ];

		return *this;
	}

	template <class T>
	Matrix<T> & Matrix<T>::operator-= ( const Matrix<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		int i;
		for ( i = 0; i < _size; i++ )
			_vectors[ i ] -= src_r._vectors[ i ];

		return *this;
	}

	template <class T>
	Matrix<T> & Matrix<T>::operator*= ( const Matrix<T> &src_r )
	{

		Matrix<T> buf = *this;
		*this = buf * src_r;

		return *this;
	}

	template <class T>
	Matrix<T> & Matrix<T>::operator*= ( int src )
	{
		int i;
		for ( i = 0; i < _size; i++ )
			_vectors[ i ] *= src;

		return *this;
	}

	template <class T>
	Matrix<T> Matrix<T>::operator!( )
	{
		Matrix<T> res( _vectors[ 0 ].get_size(), _size );
		int i, j;

		for ( i = 0; i < _size; i++ )
		{
			for ( j = 0; j < _vectors[ 0 ].get_size(); j++ )
			{
				res[ j ][ i ] = _vectors[ i ][ j ];
			}
		}

		return res;
	}

	template <class T>
	Matrix<T> Matrix<T>::ret_part( int x1, int y1, int x2, int y2 )
	{
		if ( ( x1 > x2 ) || ( y1 > y2 ) ||
			( x1 < 0 ) || ( y1 < 0 ) || ( y2 >= _size ) )
				exit( EXIT_FAILURE );


		Matrix<T> buf( y2 - y1 + 1, x2 - x1 + 1 );
		int i;

		for ( i = y1; i <= y2; i++ )
			buf[ i - y1 ] = _vectors[ i ].ret_part( x1, x2 );

		return buf;
	}

	template <class T>
	Matrix<T> Matrix<T>::Minor( int x, int y )
	{
		if ( ( x < 0 ) || ( y < 0 ) || ( y >= _size ) )
			exit( EXIT_FAILURE );

		int i;
		Matrix<T> buf( _size - 1, _vectors[ 0 ].get_size() - 1 );

		for ( i = 0; i < y; i++ )
			buf[ i ] = _vectors[ i ].del_elem( x );

		for ( i = y + 1; i < _size; i++ )
			buf[ i - 1 ] = _vectors[ i ].del_elem( x );

		return buf;
	}

	template <class T>
	int Matrix<T>::Determinant( )
	{
		if ( _size == 1 )
			return _vectors[ 0 ][ 0 ];

		int i, res;

		res = 0;
		for ( i = 0; i < _vectors[ 0 ].get_size(); i++ )
		{
			Matrix<T> loop_b = Minor( i, 0 );
			res += ( ( i % 2 == 1 ) ? -1 : 1 ) * loop_b.Determinant( ) * _vectors[ 0 ][ i ];
		}
		return res;
	}

	template <class T>
	void Matrix<T>::rotate_matr( int ang )
	{
		if ( ang > 3 ) ang %= 4;
		if ( ang == 0 ) return;

		if ( ang == -1 ) ang = 3;
			else if ( ang == -2 ) ang = 2;
				else if ( ang == -3 ) ang = 1;

		int i, j, k ;

		for ( i = 0; i < ang; i++ )
		{
			Matrix<T> buf( _vectors[ 0 ].get_size(), _size );
			for ( j = 0; j < _size; j++ )
			{
				for ( k = 0; k < _vectors[ 0 ].get_size(); k++ )
				{
					buf[ k ][ j ] = _vectors[ _size - j - 1 ][ k ];
				}
			}
			*this = buf;
		}


		return;
	}

}

#endif // MATRIX_H
