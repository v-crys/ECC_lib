/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file GF.h
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#ifndef GF_H
#define GF_H

#include "GF_element.h"
#include "../Matrix.h"

namespace v_crys {
bool prime_number( int );

class GF
{
    Vector < GF_element > _field;
    int _q;
    int _m;
    int _p;
    Vector < bit > _polynomial;

    void create();

    public:
        GF( int p, int m, Vector <bit> poly );

        friend std::ostream & operator<< ( std::ostream &OS, GF &src_r );

        GF_element find_step( int step );
        GF_element find_id( int id );
        GF_element find_vect( Vector <bit> v );

        GF_element &operator[]( int i ) { return _field[ i ]; }

        friend bool operator==( const GF &src1, const GF &src2 );
        friend bool operator!=( const GF &src1, const GF &src2 );

        int get_q() { return _q; }
        int get_p() { return _p; }
        int get_m() { return _m; }


        Matrix <Vector <bit> > get_field_m();
        Vector < GF_element > get_field() { return _field; }

        Matrix <Vector <bit> > pow_( int i );
};


#define GF_P( step )  ( v_crys::POLY_2[ (step) - 2].ret_mirror() )

const Vector <bit> POLY_2[] =
    {
        "1 1",
        "0 1 1",
        "0 0 1 1",

        "0 0 1 0  1",
        "0 0 0 0  1 1",
        "0 0 0 1  0 0 1",
        "0 0 0 1  1 1 0 1",

        "0 0 0 0  1 0 0 0  1",
        "0 0 0 0  0 0 1 0  0 1",
        "0 0 0 0  0 0 0 0  1 0 1",
        "0 0 0 0  0 1 0 1  0 0 1 1",

        "0 0 0 0  0 0 0 0  1 1 0 1  1",
        "0 0 0 1  0 0 0 1  0 0 0 0  1 1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 1 1",
        "0 0 0 1  0 0 0 0  0 0 0 0  1 0 1 1",

        "0 0 0 0  0 0 0 0  0 0 0 0  0 1 0 0  1",
        "0 0 0 0  0 0 0 0  0 0 1 0  0 0 0 0  0 1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 1 0 0  1 1 1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  1 0 0 1",

        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 1 0  1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  1 1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 1 0 0  0 0 1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  1 0 0 0  0 1 1 1",

        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 1 0 0  1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 1  0 0 0 1  1 1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 1 0 0  1 1 1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 1 1",

        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 1 0  1",
        "0 0 0 0  0 0 1 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 1  1 1",
        "0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 1 1",
        "0 0 0 0  0 0 0 0  0 1 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 0 0 0  0 1 1 1"
    };
}

#endif // GF_H
