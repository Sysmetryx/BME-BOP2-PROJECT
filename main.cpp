/*
___________________________________________________________________________________________________________________________________________________________________________________________________________________
|
|       EEEEEE       sSSSS  MM       MM     EEEEEE                      LAPORTE Nathan 2Z2                          V0.1                                EEEEEE       sSSSS  MM       MM     EEEEEE
|       EE         sS       MMMM   MMMM     EE                          laporte_n@esme.fr                           DECEMBRE 2017                       EE         sS       MMMM   MMMM     EE
|       EEEEE       sSS     MM  MM   MM     EEEEEE                      https://github.com/Sysmetryx/               PROJET IHM-BDD                      EEEEE       sSS     MM  MM   MM     EEEEEE
|       EE            Ss    MM       MM     EE                                                                      GUI/SQL                             EE            Ss    MM       MM     EE
|       EEEEE    SSSSs      MM       MM     EEEEEE                                                                  IHM sous Qt5 // BDD avec MySQL      EEEEE    SSSSs      MM       MM     EEEEEE
|_____________________________________________________________________________________________________________________________________________________________________________________________________________________

*/
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSettings settings("SysSoftware", "Data Surveyor");
    QVariant v = settings.value("lang");
    QApplication::setOrganizationName("SysSoftware");
    QApplication::setOrganizationDomain("https://github.com/Sysmetryx/ESME-PROJET-IHM-BDD");
    QApplication::setApplicationDisplayName("Data Surveyor");
    QApplication::setApplicationName("Data Surveyor");
    QApplication::setApplicationVersion("1.0");
    QTranslator translator;
    if(settings.value("lang") == "French")
    {

    }
    else if(settings.value("lang") == "English")
    {
        if(translator.load("english_EN.qm"))
        {
            a.installTranslator(&translator);
        }
    }
    MainWindow w;
    w.show();

    return a.exec();
}
