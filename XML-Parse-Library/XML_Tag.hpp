#ifndef XML_TAG_HPP_
#define XML_TAG_HPP_

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "XML_BaseElement.hpp"

class XML_Tag : public XML_BaseElement
{
public:
	XML_Tag() = default;
	XML_Tag(const std::string & tagName);
	XML_Tag(const XML_Tag & tag);

	virtual XML_ElementType getElementType() const override;

	virtual void appendChild(const XML_BaseElement & element);
	virtual void appendChild(XML_BaseElement && element);
	virtual void appendChild(const std::unique_ptr<XML_BaseElement> & element);
	virtual void appendChild(std::unique_ptr<XML_BaseElement> && element);

	//bool removeChild(const XML_Tag & element);
	//bool removeChild(const XML_Tag * const elementPtr);

	virtual unsigned getChildrenCount() const;

	virtual void setAttribute(const std::string & attributeName, const std::string & value);
	virtual bool deleteAttribute(const std::string & attributeName);
	virtual std::string getAttributeValue(const std::string & attributeName) const;
	virtual bool hasAttribute(const std::string & attributeName) const;

	virtual void setTagName(const std::string & tagName);
	virtual std::string getTagName() const;
	virtual bool hasTagName() const;


	virtual void setValue(const std::string & value);

	virtual std::string getValueInOneLine() const override;
	virtual std::list<std::string> getValueInLines() const override;

	virtual std::string getElementWithValueInOneLine() const override;
	virtual std::list<std::string> getElementWithValueInLines() const override;

protected:
	virtual std::string getClassName() const override;
	virtual std::unique_ptr<XML_BaseElement> makeCopy() const override;
	virtual std::unique_ptr<XML_BaseElement> makeMovedCopy() override;

private:
	std::string getStartTag() const;
	std::string getEndTag() const;
	std::string getTagWithNoElements() const;

	std::string getAttibutesAsString() const;

private:
	std::string mTagName;
	std::map<std::string, std::string> mAttributes;  // <attributeName, attributeValue>

	std::vector<std::unique_ptr<XML_BaseElement> > mChildren;
};

#endif // XML_TAG_HPP_