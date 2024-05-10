#pragma once
#include "errors.h"
#include "interface_messages.h"
#include <wchar.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct String {
	wchar_t* self;
	size_t length;
} String;

typedef struct KeyValue {
	String key;
	String value;
	String section;
} KeyValue;

typedef struct KeyValues {
	KeyValue* self;
	size_t length;
} KeyValues;

void ReadIniFile(KeyValues* keyValues, String* filePath);
void KeyValuesNew(KeyValues* keyValues);
void KeyValuesDelete(KeyValues* keyValues);
void StringNew(String* string, const wchar_t* self);
void StringSet(String* string, const wchar_t* self);
void StringDelete(String* string);
void StringConcatWChar(String* string, const wchar_t wchar);
void StringRemoveWChar(String* string, size_t position);