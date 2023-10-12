#pragma once
#ifndef Stribog_H
#define Stribog_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <string.h>
#include <stddef.h>

	struct Stribog_buff {
		uint64_t data_size;
		uint32_t h[8];
		uint8_t last_chunk[64];
		uint8_t chunk_size;
	};

	/* Initialization, must be called before any further use */
	void Stribog_init(struct Stribog_buff* buff);

	/* Process block of data of arbitary length, can be used on data streams (files, etc) */
	void Stribog_update(struct Stribog_buff* buff, const void* data, size_t size);

	/* Produces final hash values (digest) to be read
	   If the buffer is reused later, init must be called again */
	void Stribog_finalize(struct Stribog_buff* buff);

	/* Read digest into 32-byte binary array */
	void Stribog_read(const struct Stribog_buff* buff, uint8_t* hash);

	/* Read digest into 64-char string as hex (without null-byte) */
	void Stribog_read_hex(const struct Stribog_buff* buff, char* hex);

	/* Hashes single contiguous block of data and reads digest into 32-byte binary array */
	void Stribog_easy_hash(const void* data, size_t size, uint8_t* hash);

	/* Hashes single contiguous block of data and reads digest into 64-char string (without null-byte) */
	void Stribog_easy_hash_hex(const void* data, size_t size, char* hex);

#ifdef __cplusplus
}

#include <string>

class Stribog {
private:
	struct Stribog_buff buff;
public:
	Stribog() {
		Stribog_init(&buff);
	}

	void update(const void* data, std::size_t size) {
		Stribog_update(&buff, data, size);
	}

	std::string hash() {
		char hash[64];
		Stribog_finalize(&buff);
		Stribog_read_hex(&buff, hash);
		Stribog_init(&buff);
		return std::string(hash, 64);
	}

	static std::string hashString(const std::string& str) {
		char hash[64];
		Stribog_easy_hash_hex(str.c_str(), str.length(), hash);
		return std::string(hash, 64);
	}
};

#endif

#endif