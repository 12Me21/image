TEMPLATE = app
TARGET = a.out

SOURCES += main.cpp lua.cpp window.cpp timer.cpp
HEADERS += _window.h _lua.h timer.hpp

QT += core widgets
LIBS += -llua5.3

INCLUDEPATH += .
PRECOMPILED_HEADER = precompile.hpp
CONFIG += precompile_header
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

	

luahpp.target = _%.h
luahpp.depends = %.cpp
luahpp.commands = lua5.3 hpp.lua $$$@ <$$$<
QMAKE_EXTRA_TARGETS += luahpp
QMAKE_CLEAN += _*.h
