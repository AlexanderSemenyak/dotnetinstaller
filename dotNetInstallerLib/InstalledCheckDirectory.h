#pragma once
#include "InstalledCheck.h"

class InstalledCheckDirectory : public InstalledCheck
{
public:
	// full path to the directory to check
	std::wstring path;
public:
    InstalledCheckDirectory();
    void Load(tinyxml2::XMLElement * node);
	virtual bool IsInstalled() const;
};

typedef shared_any<InstalledCheckDirectory *, close_delete> InstalledCheckDirectoryPtr;
