#include <iostream>
#include <exception>
#include <utility>
#include "XML-Parse-Library.hpp"

int main()
{
	using std::cout;
	using std::cin;

	XML_Document document;
	
	XML_Tag tag1("head");
	tag1.appendChild(XML_Tag("title"));
	tag1.setAttribute("id", "23");

	{
		XML_Tag css("link");
		css.setAttribute("rel", "stylesheet");
		css.setAttribute("href", "style.css");
		tag1.appendChild(std::move(css));
	}

	XML_Tag tag2("body");
	tag2.appendChild(XML_Value("text"));
	tag2.setAttribute("class", "typical");
	tag2.setAttribute("id", "1");

	{
		XML_CDATA someData;
		someData.setValue("Content not to be parsed");
		tag2.appendChild(std::move(someData));

		XML_Tag divTag("div");
		divTag.appendChild(XML_Comment("just a comment"));
		tag2.appendChild(std::move(divTag));
	}

	document.getRootElement().appendChild(std::move(tag1));
	document.getRootElement().appendChild(std::move(tag2));
	document.getRootElement().setTagName("html");

	document.saveToFile("test.xml");

	//cout << tag1.getTagName() << "\n" << tag1.getChildrenCount();
	//cin.get();

	return 0;
}