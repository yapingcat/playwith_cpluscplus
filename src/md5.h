#ifndef MD5_H
#define MD5_H

#include <array>
#include <string>
#include <vector>
using std::array;
using std::string;
using std::vector;

class MD5 {
   public:
	void sum(const string& content);
	void sum(const char* data, std::size_t len);
	void sumFile(const string& path);
	std::string final();

   private:
	void processChunk(const uint8_t* chunk);

   private:
	uint32_t a_ = 0x67452301;
	uint32_t b_ = 0xEFCDAB89;
	uint32_t c_ = 0x98BADCFE;
	uint32_t d_ = 0x10325476;
	string cache_;
	uint64_t total_;
};

#endif
