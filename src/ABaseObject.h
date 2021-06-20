#ifndef ABASEOBJECT_H
#define ABASEOBJECT_H
#include <list>
#include <utility>
#include <string>

class ABaseObject
{
  public:
    ABaseObject();
    ABaseObject(const ABaseObject&);
    virtual ~ABaseObject();

    void addParameter(const std::string &type, const std::string &name);

    void setName(const std::string& val);
    const std::string& getName() const;
    void setNameSpace(const std::string& val);
    const std::string& getNameSpace() const;
    void setTab(const std::string& val);
    const std::string& getTab() const;

    void setEquals(bool val);
    bool getEquals() const;
    void setTostring(bool val);
    bool getTostring() const;
    void setConstructor(bool val);
    bool getConstructor() const;
    void setParamConstructor(bool val);
    bool getParamConstructor() const;
    void setGetters(bool val);
    bool getGetters() const;
    void setSetters(bool val);
    bool getSetters() const;
    void setClone(bool val);
    bool getClone() const;

    void generate_c() const;
    void generate_cpp() const;
    void generate_cs() const;
    void generate_java() const;
    void generate_php() const;
    void generate_python() const;
    void generate_sql() const;
    void generate_txt() const;
    void generate_xml() const;

  private:
    std::string m_name;
    std::string m_nameSpace;
    std::string m_tabspace;
    bool m_equals;
    bool m_tostring;
    bool m_constructors;
    bool m_paramconstructors;
    bool m_getters;
    bool m_setters;
    bool m_clone;

  protected:
    std::list<std::pair<std::string, std::string> > m_parameters;
};

#endif //ABASEOBJECT_H
