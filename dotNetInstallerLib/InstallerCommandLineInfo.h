#pragma once
#include "afxwin.h"

class InstallerCommandLineInfo :
	public CCommandLineInfo
{
public:
	static shared_any<InstallerCommandLineInfo *, close_delete> Instance;
	InstallerCommandLineInfo();
	void ParseParam(const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
    const std::wstring& GetCompleteCommandArgs() const { return m_completeCommandArgs; }
    bool ExtractCab() const { return m_extractCab; }
	bool DisplayCab() const { return m_displayCab; }
	bool DisplayHelp() const { return m_displayHelp; }
	bool DisplayConfig() const { return m_displayConfig; }
	bool Reboot() const { return m_reboot; }
	bool Autostart() const { return m_autostart; }
	bool NoReboot() const { return m_noreboot; }
	bool EnableRunOnReboot() const { return m_enableRunOnReboot; }
	bool DisplaySplash() const { return m_displaySplash; }
public:
	std::wstring configFile;
	std::wstring logFile;
    std::map<std::wstring, std::wstring> componentCmdArgs;
	std::map<std::wstring, std::wstring> controlCmdArgs;
	std::wstring GetUsage() const;
private:
	
	enum argFlags 
	{ 
		unknown, 		
		logfile,
		configfile,		
		launcher, 
		launcherArgs, 
		completeCommandArgs,		
		componentArgs,
		controlArgs,
	};
	
	// last arg flag
	argFlags m_lastArgFlag;
	// additional complete command
    std::wstring m_completeCommandArgs;
	// extract CAB contents
    bool m_extractCab;
	// display CAB contents
	bool m_displayCab;
	// show help
	bool m_displayHelp;
	// launched via registry Run after a reboot
	bool m_reboot;
	// enables writing the RunOnReboot registry key
	bool m_enableRunOnReboot;
	// launched via UAC so autostart
	bool m_autostart;
	// don't reboot even if reboot is required
	bool m_noreboot;
	// display configuration
	bool m_displayConfig;
	// show splash screen
	bool m_displaySplash;
};

