#pragma once

typedef enum ERROR_CODE {
	ERROR_NULL_POINTER,
	ERROR_STRING_NULL_POINTER,
	ERROR_STRING_ZERO_LENGTH,
	ERROR_STRING_NOT_EMPTY,
	ERROR_STRING_DATA_CORRUPTED,
	ERROR_STRING_OUT_OF_BOUNDS,
	ERROR_KEYVALUES_NULL_POINTER,
	ERROR_FILE_OPENING,
	ERRORS__COUNT
} ERROR_CODE;

static const char* ERROR_LABELS[ERRORS__COUNT] = {
	"Null pointer",
	"Null pointer for String",
	"String has zero length",
	"String is not empty",
	"String data is corrupted",
	"Trying to access String with index out of bounds",
	"Null pointer for KeyValues",
	"Failed to open settings file"
};