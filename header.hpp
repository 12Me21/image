#include <QApplication>
#include <QClipboard>
#include <QFileSystemWatcher>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>

#include <stdio.h>
#include <chrono>

#include <lua5.3/lua.hpp>

class SharedResources {
private:
	QFileDialog* _fileDialog = NULL;
public:
	QFileDialog* fileDialog();
	QApplication* app;
};

class MyWindow : public QMainWindow {
	Q_OBJECT
public:
	MyWindow(SharedResources*);

private:
	SharedResources* share;
	
	QImage image;
	//QImage previewImage;

	QScrollArea* scrollArea;
	QLabel* imageLabel;

	QClipboard* clipboard;
	
	void setImage(const QImage &);
	
	bool saveAsFile(const QString);
	bool loadFile(const QString);
	
	/////////////
	// Top Menu
	QMenu* fileMenu;
	
	QAction* openAct;
	void onOpen();
	QAction* saveAsAct;
	void onSaveAs();
	QAction* copyAct;
	void onCopy();
	QAction* pasteAct;
	void onPaste();
	QAction* windowAct;
	void onWindow();
};

class Lua {
private:
	lua_State* L;
public:
	Lua();
	~Lua();
	int loadFile(char*);
	int run();
	void openLibs();
};
