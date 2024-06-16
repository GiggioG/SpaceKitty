#include "World.h"

#undef main

World world;
ConfigManager* cfgm;

int main(int* argc, char* argv[]) {
	srand(time(NULL));
	world.init();

	while (world.isRunning()) {
		world.run();
	}

	world.destroy();

	return 0;
}