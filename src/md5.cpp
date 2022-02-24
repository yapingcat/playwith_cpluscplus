#include "md5.h"

#include <fstream>
#include <iomanip>
#include <sstream>

uint8_t S[64] = {
    7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20, 5, 9,  14, 20,
    4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21,
};

uint32_t K[64] = {
    0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
    0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
    0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
    0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

std::string encodeHex(uint32_t n)
{
	std::stringstream ss;
	char buf[3] = {0};
	sprintf(buf, "%02x", (uint8_t)n);
	ss << std::hex << std::setw(2) << std::setfill('0') << buf;
	sprintf(buf, "%02x", (uint8_t)(n >> 8));
	ss << std::hex << std::setw(2) << std::setfill('0') << buf;
	sprintf(buf, "%02x", (uint8_t)(n >> 16));
	ss << std::hex << std::setw(2) << std::setfill('0') << buf;
	sprintf(buf, "%02x", (uint8_t)(n >> 24));
	ss << std::hex << std::setw(2) << std::setfill('0') << buf;
	return ss.str();
}

inline uint32_t leftRoate(uint32_t x, int n) { return (x << n) | (x >> (32 - n)); }

void MD5::sum(const string& content) { sum(content.data(), content.size()); }

void MD5::sumFile(const string& path)
{
	std::ifstream in_(path, std::ifstream::binary | std::ifstream::in);
	if (!in_)
	{
		throw std::runtime_error("open file failed");
	}
	char buf[64 * 512] = {0};
	while (in_.read(buf, 64 * 512))
	{
		sum(buf, 64 * 512);
	}
	sum(buf, in_.gcount());
}
void MD5::sum(const char* data, std::size_t len)
{
	const char* message = data;
	uint32_t length = len;

	if (!cache_.empty())
	{
		cache_.append(data, len);
		message = cache_.data();
		length = len;
	}

	total_ += len;
	int i = 0;
	for (i = 0; i + 64 <= length; i += 64)
	{
		processChunk((const uint8_t*)message + i);
	}
	if (cache_.empty())
	{
		if (i < length)
		{
			cache_.append(message + i, length - i);
		}
	}
	else
	{
		cache_ = cache_.substr(i);
	}
}
void MD5::processChunk(const uint8_t* chunk)
{
	uint32_t A = a_;
	uint32_t B = b_;
	uint32_t C = c_;
	uint32_t D = d_;
	uint32_t M[16] = {0};
	for (int j = 0; j < 16; j++)
	{
		M[j] = chunk[0 + j * 4];
		M[j] |= uint32_t(chunk[1 + j * 4]) << 8;
		M[j] |= uint32_t(chunk[2 + j * 4]) << 16;
		M[j] |= uint32_t(chunk[3 + j * 4]) << 24;
	}

	for (int i = 0; i < 64; i++)
	{
		uint32_t F, g;
		if (i >= 0 && i < 16)
		{
			F = (B & C) | ((~B) & D);
			g = i;
		}
		else if (i >= 16 && i < 32)
		{
			F = (D & B) | ((~D) & C);
			g = (5 * i + 1) % 16;
		}
		else if (i >= 32 && i < 48)
		{
			F = B ^ C ^ D;
			g = (3 * i + 5) % 16;
		}
		else
		{
			F = C ^ (B | (~D));
			g = (7 * i) % 16;
		}
		F = F + A + K[i] + M[g];
		A = D;
		D = C;
		C = B;
		B = B + leftRoate(F, S[i]);
	}
	a_ = a_ + A;
	b_ = b_ + B;
	c_ = c_ + C;
	d_ = d_ + D;
}
std::string MD5::final()
{
	int least = total_ % 64;
	int appendLen = 0;
	if (least < 56)
	{
		appendLen = 56 - least;
	}
	else if (least > 56)
	{
		appendLen = 120 - least;
	}
	if (appendLen > 0)
	{
		cache_.push_back(0x80);
		cache_.append(string(appendLen - 1, 0x00));
	}
	total_ = total_ * 8;
	cache_.push_back(uint8_t(total_ & 0xFF));
	cache_.push_back(uint8_t(total_ >> 8 & 0xFF));
	cache_.push_back(uint8_t(total_ >> 16 & 0xFF));
	cache_.push_back(uint8_t(total_ >> 24 & 0xFF));
	cache_.push_back(uint8_t(total_ >> 32 & 0xFF));
	cache_.push_back(uint8_t(total_ >> 40 & 0xFF));
	cache_.push_back(uint8_t(total_ >> 48 & 0xFF));
	cache_.push_back(uint8_t(total_ >> 52 & 0xFF));
	sum(cache_.data(), cache_.size());
	string digest = "";
	digest += encodeHex(a_);
	digest += encodeHex(b_);
	digest += encodeHex(c_);
	digest += encodeHex(d_);
	return digest;
}

void MD5::reset()
{
	a_ = 0x67452301;
	b_ = 0xEFCDAB89;
	c_ = 0x98BADCFE;
	d_ = 0x10325476;
	cache_.clear();
	total_ = 0;
}

#ifdef MD5_TEST

#include <iostream>

int main()
{
	std::string test = "fdsfdsacewsdfsacewcsagfsfercvsagsafecaewfsdfMedia_header:MEDIAINFO=494D4B48010300000400000111710110401F000000FA000000000000000000000000000000000000";
	std::cout << test.size() << std::endl;
	MD5 m;
	m.sum(test);
	std::cout << m.final() << std::endl;
	return 0;
}

#endif
