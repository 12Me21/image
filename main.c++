#include <stdio.h>
#include "temp/window.h++"
#include "timer.h++"

int main(int argc, char** argv) {
	timer();
	auto app = new QApplication(argc, argv);
	timer("App created");

	SharedResources shared;
	shared.app = app;
	
	timer();
	MyWindow window {&shared};
	timer("Initial window created");

	timer();
	window.show();
	timer("initial window shown");
	
	return shared.app->exec();
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
