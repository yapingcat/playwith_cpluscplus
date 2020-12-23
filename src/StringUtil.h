#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <functional>
#include <vector>

void splitString(const std::string& str,char c,const std::function<void(const char*,size_t)>& func);
void splitString(const std::string& str,const std::vector<char>& vc,std::function<void(const char*,size_t)> func);
int splitInTwoPart(const std::string& str,const char c, std::string& left, std::string& right);

bool startWithString(const std::string& str, const std::string& startStr);

std::vector<std::string> splitString(const std::string& str,char c);
std::vector<std::string> splitString(const std::string& str,const std::vector<char>& vc);


//this end with \r \n \r\n
void readLines(const std::string& str,const std::function<void(const char*,size_t)>& func);






#endif
