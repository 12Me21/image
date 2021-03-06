io.output(io.stderr)
local lines = io.open(arg[1]):lines()
local name
local out="// Automatically generated header file~!\n"

-- Find class name
for l in lines do
	_, _, name = l:find("#define _ ([A-Za-z0-9_]+)")
	if name then break end
end
if not name then
	print("[c++ header generator] ERROR: Class name not found!")
	os.exit(1)
	return
end
print("[c++ header generator] Got class name: `"..name.."`")

-- Look for #if 0 block
for l in lines do
	if l:sub(1,5)=="#if 0" then break end
end
-- output contents
for l in lines do
	if l:sub(1,7)=="class;" then
		out=out.."class "..name.." {"
	elseif l:sub(1,6)=="class:" then
		out=out.."class "..name..": "..l:sub(7,-2).." {"
	else
		if l:sub(1,6)=="#endif" then break end
		out=out..l.."\n"
	end
end

-- find function definitions
for l in lines do
	l, num = l:gsub("(.*)_::(.*)", "%1%2")
	if num>0 then
		l = l:gsub("([^:]):[^:](.*){$", "%1{") --fix `func(...): ... {`
		l, num = l:gsub("^(.-)%s*{%s*$","\t%1;\n")
		if num>0 then out=out..l end
	end
end
out=out.."};\n"

-- write to arg2
local outfile = arg[2]
local f = io.open(outfile, "r")
if f and out==f:read("*all") then
	print("[c++ header generator] (`"..outfile.."` was unchanged)")
	return
end
local f = io.open(outfile, "w")
local status, err = f:write(out)
if not status then
	print("[c++ header generator] Failed to write header: "..err)
	os.exit(1)
end
f:close()
print("[c++ header generator] Wrote `"..outfile.."`")
