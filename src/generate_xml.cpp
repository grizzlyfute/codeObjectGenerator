#include "ABaseObject.h"
#include "util.h"
#include <iostream>
using namespace std;

void ABaseObject::generate_xml() const
{
  list<pair<string, string> >::const_iterator it;

  cout << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
  cout << "<" << getName() << ">" << endl;

  if (getParamConstructor())
  {
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << "<element type=\"" << it->first << "\" name=\"" << it->second << "\"/>" << endl;
    }
  }
  else
  {
    for (it = m_parameters.begin(); it != m_parameters.end(); it++)
    {
      cout << getTab() << "<" << it->first << ">" << endl;
      cout << getTab() << getTab() << "<" << it->second << "/>" << endl;
      cout << getTab() << "</" << it->first << ">" << endl;
    }
  }

  cout << "</" << getName() << ">" << endl;
}
