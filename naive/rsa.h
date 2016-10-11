#include <gmp.h>
// Stores the values needed to encrypt and decrypt a message, without storing
// the message itself.
struct RsaVariables {
	mpz_t p;
	mpz_t q;
	mpz_t n;
	mpz_t totient;
	mpz_t e;
	mpz_t d;
} ;

// Get the p and q values for 'state'.
void FillPrimes(RsaVariables *state);

// Helper function for FillPrimes().
void GetPrime(RsaVariables *state);

// Fill the other constants in state.
void FillConstants(RsaVariables *state);
