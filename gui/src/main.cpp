#include "./mainwindow.cpp"

#include <iostream>

class UIMainWindow : public Ui_MainWindow {
      public:
	void init() {
	}
};

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	auto MainWindow = QMainWindow();

	auto ui         = UIMainWindow();
	ui.setupUi(&MainWindow);
	ui.init();

	MainWindow.show();

	app.exec();

	return 0;
}
