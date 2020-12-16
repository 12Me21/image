#define _ MyWindow
#include "_window.h"
#include "timer.hpp"
#if 0////////////////////////////////////////////////
#include <QMainWindow>
#include <QLabel>
#include <QMenuBar>
#include <QScrollArea>
#include "_sharedresources.h"
#include "_lua.h"
class MyWindow : public QMainWindow {
	Q_OBJECT
private:
	SharedResources* share;
	QImage* image;
	QScrollArea* scrollArea;
	QLabel* imageLabel;
	QMenu* fileMenu;
	QAction* openAct, *saveAsAct, *copyAct, *pasteAct, *windowAct, *runAct;
public:
};
#endif///////////////////////////////////////////////

_::MyWindow(SharedResources *share): share {share} {
	scrollArea = new QScrollArea();
	imageLabel = new QLabel();
	
	scrollArea->setBackgroundRole(QPalette::Dark);
	setCentralWidget(scrollArea);
	
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);
	scrollArea->setWidget(imageLabel);

	fileMenu = menuBar()->addMenu(tr("&File"));
	openAct = addAction(fileMenu, "&Open...", &_::onOpen);
	openAct->setShortcut(tr("Ctrl+O"));
	saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &_::onSaveAs);
	saveAsAct->setShortcut(tr("Ctrl+S"));

	fileMenu->addSeparator();
	copyAct = fileMenu->addAction(tr("&Copy"), this, &_::onCopy);
	copyAct->setShortcut(tr("Ctrl+C"));
	pasteAct = fileMenu->addAction(tr("&Paste"), this, &_::onPaste);
	pasteAct->setShortcut(tr("Ctrl+V"));

	fileMenu->addSeparator();
	windowAct = fileMenu->addAction(tr("&Window"), this, &_::onWindow);
	windowAct->setShortcut(tr("Ctrl+N"));

	fileMenu->addSeparator();
	runAct = fileMenu->addAction(tr("&Run Script..."), this, &_::onRun);

	setImage(NULL);
}

void _::onWindow() {
	timer();
	auto x = new MyWindow(share);
	x->show();
	timer("window created");
}

void _::onSaveAs() {
	share->fileDialog()->saveImage(image);
}

void _::onOpen() {
	auto image = share->fileDialog()->loadImage();
	if (image)
		setImage(image);
}

void _::onCopy() {
	if (image)
		share->setClipboardImage(image);
}

void _::onPaste() {
	auto image = share->getClipboardImage();
	if (image)
		setImage(image);
}

void _::setImage(QImage* newImage) {
	image = newImage;
	if (!image) {
		imageLabel->hide();
	} else {
		imageLabel->setPixmap(QPixmap::fromImage(*image));
		imageLabel->adjustSize();
		imageLabel->show();
	}
	saveAsAct->setEnabled(image != NULL);
}

void _::runLua(QString filename) {
	puts("running lua");
	timer();
	Lua lua {};
	lua.openLibs();
	int status = lua.loadFile(filename.toUtf8().data());
	if (status) {
		puts("error loading lua");
		return;
	}
	status = lua.run();
	if (status) {
		puts("error running lua");
		return;
	}
	lua.processImage(image, image);
	setImage(image);
	timer("Ran lua script");
}

void _::onRun() {
	auto filename = share->fileDialog()->selectScript();
	if (!filename.isNull())
		runLua(filename);
}

QAction* _::addAction(QMenu* menu, const char* text, void (MyWindow::* func)()) {
	return menu->addAction(tr(text), this, func);
}


