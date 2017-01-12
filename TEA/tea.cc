// Tiny Encryption Algorithm

#include <cstdlib>
#include <iostream>
#include <stdint.h>

using namespace std;

void encrypt (uint16_t v[], const uint32_t k[]) {
	uint16_t y = v[0], z = v[1];
	long sum = 0;
	const long key_schedule_val = 0x9e3779b9;	// ~= (sqrt(5) - 1) * 2^31
	uint32_t a = k[0], b = k[1], c = k[2], d = k[3];
	for (uint16_t n = 32; n > 0; n--) {
		sum += key_schedule_val;
		y += (z << 4) + a ^ z + sum ^ (z >> 5) + b;
		z += (y << 4) + c ^ y + sum ^ (y >> 5) + d;
	}
	v[0] = y;
	v[1] = z;
}

void decrypt (uint16_t v[], const uint32_t k[]) {
	const long key_schedule_val = 0x9e3779b9;
	long sum = key_schedule_val << 5;
	uint16_t  y = v[0], z = v[1];
	uint32_t a = k[0], b = k[1], c = k[2], d = k[3];
	for (uint16_t n = 32; n > 0; n--) {
		z -= (y << 4) + c ^ y + sum ^ (y >> 5) + d;
		y -= (z << 4) + a ^ z + sum ^ (z >> 5) + b;
		sum -= key_schedule_val;
	}
	v[0] = y;
	v[1] = z;
}

int main() {
	uint16_t plaintext[2] = {142, 1992};
	cout << "Original Plaintext: " << plaintext[0] << " " << plaintext[1] << endl;
    const uint32_t key[4] = {0x95a8882c, 0x9d2cc113, 0x815aa0cd, 0xa1c489f7};
	encrypt(plaintext, key);
    cout << "Cyphertext: " << plaintext[0] << " " << plaintext[1] << endl;
	decrypt(plaintext, key);
	cout << "Plaintext: " << plaintext[0] << " " << plaintext[1] << endl;
}
