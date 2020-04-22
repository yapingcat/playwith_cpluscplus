#include <algorithm>
#include <string>
#include "log.h"

void test_all_any_none_of()
{
    std::vector<int> seqence {1,2,3,4,5,6,8,9,0,10};
    
    if(all_of(seqence.begin(),seqence.end(),[](const int& c){ if(c < 20) return true;}))
    {
        logd("all_of the vector is small than 20");
    }

    if(all_of(seqence.begin(),seqence.end(),[](const int& c){ if(c > 2) return true;}))
    {
        logd("some small than 2");
    }

    if(any_of(seqence.begin(),seqence.end(),[](const int& c) { if(c < 2) return true;}))
    {
        logd("exist one small than 2");
    }

    if(any_of(seqence.begin(),seqence.end(),[](const int& c){ if(c > 10) return true;}))
    {   
        logd("there is no number bigger than 10");
    }

    if(none_of(seqence.begin(),seqence.end(),[](const int& c){ if(c > 20) return true;}))
    {
        logd("thers is no number bigger than 20");
    }

    if(none_of(seqence.begin(),seqence.end(),[](const int&c){ if(c > 9) return true;}))
    {
        logd("there is one bigger than 9");
    }
}

void test_for_each()
{
    std::vector<int> v{1,2,3,4,5,6,7,8,9,10,11};
    std::for_each(v.begin(),v.end(),[](const int& c) { logd("%d",c);});
}

void test_count()
{
    std::vector<int> v{1,2,3,45,6,7,8,9,0,10};
    auto ret = std::count(v.begin(),v.end(),5);
    logd("find %d count 5");
    auto ret2 = std::count_if(v.begin(),v.end(),[](const int&c ){ if(c == 10) return true;});
    logd("find %d count 10");
}

void test_mismatch()
{
    std::string s = "abcdefg";
    std::string s2 = "abcdlll";
    auto ret = std::mismatch(s.begin(),s.end(),s2.begin());
    logd("%c %c",*(ret.first),*(ret.second));
    auto ret1 = std::mismatch(s.begin(),s.end(),s2.begin(),[](const char& c,const char&c2) {
            if(c1 == c2)
                return true;
    });

    logd("%c %c",*(ret.first),*(ret.second));

    auto ret2 = std::mismatch(s.begin(),s.end(),s2.begin(),s2.end(),[](const char&c,const char& c1){
            if(c1 == c2)
                return c2;
    });
}


void test_find()
{
    std::vector<int> v{2,3,4,5,6,744,523,5,231,4,5};
    std::vector<int> v2{4,5,6,2,34,56,7,8,9,0,9};
    auto ret = std::find(v.begin(),v.end(),523);
    if(ret != v.end())
        logd("find this value %d", *ret);
    auto ret1 = std::find_if(v.begin(),v.end(),[](const int& v) { if(v == 69999) return true;});
    if(ret1 == v.end())
        logd("find nothing");
    auto ret2 = std::find_if_not(v.being(),v.end(),[](const int& v){ return v < 700;}
    if(ret2 != v.end())
        logd("find this %d",*ret2);

    auto ret3 = std::find_end(v.begin(),v.end(),v2.begin(),v2.end());
    if(ret3 == v.end())
        logd("find nothing");
    else
        logd("find this location %d",std::distance(v.begin(),ret3));
    
    auto ret4 = std::find_end(v.begin(),v.end(),v2.begin(),v2.end(),[](const int&a, const int&b){
            if(a == b)
                return true;
            else 
                return false;
    });

    if(ret4 == v.end())
        logd("find nothing");
    else    
        logd("find sucessful %d",std::distance(v.begin(),ret4));

    auto ret5 = std::find_first_of(v.begin(),v.end(),v2.begin(),v2.end(),[](const int&a,const int&b){ 
            if(a == b)
                return true;
            else  
                return false;
    });

    if(ret5 == v.end())
        logd("find nothing");
    else 
        logd("find this %d",std::distance(v.begin(),ret5);

    auto ret6 = std::find_first_of(v.begin(),v.end(),v2.begin(),v2.end());
    if(ret6 == v.end())
        logd("find nothing");
    else 
        log("find sucess %d",ret6 - v.begin());
}

int main()
{
    test_all_any_none_of();
    test_for_each();
    test_mismatch();
    test_find();
}





