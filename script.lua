return function(c, x, y)
	local b = c&255
	local g = c>>8 & 255
	local r = c>>16 & 255
	local a = c>>24
	local l = (r*.2+g*.7+b*.1)//1
	return a<<24 | l<<16 | l<<8 | l
end
