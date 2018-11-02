#include "Utilities.hpp"

std::string translateStringIntoXMLStyle(const std::string & str)
{
	std::string copy(str);
	
	replaceOccurencies(copy, "&" , "&amp;");
	replaceOccurencies(copy, "<" , "&lt;");
	replaceOccurencies(copy, ">" , "&gt;");
	replaceOccurencies(copy, "\"", "&quot;");
	replaceOccurencies(copy, "'" , "&apos;");

	return copy;
}

std::string translateStringFromXMLStyle(const std::string & str)
{
	std::string copy(str);

	replaceOccurencies(copy, "&apos;", "'");
	replaceOccurencies(copy, "&quot;", "\"");
	replaceOccurencies(copy, "&gt;"  , ">");
	replaceOccurencies(copy, "&lt;"  , "<");
	replaceOccurencies(copy, "&amp;" , "&");

	return copy;
}

void replaceOccurencies(std::string & str, const std::string & substringToFind, const std::string & substringToReplace)
{
	auto size = substringToFind.size();
	if (size == 0)
		return;

	auto pos = str.find(substringToFind);

	while (pos != std::string::npos)
	{
		str.replace(pos, size, substringToReplace);
		pos = str.find(substringToFind, pos+1);
	}
}
