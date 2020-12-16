#define _ FileDialog
#include "_filedialog.h"
#if 0
#include <QFileDialog>
#include <QImage>
#include <QImageReader>
#include <QImageWriter>
#include <QMessageBox>
class FileDialog: QFileDialog {
public:
};
#endif///////////////////////////////////////////////

bool _::saveImage(const QImage* image) {
	setFileMode(_::AnyFile);
	setAcceptMode(_::AcceptSave);
	if (exec() != _::Accepted) return false;
	auto name = selectedFiles().first();
	// this should probably check if name is empty too
	if (!name.contains("."))
		name += ".png";
	QImageWriter writer {name};
	if (!writer.write(*image)) {
		QMessageBox::warning(this, "Save Error", tr("Can't save file: %1").arg(writer.errorString()));
		return false;
	}
	return true;
}

QImage* _::loadImage() {
	setFileMode(_::ExistingFile);
	setAcceptMode(_::AcceptOpen);
	if (exec() != _::Accepted) return NULL;
	QImageReader reader {selectedFiles().first()};
	reader.setAutoTransform(true); //handle rotation metadata
	auto image = reader.read();
	if (image.isNull()) {
		QMessageBox::warning(this, "Load Error", tr("Can't load file: %1").arg(reader.errorString()));
		return NULL;
	}
	return new QImage(image);
}

QString _::selectScript() {
	setFileMode(_::ExistingFile);
	setAcceptMode(_::AcceptOpen);
	setNameFilter(tr("Lua Script (*.lua)"));
	if (exec() != _::Accepted) return QString();
	return selectedFiles().first();
}
