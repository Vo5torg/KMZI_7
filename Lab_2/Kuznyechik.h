#pragma once
#pragma once
#include "mycrypto.h"
#define BLOCK_LENGTH 16
void init_perms();
void init_consts();
void nonlinear_transform_direct128(BYTE * target);
void nonlinear_transform_inverse128(BYTE * target);
WORD multiply(WORD lhs, WORD rhs);
void xor128(BYTE * dst, const BYTE * lhs, const BYTE * rhs);
BYTE linear_transform_core128(const BYTE * target);
void linear_transform_direct128(BYTE * target);
void linear_transform_inverse128(BYTE * target);
void iteration_linear_transform_direct128(BYTE * target);
void iteration_linear_transform_inverse128(BYTE * target);
void encrypt128(BYTE * target, const vector<ByteBlock> & keys);
void decrypt128(BYTE * target, const vector<ByteBlock> & keys);
void keys_transform128(BYTE * k1, BYTE * k2, int iconst);
void key_derivation128(BYTE * k1, BYTE * k2, BYTE * k3, BYTE * k4,
	int ipair);
class Kuznyechik {
	std::vector<ByteBlock> keys;
	static bool is_init;
public:
	static const int block_lenght{ BLOCK_LENGTH };
	Kuznyechik(const ByteBlock & key);
	Kuznyechik(const Kuznyechik & rhs);
	~Kuznyechik();
	void encrypt(const ByteBlock & src, ByteBlock & dst) const;
	void decrypt(const ByteBlock & src, ByteBlock & dst) const;
};
