# names of source files with autogenerated headers:
classes = lua window sharedresources filedialog

# normal sources and headers:
sources = main.cpp timer.cpp
headers = timer.hpp

TEMPLATE = app
TARGET = a.out
QT += core widgets
LIBS += -llua5.3

PRECOMPILED_HEADER = precompile.hpp
CONFIG += precompile_header

SOURCES += $$sources $$replace(classes,"$",".cpp")
HEADERS += $$headers
message("generating headers...")
# qmake needs our headers to exist BEFORE it generates the makefile
# because it scans them to determine which ones use Qt classes
for(name, classes) {
	ignore = $$system(lua5.3 hpp.lua $$name)
	HEADERS += "_"$$replace(name,"$",".h")
}
# extra Make rules to generate headers:
luahpp.target = _%.h
luahpp.depends = %.cpp
luahpp.commands = @echo generating header from $$$< && lua5.3 hpp.lua $$$*
QMAKE_EXTRA_TARGETS += luahpp
QMAKE_CLEAN += _*.h

# reduced output
CONFIG += silent

# put SOME of the temp files in a seprate dir
MOC_DIR = .temp

# excessive C++ warnings because why not
QMAKE_CXXFLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept -Woverloaded-virtual -Wredundant-decls -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused


