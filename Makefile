# Temporary initial makefile
# This will be replaced when `qmake` runs

.FORCE:
Makefile: .FORCE
	qmake
	@echo "watch this:"
# note: we don't need to call `make` again in this rule
#  magic!
