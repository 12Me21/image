// Automatically generated header file~!
#include <QMainWindow>
#include <QLabel>
#include <QMenuBar>
#include <QScrollArea>
#include "temp/sharedresources.h++"
#include "temp/lua.h++"
class MyWindow:  public QMainWindow {Q_OBJECT
private:
SharedResources* share;
QImage* image;
QScrollArea* scrollArea;
QLabel* imageLabel;
QMenu* fileMenu;
QAction* openAct, *saveAsAct, *copyAct, *pasteAct, *windowAct, *runAct;
public:
	MyWindow(SharedResources *share);
	void onWindow();
	void onSaveAs();
	void onOpen();
	void onCopy();
	void onPaste();
	void setImage(QImage* newImage);
	void runLua(QString filename);
	void onRun();
	QAction* addAction(QMenu* menu, const char* text, void (MyWindow::* func)());
};
