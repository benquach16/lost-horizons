#include "windows.h"
#include "config.h"
#include "lib/ini_io.h"
Config gConfig;


Config::Config()
{
}

Config::~Config()
{
}

void Config::Load(const char *iniFileName)
{
	iniFilename_ = iniFileName;
	bSaveSettings = true;

	IniFile iniFile;
	if (!iniFile.Load(iniFileName)) {
	}

	HDC dc = GetDC(NULL);
	iBits = GetDeviceCaps(dc, BITSPIXEL);
	ReleaseDC(NULL, dc);

	IniFile::Section *general = iniFile.GetOrCreateSection("General");

	general->Get("FirstRun", &bFirstRun, true);
	general->Get("AutoLoadLast", &bAutoLoadLast, false);
	general->Get("ConfirmOnQuit", &bConfirmOnQuit, false);
	general->Get("WindowPositionX", &iWindowX, 40);
	general->Get("WindowPositionY", &iWindowY, 20);
	general->Get("TopMost", &bTopMost, false);

	IniFile::Section *graphics = iniFile.GetOrCreateSection("Graphics");

	graphics->Get("ShowFPSCounter", &bShowFPSCounter, false);
	graphics->Get("ResolutionX", &iResolutionX, 1024);
	graphics->Get("ResolutionY", &iResolutionY, 768);
	graphics->Get("FullScreen", &bFullScreen, false);
//	graphics->Get("Vsync", &bVsync, false);
//	graphics->Get("Shaders", &bShaders, true);

	IniFile::Section *sound = iniFile.GetOrCreateSection("Sound");

	sound->Get("Music", &iMusic, 100);
	sound->Get("SFX", &iSFX, 100);
}

void Config::Save()
{
	if (iniFilename_.size() && gConfig.bSaveSettings) {
		IniFile iniFile;
		if (!iniFile.Load(iniFilename_.c_str())) {
		}
		
		IniFile::Section *general = iniFile.GetOrCreateSection("General");
		
		// Next time won't be the first run
		bFirstRun = false;
		general->Set("FirstRun", bFirstRun);

		general->Set("AutoLoadLast", bAutoLoadLast);
		general->Set("ConfirmOnQuit", bConfirmOnQuit);
		general->Set("WindowPositionX", iWindowX);
		general->Set("WindowPositionY", iWindowY);
		general->Set("TopMost", bTopMost);

		IniFile::Section *graphics = iniFile.GetOrCreateSection("Graphics");

		graphics->Set("ShowFPSCounter", bShowFPSCounter);
		graphics->Set("ResolutionX", iResolutionX);
		graphics->Set("ResolutionY", iResolutionY);
		graphics->Set("FullScreen", bFullScreen);
//		graphics->Set("Vsync", bVsync);
//		graphics->Set("Shaders", bShaders);

		IniFile::Section *sound = iniFile.GetOrCreateSection("Sound");

		sound->Set("Music", iMusic);
		sound->Set("SFX", iSFX);
		
		if (!iniFile.Save(iniFilename_.c_str())) {
			return;
		}
		// config saved
	} else {
		// not saving config
	}
}
