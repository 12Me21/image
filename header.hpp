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

#include <lua5.3/lua.hpp>

class MyWindow : public QMainWindow {
	Q_OBJECT
public:
	MyWindow();

	QImage image;
	QImage previewImage;

	QScrollArea scrollArea;
	QLabel imageLabel;

	QClipboard* clipboard;
	
	void setImage(const QImage &);
	
	QFileDialog fileDialog;
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
};
