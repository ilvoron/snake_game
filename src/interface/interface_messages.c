#include "interface_messages.h"

// private

static void ThrowFallbackError(ERROR_CODE error, char* errorLabel) {
	fprintf(stderr, "Error while running ThrowError()... Data without args for format string:\n[error] %d\n[errorLabel] %s", error, errorLabel);
	exit(EXIT_FAILURE);
}

// public

void ThrowError(ERROR_CODE error, char* errorLabel, ...) {
	va_list errorLabelArgs, errorLabelArgsCopy;
	va_start(errorLabelArgs, errorLabel);
	va_copy(errorLabelArgsCopy, errorLabelArgs);
	size_t errorLabelLength = (size_t)vsnprintf(NULL, 0, errorLabel, errorLabelArgs) + 1; // one for string terminator
	va_end(errorLabelArgs);
	char* errorLabelCopy = (char*)malloc(sizeof(char) * errorLabelLength);
	if (errorLabelCopy == NULL) { ThrowFallbackError(error, errorLabel); }
	vsnprintf(errorLabelCopy, errorLabelLength, errorLabel, errorLabelArgsCopy);
	errorLabel = errorLabelCopy;
	errorLabelCopy = NULL;

	char* errorMessageFormat = "[%d] %s...%c(%s)"; // error code, error message, separator (space or new line), error label
	size_t errorMessageLength = (size_t)snprintf(NULL, 0, errorMessageFormat, error, ERROR_LABELS[error], '\n', errorLabel) + 1; // one for string terminator
	char* errorMessageMsgBox = (char*)malloc(sizeof(char) * errorMessageLength); // one for terminator string
	if (errorMessageMsgBox == NULL) { ThrowFallbackError(error, errorLabel); }
	snprintf(errorMessageMsgBox, errorMessageLength, errorMessageFormat, error, ERROR_LABELS[error], '\n', errorLabel);

	fprintf(stderr, errorMessageFormat, error, ERROR_LABELS[error], ' ', errorLabel);
	MessageBox(NULL, errorMessageMsgBox, "Error", MB_ICONERROR | MB_OK);
	exit(EXIT_FAILURE);

	free(errorMessageMsgBox);
}