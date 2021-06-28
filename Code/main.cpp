#include <launcher.h>


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;

    Launcher launcher(window);
    launcher.launch();

    window.show();
    return app.exec();
}
