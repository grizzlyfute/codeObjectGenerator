# ObjectGenerator
## General purpose
This software will generate container object in many language. This may be
usefull if you get an entity from database and want to convert in an explotaible
code.
It is able to generate equals, to string, getter, setter according to the given
type (may be an object or a standart type)

## Compilation
Simply do make

## Usage
usage bin/objectGenerator <-l LANGUAGE> [options] parm:type parm:type ...
Generate an object in the specified language with parameters
Language is one of c, cpp, cs, java, php, text, xml
--language    | -l <...>        target programming language
--object-name | -n <...>        the object name
--namespace   | -N <...>        the namesapce
--tabulation  | -t <...>        the tabulation string to use
--constructor | -C <true|false> Generate object constructor
--paramCstr   | -P <true|false> Generate a parametrize constructor
--toString    | -S <true|false> Generate toString method
--clonable    | -c <true|false> Generate a clonable method
--equals      | -e <true|false> Generate a equals method
--getters     | -g <true|false> Generate getters
--setters     | -s <true|false> Generate setters

##
Examples
	bin/objectGenerator \
		--language java \
		--object-name MyEntity \
		--namespace MyNameSpace \
		--tabulation "  " \
		--constructor true \
		--paramCstr true \
		--toString true \
		--clonable true \
		--equals true \
		--getters true \
		--setters true \
		intValue:int \
		doubleValue:double \
		stringValue:String \
		otherEntity:Entity
