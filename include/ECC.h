/// Copyright by v_crys © 2017-2019.
/// @authors Vladimir Khrustalev (advised by N.Shekhunova, S. Kovalev)
/// @brief Library for research and development in the error correction theory
/// @file ECC.h
/// @email: v_crys@mail.ru
/// *Especially for SUAI students*

#ifndef ECC_H
#define ECC_H

#include "ostream"
#include <string>
#include "../Matrix.h"

namespace v_crys
{

	template <class T_G, class T_H>
	class ECC ;

	template <class T_G, class T_H>
	std::ostream & operator<< ( std::ostream &OS, const ECC <T_G, T_H> &src_r )
	{
		src_r.Print( OS );
		return OS;
	}

	template <class T_G, class T_H>
	std::ifstream & operator>> ( std::ifstream &OS, ECC <T_G, T_H> &src_r )
	{
		OS >> src_r._G;
		src_r._n = src_r._G.get_len_vect();
		src_r._k = src_r._G.get_size();

		src_r.calc_H_by_G();
		return OS;
	}

	template <class T_G, class T_H>
	class ECC {
		private:
			std::string _name;
			int _n;
			int _k;
			Matrix <T_H> _H;
			Matrix <T_G> _G;

			void calc_H_by_G()
			{
				Matrix <T_G> copy_G = _G;
				Matrix <Vector <int> > perest = copy_G.diagonal( true );

				Matrix <T_H> new_H = copy_G.ret_part( copy_G.get_size(), 0, copy_G.get_len_vect() - 1, copy_G.get_size() - 1 );
				new_H = !new_H;

				Matrix <Vector <bit> > I( new_H.get_size(), new_H.get_size() );
				I.ones();
				Matrix <T_H> new_H2 = new_H.join_right( I );

				int i;
				for ( i = 0; i < new_H2.get_len_vect(); i++ )
				{
					new_H2.swap_column( i, perest[ 0 ][ i ] );
					std::swap( perest[ 0 ][ i ],
						perest[ 0 ][ perest[ 0 ][ i ] ] );
				}

				_H = new_H2;
			}

			void calc_G_by_H()
			{
				Matrix <T_H> copy_H = _H;
				Matrix <Vector <int> > perest = copy_H.diagonal( false );

				Matrix <T_G> new_G = copy_H.ret_part( 0, 0, copy_H.get_len_vect() - copy_H.get_size() - 1, copy_H.get_size() - 1 );
				new_G = !new_G;

				Matrix <Vector <bit> > I( new_G.get_size(), new_G.get_size() );
				I.ones();
				Matrix <T_G> new_G2 = new_G.join_left( I );

				int i;
				for ( i = 0; i < new_G2.get_len_vect(); i++ )
				{
					new_G2.swap_column( i, perest[ 0 ][ i ] );
					std::swap( perest[ 0 ][ i ], perest[ 0 ][ perest[ 0 ][ i ] ] );
				}
				_G = new_G2;
			}

		public:

			ECC( ) : _n(0), _k(0) {}
			ECC ( std::string name ) : _name( name ), _n(0), _k(0) {};
			ECC( std::string name, int n, int k ) : _name( name ), _n( n ), _k( k ) { _G = Matrix <T_G>( _n, _k );
																							_H = Matrix<T_H>( _n, _n - _k ); };

			int get_n() { return _n; }
			int get_k() { return _k; }
			int get_r() { return _n - _k; }
			Matrix <T_G> get_G() { return _G; }
			Matrix <T_H> get_H() { return _H; }

			void Print( std::ostream &OS ) const
			{
				OS << std::endl << "Code: " << _name << "(" << _n << ", " << _k << ")" << std::endl;
				OS << "G = " << std::endl << _G << std::endl;
				OS << "H = " << std::endl << _H << std::endl;
			}


			friend std::ostream & operator<< <T_G, T_H>( std::ostream &OS, const ECC <T_G, T_H>&src_r );
			friend std::ifstream & operator>> <T_G, T_H>( std::ifstream &OS, ECC <T_G, T_H> &src_r );

			void set_G( Matrix <T_G> &src )
			{
				_G = src;
				_n = _G.get_len_vect();
				_k = _G.get_size();

				calc_H_by_G();
			}

			void set_H( Matrix <T_H> &src )
			{
				_H = src;
				_n = src.get_len_vect();
				_k = src.get_len_vect() - src.get_size();

				calc_G_by_H();
			}

			float speed_R() { return (float)_k/_n; }

	};
}
#endif // ECC_H
