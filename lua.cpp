#include "_lua.h"
#define _ Lua
#if 0
#include <lua5.3/lua.hpp>
#include <QImage>
class Lua {
private:
	lua_State* L;
public:
};
#endif

_::Lua() {
	L = luaL_newstate();
}

_::~Lua() {
	lua_close(L);
}

int _::loadFile(const char* name) {
	return luaL_loadfile(L, name);
}

int _::run() {
	return lua_pcall(L, 0, LUA_MULTRET, 0);
}

void _::openLibs() {
	luaL_openlibs(L);
}

void _::processImage(QImage* input, QImage* output) {
	int width = input->width();
	int height = input->height();
	for(int j=0;j<height;j++) {
		for(int i=0;i<width;i++) {
			lua_pushvalue(L, -1);
			lua_Number col = input->pixelColor(i, j).rgba();
			lua_pushnumber(L, col);
			lua_pushnumber(L, i);
			lua_pushnumber(L, j);
			int status = lua_pcall(L, 3, 1, 0);
			if (status)
				goto fail;
			col = lua_tonumber(L, -1);
			output->setPixelColor(i, j, (QRgb)col);
			lua_pop(L, 1);
		}
	}
fail:
	lua_pop(L, 1);
}
