/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file GF_element.h
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#ifndef GF_ELEMENT_H
#define GF_ELEMENT_H

#include "../Vector.h"
#include "bit.h"

namespace v_crys
{
class GF;
template <class T>
class Vector;
class bit;


class GF_element
{
    private:
        Vector <bit> _vect;
        int _step;
        int _id;
        GF *field;

    public:
        friend GF;

        friend std::ostream & operator<< ( std::ostream &OS, GF_element &src_r );
        //friend std::ofstream & operator<< ( std::ofstream &OS, v_crys::GF_element &src_r );

        GF_element( GF *f );
        GF_element() : field( NULL ) {};

      //  GF_element & operator=( GF_element &src );
        GF_element & operator=( GF_element src );
        GF_element & operator=( int src );

        GF_element operator+( GF_element src_r );
        GF_element operator-( GF_element src_r );
        GF_element operator*( GF_element src_r );
        GF_element operator/( GF_element src_r );

        bit &operator[]( int i );

        Vector <bit> get_vect() { return _vect; }
        int get_id() { return _id; }
        int get_step() { return _step; }

        void Print( std::ostream &OS );

        friend bool operator== ( const GF_element &src1, const GF_element &src2 );
        friend bool operator!= ( const GF_element &src1, const GF_element &src2 );
};
}
#endif // GF_ELEMENT_H
