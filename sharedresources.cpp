#define _ SharedResources
#include "_sharedresources.h"

#if 0
#include <QApplication>
class SharedResources {
private:
	QFileDialog* _fileDialog = NULL;
public:
	QApplication* app;
};
#endif

QFileDialog* _::fileDialog() {
	if (_fileDialog)
		return _fileDialog;
	return _fileDialog = new QFileDialog();
}
