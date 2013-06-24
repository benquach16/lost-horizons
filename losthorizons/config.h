#ifndef _CONFIG_H_
#define _CONFIG_H_

// include this header file whenever you want to use the config

#include <string>


struct Config
{
	public:
		Config();
		~Config();

		// Special Use
		bool bSaveSettings;
		bool bFirstRun;
		bool bRestart;

		// General
		bool bAutoLoadLast;
		bool bConfirmOnQuit;
		bool bTopMost;
		unsigned iWindowX;
		unsigned iWindowY;

		// Video
		unsigned iBits;
		unsigned iResolutionX;
		unsigned iResolutionY;
		bool bFullScreen;
		bool bVsync;
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
