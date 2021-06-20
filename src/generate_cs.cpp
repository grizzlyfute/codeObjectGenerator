#include "ABaseObject.h"
#include "util.h"
#include <iostream>
using namespace std;

void ABaseObject::generate_cs() const
{
  list<pair<string, string> >::const_iterator it;

  cout << "using System;" << endl;
  cout << endl;

  cout << "namespace " << getNameSpace() << endl;
  cout << "{" << endl;
  cout << getTab() << "public class " << getName();
  if (getEquals() || getClone())
  {
    cout << " : ";
    if (getEquals())
    {
      cout << "IEquatable<" << getName() << '>';
      if (getClone())
      {
        cout << ", ";
      }
    }
    if (getClone())
    {
      cout << "ICloneable";
    }
  }
  cout << endl;
  cout << getTab() << "{" << endl;

  for (it = m_parameters.begin(); it != m_parameters.end(); it++)
  {
    if (getGetters() || getSetters())
    {
      cout << getTab() << getTab() << "private " << it->first << " m_" << firstToLower(it->second) << " = ";
      if (isBoolean(it->first))
        cout << "false;" << endl;
      else if (isBasicType(it->first))
        cout << "0;" << endl;
      else
        cout << "null;" << endl;

      cout << getTab() << getTab() << "public " << it->first << " " << firstToUpper(it->second) << endl;
      cout << getTab() << getTab() << "{" << endl;
      if (!getGetters())
        cout << getTab() << getTab() << getTab() << "get { return m_" << firstToLower(it->second) << "; }" << endl;
      else
        cout << getTab() << getTab() << getTab() << "get { return m_" << firstToLower(it->second) << "; }" << endl;
      if (!getSetters())
        cout << getTab() << getTab() << getTab() << "internal set { m_" << firstToLower(it->second) << " = value; }" << endl;
      else
        cout << getTab() << getTab() << getTab() << "internal set { m_" <<  firstToLower(it->second) << " = value; }" << endl;
      cout << getTab() << getTab() << "}" << endl;
      cout << endl;
    }
    else
    {
      cout << getTab() << getTab() << "public " << it->first << " " << firstToUpper(it->second) << " { get; internal set; }" << endl;
    }
  }
  cout << endl;

  if (getConstructor())
  {
    cout << getTab() << getTab() << "public " << getName() << "()" << endl;
    cout << getTab() << getTab() << "{ }" << endl;
    cout << endl;
  }

  if (getParamConstructor() && !m_parameters.empty())
  {
    cout << getTab() << getTab() << "public " << getName() << endl;
    cout << getTab() << getTab() << "(" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << getTab() << it->first << " " << firstToLower(it->second);
      if (it != --m_parameters.end())
        cout << "," << endl;
      else
        cout << endl;
    }
    cout << getTab() << getTab() << ")" << endl;
    cout << getTab() << getTab() << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << getTab() << firstToUpper(it->second) << " = " <<  firstToLower(it->second) << ";" << endl;
    }
    cout << getTab() << getTab() << "}" << endl;
    cout << endl;
  }

  if (getEquals())
  {
    cout << getTab() << getTab() << "public bool Equals(" << getName() << " other)" << endl;
    cout << getTab() << getTab() << "{" << endl;
    cout << getTab() << getTab() << getTab() << "bool l_ret = true;" << endl;
    cout << endl;
    cout << getTab() << getTab() << getTab() << "if (other == null || other.GetType() != typeof(" << getName() << "))" << endl;
    cout << getTab() << getTab() << getTab() << "{" << endl;
    cout << getTab() << getTab() << getTab() << getTab() << "l_ret = false;" << endl;
    cout << getTab() << getTab() << getTab() << "}" << endl;
    cout << getTab() << getTab() << getTab() << "else if (other == this)" << endl;
    cout << getTab() << getTab() << getTab() << "{" << endl;
    cout << getTab() << getTab() << getTab() << getTab() << "l_ret = true;" << endl;
    cout << getTab() << getTab() << getTab() << "}" << endl;
    cout << getTab() << getTab() << getTab() << "else" << endl;
    cout << getTab() << getTab() << getTab() << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (isBasicType(it->first))
      {
        cout << getTab() << getTab() << getTab() << getTab() << "l_ret &= " << firstToUpper(it->second) << " == other." << firstToUpper(it->second) << ";" << endl;
      }
      else
      {
        cout << getTab() << getTab() << getTab() << getTab() << "if (" << firstToUpper(it->second) << " != null && other." << firstToUpper(it->second) << " != null)" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << getTab() << "l_ret &= " << firstToUpper(it->second) << ".Equals(other." << firstToUpper(it->second) << ");" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "}" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "else" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << getTab() << "l_ret &= " << firstToUpper(it->second) << " == other." << firstToUpper(it->second) << ";" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "}" << endl;
      }
    }
    cout << getTab() << getTab() << getTab() << "}" << endl;
    cout << endl;
    cout << getTab() << getTab() << getTab() << "return l_ret;" << endl;
    cout << getTab() << getTab() << "}" << endl;
    cout << endl;
  }

  if (getClone())
  {
    cout << getTab() << getTab() << "public object Clone()" << endl;
    cout << getTab() << getTab() << "{" << endl;
    if (getParamConstructor())
    {
      cout << getTab() << getTab() << getTab() << "return new " << getName() << endl;
      cout << getTab() << getTab() << getTab() << "(" << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        cout << getTab() << getTab() << getTab() << getTab() << firstToUpper(it->second);
        if (it != --m_parameters.end())
        {
          cout << ",";
        }
        cout << endl;
      }
      cout << getTab() << getTab() << getTab() << ");" << endl;
    }
    else
    {
      cout << getTab() << getTab() << getTab() << getName() << " l_ret = new " << getName() << "();" << endl;
      cout << endl;
      for (it = m_parameters.begin(); it != m_parameters.end(); it++)
      {
        cout << getTab() << getTab() << getTab() << "l_ret." << firstToUpper(it->second) << " = " << firstToUpper(it->second) << ");" << endl;
      }
      cout << endl;
      cout << getTab() << getTab() << getTab() << "return l_ret;" << endl;
    }

    cout << getTab() << getTab() << "}" << endl;
    cout << endl;
  }

  if (getTostring())
  {
    cout << getTab() << getTab() << "public override string ToString()" << endl;
    cout << getTab() << getTab() << "{" << endl;
    cout << getTab() <<  getTab() << getTab() << "string l_ret = \"" << getName() << ": {\";" << endl;
    cout << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      if (isBasicType(it->first))
      {
        cout << getTab() << getTab() << getTab() << "l_ret += \"" << firstToLower(it->second) << ":\\\"\" + " << firstToUpper(it->second) << " + \"\\\", \";" << endl;
      }
      else
      {
        cout << getTab() << getTab() << getTab() << "if (" << firstToUpper(it->second) << " != null)" << endl;
        cout << getTab() << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "l_ret += \"" << firstToLower(it->second) << ":\\\"\" + " << firstToUpper(it->second) << ".ToString() + \"\\\", \";" << endl;
        cout << getTab() << getTab() << getTab() << "}" << endl;
        cout << getTab() << getTab() << getTab() << "else" << endl;
        cout << getTab() << getTab() << getTab() << "{" << endl;
        cout << getTab() << getTab() << getTab() << getTab() << "l_ret += \"" << firstToLower(it->second) << ": (null), \";" << endl;
        cout << getTab() << getTab() << getTab() << "}" << endl;
      }
    }
    cout << getTab() << getTab() << getTab() << "l_ret += \"}\";" << endl;
    cout << endl;
    cout << getTab() << getTab() << getTab() << "return l_ret;" << endl;
    cout << getTab() << getTab() << "}" << endl;
    cout << endl;
  }

  cout << getTab() << "}" << endl;
  cout << "}" << endl;
}
