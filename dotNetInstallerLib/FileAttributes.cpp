#include "StdAfx.h"
#include "FileAttributes.h"
#include "InstallerLog.h"

FileAttributes::FileAttributes()
{

}

FileAttributes::~FileAttributes()
{
}

void FileAttributes::Load(tinyxml2::XMLElement * node)
{
    CHECK_BOOL(node != NULL,
        L"Expected 'fileattributes' node");

    CHECK_BOOL(0 == strcmp(node->Value(), "fileattributes"),
        L"Expected 'fileattributes' node, got '" << DVLib::string2wstring(node->Value()) << L"'");

    for (tinyxml2::XMLNode* child = node->FirstChildElement(); child; child = child->NextSibling())
    {
        tinyxml2::XMLElement * child_element = child->ToElement();

        if (child_element == NULL)
            continue;

        if (strcmp(child_element->Value(), "fileattribute") == 0)
        {
            FileAttributePtr fileattribute(new FileAttribute());
            fileattribute->Load(child_element);
            (* this)[fileattribute->name] = fileattribute;
        }
        else
        {
            THROW_EX(L"Unexpected node '" << child_element->Value() << L"'");
        }
    }

    LOG(L"Read " << size() << L" file attribute(s)");
}

FileAttributePtr& FileAttributes::operator[](const std::wstring& name)
{ 
    return FileAttributeMap::operator[](name); 
}