#ifndef XML_BASEELEMENT_HPP_
#define XML_BASEELEMENT_HPP_

#include <string>
#include <memory>
#include <list>
#include "XML_ElementType.hpp"

class XML_Tag;

class XML_BaseElement
{
	friend XML_Tag;
public:
	XML_BaseElement();
	virtual ~XML_BaseElement() = default;
	virtual XML_ElementType getElementType() const = 0;

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

	virtual void setValue(const std::string & value) = 0;
	
	virtual std::string getValueInOneLine() const = 0;
	virtual std::list<std::string> getValueInLines() const = 0;
	
	virtual std::string getElementWithValueInOneLine() const = 0;
	virtual std::list<std::string> getElementWithValueInLines() const = 0;

	XML_Tag * getParent();
	const XML_Tag * getParent() const;
	bool hasParent() const;

protected:
	virtual std::string getClassName() const = 0;
	virtual std::unique_ptr<XML_BaseElement> makeCopy() const = 0;
	virtual std::unique_ptr<XML_BaseElement> makeMovedCopy() = 0;

private:
	void setParent(XML_Tag * parent);

private:
	XML_Tag * mParent;
};

#endif // XML_BASEELEMENT_HPP_