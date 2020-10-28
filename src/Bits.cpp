#include "Bits.h"
#include <cassert>

int get_bits_of_byte(unsigned char* byte,int start_offset,int len)
{   
    assert(len <= 8 && start_offset < 8 && len + start_offset <= 8);
    return ((unsigned char)(*byte << start_offset) ) >> (8 - len);
}

void set_bits_of_byte(unsigned char* byte,int start_offset,int len,unsigned char v)
{
    assert(len <= 8 && start_offset < 8 && len + start_offset <= 8);
    unsigned char c = 0xff;
    unsigned char d = *byte & ~((unsigned char)(c << start_offset) >> (8 - len) <<(8 - len - start_offset));
    unsigned char e = v << (8 - start_offset - len);
    *byte = ((unsigned char)(*byte & d)) | e;
}


#ifdef BIT_TEST
#include <cstdio>
#include <cstdint>

int main()
{
    unsigned char c = 0x78;
    auto d = get_bits_of_byte(&c,2,2);
    printf("%x\n",c);
    set_bits_of_byte(&c,1,3,5);
    printf("%x\n",c);
    set_bits_of_byte(&c,1,3,3);
    printf("%x\n",c);
}




#endif


