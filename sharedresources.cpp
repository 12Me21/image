#define _ SharedResources
#include "_sharedresources.h"
#include "timer.hpp"
#if 0////////////////////////////////////////////////
#include <QApplication>
#include <QClipboard>
#include "_filedialog.h"
class SharedResources {
private:
	FileDialog* _fileDialog = NULL;
public:
	QApplication* app;
	QClipboard* clipboard;
};
#endif///////////////////////////////////////////////

_::SharedResources(): clipboard {QGuiApplication::clipboard()} {
}

FileDialog* _::fileDialog() {
	if (_fileDialog)
		return _fileDialog;
	return _fileDialog = new FileDialog();
}

QImage* _::getClipboardImage() {
	
	if (auto mimeData = clipboard->mimeData()) {
		if (mimeData->hasImage()) {
			auto a = mimeData->imageData(); //<- this is the only slow part
			auto b = qvariant_cast<QImage>(a);
			auto x = new QImage(b);
			return x;
		}
	}
	return NULL;
}

void _::setClipboardImage(QImage* image) {
	clipboard->setImage(*image);
}
