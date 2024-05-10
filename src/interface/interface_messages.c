#include "interface_messages.h"

void ThrowError(ERROR_CODE error, const char* errorLabel) {
	size_t errorMessageLength = snprintf(NULL, 0, "[%d] ", error) + strlen(ERROR_LABELS[error]) + strlen(errorLabel) + 7; // one for terminator char, 2 for scopes and 1 for space (new line), 3 for dots

	char* errorMessageConsole = (char*)malloc(sizeof(char) * errorMessageLength);
	char* errorMessageMessageBox = (char*)malloc(sizeof(char) * errorMessageLength);

	errorMessageConsole[0] = '\0';
	errorMessageMessageBox[0] = '\0';

	snprintf(errorMessageConsole, errorMessageLength, "[%d] ", error);
	snprintf(errorMessageMessageBox, errorMessageLength, "[%d] ", error);

	strcat(errorMessageConsole, ERROR_LABELS[error]);
	strcat(errorMessageMessageBox, ERROR_LABELS[error]);

	strcat(errorMessageConsole, "... (");
	strcat(errorMessageMessageBox, "...\n(");

	strcat(errorMessageConsole, errorLabel);
	strcat(errorMessageMessageBox, errorLabel);

	strcat(errorMessageConsole, ")");
	strcat(errorMessageMessageBox, ")");

	fprintf(stderr, errorMessageConsole);
	MessageBox(NULL, errorMessageMessageBox, "Error", MB_ICONERROR | MB_OK);
	exit(EXIT_FAILURE);

	free(errorMessageConsole);
	free(errorMessageMessageBox);
}