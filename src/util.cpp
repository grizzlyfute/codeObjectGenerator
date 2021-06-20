#include "util.h"
#include <algorithm>
#include <string>
#include <ctype.h>

using namespace std;
string strToLower(const string &str)
{
  string ret(str);
  transform(ret.begin(), ret.end(), ret.begin(), ::tolower);
  return ret;
}

string strToUpper(const string &str)
{
  string ret(str);
  transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
  return ret;
}

string firstToUpper(const std::string &str)
{
  string ret(str);
  if (!ret.empty())
  {
    ret[0] = toupper(ret[0]);
  }
  return ret;
}

string firstToLower(const std::string &str)
{
  string ret(str);
  if (!ret.empty())
  {
    ret[0] = tolower(ret[0]);
  }
  return ret;
}

bool isBoolean(const std::string &str)
{
  return
    str == "bool" || str == "boolean" ||
    false;
}

bool isBasicType(const std::string &str)
{
  return
    str == "bool" || str == "boolean" ||
    str == "int8_t" || str == "qint8" || str == "char" || str == "sbyte" ||
    str == "uint8_t" || str == "quint8" || str == "unsigned char" || str == "byte" ||
    str == "int16_t" || str == "qint16" || str == "short" || str == "short int" ||
    str == "uint16_t" || str == "quint16" || str == "unsigned short" || str == "ushort" ||
    str == "int32_t" || str == "qint32" || str == "int" ||
    str == "uint32_t" || str == "quint32" || str == "unsigned int" || str == "unsigned" || str == "uint" ||
    str == "int64_t" || str == "qint64" || str == "long" || str == "long long" ||
    str == "uint64_t" || str == "quint64" || str == "unsigned long long" || str == "ulong" ||
    str == "float" || str == "double" ||
    false;
}

bool isCString(const std::string &str)
{
  return
    str.find("char *") != string::npos || str.find("char*") != string::npos ||
    str.find("int8_t *") != string::npos || str.find("int8_t*") != string::npos ||
    str.find("uint8_t *") != string::npos || str.find("uint8_t*") != string::npos ||
    str.find("qint8 *") != string::npos || str.find("int8 *") != string::npos ||
    str.find("quint8 *") != string::npos || str.find("uint8 *") != string::npos ||
    false;
}
