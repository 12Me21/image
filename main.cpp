#include <QFileSystemWatcher>
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QClipboard>
#include <QScrollArea>
#include <QImageReader>
#include <stdio.h>

#include <lua5.3/lua.hpp>

QScrollArea* scroll;
QLabel* label;
QMainWindow* window;
QImage* image;
QImage image2;

void setImage(QImage& newImage) {
	image = new QImage(newImage);
	label->setPixmap(QPixmap::fromImage(*image));
	label->adjustSize();
	scroll->setVisible(true);
}

bool loadFile(const QString &name) {
	QImageReader reader {name};
	reader.setAutoTransform(true);
	auto image = reader.read();
	if (image.isNull()) {
		return false;
	}
	image2 = image.copy();
	setImage(image);
	return true;
}

void runLua(const char* filename) {
	puts("running lua");
	puts(filename);
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	int status = luaL_loadfile(L, filename);
	if (status) {
		puts("error loading lua");
		return;
	}
	status = lua_pcall(L, 0, LUA_MULTRET, 0);
	if (status) {
		puts("error running lua");
		return;
	}
	int width = image->width();
	int height = image->height();
	for(int j=0;j<height;j++) {
		for(int i=0;i<width;i++) {
			lua_pushvalue(L, -1);
			lua_Number col = image2.pixelColor(i, j).rgba();
			lua_pushnumber(L, col);
			lua_pushnumber(L, i);
			lua_pushnumber(L, j);
			status = lua_pcall(L, 3, 1, 0);
			if (status) {
				goto fail;
			}
			col = lua_tonumber(L, -1);
			image->setPixelColor(i, j, (QRgb)col);
			lua_pop(L, 1);
		}
	}
fail:
	lua_pop(L, 1);
	lua_close(L);
}

static int lf_mapAll(lua_State *L) {
	int n = lua_gettop(L);    /* number of arguments */
	if (n != 1) {
		lua_pushliteral(L, "incorrect arguments");
		lua_error(L);
	}
	return 0;
}

int main(int argc, char **argv) {
	QApplication app {argc, argv};
	window = new QMainWindow {};
	
	scroll = new QScrollArea();
	scroll->setBackgroundRole(QPalette::Dark);
	scroll->setVisible(false);
	window->setCentralWidget(scroll);
	
	label = new QLabel();
	label->setBackgroundRole(QPalette::Base);
	label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	label->setScaledContents(true);
	scroll->setWidget(label);

	loadFile(argv[1]);

	QFileSystemWatcher watcher;
	watcher.addPath(argv[2]);
	QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [](const QString& path) {
			runLua(path.toUtf8().data());
			setImage(*image);
		});
	
	runLua(argv[2]);
	
	setImage(*image);

	window->show();
	return app.exec();
}
