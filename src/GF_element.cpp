/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file GF_element.cpp
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#ifndef GF_ELEMENT_CPP_H
#define GF_ELEMENT_CPP_H

#include "../include/GF_element.h"
#include "../include/GF.h"


namespace v_crys{

	GF_element::GF_element( GF *f )
	: field( f ), _step( 0 )
	{
		_id = 1;
		_vect.set_size( f->get_m() );
	}

	bool operator== ( const GF_element &src1, const GF_element &src2 )
	{
		return ( src1._vect == src2._vect );
	}

	bool operator!= ( const GF_element &src1, const GF_element &src2 )
	{
		return !( src1 == src2 );
	}


	bit &GF_element::operator[]( int i )
	{
		return _vect[ i ];
	}

	GF_element GF_element::operator+( GF_element src_r )
	{
		if ( field != src_r.field )
			throw( "GF_element::oerator+, elements from different field" );

		GF_element res( field );
		res = field->find_vect( _vect + src_r._vect );
		return res;
	}

	GF_element GF_element::operator-( GF_element src_r )
	{
		if ( field != src_r.field )
			throw( "GF_element::oerator+, elements from different field" );

		GF_element res( field );
		res = field->find_vect( _vect + src_r._vect );
		return res;

	}

	GF_element GF_element::operator*( GF_element src_r )
	{
		if ( field != src_r.field )
			throw( "GF_element::oerator+, elements from different field" );

		GF_element res( field );
		res = field->find_step( ( _step + src_r._step ) % (field->get_q() - 1) );
		return res;
	}

	GF_element GF_element::operator/( GF_element src_r )
	{
		if ( field != src_r.field )
			throw( "GF_element::oerator+, elements from different field" );

		GF_element res( field );


		res = field->find_step( ((field->get_q() - 1) + (_step - src_r._step)) % (field->get_q() - 1) );

		return res;
	}

	GF_element & GF_element::operator=( int src )
	{
		*this = field->find_id( src );
		return *this;
	}

	GF_element &GF_element::operator=( GF_element src )
	{
		if ( field == NULL ) return *this;

		if ( field != src.field )
			throw( "GF_element::GF_element, field error" );

		_id = src._id;
		_step = src._step;
		_vect = src._vect;
		field = src.field;
		return *this;
	}

	void GF_element::Print( std::ostream &OS )
	{
		OS << _vect;
	}

    std::ostream & operator<< ( std::ostream &OS, GF_element &src_r )
	{
		src_r.Print( OS );
		return OS;
    }

}

#endif // GF_ELEMENT_CPP_H
