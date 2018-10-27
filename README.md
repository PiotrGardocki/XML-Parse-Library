# XML-Parse-Library
XML-Parse-Library will be a convenient way to handle XML files in C++. It will support reading files, modifying them, and creating new ones.
For now, library supports only creating XML files.

## Supported features
### Classes
- XML_Tag
  - adding/getting children elements
  - handling tag's attributes
  - handling tag's name
- XML_Comment
- XML_CDATA
- XML_Value (normal text)
- XML_Document for saving XML structure into the file

## Planned features
- Add handling XML tag's children (removing, getting, other operations)
- Create documentation for library
- Add XML_Parser class for reading XML files and parsing them
- Add namespace for whole library and change classes' names