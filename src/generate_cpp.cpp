#include "ABaseObject.h"
#include "util.h"
#include <iostream>
using namespace std;

void ABaseObject::generate_cpp() const
{
  list<pair<string, string> >::const_iterator it;

  cout << "// ========== header ==========" << endl;
  cout << "#ifndef " << strToUpper(getName()) << "_H" << endl;
  cout << "#define " << strToUpper(getName()) << "_H" << endl;
  if (getTostring())
  {
    cout << "#include <string>" << endl;
  }
  cout << endl;
  cout << "namespace " << getNameSpace() << endl;
  cout << "{" << endl;
  cout << getTab() << "class " << getName() << endl;
  cout << getTab() << "{" << endl;
  cout << getTab() << getTab() <<  "public:" << endl;
  if (getConstructor())
  {
    cout << getTab() << getTab() << getTab() << getName() << "();" << endl;
  }
  if (getParamConstructor() && !m_parameters.empty())
  {
    cout << getTab() << getTab() << getTab() << getName() << endl;
    cout << getTab() << getTab() << getTab() << "(" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << getTab() << getTab() << it->first << " " << it->second;
      if (it != --m_parameters.end()) cout << "," << endl;
      else cout << endl;
    }
    cout << getTab() << getTab() << getTab() << ");" << endl;
  }
  if (getConstructor())
  {
    cout << getTab() << getTab() << getTab() << getName() << "(const " << getName() << "&);" << endl;
    cout << getTab() << getTab() << getTab() << "virtual ~" << getName() << "();" << endl;
    cout << endl;
  }

  if (getEquals())
  {
    cout << getTab() << getTab() << getTab() << "bool operator==(const " << getName() << "&) const;" << endl;
  }

  if (getClone())
  {
    cout << getTab() << getTab() << getTab() << "const " << getName() << "& operator=(const " << getName() << "&);" << endl;
  }

  if (getTostring())
  {
    cout << getTab() << getTab() << getTab() << "std::string toString() const;" << endl;
  }

  if (getSetters() || getGetters())
  {
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (getGetters())
      {
        cout << getTab() << getTab() << getTab() << it->first << " get" << firstToUpper(it->second) << "() const;" << endl;
      }
      if (getSetters())
      {
        cout << getTab() << getTab() << getTab() << "void set" << firstToUpper(it->second) << "(" << it->first << " val);" << endl;
      }
    }
  }

  cout << endl;
  cout << getTab() << getTab() << "private:" << endl;
  for (it = m_parameters.begin(); it != m_parameters.end(); it++)
  {
    cout << getTab() << getTab() << getTab() << it->first << " m_" << firstToLower(it->second) << ";" << endl;
  }

  cout << getTab() << "};" << endl;
  cout << "}" << endl;
  cout << endl;
  cout << "#endif // " << strToUpper(getName()) << "_H" << endl;
  cout << "// ========== body ==========" << endl;
  cout << "// #include \"" << firstToLower(getName()) << ".h\"" << endl;
  if (getTostring() || getEquals())
  {
    cout << "#include <string>" << endl;
  }
  cout << "using namespace " << getNameSpace() << ";" << endl;
  cout << "// using namespace std;" << endl;
  cout << endl;
  if (getConstructor())
  {
    cout << getName() << "::" << getName() << "()" << endl;
    cout << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (isBoolean(it->first))
         cout << getTab() << "m_" << firstToLower(it->second) << " = false;" << endl;
      else if (isBasicType(it->first))
         cout << getTab() << "m_" << firstToLower(it->second) << " = 0;" << endl;
      else if (isCString(it->first))
        cout << getTab() << "m_" << firstToLower(it->second) << " = NULL;" << endl;
      else
        cout << getTab() << "// m_" << firstToLower(it->second) << " = ?;" << endl;
    }
    cout << "}" << endl;
    cout << endl;
  }
  if (getParamConstructor() && !m_parameters.empty())
  {
    cout << getName() << "::" << getName() << endl;
    cout << "(" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << it->first << " " << firstToLower(it->second);
      if (it != --m_parameters.end())
        cout << ',' << endl;
      else
        cout << endl;
    }
    cout << ")" << endl;
    cout << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << "m_" << firstToLower(it->second) << " = " << firstToLower(it->second) << ";" << endl;
    }
    cout << "}" << endl;
    cout << endl;
  }
  if (getConstructor())
  {
    cout << getName() << "::" << getName() << "(const " << getName() << " &other)" << endl;
    cout << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << "m_" << firstToLower(it->second) << " = other." << "m_" << firstToLower(it->second) << ";" << endl;
    }
    cout << "}" << endl;
    cout << endl;

    cout << getName() << "::~" << getName() << "()" << endl;
    cout << "{ }" << endl;
    cout << endl;
  }

  if (getEquals())
  {
    cout << "bool " << getName() << "::" << "operator==(const " << getName() << " &other) const" << endl;
    cout << "{" << endl;
    cout << getTab() << "bool l_ret = true;" << endl;
    cout << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (isCString(it->first))
        cout << getTab() << "l_ret &= std::string(m_" << firstToLower(it->second) << ") == std::string(other.m_" << firstToLower(it->second) << ");" << endl;
      else
        cout << getTab() << "l_ret &= m_" << firstToLower(it->second) << " == other." << "m_" << firstToLower(it->second) << ";" << endl;
    }
    cout << endl;
    cout << getTab() << "return l_ret;" << endl;
    cout << "}" << endl;
    cout << endl;
  }

  if (getClone())
  {
    cout << "const " << getName() << "& " << getName() << "::" << "operator=(const " << getName() << " &other)" << endl;
    cout << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << "m_" << firstToLower(it->second) << " = other." << "m_" << firstToLower(it->second) << ";" << endl;
    }
    cout << endl;
    cout << getTab() << "return *this;" << endl;
    cout << "}" << endl;
    cout << endl;
  }

  if (getTostring())
  {
    cout << "std::string " << getName() << "::" << "toString() const" << endl;
    cout << "{" << endl;
    cout << getTab() << "std::string l_ret(\"" << getName() << ": {\");" << endl;
    cout << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << "l_ret += \"" << it->second << ":\\\"\";" << endl;
      cout << getTab() << "l_ret += " << "m_" << firstToLower(it->second) << ";" << endl;
      cout << getTab() << "l_ret += " << "\"\\\", \";" << endl;
      cout << endl;
    }
    cout << getTab() << "l_ret += \"}\";" << endl;
    cout << endl;
    cout << getTab() << "return l_ret;" << endl;
    cout << "}" << endl;
    cout << endl;
  }

  if (getSetters() || getGetters())
  {
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (getGetters())
      {
        cout << it->first << " " << getName() << "::get" << firstToUpper(it->second) << "() const" << endl;
        cout << "{" << endl;
        cout << getTab() << "return m_" << firstToLower(it->second) << ";" << endl;
        cout << "}" << endl;
        cout << endl;
      }
      if (getSetters())
      {
        cout << "void " << getName() << "::set" << firstToUpper(it->second) << "(" << it->first << " val)" << endl;
        cout << "{" << endl;
        cout << getTab() << "m_" << firstToLower(it->second) << " = val;" << endl;
        cout << "}" << endl;
        cout << endl;
      }
    }
  }
}
