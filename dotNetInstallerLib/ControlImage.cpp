#include "StdAfx.h"
#include "XmlAttribute.h"
#include "ControlImage.h"
#include "InstallerSession.h"
#include "InstallerLog.h"

ControlImage::ControlImage()
: Control(control_type_image),
center(false)
{

}

void ControlImage::Load(tinyxml2::XMLElement * node)
{
    resource_id = node->Attribute("resource_id");
    image_file = node->Attribute("image_file");
    center = XmlAttribute(node->Attribute("center")).GetBoolValue(false);
    Control::Load(node);
}

std::wstring ControlImage::GetString() const
{
    std::wstringstream ss;
    ss << L"'image' control, " << Control::GetString();
    return ss.str();
}
