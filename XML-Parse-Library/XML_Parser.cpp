#include <fstream>
#include <utility>
#include <cctype>
#include <map>
#include "XML_Parser.hpp"

bool XML_Parser::parseFromFile(const std::string & fileName)
{
	std::ifstream file(fileName);

	if (!file.is_open())
		return false;

	parseFromStream(file);
	return true;
}

size_t findFirstNotSpace(const std::string & str, size_t startPos = 0)
{
	for (; startPos < str.size(); ++startPos)
		if (!isspace(str[startPos]))
			return startPos;

	return std::string::npos;
}

size_t findLastNotSpace(const std::string & str, size_t endPos = std::string::npos)
{
	if (endPos >= str.size())
		endPos = str.size() - 1;

	for (; endPos >= 0; --endPos)
		if (!isspace(str[endPos]))
			return endPos;

	return std::string::npos;
}

std::string castStreamIntoString(std::istream & stream)
{
	std::string streamAsString;
	char ch;
	stream.get(ch);
	while (stream.good())
	{
		streamAsString += ch;
		stream.get(ch);
	}

	return streamAsString;
}

std::pair<std::string, std::string> getAttributeFromString();

std::map<std::string, std::string> getAttributesFromString(const std::string & str, size_t startPosition = 0, size_t endPosition = std::string::npos)
{
	std::map<std::string, std::string> attributes;   // name, value

	if (startPosition >= str.size())
		return attributes;
	if (endPosition > str.size())
		endPosition = str.size();

	while (startPosition < endPosition)
	{
		startPosition = findFirstNotSpace(str, startPosition);
		size_t endOfName = str.find('=', startPosition);

		std::string attributeName = str.substr(startPosition, endOfName - startPosition);

		++endOfName;

		size_t endOfValue = findLastNotSpace(str, endOfName);
		std::string attributeValue = str.substr(endOfName, endOfValue - endOfName);
	}
}

void XML_Parser::parseFromStream(std::istream & stream)
{
	auto streamAsString = castStreamIntoString(stream);
	auto parsedParts = separateComments(streamAsString);
	parsedParts = separateCDATA(parsedParts);
	parsedParts = divideRest(parsedParts);

	/*std::cout << parsedParts.size() << "\n";
	for (auto & part : parsedParts)
	{
		if (part.partType == comment)
			std::cout << "{comment{" << part.part << "}/comment}\n";
		else if (part.partType == cdata)
			std::cout << "{cdata{" << part.part << "}/cdata}\n";
		else if (part.partType == startTag)
			std::cout << "{start{" << part.part << "}/start}\n";
		else if (part.partType == endTag)
			std::cout << "{end{" << part.part << "}/end}\n";
		else if (part.partType == value)
			std::cout << "{value{" << part.part << "}/value}\n";
		else
			std::cout << "ERRORRORRRR";
	}*/
}

XML_Document & XML_Parser::getXMLDocument()
{
	return mDocument;
}

const XML_Document & XML_Parser::getXMLDocument() const
{
	return mDocument;
}

unsigned XML_Parser::getErrorsCount() const
{
	return mParseErrors.size();
}

std::vector<std::string>& XML_Parser::getParseErrors()
{
	return mParseErrors;
}

const std::vector<std::string>& XML_Parser::getParseErrors() const
{
	return mParseErrors;
}

std::vector<XML_Parser::ParsedPart> XML_Parser::separateComments(const std::string & stream)
{
	std::vector<ParsedPart> parts;

	size_t position = 0;
	while (position < stream.size())
	{
		auto startOfComment = stream.find("<!--", position);

		if (startOfComment == std::string::npos)
		{
			ParsedPart part;
			part.partType = PartType::notParsed;
			part.part = stream.substr(position);
			parts.push_back(std::move(part));
			break;
		}
		else
		{
			ParsedPart beforeComment;
			beforeComment.partType = PartType::notParsed;
			beforeComment.part = stream.substr(position, startOfComment - position);

			auto endOfComment = stream.find("-->", position);

			if (endOfComment == std::string::npos)
			{
				mParseErrors.push_back("not found end of comment");
				break;
			}

			ParsedPart comment;
			comment.partType = PartType::comment;
			comment.part = stream.substr(startOfComment + 4, endOfComment - startOfComment - 4);

			position = endOfComment + 3;

			parts.push_back(std::move(beforeComment));
			parts.push_back(std::move(comment));
		}
	}

	return parts;
}

std::vector<XML_Parser::ParsedPart> XML_Parser::separateCDATA(std::vector<ParsedPart> & parsedParts)
{
	std::vector<ParsedPart> parts;

	for (auto & part : parsedParts)
	{
		if (part.partType != PartType::notParsed)
			parts.push_back(std::move(part));
		else
		{
			size_t position = 0;
			while (position < part.part.size())
			{
				auto startOfCDATA = part.part.find("<![CDATA[", position);

				if (startOfCDATA == std::string::npos)
				{
					// to do: improve this code
					ParsedPart emptyPart;
					emptyPart.partType = PartType::notParsed;
					emptyPart.part = part.part.substr(position);

					parts.push_back(std::move(emptyPart));
					break;
				}
				else
				{
					ParsedPart beforeCDATA;
					beforeCDATA.partType = PartType::notParsed;
					beforeCDATA.part = part.part.substr(position, startOfCDATA - position);

					auto endOfCDATA = part.part.find("]]>", position);

					if (endOfCDATA == std::string::npos)
					{
						mParseErrors.push_back("not found end of CDATA");
						break;
					}

					ParsedPart CDATA;
					CDATA.partType = PartType::cdata;
					CDATA.part = part.part.substr(startOfCDATA + 9, endOfCDATA - startOfCDATA - 9);

					position = endOfCDATA + 3;

					parts.push_back(std::move(beforeCDATA));
					parts.push_back(std::move(CDATA));
				}
			}
		}
	}

	return parts;
}

std::vector<XML_Parser::ParsedPart> XML_Parser::divideRest(std::vector<ParsedPart> & parsedParts)
{
	std::vector<ParsedPart> parts;

	for (auto & part : parsedParts)
	{
		if (part.partType != PartType::notParsed)
		{
			parts.push_back(std::move(part));
			continue;
		}

		size_t position = 0;
		const std::string & str = part.part;
		while (position < str.size())
		{
			auto firstNotSpace = findFirstNotSpace(str, position);

			if (firstNotSpace == std::string::npos)
				break;

			if (str[firstNotSpace] == '<')
			{
				auto endOfTag = str.find('>', position);
				auto tagString = str.substr(firstNotSpace, endOfTag - firstNotSpace + 1);

				ParsedPart tag;
				if (str[findFirstNotSpace(str, firstNotSpace + 1)] == '/')
					tag.partType = PartType::endTag;
				else
					tag.partType = PartType::startTag;

				tag.part = std::move(tagString);

				position = endOfTag + 1;

				parts.push_back(std::move(tag));
			}
			else
			{
				auto startOfNextTag = str.find('<', position);

				ParsedPart value;
				value.partType = PartType::value;

				if (startOfNextTag == std::string::npos)
				{
					value.part = str.substr(firstNotSpace, findLastNotSpace(str) - firstNotSpace + 1);
					parts.push_back(std::move(value));
					break;
				}
				else//check this
					value.part = str.substr(position, findLastNotSpace(str, startOfNextTag - 1) - position + 1);

				parts.push_back(std::move(value));
				position = startOfNextTag;
			}
		}
	}

	return parts;
}

void XML_Parser::checkForXMLDeclaration(std::vector<ParsedPart> & parsedParts)
{
	auto iter = parsedParts.begin();

	for (; iter != parsedParts.end(); ++iter)
	{
		if (iter->partType == PartType::startTag)
		{
			if (iter->part.find("<?xml") == 0)
			{
				iter->partType = PartType::xmlDeclaration;

				break;
			}
		}
	}

	if (iter == parsedParts.end())
		mParseErrors.push_back("Missing xml declaration");
	else if (iter != parsedParts.begin())
		mParseErrors.push_back("Content before xml declaration");
}
