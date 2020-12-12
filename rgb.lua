return function(c)
	local r = c>>16 & 0xFF
	local g = c>>8 & 0xFF
	local b = c & 0xFF
	return c & 0xFF000000 | b<<16 | r<<8 | g
end
