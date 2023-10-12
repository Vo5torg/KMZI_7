#pragma once
#pragma once
#include <stdexcept>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>
#include <vector>
#include <map>
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
typedef unsigned char BYTE;
typedef unsigned short int WORD;
class ByteBlock {
	BYTE * pBlocks;
	size_t amount_of_bytes;
public:
	ByteBlock(size_t size_ = 0, BYTE init_value = 0);
	ByteBlock(BYTE * pBlocks_, size_t size_);
	ByteBlock(ByteBlock && rhs);
	~ByteBlock();
	void operator = (ByteBlock && rhs);
	BYTE * byte_ptr();
	const BYTE * byte_ptr() const;
	BYTE & operator [] (size_t index);
	BYTE operator [] (size_t index) const;
	bool operator == (const ByteBlock & lhs) const;
	bool operator != (const ByteBlock & lhs) const;
	void reset(const BYTE * pBlocks_, size_t size_);
	size_t size() const;
	ByteBlock deep_copy() const;
	ByteBlock operator () (size_t begin, size_t length) const;
	friend void swap(ByteBlock & lhs, ByteBlock & rhs);
};
vector<ByteBlock> split_blocks(const ByteBlock & src, size_t
	length);
ByteBlock join_blocks(const vector<ByteBlock> & blocks);
void xor_blocks(ByteBlock & to_assign, const ByteBlock & lhs,
	const ByteBlock & rhs);
string hex_representation(const ByteBlock & bb);
ByteBlock hex_to_bytes(const string & s);