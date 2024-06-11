#include <QApplication>
#include "Plotter.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Plotter plotter;
    plotter.show();

    return app.exec();
}
