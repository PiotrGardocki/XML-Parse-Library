#ifndef XML_CDATA_HPP_
#define XML_CDATA_HPP_

#include <string>
#include "XML_BaseElement.hpp"

class XML_CDATA : public XML_BaseElement
{
public:
	XML_CDATA() = default;
	XML_CDATA(const std::string & value);

	virtual XML_ElementType getElementType() const override;

	virtual void setValue(const std::string & value) override;

	virtual std::string getValueInOneLine() const override;
	virtual std::list<std::string> getValueInLines() const override;

	virtual std::string getElementWithValueInOneLine() const override;
	virtual std::list<std::string> getElementWithValueInLines() const override;

protected:
	virtual std::string getClassName() const override;
	virtual std::unique_ptr<XML_BaseElement> makeCopy() const override;
	virtual std::unique_ptr<XML_BaseElement> makeMovedCopy() override;

private:
	std::string mValue;
};

#endif // XML_CDATA_HPP_