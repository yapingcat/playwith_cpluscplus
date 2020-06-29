#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <string>
#include <functional>
#include <vector>

void splitString(const std::string& str,char c,std::function<void(const char*,size_t)> func);
void splitString(const std::string& str,const std::vector<char>& vc,std::function<void(const char*,size_t)> func);

std::vector<std::string> splitString(const std::string& str,char c);
std::vector<std::string> splitString(const std::string& str,const std::vector<char>& vc);











#endif