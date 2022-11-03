#include "Lab13.h"
#include "Gui.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    Lab13 w;
    MedicamentRepository repo;

    MedicamentValidator val;
    MedicamentStore srv{ repo,val };
    Gui gui{ srv };
    gui.show();
    return a.exec();
}
