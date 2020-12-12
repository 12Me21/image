include project.pro

# this is required because
# qmake is dumb
initial: $(HEADERS)
	qmake
	$(MAKE)

_%.h: %.cpp
	lua5.3 hpp.lua $@ <$<
