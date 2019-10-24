/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file bit.h
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#ifndef BIT_H
#define BIT_H
#pragma once

namespace v_crys
{
class bit
{
    public:
        bit() : _val( 0 ) {};
        bit( int val ) { val = test_val( val ); };
        ~bit() {};


        bit( const bit &src );

    //------- binary operators
        bit & operator=( int src );
        bit & operator=( const bit &src );
        bit operator+( const bit &src_r );
        bit operator-( const bit &src_r );
        bit operator+( int src_r );
        bit operator-( int src_r );
        bit operator*( const bit &src_r );
        bit operator*( int );
        bit operator^( const bit &src_r );
        bit operator^( int src_r );
        friend bit operator*( int l, const bit &src_r );
        friend bit operator+( int l, bit &src_r );
        friend bit operator-( int l, bit &src_r );
        friend bit operator^( int l, bit &src_r );


        friend std::ostream & v_crys::operator<< ( std::ostream &OS, const bit &src_r );
        friend std::istream & v_crys::operator>> ( std::istream &OS, bit &src_r );

        bool operator== ( int src_r );
        friend bool operator!= ( const bit &src_l, const int src_r );
        friend bool operator== ( const bit &src_l, const int src_r );
        friend bool operator== ( const bit &src_l, const bit &src_r );
        friend bool operator!= ( const bit &src_l, const bit &src_r );
        bit & operator+= ( const bit &src_r );
        bit & operator-= ( const bit &src_r );
        bit & operator*= ( const bit &src_r );
        bit & operator*= ( int src );
        bit &operator^=( const bit &src_r );

        bit operator-() { bit res; res = *this; return res; };

        int get_val() const { return _val; };

        operator int() { return _val;}

    private:
        int _val;

        int test_val( int val ) const { if ( ( val == 0 ) || ( val == 1 ) ) return val; else throw( "bit::test_val, don't bit" );}
};

#define TEST_BIT        bit a, b, c;   \
                        a = 1;         \
                        b = 1;         \
                        c = 0;         \
                                       \
                        cout << "a = " << a << " b = " << b << endl;    \
                        cout << "a + b = " << a + b << endl;            \
                        cout << "a - b = " << a - b << endl;            \
                        cout << "a * b = " << a * b << endl;            \
                        cout << "a ^ b = " << (a ^ b) << endl << endl;  \
                                                                        \
                        cout << "a + 1 = " << a + 1 << endl;            \
                        cout << "a - 0 = " << a - 0 << endl;            \
                        cout << "a * 1 = " << a * 1 << endl;            \
                        cout << "a ^ 0 = " << (a ^ 0) << endl << endl;  \
                                                                        \
                        cout << "1 + a = " << 1 + a << endl;            \
                        cout << "0 - a = " << 0 - a << endl;            \
                        cout << "1 * a = " << 1 * a << endl;            \
                        cout << "0 ^ a = " << ( 0 ^ a ) << endl;


}

#endif // BIT_H
