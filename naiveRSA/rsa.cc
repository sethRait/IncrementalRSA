#include <cmath>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <linux/random.h>

#include "rsa.h"
// For fast arbitrary-precision arithmetic.
#include <gmpxx.h>
#include <gmp.h>

using namespace std;

int main() {
	RsaVariables state;
	string message;
	cout << "Please enter an integer to encrypt: ";
	cin >> message;

	// A third argument of 0 causes the base to be inferred from leading digits
	// of the second argument.
	mpz_t plaintext;
	mpz_init_set_str(plaintext, message.c_str(), 0);
	// Generate the values needed for encryption and decryption.
	FillPrimes(&state);
	FillConstants(&state);

	// Encrypt plaintext into cyphertext.
	mpz_t cyphertext;
	mpz_init(cyphertext);
	mpz_powm(cyphertext, plaintext, state.e, state.n); // Bless this pow-mod
	mpz_clear(plaintext); // No more plaintext!
	cout << "\nCyphertext:\n" << cyphertext << endl;

	// Decrypt cyphertext back into plaintext.
	mpz_t recovered_plaintext;
	mpz_init(recovered_plaintext);
	mpz_powm(recovered_plaintext, cyphertext, state.d, state.n);
	cout << "\nSecret: " << recovered_plaintext << endl;
	return 0;
}

void FillPrimes(RsaVariables *state) {
	mpz_init(state->p);
	mpz_init(state->q);
	mpz_t candidate_prime;
	mpz_init(candidate_prime);	
	mpz_class ran;
	gmp_randclass rr(gmp_randinit_default);

	// Get two 512 bit primes seeded from the current clock time.
	rr.seed(time(NULL));
	ran = rr.get_z_bits(512);  // This is short enough for a brute-force attack.
	mpz_nextprime(candidate_prime, ran.get_mpz_t());
	mpz_set(state->p, candidate_prime);
	ran = rr.get_z_bits(512);
	mpz_nextprime(candidate_prime, ran.get_mpz_t());
	mpz_set(state->q, candidate_prime);
}

void FillConstants(RsaVariables *state) {
	mpz_t temp1;
	mpz_t temp2;
	mpz_init(temp1);
	mpz_init(temp2);
	// Set the modulus.  |n| = |p| + |q|
	mpz_init(state->n);
	mpz_mul(state->n, state->p, state->q);
	// Set the totient
	mpz_init(state->totient);
	mpz_sub_ui(temp1, state->p, 1);
	mpz_sub_ui(temp2, state->q, 1);
	mpz_mul(state->totient, temp1, temp2);

	// Set the public exponent.  Common choices are 3 and 65537.
	mpz_init_set_str(state->e, "65537", 0); // That was easy...
	// Set the private exponent.
	mpz_t s;
	mpz_init(s);
	mpz_init(state->d);
	mpz_t gcd;
	mpz_init(gcd);

	// Use the Extended Euclidean GCD algorithm to find the decryption exponent.
	// gcd(e, totient) = se + d(totient)
	mpz_gcdext(gcd, state->d, s, state->e, state->totient);
}
