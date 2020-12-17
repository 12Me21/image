// Automatically generated header file~!
#include <QFileDialog>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
class FileDialog:  QFileDialog {public:
	bool saveImage(const QImage* image);
	QImage* loadImage();
	QString selectScript();
};
