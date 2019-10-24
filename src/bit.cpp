/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file bit.cpp
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#ifndef BIT_CPP_H
#define BIT_CPP_H

#include <iostream>
#include "../include/bit.h"


namespace v_crys{
    std::istream & operator>> ( std::istream &OS, bit &src_r )
    {
        OS >> src_r._val;
        src_r.test_val( src_r._val );
        return OS;
    }

    std::ostream & operator<< ( std::ostream &OS, const bit &src_r )
    {
        OS << src_r.get_val();
        return OS;
    }

    bit operator+( int l, bit &src_r )
    {
        return src_r + l;
    }

    bit operator-( int l, bit &src_r )
    {
        return src_r + l;
    }

    bit operator^( int l, bit &src_r )
    {
        return src_r ^ l;
    }


    bit operator*( int l, const v_crys::bit &src_r )
    {
        v_crys::bit res;
        res._val = l & 1;
        res = res * src_r;
        return res;
    }

    bool operator== ( const v_crys::bit &src_l, const int src_r )
    {
        return ( src_l._val == src_r );
    }

    bool operator== ( const v_crys::bit &src_l, const v_crys::bit &src_r )
    {
        return ( src_l._val == src_r._val );
    }

    bool operator!= ( const bit &src_l, const bit &src_r )
    {
        return !( src_l == src_r );
    }

    bool operator!= ( const bit &src_l, const int src_r )
    {
        return !( src_l == src_r );
    }


    bit::bit( const bit &src )
    {
        _val = src._val;
    }

    bit & bit::operator=( int src )
    {
        _val = src & 1;
        return *this;
    }

    bit & bit::operator=( const bit &src )
    {
        _val = src._val;
        return *this;
    }

    bool bit::operator== ( int src_r )
    {
        return ( _val == src_r );
    }

    bit bit::operator+( const bit &src_r )
    {
        bit res;
        res._val = ( _val + src_r._val ) & 1;
        return res;
    }

    bit bit::operator-( const bit &src_r )
    {
        return (*this) + src_r;
    }

    bit bit::operator+( int src_r )
    {
        bit res;
        res._val = ( _val + src_r ) & 1;
        return res;
    }

    bit bit::operator-( int src_r )
    {
        return (*this) + src_r;
    }

    bit bit::operator*( const bit &src_r )
    {
        bit res;
        res = _val * src_r._val;
        return res;
    }

    bit bit::operator*( int src )
    {
        bit res;
        res._val = src & 1;
        res = res * (*this);
        return res;
    }

    bit bit::operator^( const bit &src_r )
    {
        bit res;
        res._val = _val ^ src_r._val;
        return res;
    }

    bit bit::operator^( int src_r )
    {
        bit res;
        res._val = ( _val ^ src_r ) & 1;
        return res;
    }

    bit & bit::operator+= ( const bit &src_r )
    {
        *this = *this + src_r;
        return *this;
    }

    bit & bit::operator-= ( const bit &src_r )
    {
        *this += src_r;
        return *this;
    }

    bit & bit::operator*= ( const bit &src_r )
    {
        *this = *this * src_r;
        return *this;
    }

    bit & bit::operator*= ( int src )
    {
        *this = *this * src;
        return *this;
    }

    bit & bit::operator^=( const bit &src_r )
    {
        *this = *this ^ src_r;
        return *this;
    }


}

#endif