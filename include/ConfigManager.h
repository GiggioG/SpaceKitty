#pragma once

#include <unordered_map>
#include <filesystem>
#include "defines.h"

struct ConfigItem {
	char type;
	int i;
	string s;
	float f;
};

class ConfigManager {
public:
	ConfigManager();
	~ConfigManager();

	unordered_map<string, ConfigItem> cfg;

	void init();
	void destruct();
private:
	void enterConfigFile(string path);
};