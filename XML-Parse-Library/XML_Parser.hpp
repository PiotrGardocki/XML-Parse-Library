#ifndef XML_PARSER_HPP_
#define XML_PARSER_HPP_

#include <string>
#include <iostream>
#include <vector>
#include "XML_Document.hpp"
#include "XML_Tag.hpp"

class XML_Parser
{
public:

	bool parseFromFile(const std::string & fileName);
	void parseFromStream(std::istream & stream);

	XML_Document & getXMLDocument();
	const XML_Document & getXMLDocument() const;

	unsigned getErrorsCount() const;
	std::vector<std::string> & getParseErrors();
	const std::vector<std::string> & getParseErrors() const;

private:
	enum PartType
	{
		notParsed,
		comment,
		cdata,
		value,
		startTag,
		endTag,
		xmlDeclaration
	};
	struct ParsedPart
	{
		std::string part;
		PartType partType;
	};

	std::vector<ParsedPart> separateComments(const std::string & stream);
	std::vector<ParsedPart> separateCDATA(std::vector<ParsedPart> & parsedParts);
	std::vector<ParsedPart> divideRest(std::vector<ParsedPart> & parsedParts);

	void checkForXMLDeclaration(std::vector<ParsedPart> & parsedParts);
	
	//XML_Tag parseAsTag(std::istream & stream);

	/*std::string parseAsXMLDeclaration(std::istream & stream);
	std::string parseAsValue(std::istream & stream);
	std::string parseAsComment(std::istream & stream);
	std::string parseAsCDATA(std::istream & stream);*/

private:
	XML_Document mDocument;
	std::vector<std::string> mParseErrors;
};

#endif // XML_PARSER_HPP_