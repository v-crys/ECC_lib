/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file main.cpp
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

#include "include/GF_element.h"
#include "Vector.h"
#include "Matrix.h"

#include "include/ECC.h"
#include "include/bit.h"


#include "include/GF.h"


using namespace std;
using namespace v_crys;


#define STEPEN 5                                    ///< Set gf pow

#define LEN_CODE (pow( 2, STEPEN ) - 1 )            ///< calculate len code
#define CNT_ERROR 2                                 ///< count errors (warning! need modify code)
#define INF_CODE (LEN_CODE - CNT_ERROR * STEPEN)    ///< size information word


int main()
{
    ///------- LAB2 Galoys Field

    GF gf( 2, 5, GF_P( 5 ) ); ///< Generate Galoys Fiels 2^5

    ofstream file_gf( "GF_5.txt" );
    file_gf << gf;
    file_gf.close();

    ///------- LAB3 BCH code

    GF gf_bch( 2, STEPEN, GF_P( STEPEN ) );

    Matrix <Vector <bit> > H_top =  !(gf_bch.get_field_m().del_row( 0 ) );  ///< Top part H matrix (all gf elements)
    Matrix <Vector <bit> > H_down = !(gf_bch.pow_( 3 ).del_row( 0 ) );      ///< Down part H matrix (all gf elements in pow 3)
    Matrix <Vector <bit> > H = H_top.join_down( H_down );                   ///< Merge top and down matrix

    //------ create code
    ECC <Vector <bit> , Vector <bit> > BCH( "BCH", LEN_CODE, INF_CODE  );   ///< Create code with parameters
    BCH.set_H( H );                                                         ///< Set H matrix for code

    //------- create inf_word & code_word
    Matrix <Vector <bit> > inf_WORD( 1, INF_CODE );                         ///< Information word
    //inf_WORD[ 0 ] = "0 0 0 0  1 1 1 1  0 0 0 0  1 1 1 1  0 0 0 0  1";     ///< Set random inf word
    inf_WORD[ 0 ].zeros();                                                  ///< in example: zero information word
    Matrix <Vector <bit> > code_WORD = inf_WORD * BCH.get_G();              ///< Generate code word (i*G)
    code_WORD.binaris();                                                    ///< All bits mod 2
    cout << "Code word: " << code_WORD << endl;                             ///< Print code word

    //-------- accepted word
    code_WORD[ 0 ][ 3 ] = !code_WORD[ 0 ][ 3 ];                             ///< Add first errors on the code word
    code_WORD[ 0 ][ 10 ] = !code_WORD[ 0 ][ 10 ];                           ///< Add second errors on the code word
    cout << "Accepted word: " << code_WORD << endl;

    //-------- calc syndrome
    Matrix <Vector <bit> > S = code_WORD * !BCH.get_H();                    ///< Syndrome calculate (c*H')
    S.binaris();                                                            ///< All bits mod 2
    Vector <bit> s1( STEPEN ), s2( STEPEN );                                ///< Double part syndrome
    for ( int i = 0; i < STEPEN; i++ )
    {
        s1[ i ] = S[ 0 ][ i ];                                              ///< first part syndrom a^1
        s2[ i ] = S[ 0 ][ i + STEPEN ];                                     ///< second part syndrom a^3
    }
    cout << "Syndrome: " << S << endl;                                      ///< Print syndrome

    //-------- field elements
    GF_element e_s1( &gf_bch );                                             ///< Create GF element for use field
    GF_element e_s2( &gf_bch );
    e_s1 = gf_bch.find_vect( s1 );                                          ///< Log (s1)
    e_s2 = gf_bch.find_vect( s2 );                                          ///< Log (s2)

    //------- coefficient calc
    GF_element  k1( &gf_bch ),                                              ///< Coefficient for equation
                k2( &gf_bch );

    k1 = e_s1;
    k2 = (e_s2/e_s1) - e_s1 * e_s1;                                         ///< Calculate coefficient

    cout << "k1 = " << k1.get_step() << " k2 = " << k2.get_step() << endl;  ///< Print calculated coefficient
    for ( int i = 1; i < gf_bch.get_q() ; i++ )                             ///< Chain procedure (bruit-force all element in field)
    {
        GF_element X( &gf_bch ), buf( &gf_bch );
        X = i;

        buf = X * X + k1 * X + k2;                                          ///< Quad equation X^2 + k1*x + k2

        if ( buf.get_id() == 0 )                                            ///< if find equation solution
            cout << "pos err = " << i << endl;                              ///< print position error
    }

    return 0;
}
