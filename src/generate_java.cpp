#include "ABaseObject.h"
#include "util.h"
#include <iostream>
using namespace std;

void ABaseObject::generate_java() const
{
  list<pair<string, string> >::const_iterator it;

  cout << "package " << getNameSpace() << ";" << endl;
  cout << "import java.lang.*;" << endl;
  cout << "// import java.util.*;" << endl;
  cout << endl;

  cout << "public class " << getName() << endl;
  cout << "{" << endl;

  for (it = m_parameters.begin(); it != m_parameters.end(); it++)
  {
    cout << getTab() << "private " << it->first << " m_" << firstToLower(it->second) << " = ";
    if (isBoolean(it->first))
      cout << "false;" << endl;
    else if (isBasicType(it->first))
      cout << "0;" << endl;
    else
      cout << "null;" << endl;

    if (getGetters())
    {
      cout << getTab() << "public " << it->first << " get" << firstToUpper(it->second) << "()" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "return m_" << firstToLower(it->second) << ";" << endl;
      cout << getTab() << "}" << endl;
    }
    if (getSetters())
    {
      cout << getTab() << "public void set" << firstToUpper(it->second) << "(" << it->first << " val)" << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "m_" << firstToLower(it->second) << " = val;" << endl;
      cout << getTab() << "}" << endl;
    }
    if (getGetters() || getSetters())
    {
      cout << endl;
    }
  }
  if (!getGetters() && !getSetters())
  {
    cout << endl;
  }

  if (getConstructor())
  {
    cout << getTab() << "public " << getName() << "()" << endl;
    cout << getTab() << "{ }" << endl;
    cout << endl;
  }

  if (getParamConstructor() && !m_parameters.empty())
  {
    cout << getTab() << "public " << getName() << endl;
    cout << getTab() << "(" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << it->first << " " << firstToLower(it->second);
      if (it != --m_parameters.end())
        cout << "," << endl;
      else
        cout << endl;
    }
    cout << getTab() << ")" << endl;
    cout << getTab() << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << "m_" << firstToLower(it->second) << " = " <<  firstToLower(it->second) << ";" << endl;
    }
    cout << getTab() << "}" << endl;
    cout << endl;
  }

  if (getEquals())
  {
    cout << getTab() << "@Override" << endl;
    cout << getTab() << "public boolean equals(Object obj)" << endl;
    cout << getTab() << "{" << endl;
    cout << getTab() << getTab() << "boolean l_ret = true;" << endl;
    cout << endl;
    cout << getTab() << getTab() << "if (obj == null || !(obj instanceof " << getName() << "))" << endl;
    cout << getTab() << getTab() << "{" << endl;
    cout << getTab() << getTab() << getTab() << "l_ret = false;" << endl;
    cout << getTab() << getTab() << "}" << endl;
    cout << getTab() << getTab() << "else if (obj == this)" << endl;
    cout << getTab() << getTab() << "{" << endl;
    cout << getTab() << getTab() << getTab() << "l_ret = true;" << endl;
    cout << getTab() << getTab() << "}" << endl;
    cout << getTab() << getTab() << "else" << endl;
    cout << getTab() << getTab() << "{" << endl;
    cout << getTab() << getTab() << getTab() << getName() << " other = (" << getName() << ")obj;" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (isBasicType(it->first))
      {
        cout << getTab() << getTab() << getTab() << "l_ret &= m_" << firstToLower(it->second) << " == other.m_" << firstToLower(it->second) << ";" << endl;
      }
      else
      {
        cout << getTab() << getTab() << getTab() << "if (m_" << firstToLower(it->second) << " != null && other.m_" << firstToLower(it->second) << " != null)" << endl;
        cout << getTab() << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "l_ret &= m_" << firstToLower(it->second) << ".equals(other.m_" << firstToLower(it->second) << ");" << endl;
        cout << getTab() << getTab() << getTab() << "}" << endl;
        cout << getTab() << getTab() << getTab() << "else" << endl;
        cout << getTab() << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "l_ret &= m_" << firstToLower(it->second) << " == other.m_" << firstToLower(it->second) << ";" << endl;
        cout << getTab() << getTab() << getTab() << "}" << endl;
      }
    }
    cout << getTab() << getTab() << "}" << endl;
    cout << endl;
    cout << getTab() << getTab() << "return l_ret;" << endl;
    cout << getTab() << "}" << endl;
    cout << endl;

    cout << getTab() << "@Override" << endl;
    cout << getTab() << "public int hashCode()" << endl;
    cout << getTab() << "{" << endl;
    cout << getTab() << getTab() << "int l_ret = 0;" << endl;
    cout << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
	  if (isBoolean(it->first))
	  {
        cout << getTab() << getTab() << "l_ret += (m_" << firstToLower(it->second) << " ? 13 : -17);" << endl;
	  }
	  else if (isBasicType(it->first))
      {
		  if (it->first == "byte")
			  cout << getTab() << getTab() << "l_ret += Byte.valueOf(m_" << firstToLower(it->second) << ").hashCode();" << endl;
		  else if (it->first == "short")
			  cout << getTab() << getTab() << "l_ret += Short.valueOf(m_" << firstToLower(it->second) << ").hashCode();" << endl;
		  else if (it->first == "int")
			  cout << getTab() << getTab() << "l_ret += Integer.valueOf(m_" << firstToLower(it->second) << ").hashCode();" << endl;
		  else if (it->first == "long")
			  cout << getTab() << getTab() << "l_ret += Long.valueOf(m_" << firstToLower(it->second) << ").hashCode();" << endl;
		  else if (it->first == "float")
			  cout << getTab() << getTab() << "l_ret += Float.valueOf(m_" << firstToLower(it->second) << ").hashCode();" << endl;
		  else if (it->first == "double")
			  cout << getTab() << getTab() << "l_ret += Double.valueOf(m_" << firstToLower(it->second) << ").hashCode();" << endl;
		  else if (it->first == "boolean")
			  cout << getTab() << getTab() << "l_ret += Boolean.valueOf(m_" << firstToLower(it->second) << ").hashCode();" << endl;
		  else
			  cout << getTab() << getTab() << "l_ret += (int)m_" << firstToLower(it->second) << ";" << endl;
      }
      else
      {
        cout << getTab() << getTab() << "if (m_" << firstToLower(it->second) << " != null)" << endl;
        cout << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << "l_ret += m_" << firstToLower(it->second) << ".hashCode();" << endl;
        cout << getTab() << getTab() << "}" << endl;
      }
    }
    cout << endl;
    cout << getTab() << getTab() << "return l_ret;" << endl;
    cout << getTab() << "}" << endl;
    cout << endl;
  }

  if (getClone())
  {
    cout << getTab() << "@Override" << endl;
    cout << getTab() << "public Object clone()" << endl;
    if (!getParamConstructor() && !getSetters())
    {
      cout << getTab() << getTab() << "throws CloneNotSupportedException" << endl;
    }
    cout << getTab() << "{" << endl;
    if (getParamConstructor())
    {
      cout << getTab() << getTab() << "return new " << getName() << endl;
      cout << getTab() << getTab() << "(" << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        cout << getTab() << getTab() << getTab() << "m_" << firstToLower(it->second);
        if (it != --m_parameters.end())
        {
          cout << ",";
        }
        cout << endl;
      }
      cout << getTab() << getTab() << ");" << endl;
    }
    else if (getSetters())
    {
      cout << getTab() << getTab() << getName() << " l_ret = new " << getName() << "();" << endl;
      cout << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        cout << getTab() << getTab() << "l_ret.set" << firstToUpper(it->second) << "(" << "m_" << firstToLower(it->second) << ");" << endl;
      }
      cout << endl;
      cout << getTab() << getTab() << "return l_ret;" << endl;
    }
    else
    {
      cout << getTab() << getTab() << "throw new CloneNotSupportedException(\"generator found no way for implementing clone\");" << endl;
    }

    cout << getTab() << "}" << endl;
    cout << endl;
  }

  if (getTostring())
  {
    cout << getTab() << "@Override" << endl;
    cout << getTab() << "public String toString()" << endl;
    cout << getTab() << "{" << endl;
    cout << getTab() << getTab() << "String l_ret = \"" << getName() << ": {\";" << endl;
    cout << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (isBasicType(it->first))
      {
        cout << getTab() << getTab() << "l_ret += \"" << firstToLower(it->second) << ":\\\"\" + m_" << firstToLower(it->second) << " + \"\\\", \";" << endl;
      }
      else
      {
        cout << getTab() << getTab() << "if (m_" << firstToLower(it->second) << " != null)" << endl;
        cout << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << "l_ret += \"" << firstToLower(it->second) << ":\\\"\" + m_" << firstToLower(it->second) << ".toString() + \"\\\", \";" << endl;
        cout << getTab() << getTab() << "}" << endl;
        cout << getTab() << getTab() << "else" << endl;
        cout << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << "l_ret += \"" << firstToLower(it->second) << ": (null), \";" << endl;
        cout << getTab() << getTab() << "}" << endl;
      }
    }
    cout << getTab() << getTab() << "l_ret += \"}\";" << endl;
    cout << endl;
    cout << getTab() << getTab() << "return l_ret;" << endl;
    cout << getTab() << "}" << endl;
    cout << endl;
  }

  cout << "}" << endl;
}
