#include <stdio.h>
#include "_window.h"
#include "timer.hpp"

/*
void runLua(const char* filename) {
	puts("running lua");
	puts(filename);
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	int status = luaL_loadfile(L, filename);
	if (status) {
		puts("error loading lua");
		return;
	}
	status = lua_pcall(L, 0, LUA_MULTRET, 0);
	if (status) {
		puts("error running lua");
		return;
	}
	int width = image->width();
	int height = image->height();
	for(int j=0;j<height;j++) {
		for(int i=0;i<width;i++) {
			lua_pushvalue(L, -1);
			lua_Number col = image2.pixelColor(i, j).rgba();
			lua_pushnumber(L, col);
			lua_pushnumber(L, i);
			lua_pushnumber(L, j);
			status = lua_pcall(L, 3, 1, 0);
			if (status) {
				goto fail;
			}
			col = lua_tonumber(L, -1);
			image->setPixelColor(i, j, (QRgb)col);
			lua_pop(L, 1);
		}
	}
fail:
	lua_pop(L, 1);
	lua_close(L);
	}*/

/*static int lf_mapAll(lua_State* L) {
	int n = lua_gettop(L);   
	if (n != 1) {
		lua_pushliteral(L, "incorrect arguments");
		lua_error(L);
	}
	return 0;
}*/

int main(int argc, char** argv) {
	SharedResources shared;
	timer();
	shared.app = new QApplication(argc, argv);
	timer("App created");

	timer();
	MyWindow window {&shared};
	timer("Initial window created");

	timer();
	window.show(); //snow
	timer("initial window shown");
	
	return shared.app->exec();
	/*
	loadFile(argv[1]);

	QFileSystemWatcher watcher;
	watcher.addPath(argv[2]);
	QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [](const QString& path) {
			runLua(path.toUtf8().data());
			setImage(*image);
		});
	
	runLua(argv[2]);
	
	setImage(*image);

	*/
}
