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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QGridLayout>
#include <QApplication>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QToolTip>
#include <QVBoxLayout>
#include <vector>
#include <QToolBar>
#include <QMenu>
#include <QMenuBar>
#include <QTableView>
#include <QStandardItemModel>
#include <QList>
#include <QStackedWidget>
#include <QCheckBox>
#include <QFormLayout>
#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QLocale>
#include <QTextStream>
#include <QSettings>
#include <QVariant>
#include <QWidgetAction>
#include <QTranslator>
#define q2c(string) string.toStdString()

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectpageBuildup();
    void connectpageCleanup();
    void connectpageRebuild();
    void mainpageBuildup();
    void customreqBuildup();
    void customreqCleanup();
    void customreqRebuild();
    void extractTables();
    void createTableBox();
    void createFieldBox();
    void mode1Buildup();
    void mode1Cleanup();
    void mode1Rebuild();
    QString prepareQuery1();
    QString prepareQuery1bis();
    void mode2Buildup();
    void mode2Cleanup();
    void mode2Rebuild();
    void mode3Buildup();
    void mode3Cleanup();
    void mode3Rebuild();

public slots:
    void connection();  
    void customQuery();
    void selectMode();
    void execReq1();
    void makeInter();
    void selectField(QString activeTable);
    void insertSelection();
    void insert();
    void req3execute();
    void charger();
    void save();
    void changeLang();
    void translate();
private:
    /*---misc---*/
    QMenu *menu1;
    QToolBar *mainMenu;
    QTableView *tableDisplay;
    QStandardItemModel *model;
    QAction *ouvrir;
    QAction *sauvegarder;
    /*--- TABLES INFO ---*/
    std::vector<string> tableNames;
    QGridLayout *mainLayout;
    /*--- FIELD INFO ---*/
    std::vector<string> fieldNames;
    /*--- CONNECT PAGE ---*/
    QPushButton *connector;
    QLabel *portDesc;
    QLineEdit *portText;
    QLabel *hostDesc;
    QLineEdit *hostText;
    QLabel *userDesc;
    QLineEdit *userText;
    QLabel *pwdDesc;
    QLineEdit *pwdText;
    QLabel *nameDesc;
    QLineEdit *nameText;
    int port = 3306;
    QString host = "localhost";
    QString user = "root";
    QString pwd = "root";
    QString name = "auchan";
    /*--- CUSTOMREQ PAGE ---*/
    QComboBox *reqSelect;
    QLabel *reqDesc;
    QLabel *tableDesc;
    QLabel *customReqDesc;
    QLineEdit *customReq;
    QPushButton *customExec;
    /*--- REQ1 ---*/
    QString filtertype = "=";
    QLabel *MP1tableDesc;
    QComboBox *tableSelect;
    QComboBox *fieldSelect = new QComboBox;
    QLineEdit *value;
    QComboBox *filter1;
    QComboBox *exactBox;
    QCheckBox *borderBox;
    QLineEdit *lowvalue;
    QLabel *lowvalueDesc;
    QLineEdit *highvalue;
    QLabel *highvalueDesc;
    QPushButton *recherche1;
    QLabel *mod1TableDesc;
    /*--- REQ2 ---*/
    QFormLayout *approvisionnementLayout;
    QFormLayout *clientsLayout;
    QFormLayout *commandesLayout;
    QFormLayout *details_commandesLayout;
    QFormLayout *employesLayout;
    QFormLayout *fournisseursLayout;
    QFormLayout *magasinsLayout;
    QFormLayout *produitsLayout;
    QFormLayout *stocksLayout;
    QWidget *approvisionnementWidget;
    QWidget *clientsWidget;
    QWidget *commandesWidget;
    QWidget *details_commandeWidget;
    QWidget *employesWidget;
    QWidget *fournisseursWidget;
    QWidget *magasinsWidget;
    QWidget *produitsWidget;
    QWidget *stocksWidget;
    QPushButton *req2exec;
    QWidget *req2Widget;
    QVBoxLayout *req2Layout;
        /* --- Clients Insert --- */
        QLabel *DescclientInsertID;
        QLabel *DescclientInsertNOM;
        QLabel *DescclientInsertDATE_NAISSANCE;
        QLabel *DescclientInsertEMAIL;
        QLabel *DescclientInsertTELEPHONE;
        QLabel *DescclientInsertADRESSE;
        QLabel *DescclientInsertCP;
        QLabel *DescclientInsertPAYS;
        QLabel *DescclientInsertDATE_INSCRIPTION;
        QLabel *DescclientInsertCARTE_FIDELITE;
        QLineEdit *InclientInsertID;
        QLineEdit *InclientInsertNOM;
        QLineEdit *InclientInsertDATE_NAISSANCE;
        QLineEdit *InclientInsertEMAIL;
        QLineEdit *InclientInsertTELEPHONE;
        QLineEdit *InclientInsertADRESSE;
        QLineEdit *InclientInsertCP;
        QLineEdit *InclientInsertPAYS;
        QLineEdit *InclientInsertDATE_INSCRIPTION;
        QLineEdit *InclientInsertCARTE_FIDELITE;
        /* --- Magasins Insert --- */
        QLabel *DescmagasinsInsertID;
        QLabel *DescmagasinsInsertADRESSE;
        QLabel *DescmagasinsInsertCP;
        QLabel *DescmagasinsInsertTELEPHONE;
        QLabel *DescmagasinsInsertPAYS;
        QLabel *DescmagasinsInsertDATE_OUVERTURE;
        QLineEdit *InmagasinsInsertID;
        QLineEdit *InmagasinsInsertADRESSE;
        QLineEdit *InmagasinsInsertCP;
        QLineEdit *InmagasinsInsertTELEPHONE;
        QLineEdit *InmagasinsInsertPAYS;
        QLineEdit *InmagasinsInsertDATE_OUVERTURE;
        /* --- Fournisseurs Insert --- */
        QLabel *DescfournisseursInsertID;
        QLabel *DescfournisseursInsertNOM;
        QLabel *DescfournisseursInsertTELEPHONE;
        QLabel *DescfournisseursInsertADRESSE;
        QLabel *DescfournisseursInsertCP;
        QLabel *DescfournisseursInsertPAYS;
        QLineEdit *InfournisseursInsertID;
        QLineEdit *InfournisseursInsertNOM;
        QLineEdit *InfournisseursInsertTELEPHONE;
        QLineEdit *InfournisseursInsertADRESSE;
        QLineEdit *InfournisseursInsertCP;
        QLineEdit *InfournisseursInsertPAYS;
        /* --- PRODUITS INSERT --- */
        QLabel *DescproduitsInsertID;
        QLabel *DescproduitsInsertNOM;
        QLabel *DescproduitsInsertCATEGORIE;
        QLabel *DescproduitsInsertDESCRIPTION;
        QLabel *DescproduitsInsertPRIX_UNITAIRE;
        QLineEdit *InproduitsInsertID;
        QLineEdit *InproduitsInsertNOM;
        QLineEdit *InproduitsInsertCATEGORIE;
        QLineEdit *InproduitsInsertDESCRIPTION;
        QLineEdit *InproduitsInsertPRIX_UNITAIRE;
        /* --- STOCKS INSERT --- */
        QLabel *DescstocksInsertIDPROD;
        QLabel *DescstocksInsertIDMAG;
        QLabel *DescstocksInsertQTREST;
        QComboBox *InstocksIDPROD;
        QComboBox *InstocksInsertIDMAG;
        QLineEdit *InstocksInsertQTREST;
        /* --- DETAILS COMMANDE INSERT --- */
        QLabel *DescdetailsCommandesInsertIDCOMM;
        QLabel *DescdetailsCommandesInsertIDPROD;
        QLabel *DescdetailsCommandesInsertQTE;
        QComboBox *IndetailsCommandesInsertIDCOMM;
        QComboBox *IndetailsCommandesInsertIDPROD;
        QLineEdit *InetailsCommandesInsertQTE;
        /* --- APPROVISIONNEMENT INSERT --- */
        QLabel *DescapprovisionnementInsertNUMMAG;
        QLabel *DescapprovisionnementInsertNUMPROD;
        QLabel *DescapprovisionnementInsertNUMFOURN;
        QLabel *DescapprovisionnementInsertDATE;
        QLabel *DescapprovisionnementInsertQTE;
        QLabel *DescapprovisionnementInsertPRIXAU;
        QComboBox *InapprovisionnementInsertNUMMAG;
        QComboBox *InapprovisionnementInsertNUMPROD;
        QComboBox *InapprovisionnementInsertNUMFOURN;
        QLineEdit *InapprovisionnementInsertDATE;
        QLineEdit *InapprovisionnementInsertQTE;
        QLineEdit *InapprovisionnementInsertPRIXAU;
        /*--- EMPLOYES INSERT --- */
        QLabel *DescemployesInsertID;
        QLabel *DescemployesInsertNOM;
        QLabel *DescemployesInsertDATENAIS;
        QLabel *DescemployesInsertEMAIL;
        QLabel *DescemployesInsertTELEPHONE;
        QLabel *DescemployesInsertADRESSE;
        QLabel *DescemployesInsertCP;
        QLabel *DescemployesInsertPAYS;
        QLabel *DescemployesInsertDATEREC;
        QLabel *DescemployesInsertSALAIRE;
        QLabel *DescemployesInsertTITRE;
        QLabel *DescemployesInsertIDMAG;
        QLineEdit *InemployesInsertID;
        QLineEdit *InemployesInsertNOM;
        QLineEdit *InemployesInsertDATENAIS;
        QLineEdit *InemployesInsertEMAIL;
        QLineEdit *InemployesInsertTELEPHONE;
        QLineEdit *InemployesInsertADRESSE;
        QLineEdit *InemployesInsertCP;
        QLineEdit *InemployesInsertPAYS;
        QLineEdit *InemployesInsertDATEREC;
        QLineEdit *InemployesInsertSALAIRE;
        QLineEdit *InemployesInsertTITRE;
        QComboBox *InemployesInsertIDMAG;
        /* --- COMMANDES INSERT --- */
        QLabel *DesccommandesInsertID;
        QLabel *DesccommandesInsertIDCLIENT;
        QLabel *DesccommandesInsertIDMAG;
        QLabel *DesccommandesInsertDATE_COMM;
        QLabel *DesccommandesInsertEMPLOYERES;
        QLabel *DesccommandesInsertMODE_PAI;
        QLineEdit *IncommandesInsertID;
        QComboBox *IncommandesInsertIDCLIENT;
        QComboBox *IncommandesInsertIDMAG;
        QLineEdit *IncommandesInsertDATE_COMM;
        QComboBox *IncommandesInsertEMPLOYERES;
        QLineEdit *IncommandesInsertMODE_PAI;
    /* --- MODE 3 --- */
    QFormLayout *req3Layout;
    QLabel *req3Desc1;
    QLabel *req3Desc2;
    QLineEdit *req3ID;
    QPushButton *req3Exec;
    QWidget *req3Widget;
    /* --- TRAD --- */
    QSettings *settings;
    QMenu *langSelect;
    QComboBox *langBox;





};

#endif // MAINWINDOW_H
