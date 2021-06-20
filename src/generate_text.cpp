#include "ABaseObject.h"
#include "util.h"
#include <iostream>
using namespace std;

void ABaseObject::generate_txt() const
{
  list<pair<string, string> >::const_iterator it;

  cout << "# " << getNameSpace() << "." << getName() << endl;
  for (it = m_parameters.begin(); it != m_parameters.end(); it++)
  {
    cout << it->second << ":" << it->first << endl;;
  }
}
