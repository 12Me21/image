#include "header.hpp"
;

/*void setImage(QImage& newImage) {
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
	}*/

/*static int lf_mapAll(lua_State* L) {
	int n = lua_gettop(L);   
	if (n != 1) {
		lua_pushliteral(L, "incorrect arguments");
		lua_error(L);
	}
	return 0;
}*/


MyWindow::MyWindow() : clipboard {QGuiApplication::clipboard()} {
	//fileDialog = new QFileDialog(this);
	scrollArea = new QScrollArea();
	imageLabel = new QLabel();
	
	scrollArea->setBackgroundRole(QPalette::Dark);
	setCentralWidget(scrollArea);
	
	imageLabel->setBackgroundRole(QPalette::Base);
	imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	imageLabel->setScaledContents(true);
	scrollArea->setWidget(imageLabel);

	fileMenu = menuBar()->addMenu(tr("&File"));
	openAct = fileMenu->addAction(tr("&Open..."), this, &MyWindow::onOpen);
	openAct->setShortcut(tr("Ctrl+O"));
	saveAsAct = fileMenu->addAction(tr("&Save As..."), this, &MyWindow::onSaveAs);
	saveAsAct->setShortcut(tr("Ctrl+S"));

	fileMenu->addSeparator();
	copyAct = fileMenu->addAction(tr("&Copy"), this, &MyWindow::onCopy);
	copyAct->setShortcut(tr("Ctrl+C"));
	pasteAct = fileMenu->addAction(tr("&Paste"), this, &MyWindow::onPaste);
	pasteAct->setShortcut(tr("Ctrl+V"));

	fileMenu->addSeparator();
	windowAct = fileMenu->addAction(tr("&Window"), this, &MyWindow::onWindow);
	windowAct->setShortcut(tr("Ctrl+N"));
}

void MyWindow::onWindow() {
	using namespace std;
	using namespace chrono;
	auto start = high_resolution_clock::now(); 
	auto x = new MyWindow();
	x->show();
	auto duration = duration_cast<microseconds>(high_resolution_clock::now() - start); 
	cout << duration.count() << endl; 
}

void MyWindow::onSaveAs() {
	fileDialog->setFileMode(QFileDialog::AnyFile);
	fileDialog->setAcceptMode(QFileDialog::AcceptSave);
	if (fileDialog->exec() != QDialog::Accepted) return;
	saveAsFile(fileDialog->selectedFiles().first());
}

void MyWindow::onOpen() {
	fileDialog->setFileMode(QFileDialog::ExistingFile);
	fileDialog->setAcceptMode(QFileDialog::AcceptOpen);
	if (fileDialog->exec() != QDialog::Accepted) return;
	loadFile(fileDialog->selectedFiles().first());
}

void MyWindow::onCopy() {
	clipboard->setImage(image);
}

void MyWindow::onPaste() {
	if (const QMimeData* mimeData = clipboard->mimeData())
		if (mimeData->hasImage())
			setImage(qvariant_cast<QImage>(mimeData->imageData()));
}


bool MyWindow::saveAsFile(const QString name) {
	QImageWriter writer {name};
	if (!writer.write(image)) {
		QMessageBox::warning(this, "Save Error", tr("Can't save file: %1").arg(writer.errorString()));
		return false;
	}
	return true;
}
bool MyWindow::loadFile(const QString name) {
	QImageReader reader {name};
	reader.setAutoTransform(true); //handle rotation metadata
	setImage(reader.read());
	if (image.isNull()) {
		QMessageBox::warning(this, "Load Error", tr("Can't load file: %1").arg(reader.errorString()));
		return false;
	}
	return true;
}

void MyWindow::setImage(const QImage &newImage) {
	image = newImage;
	imageLabel->setPixmap(QPixmap::fromImage(image));
	imageLabel->adjustSize();
}

int main(int argc, char** argv) {
	puts("1");
	QApplication app {argc, argv};
	puts("2");
	MyWindow window {};
	puts("3");
	window.show(); //snow
	puts("4");
	puts("6");
	//exit(0);
	return app.exec();
	/*
	loadFile(argv[1]);

	QFileSystemWatcher watcher;
	watcher.addPath(argv[2]);
	QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, [](const QString& path) {
			runLua(path.toUtf8().data());
			setImage(*image);
		});
	
	runLua(argv[2]);
	
	setImage(*image);

	*/
}
