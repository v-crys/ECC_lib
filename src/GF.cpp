/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file GF.cpp
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#include "../include/GF.h"

#include "../include/GF_element.h"
#include "../Matrix.h"
#include "../Vector.h"

#include "math.h"

namespace v_crys{


	bool prime_number( int a )
	{
		for ( int i = 2; i < sqrt( a ); i++ )
			if ( ( a % i ) == 0 )
				return false;

		return true;
	}

	std::ostream & operator<< ( std::ostream &OS, GF &src_r )
	{
		OS << std::endl << "GF( " << src_r._p << "^" << src_r._m << " ):\t---->" << std::endl;
		OS << "id\t|\tstep\t|\tvect" << std::endl;
		for ( int i = 0; i < src_r._q; i++ )
			OS << src_r._field[ i ].get_id() << "\t|\t" << src_r._field[ i ].get_step() << "\t|\t" << src_r._field[ i ] << std::endl;
		return OS;
	}

	GF::GF( int p, int m, Vector <bit> poly )
		: _p( p ), _m( m ), _polynomial( poly )
	{
		if ( !prime_number( _p ) )
			throw( "GF::GF, _p don't prime" );

		_q = pow( _p, _m );
		_field.set_size( _q );
		for ( int i = 0; i < _q; i++ )
		{
			_field[ i ].field = this;
			_field[ i ]._vect.set_size( _m );
		}


		create();
	}

	void GF::create()
	{
		_field[ 0 ][ 0 ] = 0;
		_field[ 0 ]._id = 0;
		_field[ 0 ]._step = -1;
		_field[ 1 ][ 0 ] = 1;
		_field[ 1 ]._id = 1;
		_field[ 1 ]._step = 0;

		for ( int i = 1 ; i < _q - 1; i++ )
		{
			if ( _field[ i ][ _field[ 0 ].get_vect().get_size() - 1 ] == 1 )
				_field[ i + 1 ]._vect = (_field[ i ].get_vect() >> 1) ^ _polynomial;
			else
				_field[ i + 1 ]._vect = (_field[ i ].get_vect() >> 1);

			_field[ i + 1 ]._id = i + 1;
			_field[ i + 1 ]._step = i;
		}

		if ( ( _field[ _q - 1 ]._vect >> 1 ^ _polynomial ) != _field[ 1 ]._vect )
			throw( "GF::create, error" );
	}

	GF_element GF::find_step( int step )
	{
		GF_element res( this );

		for ( int i = 0; i < _q; i++ )
			if ( _field[ i ].get_step() == step )
			{
				res = _field[ i ];
				return res;
			}

		throw( "GF::find_step, error" );
		return res;
	}

	GF_element GF::find_id( int id )
	{
		GF_element res( this );

		for ( int i = 0; i < _q; i++ )
			if ( _field[ i ].get_id() == id )
			{
				res = _field[ i ];
				return res;
			}

		throw( "GF::find_step, error" );
	}

	GF_element GF::find_vect( Vector <bit> v )
	{
		GF_element res( this );

		for ( int i = 0; i < _q; i++ )
			if ( _field[ i ].get_vect() == v )
			{
				res = _field[ i ];
				return res;
			}

		throw( "GF::find_step, error" );
	}

	bool operator==( const GF & src1, const GF & src2 )
	{
		if ( ( src1._q == src2._q ) && ( src1._p == src2._p ) && ( src1._m == src2._m ) )
			return true;
		else
			return false;
	}

	bool operator!=( const GF & src1, const GF & src2 )
	{
		return !( src1 == src2 );
	}

	Matrix <Vector <bit> > GF::get_field_m()
	{
		Matrix <Vector <bit> > res( _field.get_size(), _field[ 0 ].get_vect().get_size() );
		for ( int i = 0; i < _field.get_size(); i++ )
			for ( int j = 0; j < _field[ 0 ].get_vect().get_size(); j++ )
				res[ i ][ j ] = _field[ i ][ j ];

		return res;

	}

	Matrix <Vector <bit> > GF::pow_( int ind )
	{
		Matrix <Vector <bit> > res( _q, _m);
		for ( int i = 1; i < _q; i++ )
			res[ i ] = find_step( ( _field[ i ].get_step() * ind ) % (_q - 1) ).get_vect();
		return res;
	}

}
