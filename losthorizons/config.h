#ifndef _CONFIG_H_
#define _CONFIG_H_

// include this header file whenever you want to use the config

#include <string>


struct Config
{
	public:
		Config();
		~Config();

		// Whether to save the config on close.
		bool bSaveSettings;

		bool bFirstRun;

		// General
		bool bAutoLoadLast;
		bool bConfirmOnQuit;
		unsigned iWindowX;
		unsigned iWindowY;
		bool bTopMost;

		// Video
		unsigned iResolutionX;
		unsigned iResolutionY;
		unsigned iBits;
		bool bFullScreen;
		//bool bVsync;
		//bool bShaders;

		// Audio
		unsigned iMusic;
		unsigned iSFX;
		
		// UI
		bool bShowFPSCounter;
		bool bShowDebugStats;

		// functions
		void Load(const char *iniFileName = "config.ini");
		void Save();

	private:
		std::string iniFilename_;
};
extern Config gConfig;

#endif
