#pragma once

typedef enum {
	ERROR_FILE_OPENING,
	ERRORS__COUNT
} ERROR_CODE;

static const char* ERROR_LABELS[ERRORS__COUNT] = {
	"Failed to open settings file..."
};