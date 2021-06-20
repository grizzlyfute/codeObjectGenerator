#ifndef UTIL_H
#define UTIL_H

#include <string>

std::string strToLower(const std::string &);
std::string strToUpper(const std::string &);

std::string firstToUpper(const std::string &);
std::string firstToLower(const std::string &);

bool isBoolean(const std::string &str);
bool isBasicType(const std::string &str);
bool isCString(const std::string &str);

#endif // UTIL_H
