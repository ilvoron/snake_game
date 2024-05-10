#include "interface.h"

KeyValues settings;

void InitInterface() {
	KeyValuesNew(&settings);
	String filePath;
	StringNew(&filePath, settingsIniFile);
	ReadIniFile(&settings, &filePath);
	StringDelete(&filePath);
}

void CloseInterface() {
	KeyValuesDelete(&settings);
}