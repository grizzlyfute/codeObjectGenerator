#include "ABaseObject.h"
using namespace std;

ABaseObject::ABaseObject()
{
  m_equals = false;
  m_tostring = false;
  m_constructors = false;
  m_getters = false;
  m_setters = false;
  m_clone = false;
}

ABaseObject::ABaseObject(const ABaseObject& o)
{
  m_equals = o.m_equals;
  m_tostring = o.m_tostring;
  m_constructors = o.m_constructors;
  m_getters = o.m_getters;
  m_setters = o.m_setters;
  m_clone = o.m_clone;
}

ABaseObject::~ABaseObject()
{ }

void ABaseObject::addParameter(const string& type, const string& name)
{
  m_parameters.push_back (pair<string, string>(type, name));
}

void ABaseObject::setName(const string &val)
{
  m_name = val;
  if (val[0] >= 'a' && val[0] <= 'z')
    m_name[0] = m_name[0] - 'a' + 'A';
}

const string& ABaseObject::getName() const
{
  return m_name;
}

void ABaseObject::setNameSpace(const string &val)
{
  // Warning : pointer name should not be deleted...
  m_nameSpace = val;
}

const string& ABaseObject::getNameSpace() const
{
  return m_nameSpace;
}

void ABaseObject::setTab(const string &val)
{
  m_tabspace = val;
}

const string& ABaseObject::getTab() const
{
  return m_tabspace;
}

void ABaseObject::setEquals(bool val)
{
  m_equals = val;
}

bool ABaseObject::getEquals() const
{
  return m_equals;
}

void ABaseObject::setTostring(bool val)
{
  m_tostring = val;
}

bool ABaseObject::getTostring() const
{
  return m_tostring;
}

void ABaseObject::setConstructor(bool val)
{
  m_constructors = val;
}

bool ABaseObject::getConstructor() const
{
  return m_constructors;
}

void ABaseObject::setParamConstructor(bool val)
{
  m_paramconstructors = val;
}

bool ABaseObject::getParamConstructor() const
{
  return m_paramconstructors;
}

void ABaseObject::setGetters(bool val)
{
  m_getters = val;
}

bool ABaseObject::getGetters() const
{
  return m_getters;
}

void ABaseObject::setSetters(bool val)
{
  m_setters = val;
}

bool ABaseObject::getSetters() const
{
  return m_setters;
}

void ABaseObject::setClone(bool val)
{
  m_clone = val;
}

bool ABaseObject::getClone() const
{
  return m_clone;
}
