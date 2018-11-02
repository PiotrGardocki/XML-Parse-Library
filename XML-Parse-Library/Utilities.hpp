#ifndef UTILITIES_HPP_
#define UTILITIES_HPP_

#include <string>

std::string translateStringIntoXMLStyle(const std::string & str);
std::string translateStringFromXMLStyle(const std::string & str);

void replaceOccurencies(std::string & str, const std::string & substringToFind, const std::string & substringToReplace);

#endif // UTILITIES_HPP_