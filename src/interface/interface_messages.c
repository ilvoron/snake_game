#include "interface_messages.h"

void ThrowError(ERROR_CODE error) {
	perror(ERROR_LABELS[error]);
	MessageBox(NULL, ERROR_LABELS[error], "Error", MB_ICONERROR | MB_OK);
	exit(1 + error);
}