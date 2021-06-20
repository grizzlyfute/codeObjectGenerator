#include "ABaseObject.h"
#include "util.h"
#include <iostream>
using namespace std;

void ABaseObject::generate_c() const
{
  list<pair<string, string> >::const_iterator it;

  cout << "// ========== header ==========" << endl;
  cout << "#ifndef " << strToUpper(getName()) << "_H" << endl;
  cout << "#define " << strToUpper(getName()) << "_H" << endl;
  cout << endl;

  cout << "// typedef struct " << getName() << " " << getName() << ";" << endl;
  cout << "// struct " << getName() << endl;
  cout << "typedef struct" << endl;
  cout << "{" << endl;
  for (it = m_parameters.begin(); it != m_parameters.end(); it++)
  {
    cout << getTab() << it->first << " " << firstToLower(it->second) << ";" << endl;
  }
  cout << "} " << getName() << ";" << endl;
  cout << endl;

  if (getConstructor())
  {
    cout << getName() << "* constructor" << firstToUpper(getName()) << "();" << endl;
  }
  if (getParamConstructor() && !m_parameters.empty())
  {
    cout << getName() << "* constructorParams" << firstToUpper(getName()) << endl;
    cout << "(" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (isBasicType(it->first))
        cout << getTab() << it->first << " " << firstToLower(it->second);
      else if (isCString(it->first))
        cout << getTab() << it->first << " " << firstToLower(it->second);
      else
        cout << getTab() << it->first << " *" << firstToLower(it->second);
      if (it != --m_parameters.end())
        cout << "," << endl;
      else
        cout << endl;
    }
    cout << ");" << endl;
  }
  if (getConstructor() || (getParamConstructor() && !m_parameters.empty())|| getClone())
  {
    cout << "void free" << firstToUpper(getName()) << "(" << getName() << "* a);" << endl;
  }
  if (getEquals())
  {
    cout << "int equals" << firstToUpper(getName()) << "(" << getName() << " *a, " << getName() << " *b);" << endl;
  }
  if (getTostring())
  {
    cout << "char* appendTo(char *str, const char *what, int size_what);" << endl;
    cout << "// returned value should be freed with free()" << endl;
    cout << "char * toString" << firstToUpper(getName()) << "(" << getName() << " *a);" << endl;
  }
  if (getClone() || (getParamConstructor() && !m_parameters.empty()))
  {
    cout << getName() << "* clone" << getName() << "(" << getName() << " *other);" << endl;
  }

  if (getEquals() || getConstructor() || getParamConstructor() || getTostring() || getClone())
  {
    cout << endl;
  }

  cout << "#endif // " << strToUpper(getName()) << "_H" << endl;
  cout << endl;

  if (getEquals() || getConstructor() || getParamConstructor() || getTostring() || getClone())
  {
    cout << "// ========== body ==========" << endl;
    cout << "// #include \"" << firstToLower(getName()) << ".h\"" << endl;
    cout << "#include <stdlib.h>" << endl;
    cout << "#include <stdio.h>" << endl;
    cout << "#include <string.h>" << endl;
    cout << endl;
    cout << "#define STRINGIFY(x) #x" << endl;
    cout << "#define TOSTRING(x) STRINGIFY(x)" << endl;
    cout << "#define errlog(format, ...) \\" << endl;
    cout << "do \\" << endl;
    cout << "{ \\" << endl;
    cout << getTab() << "fprintf(stderr, \"Error at \" __FILE__ \":\" TOSTRING(__LINE__) \": \" format, ##__VA_ARGS__); \\" << endl;
    cout << "} while(0)" << endl;
    cout << endl;

    if (getConstructor())
    {
      cout << getName() << "* constructor" << firstToUpper(getName()) << "()" << endl;
      cout << "{" << endl;
      cout << getTab() << getName() << " *l_ret = calloc(1, sizeof(" << getName() << "));" << endl;
      cout << endl;
      cout << getTab() << "if (l_ret == NULL)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "errlog(\"calloc failed\");" << endl;
      cout << getTab() << "}" << endl;
      cout << endl;
      cout << getTab() << "return l_ret;" << endl;
      cout << "}" << endl;
      cout << endl;
    }

    if (getParamConstructor() && !m_parameters.empty())
    {
      cout << getName() << "* constructorParams" << firstToUpper(getName()) << endl;
      cout << "(" << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        if (isBasicType(it->first))
          cout << getTab() << it->first << " " << firstToLower(it->second);
        else if (isCString(it->first))
          cout << getTab() << it->first << " " << firstToLower(it->second);
        else
          cout << getTab() << it->first << " *" << firstToLower(it->second);
        if (it != --m_parameters.end())
          cout << ',' << endl;
        else
          cout << endl;
      }
      cout << ")" << endl;
      cout << "{" << endl;
      cout << getTab() << getName() << " *l_ret = NULL;" << endl;
      cout << endl;
      cout << getTab() << "l_ret = malloc(sizeof(" << getName() << "));" << endl;
      cout << getTab() << "if (l_ret == NULL)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "errlog(\"malloc failed\");" << endl;
      cout << getTab() << getTab() << "goto bye;" << endl;
      cout << getTab() << "}" << endl;
      cout << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        if (isBasicType(it->first))
        {
          cout << getTab() << "l_ret->" << firstToLower(it->second) << " = " << firstToLower(it->second) << ";" << endl;
        }
        else if (isCString(it->first))
        {
          cout << getTab() << "l_ret->" << firstToLower(it->second) << " = strdup(" << firstToLower(it->second) << ");" << endl;
        }
        else
        {
          cout << getTab() << "l_ret->" << firstToLower(it->second) << " = clone" << firstToUpper(it->first) << "(" << firstToLower(it->second) << ");" << endl;
        }
      }
      cout << endl;
      cout << getTab() << "bye:;" << endl;
      cout << getTab() << "return l_ret;" << endl;
      cout << "}" << endl;
      cout << endl;
    }

    if (getConstructor() || getClone() || (getParamConstructor() && !m_parameters.empty()))
    {
      cout << "void free" << firstToUpper(getName()) << "(" << getName() << "* a)" << endl;
      cout << "{" << endl;
      cout << getTab() << "if (a != NULL)" << endl;
      cout << getTab() << "{" << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        if (isCString(it->first))
        {
          cout << getTab() << getTab() << "if (a->" << firstToLower(it->second) << " != NULL)" << endl;
          cout << getTab() << getTab() << "{" << endl;
          cout << getTab() << getTab() << getTab() << "free(a->" << firstToLower(it->second) << ");" << endl;
          cout << getTab() << getTab() << "}" << endl;
        }
        else if (!isBasicType(it->first))
        {
          cout << getTab() << getTab() << "if (a->" << firstToLower(it->second) << " != NULL)" << endl;
          cout << getTab() << getTab() << "{" << endl;
          cout << getTab() << getTab() << getTab() << "free" << firstToUpper(it->first) << "(a->" << firstToLower(it->second) << ");" << endl;
          cout << getTab() << getTab() << "}" << endl;
        }
      }
      cout << getTab() << "}" << endl;
      cout << getTab() << getTab() << "free(a);" << endl;
      cout << "}" << endl;
      cout << endl;
    }

    if (getEquals())
    {
      cout << "int equals" << firstToUpper(getName()) << "(" << getName() << " *a, " << getName() << " *b)" << endl;
      cout << "{" << endl;
      cout << getTab() << "int l_ret = 1;" << endl;
      cout << endl;
      cout << getTab() << "// memcmp(a, b, sizeof(" << getName() << "));" << endl;
      cout << getTab() << "if ((a == NULL && b != NULL) || (a != NULL && b == NULL))" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "l_ret = 0;" << endl;
      cout << getTab() << "}" << endl;
      cout << getTab() << "else if (a == b)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "l_ret = 1;" << endl;
      cout << getTab() << "}" << endl;
      cout << getTab() << "else" << endl;
      cout << getTab() << "{" << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        if (isBasicType(it->first))
        {
          cout << getTab() << getTab() << "l_ret &= a->" << firstToLower(it->second) << " == b->" << firstToLower(it->second) << ";" << endl;
        }
        else if (isCString(it->first))
        {
          cout << getTab() << getTab() << "l_ret &= !strcmp(a->" << firstToLower(it->second) << ", b->" << firstToLower(it->second) << ");" << endl;
        }
        else
        {
          cout << getTab() << getTab() << "l_ret &= equals" << firstToUpper(it->first) << "(a->" << firstToLower(it->second) << ", b->" << firstToLower(it->second) << ");" << endl;
        }
      }
      cout << getTab() << "}" << endl;
      cout << endl;
      cout << getTab() << "return l_ret;" << endl;
      cout << "}" << endl;
      cout << endl;
    }

    if (getTostring())
    {
      cout << "char* appendTo(char *str, const char *what, int size_what)" << endl;
      cout << "{" << endl;
      cout << getTab() << "int l;" << endl;
      cout << getTab() << "char *ptr = NULL;" << endl;
      cout << endl;
      cout << getTab() << "if (str == NULL)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "l = 0;" << endl;
      cout << getTab() << "}" << endl;
      cout << getTab() << "else" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "l = strlen(str);" << endl;
      cout << getTab() << "}" << endl;
      cout << endl;
      cout << getTab() << "if (size_what < 0)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "size_what = strlen(what);" << endl;
      cout << getTab() << "}" << endl;
      cout << endl;
      cout << getTab() << "ptr = realloc(str, sizeof(char)*(l + size_what + 1));" << endl;
      cout << getTab() << "if (ptr)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "str = ptr;" << endl;
      cout << getTab() << getTab() << "strncpy(str + l, what, size_what);" << endl;
      cout << getTab() << getTab() << "*(str + l + size_what) = '\\0';" << endl;
      cout << getTab() << "}" << endl;
      cout << getTab() << "else" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "errlog(\"realloc failed\");" << endl;
      cout << getTab() << "}" << endl;
      cout << endl;
      cout << getTab() << "return str;" << endl;
      cout << "}" << endl;
      cout << endl;
      cout << "// returned value should be freed with free()" << endl;
      cout << "char * toString" << firstToUpper(getName()) << "(" << getName() << " *a)" << endl;
      cout << "{" << endl;
      cout << getTab() << "char * l_ret = NULL;" << endl;
      cout << getTab() << "char * l_tmp = NULL;" << endl;
      cout << getTab() << "char l_buf[8] = {0};" << endl;
      cout << getTab() << "if (l_tmp != NULL) l_tmp = NULL; // avoid unused varaiable warnings" << endl;
      cout << getTab() << "if (l_buf[0] != '\\0') l_buf[0] = '\\0'; // avoid unused varaiable warnings" << endl;
      cout << endl;
      cout << getTab() << "if (a == NULL)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "// errlog(\"NULL argument given\");" << endl;
      cout << getTab() << getTab() << "goto bye;" << endl;
      cout << getTab() << "}" << endl;
      cout << endl;
      cout << getTab() << "l_ret = strdup(\"" << getName() << ": {\");" << endl;
      cout << getTab() << "if (l_ret == NULL)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << "errlog(\"strdup failed\");" << endl;
      cout << getTab() << getTab() << "goto bye;" << endl;
      cout << getTab() << "}" << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        cout << getTab() << "l_ret = appendTo(l_ret, \"" << firstToLower(it->second) << ": \", sizeof(\"" << firstToLower(it->second) << ": \") - 1);" << endl;
        cout << getTab() << "if (l_ret == NULL)" << endl;
        cout << getTab() << "{" << endl;
        cout << getTab() << getTab() << "errlog(\"appendTo failed\");" << endl;
        cout << getTab() << getTab() << "goto bye;" << endl;
        cout << getTab() << "}" << endl;
        if (isBasicType(it->first))
        {
          if (it->first == "int8_t" || it->first == "qint8" || it->first == "char" || it->first == "sbyte")
          {
            cout << getTab() << "strncpy(l_buf, \"'x'\", sizeof(l_buf)/sizeof(l_buf[0]);" << endl;
            cout << getTab() << "l_buf[1] = a->" << firstToLower(it->second) << ":" << endl;
          }
          else if
          (
            it->first == "int16_t" || it->first == "qint16" || it->first == "short" || it->first == "short int" ||
            it->first == "int32_t" || it->first == "qint32" || it->first == "int"
          )
          {
            cout << getTab() << "snprintf(l_buf, sizeof(l_buf)/sizeof(l_buf[0]), \"%d\", a->" << firstToLower(it->second) << ");" << endl;
          }
          else if
          (
            it->first == "uint8_t" || it->first == "quint8" || it->first == "unsigned char" || it->first == "byte" ||
            it->first == "uint16_t" || it->first == "quint16" || it->first == "unsisgned short" || it->first == "ushort" ||
            it->first == "uint32_t" || it->first == "quint32" || it->first == "unsigned int" || it->first == "unsigned"
          )
          {
            cout << getTab() << "snprintf(l_buf, sizeof(l_buf)/sizeof(l_buf[0]), \"%u\", a->" << firstToLower(it->second) << ");" << endl;
          }
          else if (it->first == "int64_t" || it->first == "qint64" || it->first == "long" || it->first == "long long")
          {
            cout << getTab() << "snprintf(l_buf, sizeof(l_buf)/sizeof(l_buf[0]), \"%lld\", a->" << firstToLower(it->second) << ");" << endl;
          }
          else if (it->first == "uint64_t" || it->first == "quint64" || it->first == "ulong" || it->first == "unsigned long long")
          {
            cout << getTab() << "snprintf(l_buf, sizeof(l_buf)/sizeof(l_buf[0]), \"%llu\", a->" << firstToLower(it->second) << ");" << endl;
          }
          else if (it->first == "float")
          {
            cout << getTab() << "snprintf(l_buf, sizeof(l_buf)/sizeof(l_buf[0]), \"%f\", a->" << firstToLower(it->second) << ");" << endl;
          }
          else if (it->first == "double")
          {
            cout << getTab() << "snprintf(l_buf, sizeof(l_buf)/sizeof(l_buf[0]), \"%lf\", a->" << firstToLower(it->second) << ");" << endl;
          }
          else
          {
            cout << getTab() << "strncpy(l_buf, \"?\", sizeof(l_buf)/sizeof(l_buf[0]));" << endl;
          }
          cout << getTab() << "l_ret = appendTo(l_ret, l_buf, -1);" << endl;
        }
        else if (isCString(it->first))
        {
          cout << getTab() << "if (a->" << firstToLower(it->second) << ")" << endl;
          cout << getTab() << "{" << endl;
          cout << getTab() << getTab() << "l_ret = appendTo(l_ret, \"\\\"\", sizeof(\"\\\"\") - 1);" << endl;
          cout << getTab() << getTab() << "l_ret = appendTo(l_ret, a->" << firstToLower(it->second) << ", -1);" << endl;
          cout << getTab() << getTab() << "l_ret = appendTo(l_ret, \"\\\"\", sizeof(\"\\\"\") - 1);" << endl;
          cout << getTab() << "}" << endl;
        }
        else
        {
          cout << getTab() << "l_tmp = toString" << firstToUpper(it->first) << "(a->" << firstToLower(it->second) << ");" << endl;
          cout << getTab() << "if (l_tmp != NULL)" << endl;
          cout << getTab() << "{" << endl;
          cout << getTab() << getTab() << "l_ret = appendTo(l_ret, l_tmp, -1);" << endl;
          cout << getTab() << getTab() << "free(l_tmp);" << endl;
          cout << getTab() << getTab() << "l_tmp = NULL;" << endl;
          cout << getTab() << "}" << endl;
        }
        cout << getTab() << "if (l_ret == NULL)" << endl;
        cout << getTab() << "{" << endl;
        cout << getTab() << getTab() << "errlog(\"appendTo failed\");" << endl;
        cout << getTab() << getTab() << "goto bye;" << endl;
        cout << getTab() << "}" << endl;
        cout << getTab() << "l_ret = appendTo(l_ret, \",\", sizeof(\",\") - 1);" << endl;
        cout << getTab() << "if (l_ret == NULL)" << endl;
        cout << getTab() << "{" << endl;
        cout << getTab() << getTab() << "errlog(\"appendTo failed\");" << endl;
        cout << getTab() << getTab() << "goto bye;" << endl;
        cout << getTab() << "}" << endl;
      }
      cout << getTab() << "l_ret = appendTo(l_ret, \"}\", sizeof(\"}\") - 1);" << endl;
      cout << getTab() << "if (l_ret == NULL)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "errlog(\"appendTo failed\");" << endl;
      cout << getTab() << getTab() << "goto bye;" << endl;
      cout << getTab() << "}" << endl;

      cout << endl;
      cout << getTab() << "bye:;" << endl;
      cout << getTab() << "return l_ret;" << endl;
      cout << "}" << endl;
      cout << endl;
    }

    if (getClone() || (getParamConstructor() && !m_parameters.empty()))
    {
      cout << getName() << "* clone" << firstToUpper(getName()) << "(" << getName() << " *other)" << endl;
      cout << "{" << endl;
      cout << getTab() << getName() << " *l_ret = NULL;" << endl;
      cout << endl;
      cout << getTab() << "if (other == NULL)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "// errlog(\"NULL argument given\");" << endl;
      cout << getTab() << getTab() << "goto bye;" << endl;
      cout << getTab() << "}" << endl;
      cout << getTab() << "l_ret = malloc(sizeof(" << getName() << "));" << endl;
      cout << getTab() << "// memcpy(l_ret, other, sizeof(" << getName() << ");" << endl;
      cout << getTab() << "if (l_ret == NULL)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "errlog(\"malloc failed\");" << endl;
      cout << getTab() << getTab() << "goto bye;" << endl;
      cout << getTab() << "}" << endl;
      cout << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        if (isBasicType(it->first))
        {
          cout << getTab() << "l_ret->" << firstToLower(it->second) << " = other->" << firstToLower(it->second) << ";" << endl;
        }
        else if (isCString(it->first))
        {
          cout << getTab() << "l_ret->" << firstToLower(it->second) << " = strdup(other->" << firstToLower(it->second) << ");" << endl;
        }
        else
        {
          cout << getTab() << "l_ret->" << firstToLower(it->second) << " = clone" << firstToUpper(it->first) << "(other->" << firstToLower(it->second) << ");" << endl;
        }
      }

      cout << endl;
      cout << getTab() << "bye:;" << endl;
      cout << getTab() << "return l_ret;" << endl;
      cout << "}" << endl;
      cout << endl;
    }
  }
}
