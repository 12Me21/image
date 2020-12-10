#include "header.hpp"

Lua::Lua() {
	L = luaL_newstate();
}
Lua::~Lua() {
	lua_close(L);
}

int Lua::loadFile(char* name) {
	return luaL_loadfile(L, name);
}

int Lua::run() {
	return lua_pcall(L, 0, LUA_MULTRET, 0);
}

void Lua::openLibs() {
	luaL_openlibs(L);
}
