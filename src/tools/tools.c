#include "tools.h"

// ---------
//  private
// ---------

/*void ClearIniLine(String* line) {
	if (line == NULL) { ThrowError(ERROR_NULL_POINTER, "private ClearIniLine"); }
	if (line->self == NULL) { ThrowError(ERROR_STRING_NULL_POINTER, "private ClearIniLine"); }

}

void ReadFileLine(FILE* file, String* line) {
	wchar_t wchar;
	if (file == NULL) { ThrowError(ERROR_NULL_POINTER, "private ReadIniFileLine"); }
	StringSet(line, L"");
	while (fwscanf(file, L"%lc", &wchar) == 1 && wchar != L'\n') { StringConcatWChar(line, wchar); }
}

void ReadIniFileLine(FILE* file, KeyValue* keyValue) {
	String line;
	StringNew(&line, L"");
	ReadFileLine(file, &line);
}*/

// --------
//  public
// --------

// make it work
void ReadIniFile(KeyValues* keyValues, String* filePath) { // provide file path for error
	if (keyValues == NULL || filePath == NULL) { ThrowError(ERROR_NULL_POINTER, "public ReadIniFile"); }
	if (filePath->length <= 0) { ThrowError(ERROR_STRING_ZERO_LENGTH, "public ReadIniFile"); }
	if (filePath->self == NULL) { ThrowError(ERROR_STRING_NULL_POINTER, "public ReadIniFile"); }
	FILE* file = _wfopen(filePath->self, L"r");
	if (!file) { ThrowError(ERROR_FILE_OPENING, "public ReadIniFile"); }
	
	String temp;
	StringNew(&temp, L"random string");
	wprintf(L"%ls|%zu\n", temp.self, temp.length);
	StringRemoveWChar(&temp, 2);
	wprintf(L"%ls|%zu\n", temp.self, temp.length);

	fclose(file);
}

void KeyValuesNew(KeyValues* keyValues) {
	if (keyValues == NULL) { ThrowError(ERROR_NULL_POINTER, "tools: public KeyValuesNew()"); }

	keyValues->self = NULL;
	keyValues->length = 0;
}

void KeyValuesDelete(KeyValues* keyValues) {
	if (keyValues == NULL) { ThrowError(ERROR_NULL_POINTER, "tools: public KeyValuesDelete()"); }

	if (keyValues->length > 0) {
		if (keyValues->self == NULL) { ThrowError(ERROR_KEYVALUES_NULL_POINTER, "tools: public KeyValuesDelete()"); }

		for (size_t i = 0; i < keyValues->length; i++) {
			StringDelete(&(keyValues->self[i].key));
			StringDelete(&(keyValues->self[i].value));
			StringDelete(&(keyValues->self[i].section));
		}
		free(keyValues->self);
		keyValues->self = NULL;
		keyValues->length = 0;
	}
}

void StringNew(String* string, const wchar_t* self) {
	if (string == NULL || self == NULL) { ThrowError(ERROR_NULL_POINTER, "tools: public StringNew()"); }

	string->length = wcslen(self);
	string->self = (wchar_t*)malloc(sizeof(wchar_t) * (string->length + 1)); // one for string terminator
	if (string->length > 0) { wcscpy(string->self, self); }
	else { string->self[0] = L'\0'; }
}

void StringSet(String* string, const wchar_t* self) {
	if (string == NULL || self == NULL) { ThrowError(ERROR_NULL_POINTER, "tools: public StringSet()"); }
	if (string->self == NULL) { ThrowError(ERROR_STRING_NULL_POINTER, "tools: public StringSet()"); }
	if (string->length != wcslen(string->self)) { ThrowError(ERROR_STRING_DATA_CORRUPTED, "tools: public StringSet()"); }

	StringDelete(string);
	StringNew(string, self);
}

void StringDelete(String* string) {
	if (string == NULL) { ThrowError(ERROR_NULL_POINTER, "tools: public StringDelete()"); }
	if (string->self == NULL) { ThrowError(ERROR_STRING_NULL_POINTER, "tools: public StringDelete()"); }
	if (string->length != wcslen(string->self)) { ThrowError(ERROR_STRING_DATA_CORRUPTED, "tools: public StringDelete()"); }

	free(string->self);
	string->self = NULL;
	string->length = 0;
}

void StringConcatWChar(String* string, const wchar_t wchar) {
	if (string == NULL) { ThrowError(ERROR_NULL_POINTER, "tools: public StringConcatWChar()"); }
	if (string->self == NULL) { ThrowError(ERROR_STRING_NULL_POINTER, "tools: public StringConcatWChar()"); }
	if (string->length != wcslen(string->self)) { ThrowError(ERROR_STRING_DATA_CORRUPTED, "tools: public StringConcatWChar()"); }

	wchar_t* buffer = (wchar_t*)malloc(sizeof(wchar_t) * (string->length + 2)); // one for new wchar, one for string terminator
	if (string->length > 0) { wcscpy(buffer, string->self); }
	buffer[string->length] = wchar;
	buffer[string->length + 1] = L'\0';
	StringSet(string, buffer);
}

void StringRemoveWChar(String* string, size_t position) {
	if (string == NULL) { ThrowError(ERROR_NULL_POINTER, "tools: public StringRemoveWChar()"); }
	if (string->self == NULL) { ThrowError(ERROR_STRING_NULL_POINTER, "tools: public StringRemoveWChar()"); }
	if (string->length != wcslen(string->self)) { ThrowError(ERROR_STRING_DATA_CORRUPTED, "tools: public StringRemoveWChar()"); }
	if (string->length == 0) { ThrowError(ERROR_STRING_ZERO_LENGTH, "tools: public StringRemoveWChar()"); }
	if (position >= string->length) { ThrowError(ERROR_STRING_OUT_OF_BOUNDS, "tools: public StringRemoveWChar()"); }

	wchar_t* buffer = (wchar_t*)malloc(sizeof(wchar_t) * (string->length)); // we doesnt reduce memory allocation size 'cause of string terminator
	buffer[string->length - 1] = L'\0';
	bool passedWChar = false;
	for (size_t i = 0; i < string->length; i++) {
		if (i == position) { passedWChar = true; }
		buffer[i] = string->self[i + passedWChar];
	}

	StringSet(string, buffer);
}