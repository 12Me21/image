local lines = io.lines()
local name
local out=""
-- find class name
for l in lines do
	_, _, name = l:find("#define _ ([%w_]+)")
	if name then break end
end
if not name then
	io.stderr:write("name not found\n")
	os.exit(1)
	return
end
io.stderr:write("got name: "..name.."\n")
-- look for #if 0 block
for l in lines do
	if l=="#if 0" then break end
end
local last = ""
-- output contents
for l in lines do
	local l2 = last
	last = l -- hacks to skip last line (closing brace)
	if l=="#endif" then break end
	out=out..l2.."\n"
end
-- find function definitions
for l in lines do
	l, num = l:gsub("(.*)_::(.*)", "%1%2")
	if num>0 then
		l = l:gsub("[^:]:[^:](.*){$", "{") --fix `func(...): ... {`
		l, num = l:gsub("^(.-)%s*{%s*$","\t%1;\n")
		if num>0 then out=out..l end
	end
end
out=out.."};\n"
local f = io.open(arg[1], "r")
if f and out==f:read("*all") then
	print("(header file unchanged)")
	return
end
local f = io.open(arg[1], "w")
f:write(out)
f:close()
