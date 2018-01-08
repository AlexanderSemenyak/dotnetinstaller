#include "StdAfx.h"
#include "XmlAttribute.h"
#include "EmbedFolder.h"
#include "InstallConfiguration.h"
#include "InstallerLog.h"
#include "InstallerSession.h"

EmbedFolder::EmbedFolder()
{

}

void EmbedFolder::Load(tinyxml2::XMLElement * node)
{
    CHECK_BOOL(node != NULL,
        L"Expected 'embedfolder' node");

    CHECK_BOOL(0 == strcmp(node->Value(), "embedfolder"),
        L"Expected 'embedfolder' node, got '" << DVLib::string2wstring(node->Value()) << L"'");

    sourcefolderpath = node->Attribute("sourcefolderpath");
    targetfolderpath = node->Attribute("targetfolderpath");

    LOG(L"Read 'embedfolder', source=" << sourcefolderpath
        << L", target=" << targetfolderpath);
}
