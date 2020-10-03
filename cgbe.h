#pragma once

/*
 * cgbe.h
 *
 *  Created on: Apr 24, 2014
 *      Author: zfan
 */

#ifndef CGBE_H_
#define CGBE_H_

#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

using namespace std;

#define     DEFAULTMSGSIZE        2048
#define     DEFAULTRANDOM         32

class CGBE {
public:
	// variables
	mpz_t encoding;
	mpz_t zero;
	mpz_t I;
	mpz_t r, g, x, gx, gx_1, n;
	mpz_t combined_private_key1;
	mpz_t combined_private_key2;
	mpz_t combined_private_key3;
	mpz_t combined_private_key4;
	gmp_randstate_t r_state;

	// scheme functions
	CGBE();
	~CGBE();
	void encrypt(mpz_t& m, mpz_t& c);
	void decrypt(mpz_t& c, mpz_t& m);
	void decrypt(mpz_t& c, mpz_t& m, int cnt);
	void decryption_OneIter(mpz_t& c, mpz_t& m);
	void decryption_NeighborLabel(mpz_t& c, mpz_t& m);
	void decryption_TwoIter(mpz_t& c, mpz_t& m);
	void decryption_Path(mpz_t& c, mpz_t& m);

	void setvalue(mpz_t& _d, mpz_t& _s);
	void setvalue(mpz_t& _d, int _s);
	void mul(mpz_t& _rs, mpz_t& _l, mpz_t& _r);
	void add(mpz_t& _rs, mpz_t& _l, mpz_t& _r);
	bool isZero(mpz_t& _m);
	void setCombinedPrivateKey_OneIter(int _n);
	void setCombinedPrivateKey_NeighborLabel(int _n);
	void setCombinedPrivateKey_TwoIter(int _n);
	void setCombinedPrivateKey_Path(int _n);
	bool isEqual(mpz_t& _l, mpz_t& _r);

private:
	// utilities
	void genRand(mpz_t& _r, int _size);
	void _mulmod(mpz_t& res, mpz_t& a, mpz_t& b, mpz_t& mod);
	void _addmod(mpz_t& res, mpz_t& a, mpz_t& b, mpz_t& mod);

	void generator();
};


CGBE::CGBE() {
	mpz_init(encoding);
	mpz_init(zero);
	mpz_init(r);
	mpz_init(g);
	mpz_init(x);
	mpz_init(gx);
	mpz_init(gx_1);
	mpz_init(n);		//public key
	mpz_init(I);
	mpz_init(combined_private_key1);
	mpz_init(combined_private_key2);
	mpz_init(combined_private_key3);
	mpz_init(combined_private_key4);

	// random
	gmp_randinit_default(r_state);
	gmp_randinit_mt(r_state);

	generator();
}

CGBE::~CGBE() {
	mpz_clear(encoding);
	mpz_clear(zero);
	mpz_clear(r);
	mpz_clear(g);
	mpz_clear(x);
	mpz_clear(gx);
	mpz_clear(gx_1);
	mpz_clear(n);
	mpz_clear(I);
	mpz_clear(combined_private_key1);
	mpz_clear(combined_private_key2);
	mpz_clear(combined_private_key3);
	mpz_clear(combined_private_key4);	
}

void CGBE::setvalue(mpz_t& _d, mpz_t& _s) {
	mpz_set(_d, _s);
}

void CGBE::setvalue(mpz_t& _d, int _s) {
	mpz_set_d(_d, _s);
}

void CGBE::mul(mpz_t& _rs, mpz_t& _l, mpz_t& _r) {
	_mulmod(_rs, _l, _r, n);
}

void CGBE::add(mpz_t& _rs, mpz_t& _l, mpz_t& _r) {
	_addmod(_rs, _l, _r, n);
}

void CGBE::genRand(mpz_t& _r, int _size) {
	mpz_urandomb(_r, r_state, _size);
}

void CGBE::generator() {
	// encoding
	mpz_set_d(encoding, 2147483647);

	mpz_set_d(zero, 0);

	// x, n
	/*mpz_set_str(
		n,
		"16594900510468848618779859529048970562434151887982758146333908610126995606875959583150754096904939163058088732836622155984787148951754484085080055100022863834734805390568247562546896289033380553816126638204887528488669669650795595078243509793710242842807549471564349489475385605450605971121686746302940877979192119330073120037897310684720105742251875954769621467756551735273135476454843803189963924528556657594267637567873522001475725298702714900996470201476441839588209221083986823968709674978326806081379946096271872621299301620422089624262355737113475982440526827509351111547011077378815198009079208558801443913617", //2048 bits
		10);*/

	mpz_set_str(
		n,
		"768595156829439879994515994333421150800566015989927862172785417091634875624487127681627669464994298176935567237226601013022205171652416159202251787081580158986100211849323820366353504365984333749417611589518842429872457874860135214530319168310700181788606417605165021621635686930787968649830901539001923081995264429684108396883448352035033226178475718742729694655610179845439806508911420844823035723559633630716182482599570184502293496294830282368359996964511913838875771979522469415865693586851921709764277866012467997763372590390984795620507405511293984885916118647248339798359639152361553476431173203793056634649692895547135636675529228929667628370904927948122208020805820569200872995606106841632458220096699886883923779991816858073418393381992186493816060203022144159697162970381502280125900038339505798959820825304066206929545646630203556889349127196151629958014681607978721917031448679231689308272494794125791252898066384323857827061262040178436782277945282598455359548103568011016383053742863706563583843666209311715826205061323215720733044083633588914725314729375466462416793086127618605931882622916433650561011898428347627880754975088090172881311618067320485773782628233969848943951827618769652867652245093254179941814967597", //4096 bits
		10);
	genRand(x, DEFAULTMSGSIZE);

	// g, gx, gx_1
	mpz_set_d(g, 3);
	mpz_powm(gx, g, x, n);
	mpz_invert(gx_1, gx, n);
}

void CGBE::encrypt(mpz_t& m, mpz_t& c) {
	genRand(r, DEFAULTRANDOM);
	mpz_mul(c, m, r);
	_mulmod(c, c, gx, n);
}

void CGBE::decrypt(mpz_t& c, mpz_t& m) {
	// m = c * gx_1 % n
	_mulmod(m, c, gx_1, n);

	// m = m % encoding
	mpz_mod(m, m, encoding);
}

bool CGBE::isZero(mpz_t& _m) {
	if (mpz_cmp_d(_m, 0) == 0) {
		return true;
	}
	return false;
}

bool CGBE::isEqual(mpz_t& _l, mpz_t& _r) {
	if (mpz_cmp(_l, _r) == 0) {
		return true;
	}
	return false;
}

void CGBE::decrypt(mpz_t& c, mpz_t& m, int cnt) {
	mpz_t gx_m, _cnt;
	mpz_init(gx_m);
	mpz_init(_cnt);
	mpz_set_d(_cnt, cnt);

	// gx_m = gx_1 ^ _cnt
	mpz_powm(gx_m, gx_1, _cnt, n);

	// m = (c * gx_m) % n
	_mulmod(m, c, gx_m, n);

	// m = m % encoding
	mpz_mod(m, m, encoding);

	mpz_clear(_cnt);
	mpz_clear(gx_m);
}

void CGBE::_addmod(mpz_t& res, mpz_t& a, mpz_t& b, mpz_t& mod) {
	mpz_add(res, a, b);
	mpz_mod(res, res, mod);
}

void CGBE::_mulmod(mpz_t& res, mpz_t& a, mpz_t& b, mpz_t& mod) {
	mpz_mul(res, a, b);
	mpz_mod(res, res, mod);
}

void CGBE::setCombinedPrivateKey_OneIter(int cnt) {
	mpz_t _cnt;
	mpz_init(_cnt);
	mpz_set_d(_cnt, cnt);
	mpz_powm(combined_private_key1, gx_1, _cnt, n);

	mpz_clear(_cnt);
}

void CGBE::setCombinedPrivateKey_NeighborLabel(int cnt) {
	mpz_t _cnt;
	mpz_init(_cnt);
	mpz_set_d(_cnt, cnt);
	mpz_powm(combined_private_key2, gx_1, _cnt, n);
	mpz_clear(_cnt);
}

void CGBE::setCombinedPrivateKey_TwoIter(int cnt) {
	mpz_t _cnt;
	mpz_init(_cnt);
	mpz_set_d(_cnt, cnt);
	mpz_powm(combined_private_key3, gx_1, _cnt, n);

	mpz_clear(_cnt);
}

void CGBE::setCombinedPrivateKey_Path(int cnt) {
	mpz_t _cnt;
	mpz_init(_cnt);
	mpz_set_d(_cnt, cnt);
	mpz_powm(combined_private_key4, gx_1, _cnt, n);
	mpz_clear(_cnt);
}

void CGBE::decryption_OneIter(mpz_t& c, mpz_t& m) {
	// m = c * gx_1 % n
	_mulmod(m, c, combined_private_key1, n);

	// m = m % encoding
	mpz_mod(m, m, encoding);
}


void CGBE::decryption_NeighborLabel(mpz_t& c, mpz_t& m) {
	// m = c * gx_1 % n
	_mulmod(m, c, combined_private_key2, n);

	// m = m % encoding
	mpz_mod(m, m, encoding);
}

void CGBE::decryption_TwoIter(mpz_t& c, mpz_t& m) {
	// m = c * gx_1 % n
	_mulmod(m, c, combined_private_key3, n);

	// m = m % encoding
	mpz_mod(m, m, encoding);
}

void CGBE::decryption_Path(mpz_t& c, mpz_t& m) {
	// m = c * gx_1 % n
	_mulmod(m, c, combined_private_key4, n);

	// m = m % encoding
	mpz_mod(m, m, encoding);
}

#endif /* CGBE_H_ */

