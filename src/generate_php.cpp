#include "ABaseObject.h"
#include "util.h"
#include <iostream>
using namespace std;

void ABaseObject::generate_php() const
{
  list<pair<string, string> >::const_iterator it;

  cout << "<?php" << endl;
  cout << "namespace " << getNameSpace() << ";" << endl;
  cout << endl;
  cout << "class " << getName() << endl;
  cout << "{" << endl;

  for (it = m_parameters.begin(); it != m_parameters.end(); it++)
  {
    cout << getTab() << "private $m_" << firstToLower(it->second) << " = ";
    if (isBoolean (it->first))
      cout << "false;" << endl;
    else if (isBasicType(it->first))
      cout << "0;" << endl;
    else
      cout << "null;" << endl;
    if (getGetters())
    {
      cout << getTab() << "public function get" << firstToUpper(it->second) << "(): " << it->first << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "return $this->m_" << firstToLower(it->second) << ";" << endl;
      cout << getTab() << "}" << endl;
    }
    if (getSetters())
    {
      cout << getTab() << "public function set" << firstToUpper(it->second) << "(" << it->first << " $val): " << getName() << endl;
      cout << getTab() << "{" << endl;
      cout << getTab() << getTab() << "$this->m_" << firstToLower(it->second) << " = $val;" << endl;
      cout << getTab() << getTab() << "return $this;" << endl;
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
    cout << getTab() << "public function __construct()" << endl;
    cout << getTab() << "{ }" << endl;
    cout << endl;

  }
  if (getParamConstructor() && !m_parameters.empty())
  {
    cout << getTab() << "public function __construct" << endl;
    cout << getTab() << "(" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << it->first << " $" << firstToLower(it->second);
      if (it != --m_parameters.end())
        cout << "," << endl;
      else
        cout << endl;
    }
    cout << getTab() << ")" << endl;
    cout << getTab() << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << "$this->m_" << firstToLower(it->second) << " = $" <<  firstToLower(it->second) << ";" << endl;
    }
    cout << getTab() << "}" << endl;
    cout << endl;
  }

  if (getConstructor() || (getParamConstructor() && !m_parameters.empty()))
  {
    cout << getTab() << "public function __destruct()" << endl;
    cout << getTab() << "{ }" << endl;
    cout << endl;
  }

  if (getEquals())
  {
    cout << getTab() << "// equals not applicable. use operator== or operator===" << endl;
    cout << endl;
  }

  if (getClone())
  {
    cout << getTab() << "public function __clone()" << endl;
    cout << getTab() << "{" << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << getTab() << "$this->m_" << firstToLower(it->second) << " = clone $this->m_" << firstToLower(it->second) << ";" << endl;
    }
    cout << getTab() << "}" << endl;
    cout << endl;
  }

  if (getTostring())
  {
    cout << getTab() << "public function __toString()" << endl;
    cout << getTab() << "{" << endl;
    cout << getTab() << getTab() << "$l_ret = '" << getName() << ": {';" << endl;
    cout << endl;
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << getTab() << "$l_ret .= $this->m_" << firstToLower(it->second) << " . ',';" << endl;
    }
    cout << getTab() << getTab() << "$l_ret .= '}';" << endl;
    cout << endl;
    cout << getTab() << getTab() << "return $l_ret;" << endl;
    cout << getTab() << "}" << endl;
    cout << endl;
  }

  cout << "}" << endl;
  cout << "?>" << endl;
}
