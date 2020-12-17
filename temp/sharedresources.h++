// Automatically generated header file~!
#include <QApplication>
#include <QClipboard>
#include "temp/filedialog.h++"
class SharedResources {private:
FileDialog* _fileDialog = NULL;
public:
QApplication* app;
QClipboard* clipboard;
	SharedResources();
	FileDialog* fileDialog();
	QImage* getClipboardImage();
	void setClipboardImage(QImage* image);
};
