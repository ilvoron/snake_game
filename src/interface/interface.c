#include "interface.h"

void InitInterface() {
	KeyValue keyValues;
	KeyValueNew(&keyValues);
	String filePath;
	StringNew(&filePath, settingsIniFile);
	ReadIniFile(&keyValues, &filePath);
}