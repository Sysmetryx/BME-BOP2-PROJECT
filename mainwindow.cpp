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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setBaseSize(1920,1080);
    settings = new QSettings;
    translate();
    mainLayout = new QGridLayout; //Layout principal sur lequel viennet se greffer les layouts secondaires
    connectpageBuildup(); //Construit la page de connexion
    this->setCentralWidget (new QWidget(this));
    this->centralWidget()->setLayout(mainLayout);
}

void MainWindow::connectpageBuildup()
{
    portDesc = new QLabel(); //Label qui décrit le port
    portDesc->setText(tr("Port :"));
    mainLayout->addWidget(portDesc, 0, 0, 1, 1);
    hostDesc = new QLabel();//Label qui décrit l'hôte
    hostDesc->setText(tr("Hote :"));
    mainLayout->addWidget(hostDesc, 1, 0, 1, 1);
    userDesc = new QLabel();//Label qui décrit l'utilisateur
    userDesc->setText(tr("Utilisateur :"));
    mainLayout->addWidget(userDesc, 2, 0, 1, 1);
    pwdDesc = new QLabel();//Label qui décrit le mot de passe
    pwdDesc->setText(tr("Mot de passe :"));
    mainLayout->addWidget(pwdDesc, 3, 0, 1, 1);
    nameDesc = new QLabel();//Label qui décrit le nom de la base
    nameDesc->setText(tr("Nom :"));
    mainLayout->addWidget(nameDesc, 4, 0, 1, 1);
    portText = new QLineEdit();
    mainLayout->addWidget(portText, 0, 1, 1, 1 );
    portText->setToolTip(tr("Entrez un numéro de port pour la connexion."));
    portText->setText(QString::number(port));
    hostText = new QLineEdit();
    hostText->setToolTip(tr("Entrez une adresse d'hote pour la connexion."));
    mainLayout->addWidget(hostText, 1, 1, 1, 1);
    hostText->setText(host);
    userText = new QLineEdit();
    userText->setToolTip(tr("Entrez un nom d'utilisateur pour la connexion."));
    mainLayout->addWidget(userText, 2, 1, 1, 1);
    userText->setText(user);
    pwdText = new QLineEdit();
    pwdText->setToolTip(tr("Entrez un mot de passe pour la connexion."));
    mainLayout->addWidget(pwdText, 3, 1, 1, 1);
    pwdText->setText(pwd);
    pwdText->setEchoMode(QLineEdit::Password);
    nameText = new QLineEdit();
    nameText->setToolTip(tr("Entrez un nom pour la base de données."));
    mainLayout->addWidget(nameText, 4, 1, 1, 1);
    nameText->setText(name);
    connector = new QPushButton(tr("Connexion"), this);
    connect(connector, &QPushButton::clicked, this, &MainWindow::connection);
    mainLayout->addWidget(connector, 5, 3, 1, 1);
}
void MainWindow::connectpageCleanup()
{
    connector->hide();
    portDesc->hide();
    portText->hide();
    hostDesc->hide();
    hostText->hide();
    userDesc->hide();
    userText->hide();
    pwdDesc->hide();
    pwdText->hide();
    nameDesc->hide();
    nameText->hide();
}
void MainWindow::connectpageRebuild()
{
    connector->show();
    portDesc->show();
    portText->show();
    hostDesc->show();
    hostText->show();
    userDesc->show();
    userText->show();
    pwdDesc->show();
    pwdText->show();
    nameDesc->show();
    nameText->show();
}
void MainWindow::connection()
{
    bool check = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    host = hostText->text();
    user = userText->text();
    port = portText->text().toInt(&check, 10);
    pwd = pwdText->text();
    name = nameText->text();
    db.setPort(port);
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(pwd);
    db.setDatabaseName(name);
    if(db.open())
    {
         QMessageBox::about(this, tr("Connexion Réussie"), tr("Vous êtes maintenant connecté"));
         connectpageCleanup();
         mainpageBuildup();
    }
    else
    {
         QMessageBox::about(this, tr("Connexion échouée"), tr("La connexion a échoué"));
    }
}


MainWindow::~MainWindow()
{

}

void MainWindow::mainpageBuildup()
{
    mode1Buildup();
    mode2Buildup();
    mode3Buildup();
    tableSelect->show();
    mainMenu = new QToolBar();
    menu1 = this->menuBar()->addMenu(tr("Fichier"));
    ouvrir = new QAction(tr("Ouvrir"), this);
    connect(ouvrir, SIGNAL(triggered()), this, SLOT(charger()));
    ouvrir->setShortcut(QKeySequence("Ctrl+L"));
    ouvrir->setIcon(QIcon("ouvrir.png"));
    ouvrir->setToolTip(tr("Ouvrir un script .txt"));
    menu1->addAction(ouvrir);
    sauvegarder = new QAction(tr("Sauvegarder"), this);
    connect(sauvegarder, SIGNAL(triggered()), this, SLOT(save()));
    sauvegarder->setShortcut(QKeySequence("Ctrl+S"));
    sauvegarder->setToolTip(tr("Sauvegarder le resultat d'une requête"));
    sauvegarder->setIcon(QIcon("sauvegarder.png"));
    menu1->addAction(sauvegarder);
    QAction *quitter = new QAction(tr("Quitter"), this);
    connect(quitter, SIGNAL(triggered()), this, SLOT(close()));
    quitter->setShortcut(QKeySequence("Ctrl+Q"));
    quitter->setToolTip(tr("Quitter le programme"));
    quitter->setIcon(QIcon("quitter.png"));
    menu1->addAction(quitter);
    langSelect = this->menuBar()->addMenu(tr("Langue"));
    langBox = new QComboBox(langSelect);
    langBox->addItem(tr("Français"));
    langBox->addItem(tr("Anglais"));
    QWidgetAction *langSetter = new QWidgetAction(langSelect);
    langSetter->setDefaultWidget(langBox);
    langSelect->addAction(langSetter);
    if(settings->value("lang").toString() == "French")
    {
        langBox->setCurrentIndex(0);
    }
    else if(settings->value("lang").toString() != "French")
    {
        langBox->setCurrentIndex(1);
    }
    connect(langBox, SIGNAL(currentTextChanged(QString)), this, SLOT(changeLang()));
    reqDesc = new QLabel(tr("Choisissez une requête :"));
    mainLayout->addWidget(reqDesc,0,0,1,1,Qt::AlignLeft);
    reqSelect = new QComboBox();
    reqSelect->addItem(tr("Recherche par filtre"));
    reqSelect->addItem(tr("Insertion de données"));
    reqSelect->addItem(tr("Informations Client"));
    connect(reqSelect, SIGNAL(currentTextChanged(QString)), this, SLOT(selectMode()));
    mainLayout->addWidget(reqSelect,1,0,1,1,Qt::AlignLeft);
    customreqBuildup();

}

void MainWindow::selectMode()
{
    if(reqSelect->currentText() == tr("Recherche par filtre"))
    {
        mode3Cleanup();
        mode2Cleanup();
        mode1Rebuild();
    }
    else if(reqSelect->currentText() == tr("Insertion de données"))
    {
        mode3Cleanup();
        mode1Cleanup();
        mode2Rebuild();
    }
    else if(reqSelect->currentText() == tr("Informations Client"))
    {
        mode1Cleanup();
        mode2Cleanup();
        mode3Rebuild();
    }

}

void MainWindow::mode1Buildup()
{
    extractTables();
    mod1TableDesc = new QLabel(tr("Cette requête a pour but \n de filtrer la table choisie \n avec ce paramètre :"));
    mainLayout->addWidget(mod1TableDesc,3,0,1,1,Qt::AlignLeft);
    QSqlQuery query;
    QString query01 = "SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE (TABLE_SCHEMA='";
    query01.append(name);
    query01.append("' AND TABLE_NAME='approvisionnement');");
    if(query.exec(query01))
    {
        while(query.next())
        {
            fieldNames.push_back(q2c(query.value(0).toString()));
        }
        createFieldBox();
    }
    else
    {
        QMessageBox::about(this, tr("Tables non récupérées"), tr("La récupération des tables a échouée"));
    }
    exactBox = new QComboBox;
    exactBox->addItem(tr("Contient"));
    exactBox->addItem(tr("Commence par"));
    exactBox->addItem(tr("fini par"));
    exactBox->addItem(tr("Condition"));
    mainLayout->addWidget(exactBox, 5,0,1,1,Qt::AlignLeft);
    filter1 = new QComboBox;
    filter1->addItem("=");
    filter1->addItem("<=");
    filter1->addItem(">=");
    filter1->addItem("<");
    filter1->addItem(">");
    mainLayout->addWidget(filter1,6,0,1,1,Qt::AlignLeft);
    value = new QLineEdit();
    mainLayout->addWidget(value,7,0,1,1,Qt::AlignLeft);
    borderBox = new QCheckBox(tr("Cochez pour avoir une valeur \n comprise dans un ensemble"), this);
    connect(borderBox, SIGNAL(clicked(bool)), this, SLOT(makeInter()));
    mainLayout->addWidget(borderBox, 8,0,1,1,Qt::AlignLeft);
    lowvalueDesc = new QLabel(tr("Entrez la valeur minimum"));
    mainLayout->addWidget(lowvalueDesc, 9,0,1,1,Qt::AlignLeft);
    lowvalueDesc->hide();
    lowvalue = new QLineEdit();
    mainLayout->addWidget(lowvalue, 10,0,1,1,Qt::AlignLeft);
    lowvalue->hide();
    highvalueDesc = new QLabel(tr("Entrez la valeur maximum"));
    mainLayout->addWidget(highvalueDesc, 11,0,1,1,Qt::AlignLeft);
    highvalueDesc->hide();
    highvalue = new QLineEdit();
    mainLayout->addWidget(highvalue, 12,0,1,1,Qt::AlignLeft);
    highvalue->hide();
    recherche1 = new QPushButton(tr("recherche"));
    connect(recherche1, SIGNAL(clicked(bool)), this, SLOT(execReq1()));
    mainLayout->addWidget(recherche1,13,0,1,1,Qt::AlignLeft);


}

void MainWindow::mode1Cleanup()
{
    mod1TableDesc->hide();
    fieldSelect->hide();
    value->hide();
    filter1->hide();
    exactBox->hide();
    borderBox->hide();
    lowvalue->hide();
    highvalue->hide();
    recherche1->hide();
    highvalueDesc->hide();
    lowvalueDesc->hide();
    tableSelect->disconnect();
}

void MainWindow::mode1Rebuild()
{

    mod1TableDesc->show();
    fieldSelect->show();
    value->show();
    filter1->show();
    exactBox->show();
    borderBox->show();
    borderBox->setChecked(false);
    recherche1->show();
    connect(tableSelect, SIGNAL(currentTextChanged(QString)), this, SLOT(selectField(QString)));
}

void MainWindow::customreqBuildup()
{
    customReqDesc = new QLabel(tr("Requete speciale (MySQL)"));
    mainLayout->addWidget(customReqDesc, 0,1,1,1,Qt::AlignTop);
    customReq = new QLineEdit();
    mainLayout->addWidget(customReq, 1,1,1,25,Qt::AlignTop);
    customExec = new QPushButton(tr("Executer"));
    connect(customExec, SIGNAL(clicked(bool)), this, SLOT(customQuery()));
    mainLayout->addWidget(customExec, 2,15,1,1,Qt::AlignTop);
}

void MainWindow::customreqCleanup()
{
    reqSelect->hide();
    reqDesc->hide();
    customReqDesc->hide();
    customReq->hide();
    customExec->hide();
}

void MainWindow::customreqRebuild()
{
    reqSelect->show();
    reqDesc->show();
    customReqDesc->show();
    customReq->show();
    customExec->show();
}

void MainWindow::extractTables()
{
    QSqlQuery query;
    QString reqFull = "SELECT TABLE_NAME FROM INFORMATION_SCHEMA.TABLES WHERE(table_schema='";
    reqFull.append(name);
    reqFull.append("');");
    if(query.exec(reqFull))
    {
        while(query.next())
        {
            tableNames.push_back(q2c(query.value(0).toString()));
        }
        createTableBox();
    }
    else
    {
        QMessageBox::about(this, tr("Tables non récupérées"), tr("La récupération des tables a échouée"));
    }
}

void MainWindow::selectField(QString activeTable)
{
    for(int i = 0; i < tableNames.size(); i++)
    {
        if(activeTable == QString::fromStdString(tableNames[i]))
        {
            QSqlQuery query;
            QString para1 = name;
            QString para2 = activeTable;
            QString reqFull = para1.prepend("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS WHERE (TABLE_SCHEMA='").append("' AND TABLE_NAME='").append(para2).append("')");
            if(query.exec(reqFull))
            {
                fieldNames.clear();
                while(query.next())
                {

                   fieldNames.push_back(q2c(query.value(0).toString()));

                }
                for(int i = 0; i < fieldSelect->count(); i++)
                    fieldSelect->removeItem(i);
                createFieldBox();
            }
            else
            {
                QMessageBox::about(this, tr("Champs non récupérées"), tr("La récupération des champs a échouée, \n aucune table avec ce nom !"));
            }
        }
        else
        {

        }
    }
}


void MainWindow::createFieldBox()
{
    fieldSelect->clear();
    for(int i =0; i < fieldNames.size(); i++)
    {
        QString temp = QString::fromStdString(fieldNames[i]);
        fieldSelect->addItem(temp);
    }
    mainLayout->addWidget(fieldSelect, 4,0,1,1,Qt::AlignLeft);
}

void MainWindow::createTableBox()
{
    tableSelect = new QComboBox();
    for(int i = 0; i < tableNames.size(); i++)
    {
        QString temp = QString::fromStdString(tableNames[i]);
        tableSelect->addItem(temp);
    }
    connect(tableSelect, SIGNAL(currentTextChanged(QString)), this, SLOT(selectField(QString)));
    mainLayout->addWidget(tableSelect, 2,0,1,1,Qt::AlignLeft);
    tableSelect->show();
}

void MainWindow::customQuery()
{
    QSqlQuery query;
    QString sqlQuery = customReq->text();
    bool firstTime = true;
    int rows = 0;
    int columns = 0;
    QStandardItem *element;
    model = new QStandardItemModel(1,columns,this);
    if(query.exec(sqlQuery))
    {
        columns = query.record().count();
        while(query.next())
        {
            for(int i = 0; i < columns; i++)
            {
                if(firstTime)
                {
                    model->setHeaderData(i, Qt::Horizontal, query.record().fieldName(i));
                }
                element = new QStandardItem(query.value(i).toString());
                element->setEditable(false);
                model->setItem(rows,i,element);
            }
         rows++;
        }
    }
    customReq->clear();
    customExec->setStyleSheet("background-color: ;");
    tableDisplay = new QTableView();
    tableDisplay->setModel(model);
    tableDisplay->setSortingEnabled(true);
    mainLayout->addWidget(tableDisplay, 3,1,25,25);
}


void MainWindow::execReq1()
{
    QString queryText;
    if(!borderBox->isChecked())
    {
        queryText = prepareQuery1();
    }
    else
    {
        queryText = prepareQuery1bis();
    }
    //QMessageBox::about(this, "request :", queryText);
    QSqlQuery query;
    int rows = 0;
    int columns = fieldNames.size();
    QStandardItem *element;
    model = new QStandardItemModel(1,columns,this);
    for(int i =0; i < columns; i++)
        model->setHeaderData(i, Qt::Horizontal, QString::fromStdString(fieldNames[i]));
    if(query.exec(queryText))
    {
        while(query.next())
        {
            for(int j = 0; j < columns; j++)
            {
                element = new QStandardItem(query.value(j).toString());
                element->setEditable(false);
                model->setItem(rows,j,element);
            }
        rows++;
        }
    }
    tableDisplay = new QTableView();
    tableDisplay->setModel(model);
    tableDisplay->setSortingEnabled(true);
    mainLayout->addWidget(tableDisplay, 3,1,25,25);
}

QString MainWindow::prepareQuery1()
{
    QString tableUsed = tableSelect->currentText();
    QString queryPrepared;
    QString filterType;
    int type = exactBox->currentIndex();
    switch (type){
    case 0:
        tableUsed.prepend("SELECT * FROM ");
        tableUsed.append(" ");
        queryPrepared = tableUsed.append("WHERE(").append(fieldSelect->currentText()).append(" LIKE '%").append(value->text()).append("%')");
    break;
    case 1:
        tableUsed.prepend("SELECT * FROM ");
        tableUsed.append(" ");
        queryPrepared = tableUsed.append("WHERE(").append(fieldSelect->currentText()).append(" LIKE '").append(value->text()).append("%')");
    break;
    case 2:
        tableUsed.prepend("SELECT * FROM ");
        tableUsed.append(" ");
        queryPrepared = tableUsed.append("WHERE(").append(fieldSelect->currentText()).append(" LIKE '%").append(value->text()).append("')");
    break;
    case 3:
    filterType = filter1->currentText();
    tableUsed.prepend("SELECT * FROM ");
    tableUsed.append(" ");
    queryPrepared = tableUsed.append("WHERE(").append(fieldSelect->currentText()).append(" ").append(filterType).append(" '").append(value->text()).append("')");
    break;
    }
    return queryPrepared;
}

void MainWindow::makeInter()
{
    if(borderBox->isChecked())
    {
        value->hide();
        filter1->hide();
        exactBox->hide();
        lowvalueDesc->show();
        lowvalue->show();
        highvalueDesc->show();
        highvalue->show();
    }
    else
    {
        value->show();
        filter1->show();
        exactBox->show();
        lowvalueDesc->hide();
        lowvalue->hide();
        highvalueDesc->hide();
        highvalue->hide();
    }
}

QString MainWindow::prepareQuery1bis()
{
    QString tableUsed = tableSelect->currentText();
    QString queryPrepared;
    tableUsed.prepend("SELECT * FROM ");
    tableUsed.append(" ");
    queryPrepared = tableUsed.append("WHERE(").append(fieldSelect->currentText()).append(" <= '").append(highvalue->text()).append("' ").append("AND ").append(fieldSelect->currentText()).append(" >= '").append(lowvalue->text()).append("')");
    return queryPrepared;
}

void MainWindow::mode2Buildup()
{
    //connect(tableSelect, SIGNAL(currentTextChanged(QString)), this, SLOT(insertSelection()));
    req2Widget = new QWidget;
    req2exec = new QPushButton(tr("executer"));
    req2Layout = new QVBoxLayout;
    // CLIENTS //
    clientsLayout = new QFormLayout;
    clientsWidget = new QWidget;
    DescclientInsertID = new QLabel();
    DescclientInsertNOM = new QLabel();
    DescclientInsertDATE_NAISSANCE = new QLabel();
    DescclientInsertEMAIL = new QLabel();
    DescclientInsertTELEPHONE = new QLabel();
    DescclientInsertADRESSE = new QLabel();
    DescclientInsertCP = new QLabel();
    DescclientInsertPAYS = new QLabel();
    DescclientInsertDATE_INSCRIPTION = new QLabel();
    DescclientInsertCARTE_FIDELITE = new QLabel();
    DescclientInsertID->setText(tr("ID :"));
    DescclientInsertNOM->setText(tr("NOM :"));
    DescclientInsertDATE_NAISSANCE->setText(tr("DATE DE NAISSANCE :"));
    DescclientInsertEMAIL->setText("EMAIL :");
    DescclientInsertTELEPHONE->setText(tr("TELEPHONE :"));
    DescclientInsertADRESSE->setText(tr("ADRESSE :"));
    DescclientInsertCP->setText(tr("CODE POSTAL :"));
    DescclientInsertPAYS->setText(tr("PAYS :"));
    DescclientInsertDATE_INSCRIPTION->setText(tr("DATE D'INSCRIPTION :"));
    DescclientInsertCARTE_FIDELITE->setText(tr("CARTE DE FIDELITE :"));
    InclientInsertID = new QLineEdit();
    InclientInsertNOM = new QLineEdit();
    InclientInsertDATE_NAISSANCE = new QLineEdit();
    InclientInsertEMAIL = new QLineEdit();
    InclientInsertTELEPHONE = new QLineEdit();
    InclientInsertADRESSE = new QLineEdit();
    InclientInsertCP = new QLineEdit();
    InclientInsertPAYS = new QLineEdit();
    InclientInsertDATE_INSCRIPTION = new QLineEdit();
    InclientInsertCARTE_FIDELITE = new QLineEdit();
    clientsLayout->addRow(DescclientInsertID, InclientInsertID);
    clientsLayout->addRow(DescclientInsertNOM, InclientInsertNOM);
    clientsLayout->addRow(DescclientInsertDATE_NAISSANCE, InclientInsertDATE_NAISSANCE);
    clientsLayout->addRow(DescclientInsertEMAIL, InclientInsertEMAIL);
    clientsLayout->addRow(DescclientInsertTELEPHONE, InclientInsertTELEPHONE);
    clientsLayout->addRow(DescclientInsertADRESSE, InclientInsertADRESSE);
    clientsLayout->addRow(DescclientInsertCP, InclientInsertCP);
    clientsLayout->addRow(DescclientInsertPAYS, InclientInsertPAYS);
    clientsLayout->addRow(DescclientInsertDATE_INSCRIPTION, InclientInsertDATE_INSCRIPTION);
    clientsLayout->addRow(DescclientInsertCARTE_FIDELITE, InclientInsertCARTE_FIDELITE);
    clientsWidget->setLayout(clientsLayout);
    req2Layout->addWidget(clientsWidget, 1,Qt::AlignLeft);
    req2Widget->setLayout(req2Layout);
    clientsWidget->hide();
    //MAGASINS//
    magasinsLayout = new QFormLayout;
    magasinsWidget = new QWidget;
    DescmagasinsInsertID = new QLabel(tr("ID :"));
    DescmagasinsInsertADRESSE = new QLabel(tr("ADRESSE :"));
    DescmagasinsInsertCP = new QLabel(tr("CODE POSTAL :"));
    DescmagasinsInsertTELEPHONE = new QLabel(tr("TELEPHONE :"));
    DescmagasinsInsertPAYS = new QLabel(tr("PAYS :"));
    DescmagasinsInsertDATE_OUVERTURE = new QLabel(tr("DATE D'OUVERTERE :"));
    InmagasinsInsertID = new QLineEdit;
    InmagasinsInsertADRESSE = new QLineEdit;
    InmagasinsInsertCP = new QLineEdit;
    InmagasinsInsertTELEPHONE = new QLineEdit;
    InmagasinsInsertPAYS = new QLineEdit;
    InmagasinsInsertDATE_OUVERTURE = new QLineEdit;
    magasinsLayout->addRow(DescmagasinsInsertID,InmagasinsInsertID);
    magasinsLayout->addRow(DescmagasinsInsertADRESSE,InmagasinsInsertADRESSE);
    magasinsLayout->addRow(DescmagasinsInsertCP,InmagasinsInsertCP);
    magasinsLayout->addRow(DescmagasinsInsertTELEPHONE,InmagasinsInsertTELEPHONE);
    magasinsLayout->addRow(DescmagasinsInsertPAYS,InmagasinsInsertPAYS);
    magasinsLayout->addRow(DescmagasinsInsertDATE_OUVERTURE,InmagasinsInsertDATE_OUVERTURE);
    magasinsWidget->setLayout(magasinsLayout);
    req2Layout->addWidget(magasinsWidget, 1,Qt::AlignLeft);
    magasinsWidget->hide();
    //FOURNISSEURS//
    fournisseursLayout = new QFormLayout;
    fournisseursWidget = new QWidget;
    DescfournisseursInsertID = new QLabel(tr("ID :"));
    DescfournisseursInsertNOM = new QLabel(tr("NOM :"));
    DescfournisseursInsertTELEPHONE = new QLabel(tr("TELEPHONE :"));
    DescfournisseursInsertADRESSE = new QLabel(tr("ADRESSE :"));
    DescfournisseursInsertCP = new QLabel(tr("CODE POSTAL :"));
    DescfournisseursInsertPAYS = new QLabel(tr("PAYS :"));
    InfournisseursInsertID = new QLineEdit;
    InfournisseursInsertNOM = new QLineEdit;
    InfournisseursInsertTELEPHONE = new QLineEdit;
    InfournisseursInsertADRESSE = new QLineEdit;
    InfournisseursInsertCP = new QLineEdit;
    InfournisseursInsertPAYS = new QLineEdit;
    fournisseursLayout->addRow(DescfournisseursInsertID,InfournisseursInsertID);
    fournisseursLayout->addRow(DescfournisseursInsertNOM,InfournisseursInsertNOM);
    fournisseursLayout->addRow(DescfournisseursInsertTELEPHONE,InfournisseursInsertTELEPHONE);
    fournisseursLayout->addRow(DescfournisseursInsertADRESSE,InfournisseursInsertADRESSE);
    fournisseursLayout->addRow(DescfournisseursInsertCP,InfournisseursInsertCP);
    fournisseursLayout->addRow(DescfournisseursInsertPAYS,InfournisseursInsertPAYS);
    fournisseursWidget->setLayout(fournisseursLayout);
    req2Layout->addWidget(fournisseursWidget, 1,Qt::AlignLeft);
    fournisseursWidget->hide();
    //PRODUITS//
    produitsLayout = new QFormLayout;
    produitsWidget = new QWidget;
    DescproduitsInsertID = new QLabel(tr("ID :"));
    DescproduitsInsertNOM = new QLabel(tr("NOM :"));
    DescproduitsInsertCATEGORIE = new QLabel(tr("CATEGORIE :"));
    DescproduitsInsertDESCRIPTION = new QLabel(tr("DESCRIPTION :"));
    DescproduitsInsertPRIX_UNITAIRE = new QLabel(tr("PRIX UNITAIRE :"));
    InproduitsInsertID = new QLineEdit;
    InproduitsInsertNOM = new QLineEdit;
    InproduitsInsertCATEGORIE = new QLineEdit;
    InproduitsInsertDESCRIPTION = new QLineEdit;
    InproduitsInsertPRIX_UNITAIRE = new QLineEdit;
    produitsLayout->addRow(DescproduitsInsertID,InproduitsInsertID);
    produitsLayout->addRow(DescproduitsInsertNOM,InproduitsInsertNOM);
    produitsLayout->addRow(DescproduitsInsertCATEGORIE,InproduitsInsertCATEGORIE);
    produitsLayout->addRow(DescproduitsInsertDESCRIPTION,InproduitsInsertDESCRIPTION);
    produitsLayout->addRow(DescproduitsInsertPRIX_UNITAIRE,InproduitsInsertPRIX_UNITAIRE);
    produitsWidget->setLayout(produitsLayout);
    req2Layout->addWidget(produitsWidget, 1,Qt::AlignLeft);
    produitsWidget->hide();
    /* --- STOCKS INSERT --- */
    QSqlQuery queryStocks;
    stocksLayout = new QFormLayout;
    stocksWidget = new QWidget;
    DescstocksInsertIDPROD = new QLabel(tr("ID PRODUIT :"));
    DescstocksInsertIDMAG = new QLabel(tr("ID MAGASIN :"));
    DescstocksInsertQTREST = new QLabel(tr("QUANTITE RESTANTE :"));
    InstocksIDPROD = new QComboBox;
    if(queryStocks.exec("SELECT DISTINCT id FROM produits"))
    {
        while(queryStocks.next())
        {
            InstocksIDPROD->addItem(queryStocks.value(0).toString());
        }
    }
    else
    {

    }
    InstocksInsertIDMAG = new QComboBox;
    if(queryStocks.exec("SELECT DISTINCT id FROM magasins"))
    {
        while(queryStocks.next())
        {
            InstocksInsertIDMAG->addItem(queryStocks.value(0).toString());
        }
    }
    else
    {

    }
    InstocksInsertQTREST = new QLineEdit;
    stocksLayout->addRow(DescstocksInsertIDPROD,InstocksIDPROD);
    stocksLayout->addRow(DescstocksInsertIDMAG,InstocksInsertIDMAG);
    stocksLayout->addRow(DescstocksInsertQTREST,InstocksInsertQTREST);
    stocksWidget->setLayout(stocksLayout);
    req2Layout->addWidget(stocksWidget,1,Qt::AlignLeft);
    stocksWidget->hide();
    /* --- DETAILS COMMANDE INSERT --- */
    QSqlQuery queryDetails;
    details_commandesLayout = new QFormLayout;
    details_commandeWidget = new QWidget;
    DescdetailsCommandesInsertIDCOMM = new QLabel(tr("ID COMMANDE :"));
    DescdetailsCommandesInsertIDPROD = new QLabel(tr("ID PRODUIT :"));
    DescdetailsCommandesInsertQTE = new QLabel(tr("QUANTITE :"));
    IndetailsCommandesInsertIDCOMM = new QComboBox;
    if(queryDetails.exec("SELECT DISTINCT id FROM commandes"))
    {
        while(queryDetails.next())
        {
            IndetailsCommandesInsertIDCOMM->addItem(queryDetails.value(0).toString());
        }
    }
    else
    {

    }
    IndetailsCommandesInsertIDPROD = new QComboBox;
    if(queryDetails.exec("SELECT DISTINCT id FROM produits"))
    {
        while(queryDetails.next())
        {
            IndetailsCommandesInsertIDPROD->addItem(queryDetails.value(0).toString());
        }
    }
    else
    {

    }
    InetailsCommandesInsertQTE = new QLineEdit;
    details_commandesLayout->addRow(DescdetailsCommandesInsertIDCOMM,IndetailsCommandesInsertIDCOMM);
    details_commandesLayout->addRow(DescdetailsCommandesInsertIDPROD,IndetailsCommandesInsertIDPROD);
    details_commandesLayout->addRow(DescdetailsCommandesInsertQTE,InetailsCommandesInsertQTE);
    details_commandeWidget->setLayout(details_commandesLayout);
    req2Layout->addWidget(details_commandeWidget,1,Qt::AlignLeft);
    details_commandeWidget->hide();
    /* --- APPROVISIONNEMENT INSERT --- */
    QSqlQuery queryApprovisionnement;
    approvisionnementLayout = new QFormLayout;
    approvisionnementWidget = new QWidget;
    DescapprovisionnementInsertNUMMAG = new QLabel(tr("NUMERO DU MAGASIN :"));
    DescapprovisionnementInsertNUMPROD = new QLabel(tr("NUMERO DU PRODUIT :"));
    DescapprovisionnementInsertNUMFOURN = new QLabel(tr("NUMERO DU FOURNISSEUR :"));
    DescapprovisionnementInsertDATE = new QLabel(tr("DATE DE LIVRAISON :"));
    DescapprovisionnementInsertQTE = new QLabel(tr("QUANTITE :"));
    DescapprovisionnementInsertPRIXAU = new QLabel(tr("PRIX D'ACHAT UNITAIRE :"));
    InapprovisionnementInsertNUMMAG = new QComboBox;
    if(queryApprovisionnement.exec("SELECT DISTINCT id FROM magasins"))
    {
        while(queryApprovisionnement.next())
        {
            InapprovisionnementInsertNUMMAG->addItem(queryApprovisionnement.value(0).toString());
        }
    }
    else
    {

    }
    InapprovisionnementInsertNUMPROD = new QComboBox;
    if(queryApprovisionnement.exec("SELECT DISTINCT id FROM produits"))
    {
        while(queryApprovisionnement.next())
        {
            InapprovisionnementInsertNUMPROD->addItem(queryApprovisionnement.value(0).toString());
        }
    }
    else
    {

    }
    InapprovisionnementInsertNUMFOURN = new QComboBox;
    if(queryApprovisionnement.exec("SELECT DISTINCT id FROM fournisseurs"))
    {
        while(queryApprovisionnement.next())
        {
            InapprovisionnementInsertNUMFOURN->addItem(queryApprovisionnement.value(0).toString());
        }
    }
    else
    {

    }
    InapprovisionnementInsertDATE = new QLineEdit;
    InapprovisionnementInsertQTE = new QLineEdit;
    InapprovisionnementInsertPRIXAU = new QLineEdit;
    approvisionnementLayout->addRow(DescapprovisionnementInsertNUMMAG,InapprovisionnementInsertNUMMAG);
    approvisionnementLayout->addRow(DescapprovisionnementInsertNUMPROD,InapprovisionnementInsertNUMPROD);
    approvisionnementLayout->addRow(DescapprovisionnementInsertNUMFOURN,InapprovisionnementInsertNUMFOURN);
    approvisionnementLayout->addRow(DescapprovisionnementInsertDATE,InapprovisionnementInsertDATE);
    approvisionnementLayout->addRow(DescapprovisionnementInsertQTE,InapprovisionnementInsertQTE);
    approvisionnementLayout->addRow(DescapprovisionnementInsertPRIXAU,InapprovisionnementInsertPRIXAU);
    approvisionnementWidget->setLayout(approvisionnementLayout);
    req2Layout->addWidget(approvisionnementWidget,1,Qt::AlignLeft);
    approvisionnementWidget->hide();
    /*--- EMPLOYES INSERT --- */
    QSqlQuery queryEmployes;
    employesWidget = new QWidget;
    employesLayout = new QFormLayout;
    DescemployesInsertID = new QLabel(tr("ID :"));
    DescemployesInsertNOM = new QLabel(tr("NOM :"));
    DescemployesInsertDATENAIS = new QLabel(tr("DATE DE NAISSANCE :"));
    DescemployesInsertEMAIL = new QLabel(tr("EMAIL :"));
    DescemployesInsertTELEPHONE = new QLabel(tr("TELEPHONE :"));
    DescemployesInsertADRESSE = new QLabel(tr("ADRESSE :"));
    DescemployesInsertCP = new QLabel(tr("CODE POSTAL :"));
    DescemployesInsertPAYS = new QLabel(tr("PAYS :"));
    DescemployesInsertDATEREC = new QLabel(tr("DATE DE RECRUTEMENT :"));
    DescemployesInsertSALAIRE = new QLabel(tr("SALAIRE :"));
    DescemployesInsertTITRE = new QLabel(tr("TITRE DU POSTE :"));
    DescemployesInsertIDMAG = new QLabel(tr("ID DU MAGASIN :"));
    InemployesInsertID = new QLineEdit;
    InemployesInsertNOM = new QLineEdit;
    InemployesInsertDATENAIS = new QLineEdit;
    InemployesInsertEMAIL = new QLineEdit;
    InemployesInsertTELEPHONE = new QLineEdit;
    InemployesInsertADRESSE = new QLineEdit;
    InemployesInsertCP = new QLineEdit;
    InemployesInsertPAYS = new QLineEdit;
    InemployesInsertDATEREC = new QLineEdit;
    InemployesInsertSALAIRE = new QLineEdit;
    InemployesInsertTITRE = new QLineEdit;
    InemployesInsertIDMAG = new QComboBox;
    if(queryEmployes.exec("SELECT DISTINCT id FROM magasins"))
    {
        while(queryEmployes.next())
        {
            InemployesInsertIDMAG->addItem(queryEmployes.value(0).toString());
        }
    }
    else
    {

    }
    employesLayout->addRow(DescemployesInsertID,InemployesInsertID);
    employesLayout->addRow(DescemployesInsertNOM,InemployesInsertNOM);
    employesLayout->addRow(DescemployesInsertDATENAIS,InemployesInsertDATENAIS);
    employesLayout->addRow(DescemployesInsertEMAIL,InemployesInsertEMAIL);
    employesLayout->addRow(DescemployesInsertTELEPHONE,InemployesInsertTELEPHONE);
    employesLayout->addRow(DescemployesInsertADRESSE,InemployesInsertADRESSE);
    employesLayout->addRow(DescemployesInsertCP,InemployesInsertCP);
    employesLayout->addRow(DescemployesInsertPAYS,InemployesInsertPAYS);
    employesLayout->addRow(DescemployesInsertDATEREC,InemployesInsertDATEREC);
    employesLayout->addRow(DescemployesInsertSALAIRE,InemployesInsertSALAIRE);
    employesLayout->addRow(DescemployesInsertTITRE,InemployesInsertTITRE);
    employesLayout->addRow(DescemployesInsertIDMAG,InemployesInsertIDMAG);
    employesWidget->setLayout(employesLayout);
    req2Layout->addWidget(employesWidget,1,Qt::AlignLeft);
    employesWidget->hide();
    /* --- COMMANDES INSERT --- */
    QSqlQuery queryCommandes;
    commandesLayout = new QFormLayout;
    commandesWidget = new QWidget;
    DesccommandesInsertID = new QLabel(tr("ID :"));
    DesccommandesInsertIDCLIENT = new QLabel(tr("ID CLIENT :"));
    DesccommandesInsertIDMAG = new QLabel(tr("ID MAGASIN:"));
    DesccommandesInsertDATE_COMM = new QLabel(tr("DATE DE LA COMMANDE :"));
    DesccommandesInsertEMPLOYERES = new QLabel(tr("EMPLOYE RESPONSABLE :"));
    DesccommandesInsertMODE_PAI = new QLabel(tr("MODE DE PAIEMENT :"));
    IncommandesInsertID = new QLineEdit;
    IncommandesInsertIDCLIENT = new QComboBox;
    if(queryCommandes.exec("SELECT DISTINCT id FROM clients"))
    {
        while(queryCommandes.next())
        {
            IncommandesInsertIDCLIENT->addItem(queryCommandes.value(0).toString());
        }
    }
    else
    {

    }
    IncommandesInsertIDMAG = new QComboBox;
    if(queryCommandes.exec("SELECT DISTINCT id FROM magasins"))
    {
        while(queryCommandes.next())
        {
            IncommandesInsertIDMAG->addItem(queryCommandes.value(0).toString());
        }
    }
    else
    {

    }
    IncommandesInsertDATE_COMM = new QLineEdit;
    IncommandesInsertEMPLOYERES = new QComboBox;
    if(queryCommandes.exec("SELECT DISTINCT id FROM employes"))
    {
        while(queryCommandes.next())
        {
            IncommandesInsertEMPLOYERES->addItem(queryCommandes.value(0).toString());
        }
    }
    else
    {

    }
    IncommandesInsertMODE_PAI = new QLineEdit;
    commandesLayout->addRow(DesccommandesInsertID,IncommandesInsertID);
    commandesLayout->addRow(DesccommandesInsertIDCLIENT,IncommandesInsertIDCLIENT);
    commandesLayout->addRow(DesccommandesInsertIDMAG,IncommandesInsertIDMAG);
    commandesLayout->addRow(DesccommandesInsertDATE_COMM,IncommandesInsertDATE_COMM);
    commandesLayout->addRow(DesccommandesInsertEMPLOYERES,IncommandesInsertEMPLOYERES);
    commandesLayout->addRow(DesccommandesInsertMODE_PAI,IncommandesInsertMODE_PAI);
    commandesWidget->setLayout(commandesLayout);
    req2Layout->addWidget(commandesWidget,1,Qt::AlignLeft);
    commandesWidget->hide();




    req2Layout->addWidget(req2exec,0,Qt::AlignLeft);
    mainLayout->addWidget(req2Widget, 5,0,1,1);
    req2Widget->hide();
    insertSelection();
    connect(req2exec, SIGNAL(clicked(bool)), this, SLOT(insert()));
}

void MainWindow::mode2Rebuild()
{
    connect(tableSelect, SIGNAL(currentTextChanged(QString)), this, SLOT(insertSelection()));
    req2Widget->show();
}
void MainWindow::mode2Cleanup()
{
    tableSelect->disconnect();
    req2Widget->hide();
}

void MainWindow::insertSelection()
{
    if(tableSelect->currentIndex() == 0)//insertion dans approvisionnement
    {
        commandesWidget->hide();
        employesWidget->hide();
        approvisionnementWidget->show();
        details_commandeWidget->hide();
        stocksWidget->hide();
        produitsWidget->hide();
        fournisseursWidget->hide();
        magasinsWidget->hide();
        clientsWidget->hide();
    }
    else if(tableSelect->currentIndex() == 1)//insertion dans clients
    {
        commandesWidget->hide();
        employesWidget->hide();
        approvisionnementWidget->hide();
        details_commandeWidget->hide();
        stocksWidget->hide();
        produitsWidget->hide();
        fournisseursWidget->hide();
        magasinsWidget->hide();
        clientsWidget->show();
    }
    else if(tableSelect->currentIndex() == 2)//insertion dans commandes
    {
        commandesWidget->show();
        employesWidget->hide();
        approvisionnementWidget->hide();
        details_commandeWidget->hide();
        stocksWidget->hide();
        produitsWidget->hide();
        fournisseursWidget->hide();
        magasinsWidget->hide();
        clientsWidget->hide();
    }
    else if(tableSelect->currentIndex() == 3)//insertion dans details commandes
    {
        commandesWidget->hide();
        employesWidget->hide();
        approvisionnementWidget->hide();
        details_commandeWidget->show();
        stocksWidget->hide();
        produitsWidget->hide();
        fournisseursWidget->hide();
        magasinsWidget->hide();
        clientsWidget->hide();
    }
    else if(tableSelect->currentIndex() == 4)//insertion dans employes
    {
        commandesWidget->hide();
        employesWidget->show();
        approvisionnementWidget->hide();
        details_commandeWidget->hide();
        stocksWidget->hide();
        produitsWidget->hide();
        fournisseursWidget->hide();
        magasinsWidget->hide();
        clientsWidget->hide();
    }
    else if(tableSelect->currentIndex() == 5)//insertion dans fournisseurs
    {
        commandesWidget->hide();
        employesWidget->hide();
        approvisionnementWidget->hide();
        details_commandeWidget->hide();
        stocksWidget->hide();
        produitsWidget->hide();
        magasinsWidget->hide();
        clientsWidget->hide();
        fournisseursWidget->show();
    }
    else if(tableSelect->currentIndex() == 6)//insertion dans magasins
    {
        commandesWidget->hide();
        employesWidget->hide();
        approvisionnementWidget->hide();
        details_commandeWidget->hide();
        stocksWidget->hide();
        produitsWidget->hide();
        fournisseursWidget->hide();
        clientsWidget->hide();
        magasinsWidget->show();
    }
    else if(tableSelect->currentIndex() == 7)//insertion dans produits
    {
        commandesWidget->hide();
        employesWidget->hide();
        approvisionnementWidget->hide();
        details_commandeWidget->hide();
        stocksWidget->hide();
        produitsWidget->show();
        fournisseursWidget->hide();
        magasinsWidget->hide();
        clientsWidget->hide();
    }
    else if(tableSelect->currentIndex() == 8)//insertion dans stocks
    {
        commandesWidget->hide();
        employesWidget->hide();
        approvisionnementWidget->hide();
        details_commandeWidget->hide();
        stocksWidget->show();
        produitsWidget->hide();
        fournisseursWidget->hide();
        magasinsWidget->hide();
        clientsWidget->hide();
    }
    else
    {

    }
}

void MainWindow::insert()
{
    QSqlQuery queryInsert;
    QString typedQuery = "INSERT INTO ";
    typedQuery.append(tableSelect->currentText());
    switch (tableSelect->currentIndex()){
    case 0 ://insertion dans approvisionnement
        typedQuery.append(" (numMagasin,numProduit,numFournisseur,date_livraison,quantite,prix_achat_unitaire) VALUE('");
        typedQuery.append(InapprovisionnementInsertNUMMAG->currentText());
        typedQuery.append("','");
        typedQuery.append(InapprovisionnementInsertNUMPROD->currentText());
        typedQuery.append("','");
        typedQuery.append(InapprovisionnementInsertNUMFOURN->currentText());
        typedQuery.append("','");
        typedQuery.append(InapprovisionnementInsertDATE->text());
        typedQuery.append("','");
        typedQuery.append(InapprovisionnementInsertQTE->text());
        typedQuery.append("','");
        typedQuery.append(InapprovisionnementInsertPRIXAU->text());
        typedQuery.append("')");
        InapprovisionnementInsertNUMMAG->setCurrentIndex(0);
        InapprovisionnementInsertNUMPROD->setCurrentIndex(0);
        InapprovisionnementInsertNUMFOURN->setCurrentIndex(0);
        InapprovisionnementInsertDATE->clear();
        InapprovisionnementInsertQTE->clear();
        InapprovisionnementInsertPRIXAU->clear();
    break;
    case 1 ://insertion dans clients
        typedQuery.append(" (id,nom,date_naissance,email,telephone,adresse,code_postal,pays,date_inscription,carte_fidelite) VALUE('");
        typedQuery.append(InclientInsertID->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertNOM->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertDATE_NAISSANCE->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertEMAIL->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertTELEPHONE->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertADRESSE->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertCP->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertPAYS->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertDATE_INSCRIPTION->text());
        typedQuery.append("','");
        typedQuery.append(InclientInsertCARTE_FIDELITE->text());
        typedQuery.append("')");
        InclientInsertID->clear();
        InclientInsertNOM->clear();
        InclientInsertDATE_NAISSANCE->clear();
        InclientInsertEMAIL->clear();
        InclientInsertTELEPHONE->clear();
        InclientInsertADRESSE->clear();
        InclientInsertCP->clear();
        InclientInsertPAYS->clear();
        InclientInsertDATE_INSCRIPTION->clear();
        InclientInsertCARTE_FIDELITE->clear();
    break;
    case 2 ://insertion dans commandes
        typedQuery.append(" (id,idClient,idMagasin,date_commande,EmployeResponsableVente,mode_paiement) VALUE('");
        typedQuery.append(IncommandesInsertID->text());
        typedQuery.append("','");
        typedQuery.append(IncommandesInsertIDCLIENT->currentText());
        typedQuery.append("','");
        typedQuery.append(IncommandesInsertIDMAG->currentText());
        typedQuery.append("','");
        typedQuery.append(IncommandesInsertDATE_COMM->text());
        typedQuery.append("','");
        typedQuery.append(IncommandesInsertEMPLOYERES->currentText());
        typedQuery.append("','");
        typedQuery.append(IncommandesInsertMODE_PAI->text());
        typedQuery.append("')");
        IncommandesInsertID->clear();
        IncommandesInsertIDCLIENT->setCurrentIndex(0);
        IncommandesInsertIDMAG->setCurrentIndex(0);
        IncommandesInsertDATE_COMM->clear();
        IncommandesInsertEMPLOYERES->setCurrentIndex(0);
        IncommandesInsertMODE_PAI->clear();
    break;
    case 3 ://insertion dans details commandes
        typedQuery.append(" (idCommande,idProduit,quantite) VALUE('");
        typedQuery.append(IndetailsCommandesInsertIDCOMM->currentText());
        typedQuery.append("','");
        typedQuery.append(IndetailsCommandesInsertIDPROD->currentText());
        typedQuery.append("','");
        typedQuery.append(InetailsCommandesInsertQTE->text());
        typedQuery.append("')");
        InetailsCommandesInsertQTE->clear();
        IndetailsCommandesInsertIDPROD->setCurrentIndex(0);
        IndetailsCommandesInsertIDCOMM->setCurrentIndex(0);
    break;
    case 4 ://insertion dans employes
        typedQuery.append(" (id,nom,date_naissance,email,telephone,adresse,code_postal,pays,date_recrutement,salaire,titre_poste,id_magasin) VALUE('");
        typedQuery.append(InemployesInsertID->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertNOM->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertDATENAIS->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertEMAIL->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertTELEPHONE->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertADRESSE->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertCP->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertPAYS->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertDATEREC->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertSALAIRE->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertTITRE->text());
        typedQuery.append("','");
        typedQuery.append(InemployesInsertIDMAG->currentText());
        typedQuery.append("')");
        InemployesInsertID->clear();
        InemployesInsertNOM->clear();
        InemployesInsertDATENAIS->clear();
        InemployesInsertEMAIL->clear();
        InemployesInsertTELEPHONE->clear();
        InemployesInsertADRESSE->clear();
        InemployesInsertCP->clear();
        InemployesInsertPAYS->clear();
        InemployesInsertDATEREC->clear();
        InemployesInsertSALAIRE->clear();
        InemployesInsertTITRE->clear();
        InemployesInsertIDMAG->setCurrentIndex(0);
    break;
    case 5 ://insertion dans fournisseurs
        typedQuery.append(" (id,nom,telephone,adresse,code_postal,pays) VALUE('");
        typedQuery.append(InfournisseursInsertID->text());
        typedQuery.append("','");
        typedQuery.append(InfournisseursInsertNOM->text());
        typedQuery.append("','");
        typedQuery.append(InfournisseursInsertTELEPHONE->text());
        typedQuery.append("','");
        typedQuery.append(InfournisseursInsertADRESSE->text());
        typedQuery.append("','");
        typedQuery.append(InfournisseursInsertCP->text());
        typedQuery.append("','");
        typedQuery.append(InfournisseursInsertPAYS->text());
        typedQuery.append("')");
        InfournisseursInsertID->clear();
        InfournisseursInsertNOM->clear();
        InfournisseursInsertTELEPHONE->clear();
        InfournisseursInsertADRESSE->clear();
        InfournisseursInsertCP->clear();
        InfournisseursInsertPAYS->clear();
    break;
    case 6 ://insertion dans magasins
        typedQuery.append(" (id,adresse,code_postal,telephone,pays,date_ouverture) VALUE('");
        typedQuery.append(InmagasinsInsertID->text());
        typedQuery.append("','");
        typedQuery.append(InmagasinsInsertADRESSE->text());
        typedQuery.append("','");
        typedQuery.append(InmagasinsInsertCP->text());
        typedQuery.append("','");
        typedQuery.append(InmagasinsInsertTELEPHONE->text());
        typedQuery.append("','");
        typedQuery.append(InmagasinsInsertPAYS->text());
        typedQuery.append("','");
        typedQuery.append(InmagasinsInsertDATE_OUVERTURE->text());
        typedQuery.append("')");
        InmagasinsInsertID->clear();
        InmagasinsInsertADRESSE->clear();
        InmagasinsInsertCP->clear();
        InmagasinsInsertTELEPHONE->clear();
        InmagasinsInsertPAYS->clear();
        InmagasinsInsertDATE_OUVERTURE->clear();
    break;
    case 7 ://insertion dans produits
        typedQuery.append(" (id,nom,categorie,description,prix_vente_unitaire) VALUE('");
        typedQuery.append(InproduitsInsertID->text());
        typedQuery.append("','");
        typedQuery.append(InproduitsInsertNOM->text());
        typedQuery.append("','");
        typedQuery.append(InproduitsInsertCATEGORIE->text());
        typedQuery.append("','");
        typedQuery.append(InproduitsInsertDESCRIPTION->text());
        typedQuery.append("','");
        typedQuery.append(InproduitsInsertPRIX_UNITAIRE->text());
        typedQuery.append("')");
        InproduitsInsertID->clear();
        InproduitsInsertNOM->clear();
        InproduitsInsertCATEGORIE->clear();
        InproduitsInsertDESCRIPTION->clear();
        InproduitsInsertPRIX_UNITAIRE->clear();
    break;
    case 8 ://insertion dans stocks
        typedQuery.append(" (idProduit,idMagasin,quantite_restante) VALUE('");
        typedQuery.append(InstocksIDPROD->currentText());
        typedQuery.append("','");
        typedQuery.append(InstocksInsertIDMAG->currentText());
        typedQuery.append("','");
        typedQuery.append(InstocksInsertQTREST->text());
        typedQuery.append("')");
        InstocksIDPROD->setCurrentIndex(0);
        InstocksInsertIDMAG->setCurrentIndex(0);
        InstocksInsertQTREST->clear();
    break;
    }
    if(queryInsert.exec(typedQuery))
    {

    }
    else
    {
        QMessageBox::about(this, tr("Insertion échouée"), tr("L'insertion des données n'a pas pu aboutir, vérifiez la syntaxe des champs."));
    }
}

void MainWindow::mode3Buildup()
{
    tableSelect->hide();
    req3Layout = new QFormLayout;
    req3Widget = new QWidget;
    req3ID = new QLineEdit;
    req3Desc2 = new QLabel(tr("Entrez l'ID d'un client"));
    req3Exec = new QPushButton(tr("executer"));
    req3Desc1 = new QLabel(tr("permet pour un client donné,\n d'afficher ses postes de dépenses \n par catégorie"));
    connect(req3Exec, SIGNAL(clicked(bool)), this, SLOT(req3execute()));
    req3Layout->addRow(req3Desc2,req3ID);
    req3Layout->addRow(req3Desc1,req3Exec);
    req3Widget->setLayout(req3Layout);
    mainLayout->addWidget(req3Widget,4,0,Qt::AlignLeft);
    req3Widget->hide();



}


void MainWindow::mode3Cleanup()
{
    tableSelect->show();
    req3Widget->hide();
}

void MainWindow::mode3Rebuild()
{
    tableSelect->hide();
    req3Widget->show();
}

void MainWindow::req3execute()
{
    QSqlQuery req3query;
    QString typedQueryMode3;
    typedQueryMode3 = "SELECT clients.id,clients.nom,produits.categorie,magasins.adresse,magasins.code_postal,magasins.pays,SUM(details_commande.quantite) as quantite FROM clients JOIN commandes ON clients.id=commandes.idClient JOIN details_commande ON commandes.id=details_commande.idCommande JOIN magasins ON commandes.idMagasin=magasins.id JOIN produits ON details_commande.idProduit=produits.id  WHERE(clients.id ='";
    typedQueryMode3.append(req3ID->text());
    typedQueryMode3.append("') GROUP BY produits.categorie;");
    int rows = 0;
    int columns = 7;
    QStandardItem *element;
    model = new QStandardItemModel(1,columns,this);
    model->setHeaderData(0, Qt::Horizontal, tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, tr("Catégorie"));
    model->setHeaderData(3, Qt::Horizontal, tr("Adresse du magasin"));
    model->setHeaderData(4, Qt::Horizontal, tr("Code postal du magasin"));
    model->setHeaderData(5, Qt::Horizontal, tr("Pays"));
    model->setHeaderData(6, Qt::Horizontal, tr("Quantité"));
    if(req3query.exec(typedQueryMode3))
    {
        while(req3query.next())
        {
            for(int j = 0; j < columns; j++)
            {
                element = new QStandardItem(req3query.value(j).toString());
                element->setEditable(false);
                model->setItem(rows,j,element);
            }
        rows++;
        }
    }
    else
    {

    }
    tableDisplay = new QTableView();
    tableDisplay->setModel(model);
    tableDisplay->setSortingEnabled(true);
    mainLayout->addWidget(tableDisplay, 3,1,25,25);
}

void MainWindow::charger()
{
    QString scriptName = QFileDialog::getOpenFileName(this,"C:\\","Fichier texte (*.txt)");
    QFile script(scriptName);
    script.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream flux(&script);
    QString scriptContent = flux.readAll();
    customReq->setText(scriptContent);
    customExec->setStyleSheet("background-color: green;");
}


void MainWindow::save()
{
    //sources here https://stackoverflow.com/questions/27353026/qtableview-output-save-as-csv-or-txt
    //thanks to "momosxp" for his algorithm.
    QString filters("CSV files (*.csv);;All files (*.*)");
    QString defaultFilter("CSV files (*.csv)");
    QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                     filters, &defaultFilter);
    QFile file(fileName);

    QAbstractItemModel *modelSave =  tableDisplay->model();
    if (file.open(QFile::WriteOnly | QFile::Truncate)) {
      QTextStream data(&file);
      QStringList strList;
      for (int i = 0; i < modelSave->columnCount(); i++) {
          if (modelSave->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
              strList.append("\"" + modelSave->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
          else
              strList.append("");
      }
      data << strList.join(";") << "\n";
      for (int i = 0; i < modelSave->rowCount(); i++) {
          strList.clear();
          for (int j = 0; j < modelSave->columnCount(); j++) {

              if (modelSave->data(modelSave->index(i, j)).toString().length() > 0)
                  strList.append("\"" + modelSave->data(modelSave->index(i, j)).toString() + "\"");
              else
                  strList.append("");
          }
          data << strList.join(";") + "\n";
      }
      data << strList.join(";") << "\n";
      file.close();
    }

}

void MainWindow::changeLang()
{
    if(langBox->currentIndex() == 0)
    {
        settings->setValue("lang", "French");
        settings->sync();
    }
    else if(langBox->currentIndex() == 1)
    {
        settings->setValue("lang", "English");
        settings->sync();
    }
}

void MainWindow::translate()
{

}
