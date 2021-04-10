#include "textfinder.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    TextFinder textFinder;
    textFinder.show();

    return app.exec();
}
