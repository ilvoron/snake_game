#include <stdio.h>
#include <unistd.h>
#include "test__show_menu.h"
#include "global.h"
#include "consts.h"
#include "interface.h"
#include "tools.h"
#include "output.h"

// private

bool _hasTestShowMenuBad = false;
extern enum GAME_STATE _gameState;
unsigned int _delay = 25000;

void _GenerateExpectedOutput(struct Settings* Settings) {
	for (int i = 0; i < GS__MENU_COUNT; i++) {
		switch (i) {
			case 0: freopen(TEMP_FILE_SM_0, "w", stdout); break;
			case 1: freopen(TEMP_FILE_SM_1, "w", stdout); break;
			case 2: freopen(TEMP_FILE_SM_2, "w", stdout); break;
			default: break;
		}
		
		for (int j = 0; j < GS__MENU_COUNT; j++) {
			if (j == i) { printf("---> [%s] <---", Settings->skin.menuMainLabels[j]); }
			else { printf("[%s]", Settings->skin.menuMainLabels[j]); }
		}
		
		printf(RemoveNewlines(Settings->skin.menuMainLabel), Settings->inputTriggers[I_UP].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_CONFIRM].keyLabels[0]);
	}
	
	freopen(TEMP_FILE_SPEED, "w", stdout);
	SimulateKeyPressAssync(1, Settings->inputTriggers[I__EXIT].keyCodes[0], _delay, false, NULL);
	printf(RemoveNewlines(Settings->skin.menuSpeedLabel), Settings->speed._new, Settings->speed._default, Settings->speed.min, Settings->speed.max, Settings->inputTriggers[I_UP].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_ERASE].keyLabels[0], Settings->inputTriggers[I_CONFIRM].keyLabels[0], Settings->inputTriggers[I_RETURN].keyLabels[0]);
	usleep(_delay);

	freopen(DEFAULT_OUT, "a", stdout);
}

void _TestShowMenu1(struct Settings* Settings) {
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 1. Calling function... ");
	_gameState = GS_MENU_START;

	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(1, Settings->inputTriggers[I__EXIT].keyCodes[0], _delay, false, NULL);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_0)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_1(struct Settings* Settings) {
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.1. Testing menu inputs (select: \"%s\", keys: \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_UP].keyLabels[0]);
	_gameState = GS_MENU_START;

	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_UP].keyCodes[0], _delay, false,
	                          Settings->inputTriggers[I__EXIT].keyCodes[0], _delay, true,
	                          TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_0)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_2(struct Settings* Settings) {
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.2. Testing menu inputs (select: \"%s\", keys: \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0]);
	_gameState = GS_MENU_START;

	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(2, Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
	                          Settings->inputTriggers[I__EXIT].keyCodes[0], _delay, true,
	                          TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_1)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_3(struct Settings* Settings) {
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.3. Testing menu inputs (select: \"%s\", keys: \"%s\", \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0]);
	_gameState = GS_MENU_START;

	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(3, Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
	                          Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
	                          Settings->inputTriggers[I__EXIT].keyCodes[0], _delay, true,
	                          TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_2)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu2_4(struct Settings* Settings) {
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 2.4. Testing menu inputs (select: \"%s\", keys: \"%s\", \"%s\", \"%s\")... ", Settings->skin.menuMainLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0], Settings->inputTriggers[I_DOWN].keyLabels[0]);
	_gameState = GS_MENU_START;

	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(4, Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
							  Settings->inputTriggers[I__EXIT].keyCodes[0], _delay, true,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SM_2)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu3_1(struct Settings* Settings) {
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 3.1. Testing menu inputs (selected: \"%s\")... ", Settings->skin.menuMainLabels[0]);
	_gameState = GS_MENU_START;
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(1, Settings->inputTriggers[I_CONFIRM].keyCodes[0], _delay, false, NULL);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);

	if (Settings->gameState == GS_MENU_START) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu3_2(struct Settings* Settings) {
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 3.2. Testing menu inputs (selected: \"%s\")... ", Settings->skin.menuMainLabels[1]);
	_gameState = GS_MENU_START;
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(4, Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
							  Settings->inputTriggers[I_CONFIRM].keyCodes[0], _delay, false,
							  Settings->inputTriggers[I_CONFIRM].keyCodes[0], _delay, true,
							  Settings->inputTriggers[I__EXIT].keyCodes[0], _delay, false,
							  TEMP_FILE);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);

	if (CompareFiles(TEMP_FILE, TEMP_FILE_SPEED)) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

void _TestShowMenu3_3(struct Settings* Settings) {
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);
	PrintSTATUS(false, false, "[show_menu]");
	printf(" Test 3.3. Testing menu inputs (selected: \"%s\")... ", Settings->skin.menuMainLabels[2]);
	_gameState = GS_MENU_START;
	
	freopen(TEMP_FILE, "w", stdout);
	SimulateKeyPressAssync(3, Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
							  Settings->inputTriggers[I_DOWN].keyCodes[0], _delay, false,
							  Settings->inputTriggers[I__EXIT].keyCodes[0], _delay, false,
							  NULL);
	show_menu();
	freopen(DEFAULT_OUT, "a", stdout);
	usleep(_delay);

	if (Settings->gameState == GS_MENU_EXIT) { PrintOK(false, true); }
	else { PrintBAD(false, true); _hasTestShowMenuBad = true; }
}

// public

bool TestShowMenu(struct Settings* Settings) {
	printf("Testing ");
	PrintSTATUS(false, false, "show_menu()");
	printf("...\n");
	
	_GenerateExpectedOutput(Settings);
	_TestShowMenu1(Settings);
	_TestShowMenu2_1(Settings);
	_TestShowMenu2_2(Settings);
	_TestShowMenu2_3(Settings);
	_TestShowMenu2_4(Settings);
	_TestShowMenu3_1(Settings);
	_TestShowMenu3_2(Settings);
	_TestShowMenu3_3(Settings);
	
	printf("Testing ");
	PrintSTATUS(false, false, "show_menu()");
	printf("... ");
	if (_hasTestShowMenuBad) { PrintBAD(false, true); }
	else { PrintOK(false, true); }
	return _hasTestShowMenuBad;
}