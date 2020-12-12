TEMPLATE = app
TARGET = a.out

classes = lua.cpp window.cpp sharedresources.cpp
SOURCES += main.cpp timer.cpp $$classes
HEADERS += timer.hpp
message("generating headers...")
for(name, classes) {
	headerName = "_"$$replace(name,".cpp",".h")
	ignore = $$system(lua5.3 hpp.lua $$headerName <$$name)
	HEADERS += $$headerName
}

           
QT += core widgets
LIBS += -llua5.3

INCLUDEPATH += .
PRECOMPILED_HEADER = precompile.hpp
CONFIG += precompile_header

MOC_DIR = .temp

QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

luahpp.target = _%.h
luahpp.depends = %.cpp
luahpp.commands = lua5.3 hpp.lua $$$@ <$$$<

QMAKE_EXTRA_TARGETS += luahpp
QMAKE_CLEAN += _*.h
