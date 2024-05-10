#pragma once
#include "errors.h"
#include "tools.h"
#include <stdarg.h>
#include <windows.h>

void ThrowError(ERROR_CODE error, char* errorLabel, ...);