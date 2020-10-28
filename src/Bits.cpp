#include "Bits.h"
#include <cassert>

int get_bits_of_byte(char* byte,int start_offset,int len)
{   
    assert(len <= 8 && start_offset < 8 && len + start_offset <= 8);
    return (*byte << start_offset ) >> (start_offset + len);
}

void set_bits_of_byte(char* byte,int start_offset,int len,unsigned char v)
{
    assert(len <= 8 && start_offset < 8 && len + start_offset <= 8);
    unsigned char c = 0xff;
    unsigned char d = *byte & ~(c << start_offset) >> (start_offset + len);
    unsigned char e = (v << start_offset ) >> (start_offset + len) << ( 8 - start_offset -  len);
    *byte = d & e;
}


