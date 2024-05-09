#include "tools.h"

void ReadIniFile(KeyValue* keyValues, String* filePath) {
	FILE* file = _wfopen(filePath->self, L"r");
	if (!file) {
		ThrowError(ERROR_FILE_OPENING);
	}
	fclose(file);
}

void KeyValueNew(KeyValue* keyValue) {
	keyValue->isInit = false;
	keyValue->length = 0;
}

void StringNew(String* string, const wchar_t* self) {
	string->self = (wchar_t*)self;
	string->length = wcslen(self);
}