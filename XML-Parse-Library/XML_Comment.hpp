#ifndef XML_COMMENT_HPP_
#define XML_COMMENT_HPP_

#include <string>
#include "XML_BaseElement.hpp"

class XML_Comment : public XML_BaseElement
{
public:
	XML_Comment() = default;
	explicit XML_Comment(const std::string & value);

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

#endif // XML_COMMENT_HPP_