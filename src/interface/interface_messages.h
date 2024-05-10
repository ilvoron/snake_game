#pragma once
#include "errors.h"
#include "tools.h"

#include <windows.h>

void ThrowError(ERROR_CODE error, const char* errorLabel);