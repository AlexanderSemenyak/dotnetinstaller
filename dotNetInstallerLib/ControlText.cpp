#include "StdAfx.h"
#include "XmlAttribute.h"
#include "ControlText.h"
#include "InstallerSession.h"
#include "InstallerLog.h"

ControlText::ControlText(control_type type)
: Control(type),
font_size(0)
{

}

void ControlText::Load(tinyxml2::XMLElement * node)
{
    text = node->Attribute("text");
    font_name = node->Attribute("font_name");
    font_size = XmlAttribute(node->Attribute("font_size")).GetLongValue();
    Control::Load(node);
}

std::wstring ControlText::GetString() const
{
    std::wstringstream ss;
    ss << L"text='" << text << L"', font=" << font_name << L" (" << font_size << L" pt.), " << Control::GetString(); 
    return ss.str();
}
