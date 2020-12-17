# names of source files with autogenerated headers:
classes = lua window sharedresources filedialog

# normal sources and headers:
sources = main.c++ timer.c++
headers = timer.h++


TEMPLATE = app
TARGET = a.out
QT += core widgets

LIBS += -llua5.3


tempdir = temp #don't change this, it's hardcoded into some #includes

# put SOME of the temp files in a seprate dir
MOC_DIR = $$tempdir
OBJECTS_DIR = $$tempdir

SOURCES += $$sources $$replace(classes,"$",".c++")
HEADERS += $$headers
message("generating headers...")
# qmake needs our headers to exist BEFORE it generates the makefile
# because it scans them to determine which ones use Qt classes
for(name, classes) {
	headername = $$tempdir"/"$$name".h++"
	ignore = $$system(lua5.3 h++.lua $$name".c++" $$headername)
	HEADERS += $$headername
}
# extra Make rules to generate headers:
luahpp.target = $$tempdir"/%.h++"
luahpp.depends = %.c++
luahpp.commands = @echo generating header from $$$< && lua5.3 h++.lua $$$< $$$@
QMAKE_EXTRA_TARGETS += luahpp
QMAKE_CLEAN += $$tempdir"/*.h++"

# reduced output
#CONFIG += silent

# excessive C++ warnings because why not
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

PRECOMPILED_HEADER = precompile.h++
CONFIG += precompile_header

QMAKE_EXT_CPP += .c++
QMAKE_EXT_H += .h++
