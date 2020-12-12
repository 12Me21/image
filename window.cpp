#include "_window.h"
#include "timer.hpp"
#define _ MyWindow
#if 0
#include "_sharedresources.h"
#include <QClipboard>
#include <QImageReader>
#include <QImageWriter>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>
#include <stdio.h>
#include "_lua.h"
class MyWindow : public QMainWindow {
	Q_OBJECT
private:
	SharedResources* share;
	QImage image;
	QImage previewImage;
	QScrollArea* scrollArea;
	QLabel* imageLabel;
	QClipboard* clipboard;
	/////////////
	// Top Menu
	QMenu* fileMenu;
	QAction* openAct;
	QAction* saveAsAct;
	QAction* copyAct;
	QAction* pasteAct;
	QAction* windowAct;
	QAction* runAct;
public:
};
#endif

_::MyWindow(SharedResources *share) : share {share}, clipboard {QGuiApplication::clipboard()} {
	scrollArea = new QScrollArea();
	imageLabel = new QLabel();
	
	scrollArea->setBackgroundRole(QPalette::Dark);
	setCentralWidget(scrollArea);
	
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);
	scrollArea->setWidget(imageLabel);

	fileMenu = menuBar()->addMenu(tr("&File"));
	openAct = fileMenu->addAction(tr("&Open..."), this, &_::onOpen);
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
	runAct = fileMenu->addAction(tr("&Run"), this, &_::onRun);
}

void _::onWindow() {
	timer();
	auto x = new MyWindow(share);
	x->show();
	timer("window created");
}

void _::onSaveAs() {
	auto dialog = share->fileDialog();
	dialog->setFileMode(QFileDialog::AnyFile);
	dialog->setAcceptMode(QFileDialog::AcceptSave);
	if (dialog->exec() != QDialog::Accepted) return;
	saveAsFile(dialog->selectedFiles().first());
}

void _::onOpen() {
	auto dialog = share->fileDialog();
	dialog->setFileMode(QFileDialog::ExistingFile);
	dialog->setAcceptMode(QFileDialog::AcceptOpen);
	if (dialog->exec() != QDialog::Accepted) return;
	loadFile(dialog->selectedFiles().first());
}

void _::onCopy() {
	clipboard->setImage(image);
}

void _::onPaste() {
	if (const QMimeData* mimeData = clipboard->mimeData())
		if (mimeData->hasImage())
			setImage(qvariant_cast<QImage>(mimeData->imageData()));
}

bool _::saveAsFile(const QString name) {
	QImageWriter writer {name};
	if (!writer.write(image)) {
		QMessageBox::warning(this, "Save Error", tr("Can't save file: %1").arg(writer.errorString()));
		return false;
	}
	return true;
}
bool _::loadFile(const QString name) {
	QImageReader reader {name};
	reader.setAutoTransform(true); //handle rotation metadata
	setImage(reader.read());
	if (image.isNull()) {
		QMessageBox::warning(this, "Load Error", tr("Can't load file: %1").arg(reader.errorString()));
		return false;
	}
	return true;
}

void _::setImage(const QImage &newImage) {
	image = newImage;
	imageLabel->setPixmap(QPixmap::fromImage(image));
	imageLabel->adjustSize();
}

void _::runLua(const char* filename) {
	puts("running lua");
	puts(filename);
	Lua L {};
	L.openLibs();
	int status = L.loadFile(filename);
	if (status) {
		puts("error loading lua");
		return;
	}
	status = L.run();
	if (status) {
		puts("error running lua");
		return;
	}
	L.processImage(&image, &image);
	setImage(image);
}

void _::onRun() {
	auto dialog = share->fileDialog();
	dialog->setFileMode(QFileDialog::ExistingFile);
	dialog->setAcceptMode(QFileDialog::AcceptOpen);
	if (dialog->exec() != QDialog::Accepted) return;
	runLua(dialog->selectedFiles().first().toUtf8().data());
}
