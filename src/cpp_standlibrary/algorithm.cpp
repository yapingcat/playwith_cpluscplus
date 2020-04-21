#include <algorithm>
#include "log.h"

void test_all_any_none_of()
{
    std::vector<int> seqence {1,2,3,4,5,6,8,9,0,10};
    
    if(all_of(seqence.begin(),seqence.end(),[](const int& c){ if(c < 20) return true;}))
    {
        logd("all_of the vector is small than 20");
    }

    if(all_of(sequence.begin(),sequence.end(),[](const int& c){ if(c > 2) return true;}))
    {
        logd("some small than 2");
    }

    if(any_of(seqence.begin(),seqence.end(),[](const int* c) { if(c < 2) return true;}))
    {
        logd("exist one small than 2");
    }

    if(any_of(sequence.begin(),sequence.end(),[](const int& c){ if(c > 10) return true;}))
    {   
        logd("there is no number bigger than 10");
    }

    if(none_of(sequence.begin(),sequence.end(),[](const int& c){ if(c > 20) return true;}))
    {
        logd("thers is no number bigger than 20");
    }

    if(none_of(sequence.begin(),sequence.end(),[](const int&c){ if(c > 9) return true;}))
    {
        logd("there is one bigger than 9");
    }
}



int main()
{
    test_all_any_none_of();
}





