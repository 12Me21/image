#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QClipboard>
#include <QScrollArea>
#include <QImageReader>
#include <stdio.h>

QScrollArea* scroll;
QLabel* label;
QMainWindow* window;

void setImage(const QImage &image) {
	label->setPixmap(QPixmap::fromImage(image));
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
	setImage(image);
	return true;
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
	
	window->show();
	return app.exec();
}
