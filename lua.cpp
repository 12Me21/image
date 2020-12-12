#include "_lua.h"
#define _ Lua
#if 0
#include <lua5.3/lua.hpp>
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

int _::loadFile(char* name) {
	return luaL_loadfile(L, name);
}

int _::run() {
	return lua_pcall(L, 0, LUA_MULTRET, 0);
}

void _::openLibs() {
	luaL_openlibs(L);
}
