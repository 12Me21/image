# this is required because
# qmake is dumb
initial: _window.h _lua.h
	qmake
	make

_%.h: %.cpp
	lua5.3 hpp.lua $@ <$<
