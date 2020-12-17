// Automatically generated header file~!
#include <lua5.3/lua.hpp>
#include <QImage>
class Lua {private:
lua_State* L;
public:
	Lua();
	~Lua();
	int loadFile(const char* name);
	int run();
	void openLibs();
	void processImage(const QImage* input, QImage* output);
};
