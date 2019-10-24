/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file Vector.h
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*


#ifndef Vector_H
#define Vector_H

#include <iostream>
#include <stdlib.h>
#include <math.h>

namespace v_crys
{
	template <class T>
	class Vector;

	template <class T>
	std::ostream & operator<< ( std::ostream &OS, Vector<T> src_r )
	{
		for ( int i = 0; i < src_r.get_size(); i++ )
			OS << src_r._data[ i ] << " ";
		return OS;
	}

	template <class T>
	std::istream & operator>> ( std::istream &OS, Vector <T> src_r )
	{
		for ( int i = 0; i < src_r.get_size(); i++ )
			OS >> src_r._data[ i ];
		return OS;
	}


	template <class T>
	class Vector{
	//-------- variables
		T *_data;
		int _size;

	public:
	//------- constructors & destructor
		Vector <T>() : _data( NULL ), _size( 0 ) {}
		Vector <T>( int SIZE ) : _data( NULL ), _size( SIZE ) { set_size( SIZE ); }
		Vector <T>( std::string vect ) : _data( NULL ), _size( 0 ) {create_str( vect );};
		Vector <T>( const char * vect ) : _data( NULL ), _size( 0 ) { create_str( vect ); };
		~Vector <T>() { set_size( 0 ); };

	//------- constructor copy
		Vector <T>( const Vector <T>&src );

	//------- binary operators
		Vector <T> & operator=( int src )
		{
            for ( int i = 0; i < _size; i++ )
                _data[ i ] = src;
            return *this;
		}

		Vector <T> & operator=( const Vector <T> &src );
		Vector <T> operator+( const Vector <T> &src_r );
		Vector <T> operator-( );
		Vector <T> operator-( const Vector <T> &src_r );
		Vector <T> operator*( const Vector <T> &src_r );
		Vector <T> operator*( int );
		Vector <T> operator^( const Vector <T> &src_r );
		friend Vector <T> operator*( int l, Vector <T> &src_r ) { return src_r * l; }

		Vector <T> operator>>( int );
		Vector <T> operator<<( int );

	//-------- thread operators
		friend std::ostream & v_crys::operator<< <T> ( std::ostream &OS, Vector <T> src_r );
		friend std::istream & v_crys::operator>> <T> ( std::istream &OS, Vector <T> src_r );

	//-------------
		friend bool operator== ( const Vector <T> &src_l, const int src_r )
		{
            for ( int i = 0; i < src_l._size; i++ )
                if ( src_l._data[ i ] != src_r )
                    return false;

            return true;
		}

		friend bool operator== ( const Vector <T> &src_l, const Vector <T> &src_r )
		{
			int i;
			if ( src_l._size != src_r._size )
			return false;

			for ( i = 0; i < src_l._size; i++ )
				if ( src_l._data[ i ] != src_r._data[ i ] )
					return false;

			return true;
		}

		friend bool operator!= ( const Vector <T> &src_l, const Vector <T> &src_r )
		{ return !( src_l == src_r ); }
		Vector <T> & operator+= ( const Vector <T> &src_r );
		Vector <T> & operator-= ( const Vector <T> &src_r );
		Vector <T> & operator*= ( const Vector <T> &src_r );
		Vector <T> & operator*= ( int src );
		Vector <T> & operator<<= ( int src );
		Vector <T> & operator>>= ( int src );
		Vector <T> &operator^=( const Vector <T> &src_r );

		T &operator[]( int );

		Vector <T> ret_part( int x1, int x2 );
		Vector <T> del_elem( int ind );
		void set_size( int SIZE );
		int get_size();

		void zeros() { for ( int i = 0; i < _size; i++ ) _data[ i ] = 0; }

		void mirror()
		{
            for ( int i = 0; i < _size / 2; i++ )
                std::swap( _data[ i ], _data[ _size - i - 1 ] );
		}

		Vector <T> ret_mirror() const
		{
            Vector<T> res = *this;
            res.mirror();
            return res;
		}

        void set_int_to_bin( int val, int len )
        {
            set_size( len );
            for ( int i = 0; i < len; i++ )
            {
                _data[ i ] = val & 1;
                val >>= 1;
            }
        }
	private:
		void Print();
		void create_str( std::string vect )
		{
            int elems = 0;
            int flag = 1;
            int buf_val, pos;

            std::string vect2 = vect;
            pos = 0;
            for ( int i = 0; i < vect.length(); i++ )
            {
                if ( vect[ i ] != ' ' )
                {
                    vect2[ pos++ ] = vect[ i ];
                    flag = 0;
                } else
                    if ( flag == 0 )
                    {
                        vect2[ pos++ ] = ' ';
                        flag = 1;
                    }
            }

            if ( vect2[ pos - 1 ] == ' ' )
                vect2.resize( pos );
            else
                vect2.resize( pos + 1 );

            vect2[ pos ] = ' ';
            for ( int i = 0; i < vect2.length(); i++ )
            {
                if ( vect2[ i ] == ' ' )
                    elems++;
            }

            set_size( elems);
            elems = 0;
            pos = 0;
            buf_val = 0;

            for ( int i = 0; i < vect2.length(); i++ )
            {
                if ( vect2[ i ] == ' ' )
                {
					for ( int j = pos; j < i; j++ )
					{
						if (( vect2[ j ] < '0' ) || ( vect2[ j ] > '9' ))
							throw( "Vector::Vector, constructor, str don't num" );
						buf_val += (vect2[ j ] - '0') * pow( 10,  i - j - 1);
					}
					_data[ elems++ ] = buf_val;

					pos = i + 1;
					buf_val = 0;
                }
            }
		}
	};

	#define TEST_VECTOR     \
		Vector <bit> v_b1( 5 ); \
		Vector <bit> v_b2( 5 ); \
								\
		for ( int i = 0; i < 5; i++ )   \
		{                               \
			v_b1[ i ] = i & 1;          \
			v_b2[ i ] = ( i < 2 ) ? 0 : 1;  \
		}                                   \
											\
		cout << "v_b1 = " << v_b1 << endl;  \
		cout << "v_b2 = " << v_b2 << endl;  \
											\
		cout << "v_b1 + v_b2 = " << (v_b1 + v_b2) << endl;  \
		cout << "v_b1 - v_b2 = " << v_b1 - v_b2 << endl;    \
		cout << "v_b1 * v_b2 = " << v_b1 * v_b2 << endl;    \
		cout << "v_b1 ^ v_b2 = " << (v_b1 ^ v_b2) << endl;

	//!----------------------------------------------------------------------------------


	template <class T>
	Vector<T> &Vector<T>::operator^=( const Vector<T> &src_r )
	{
		if ( _size != src_r._size )
			throw( "Vector::operator^=, size don't correct" );

		int i;
		for ( i = 0; i < _size; i++ )
			_data[ i ] ^= src_r._data[ i ];

		return *this;
	}

	template <class T>
	Vector<T> Vector<T>::operator^( const Vector<T> &src_r )
	{
		if ( _size != src_r._size )
			throw( "Vector::operator^, size don't correct" );

		Vector res( _size );
		int i;
		for ( i = 0; i < _size; i++ )
			res[ i ] = _data[ i ] ^ src_r._data[ i ];

		return res;
	}

	template <class T>
	T &Vector<T>::operator[]( int Number )
	{
		if ( ( Number >= _size ) || ( Number < 0 ) )
			exit( EXIT_FAILURE );

		return (_data[ Number ]);
	}

	template <class T>
	Vector<T>::Vector( const Vector<T> &src ) :
		_size( 0 ), _data( NULL )
	{
		int i;
		set_size( src._size );

		for ( i = 0; i < src._size; i++ )
			_data[ i ] = src._data[ i ];
	}

	template <class T>
	Vector<T> & Vector<T>::operator=( const Vector<T> &src )
	{
		if ( this == &src )
			return *this;


		set_size( src._size );
		int i;

		for ( i = 0; i < src._size; i++ )
			_data[ i ] = src._data[ i ];

		return *this;
	}

	template <class T>
	Vector<T> Vector<T>::operator+( const Vector<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		Vector res( _size );
		int i;
		for ( i = 0; i < _size; i++ )
			res._data[ i ] = _data[ i ] + src_r._data[ i ];

		return res;
	}

	template <class T>
	Vector<T> Vector<T>::operator-( )
	{
		Vector<T> res( _size );
		int i;
		for ( i = 0; i < _size; i++ )
			res._data[ i ] = -_data[ i ];

		return res;
	}

	template <class T>
	Vector<T> Vector<T>::operator-( const Vector<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		Vector res( _size );
		res = src_r;
		res = *this + ( -res );

		return res;
	}

	template <class T>
	Vector<T> Vector<T>::operator*( const Vector<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		int i;
		Vector res( _size );

		for ( i = 0; i < _size; i++ )
			res._data[ i ] = _data[ i ] * src_r._data[ i ];

		return res;
	}

	template <class T>
	Vector<T> Vector<T>::operator*( int r )
	{
		Vector res( _size );
		int i;

		for ( i = 0; i < _size; i++ )
			res._data[ i ] = _data[ i ] * r;

		return res;
	}


	template <class T>
	Vector<T> Vector<T>::operator>>( int SHR )
	{
		if ( SHR < 0 )
			exit ( EXIT_FAILURE );

		Vector res( _size );
		int i;

		for ( i = 0; i < _size; i++ )
			if ( i < SHR )
				res[ i ] = 0;
			else
				res[ i ] = _data[ i - SHR ];

		return res;
	}

	template <class T>
	Vector<T> Vector<T>::operator<<( int SHL )
	{
		if ( SHL < 0 )
			exit( EXIT_FAILURE );

		Vector res( _size );
		int i;

		for ( i = 0; i < _size; i++ )
			if ( i + SHL >= _size )
				res[ i ] = 0;
			else
				res[ i ] = _data[ i + SHL ];

		return res;
	}


	template <class T>
	Vector<T> & Vector<T>::operator+= ( const Vector<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		int i;
		for ( i = 0; i < _size; i++ )
			_data[ i ] += src_r._data[ i ];

		return *this;
	}

	template <class T>
	Vector<T> & Vector<T>::operator-= ( const Vector<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		int i;
		for ( i = 0; i < _size; i++ )
			_data[ i ] -= src_r._data[ i ];

		return *this;
	}


	template <class T>
	Vector<T> & Vector<T>::operator*= ( const Vector<T> &src_r )
	{
		if ( _size != src_r._size )
			exit( EXIT_FAILURE );

		int i;
		for ( i = 0; i < _size; i++ )
			_data[ i ] *= src_r._data[ i ];

		return *this;
	}

	template <class T>
	Vector<T> & Vector<T>::operator*= ( int src )
	{
		int i;
		for ( i = 0; i < _size; i++ )
			_data[ i ] *= src;

		return *this;
	}

	template <class T>
	Vector<T> & Vector<T>::operator<<= ( int SHL )
	{
		int i;

		if ( SHL < 0 )
			exit ( EXIT_FAILURE );

		for ( i = 0; i < _size; i++ )
			if ( i + SHL >= _size )
				_data[ i ] = 0;
			else
				_data[ i ] = _data[ i + SHL ];

		return *this;
	}

	template <class T>
	Vector<T> & Vector<T>::operator>>= ( int SHR )
	{
		int i;

		if ( SHR < 0 )
			exit ( EXIT_FAILURE );

		for ( i = _size - 1; i >= 0; i-- )
			if ( i < SHR )
				_data[ i ] = 0;
			else
				_data[ i ] = _data[ i - SHR ];

		return *this;
	}


	//----------------- private methods
	template <class T>
	void Vector<T>::set_size( int SIZE )
	{
		if ( _data != NULL )
		{
			delete [] _data;
			_data = NULL;
		}

		if ( SIZE <= 0 )
		{
			_size = 0;
			_data = NULL;
			return;
		}

		_size = SIZE;
		_data = new T [ SIZE ];

		//zeros();
	}

	template <class T>
	void Vector<T>::Print()
	{
		int i;
		for ( i = 0; i < _size; i++ )
			std::cout << _data[ i ] << " ";

		std::cout << std::endl;

	}

	template <class T>
	int Vector<T>::get_size()
	{
		return _size;
	}

	template <class T>
	Vector<T> Vector<T>::ret_part( int x1, int x2 )
	{
		if ( ( x1 > x2 ) || ( x1 < 0 ) || ( x2 >= _size ) )
			exit( EXIT_FAILURE );

		int i;
		Vector buf( x2 - x1 + 1 );

		for ( i = x1; i <= x2; i++ )
			buf[ i - x1 ] = _data[ i ];

		return buf;
	}

	template <class T>
	Vector<T> Vector<T>::del_elem( int ind )
	{
		if ( ( ind < 0 ) || ( ind >= _size ) )
			exit( EXIT_FAILURE );

		Vector buf( _size - 1 );
		int i;

		for ( i = 0; i < ind; i++ )
			buf[ i ] = _data[ i ];

		for ( i = ind + 1; i < _size; i++ )
			buf[ i - 1 ] = _data[ i ];


		return buf;
	}

}

#endif // Vector <T>_H
