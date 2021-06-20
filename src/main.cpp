#include "ABaseObject.h"
#include <iostream>
#include <getopt.h>
#include <cstring>
using namespace std;

bool strToBool(const char * str)
{
  return
    !strcasecmp("true", str) ||
    !strcasecmp("t", str) ||
    !strcasecmp("1", str) ||
    !strcasecmp("y", str) ||
    !strcasecmp("yes", str) ||
    false;
}

int main(int argc, char *argv[])
{
  ABaseObject base;
  const char * language = NULL;
  const char *ptr;
  int r;
  struct option long_options[] =
  {
    {"help",        no_argument,       NULL, 'h'},
    {"language",    required_argument, NULL, 'l'},
    {"object-name", required_argument, NULL, 'n'},
    {"namespace",   required_argument, NULL, 'N'},
    {"tabulation",  required_argument, NULL, 't'},
    {"constructor", required_argument, NULL, 'C'},
    {"paramCstr",   required_argument, NULL, 'P'},
    {"toString",    required_argument, NULL, 'S'},
    {"clonable",    required_argument, NULL, 'c'},
    {"equals",      required_argument, NULL, 'e'},
    {"getters",     required_argument, NULL, 'g'},
    {"setters",     required_argument, NULL, 's'},
    {NULL,          0,                 NULL, '\0'}
  };

  // setting default value
  base.setName("obj");
  base.setNameSpace("mynamespace");
  base.setTab("\t");
  base.setEquals(true);
  base.setTostring(true);
  base.setConstructor(true);
  base.setClone(true);
  base.setParamConstructor(true);
  base.setGetters(true);
  base.setSetters(true);

  while ((r = getopt_long(argc, argv, "hl:n:N:t:C:P:S:c:e:g:s:", long_options, NULL)) > 0)
  {
    switch (r)
    {
      case 'h':
        cout << "usage " << argv[0] << " <-l LANGUAGE> [options] parm:type parm:type ..." << endl;
        cout << "Generate an object in the specified language with parameters" << endl;
        cout << "Language is one of c, cpp, cs, java, php, text, xml" << endl;
        cout << "--language    | -l <...>        target programming language" << endl;
        cout << "--object-name | -n <...>        the object name" << endl;
        cout << "--namespace   | -N <...>        the namesapce" << endl;
        cout << "--tabulation  | -t <...>        the tabulation string to use" << endl;
        cout << "--constructor | -C <true|false> Generate object constructor" << endl;
        cout << "--paramCstr   | -P <true|false> Generate a parametrize constructor" << endl;
        cout << "--toString    | -S <true|false> Generate toString method" << endl;
        cout << "--clonable    | -c <true|false> Generate a clonable method" << endl;
        cout << "--equals      | -e <true|false> Generate a equals method" << endl;
        cout << "--getters     | -g <true|false> Generate getters" << endl;
        cout << "--setters     | -s <true|false> Generate setters" << endl;
        return 0;
        break;
      case 'l':
        language = optarg;
        break;
      case 'n':
        base.setName(optarg);
        break;
      case 'N':
        base.setNameSpace(optarg);
        break;
      case 't':
        base.setTab(optarg);
        break;
      case 'C':
        base.setConstructor(strToBool(optarg));
        break;
      case 'P':
        base.setParamConstructor(strToBool(optarg));
        break;
      case 'S':
        base.setTostring(strToBool(optarg));
        break;
      case 'c':
        base.setClone(strToBool(optarg));
        break;
      case 'e':
        base.setEquals(strToBool(optarg));
        break;
      case 'g':
        base.setGetters(strToBool(optarg));
        break;
      case 's':
        base.setSetters(strToBool(optarg));
        break;
      default:
        cerr << "Warning : unrecognized option '" << optarg << "' ignoring." << endl;
        break;
    }
  }

  // Parse the parameters
  for (r = optind; r < argc; r++)
  {
    ptr = strchr(argv[r], ':');
    if (ptr != NULL)
    {
      base.addParameter
      (
          string(ptr + 1, 0, string::npos),
          string(argv[r], 0, ptr - argv[r])
      );
    }
    else
    {
      base.addParameter
      (
          string(""),
          string(argv[r], 0, ptr - argv[r])
      );
    }
  }

  if (language == NULL)
  {
    cerr << "No language defined" << endl;
    return 1;
  }
  else if (!strcasecmp("c", language))
    base.generate_c();
  else if (!strcasecmp("cpp", language) || !strcasecmp("c++", language))
    base.generate_cpp();
  else if (!strcasecmp("c#", language) || !strcasecmp("cs", language))
    base.generate_cs();
  else if (!strcasecmp("java", language))
    base.generate_java();
  else if (!strcasecmp("php", language))
    base.generate_php();
  else if (!strcasecmp("text", language) || !strcasecmp("txt", language))
    base.generate_txt();
  else if (!strcasecmp("xml", language))
    base.generate_xml();
  else
  {
    cerr << "Invalid language: '" << language << "'" << endl;
    return 1;
  }

  return 0;
}
