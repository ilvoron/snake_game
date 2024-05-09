#pragma once
#include "errors.h"
#include "interface_messages.h"
#include <wchar.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
	wchar_t* self;
	size_t length;
} String;

typedef struct {
	bool isInit;
	String key;
	String value;
	size_t length;
} KeyValue;

void ReadIniFile(KeyValue* keyValues, String* filePath);
void KeyValueNew(KeyValue* keyValue);
void StringNew(String* string, const wchar_t* self);