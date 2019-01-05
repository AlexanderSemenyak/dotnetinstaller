#include "StdAfx.h"
#include "XmlAttribute.h"
#include "ControlLabel.h"
#include "InstallerSession.h"
#include "InstallerLog.h"

ControlLabel::ControlLabel()
: ControlText(control_type_label)
{

}

void ControlLabel::Load(tinyxml2::XMLElement * node)
{
    ControlText::Load(node);
}

std::wstring ControlLabel::GetString() const
{
    std::wstringstream ss;
    ss << L"'label' control, " << ControlText::GetString();
    return ss.str();
}
