function br(c)
	c=c*2
	if c>=255 then return 255 end
	return c
end

return function(c)
	local r = br(c>>16 & 0xFF)
	local g = br(c>>8 & 0xFF)
	local b = br(c & 0xFF)
	return c & 0xFF000000 | r<<16 | g<<8 | b
end
