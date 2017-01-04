#include <stdint.h>
#include "export.h"
#include "main.h"

struct TS3Functions ts3Functions;

extern "C" {

	const char* ts3plugin_name() {
		return "TS3Silencer";
	}

	const char* ts3plugin_version() {
		return "1.0";
	}

	int ts3plugin_apiVersion() {
		return 21;
	}

	const char* ts3plugin_author() {
		return "Sajoch";
	}

	const char* ts3plugin_description() {
		return "This plugin mute your microphone when scoll lock key is on and unmute when is off.";
	}

	void ts3plugin_setFunctionPointers(const struct TS3Functions funcs) {
		ts3Functions = funcs;
	}

	int ts3plugin_init() {
		return init();
	}

	void ts3plugin_shutdown() {
		shutdown();
	}

}