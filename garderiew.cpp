#include "garderiew.h"
#include "ui_garderiew.h"

#include "eleve.h"

#include"exportexcel.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlDatabase>
#include <QtCore>
#include <QtWidgets/QApplication>
#include <QSound>
#include <QFileDialog>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"exportexcel.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QSqlDatabase>
#include <QtCore>
#include <QtWidgets/QApplication>
#include <QSound>
#include <QFileDialog>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

garderiew::garderiew(QWidget *parent) :
    QDialog(parent),

    ui(new Ui::garderiew)
{

    ui->setupUi(this);
    //////////////////Controle de saisie (eleve)//////////////
    QRegExp rx("[A-Z][a-zA-Z]*"); //une expression régulière (RegExp) qui contient uniquement des lettres et commence par une majuscule
    QRegExp rx2("(Homme|Femme)"); //vérifie si la chaîne est soit "Homme" soit "Femme", tout en commençant par une majuscule

    QValidator *validator = new QRegExpValidator(rx, this);
    QValidator *validator2 = new QRegExpValidator(rx2, this);

    ui->id_eleve->setValidator(validator);
     ui->nom_eleve->setValidator(validator);
      ui->prenom_eleve->setValidator(validator);
        ui->sexe_eleve->setValidator(validator2);

        ui->id_eleve_2->setValidator(validator);
         ui->nom_eleve_2->setValidator(validator);
          ui->prenom_eleve_2->setValidator(validator);
            ui->sexe_eleve_2->setValidator(validator2);


    /////////////Affichage/////////////////////

  ui->tab_eleves->setModel(EL1.afficher());
    ////////////son//////////////////////////
    son=new QSound(":/sons/sons/not.wav");
    son1=new QSound(":/sons/sons/not2.wav");
    son2=new QSound(":/sons/sons/not3.wav");
    son3=new QSound(":/sons/sons/not4.wav");
    son4=new QSound(":/sons/sons/not5.wav");
    son5=new QSound(":/sons/sons/not6.wav");

    ////////////////////////mail///////////////////////
    //des fonctions predefines par smtp.cpp
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
    ///////////////////////chat//////////////////
    mSocket=new QTcpSocket(this);
       connect(mSocket,&QTcpSocket::readyRead,[&]()
       { QTextStream T(mSocket);
          auto text=T.readAll();
          ui->textEdit->append(text);
       });

       ////////////////////time/////////////////
       timer = new QTimer(this);
       connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
       timer->start(1000);
//Starts or restarts the timer with a timeout of duration msec milliseconds.

       /////////////////camera////////////////
       ///Camera
                    mCamera = new QCamera (this);
                    mCameraViewfinder = new QCameraViewfinder(this);
                    mCameraImageCapture = new QCameraImageCapture(mCamera, this);
                    mLayout = new QVBoxLayout;
                    mOptionMenu = new QMenu ("Option", this);
                    mTurnOnAction = new QAction ("Turn on", this);
                    mTurnOffAction = new QAction ("Turn off", this);
                    mCaptureAction = new QAction ("Capture", this);

                    mOptionMenu->addActions({mTurnOnAction, mTurnOffAction, mCaptureAction});
                    ui->pb_camera->setMenu(mOptionMenu);
                    mCamera->setViewfinder(mCameraViewfinder);
                    mLayout->addWidget(mCameraViewfinder);
                    mLayout->setMargin(0);
                    ui->scrollArea->setLayout(mLayout);
                    connect (mTurnOnAction, &QAction::triggered, [&]()
                    {
                       mCamera->start();
                    });
                    connect (mTurnOffAction, &QAction::triggered, [&]()
                    {
                        mCamera->stop();
                    });
                    connect (mCaptureAction, &QAction::triggered, [&]()
                    {
                        auto filename=QFileDialog::getSaveFileName(this, "capture", "/", "Image (*.jpg; *.jpeg)");

                        if (filename.isEmpty())
                        {
                            return;
                        }
                        mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
                        QImageEncoderSettings imageEncoderSettings;
                        imageEncoderSettings.setCodec("image/jpeg");
                        imageEncoderSettings.setResolution(1600,1200);
                        mCameraImageCapture->setEncodingSettings(imageEncoderSettings);
                        mCamera->setCaptureMode(QCamera::CaptureStillImage);
                        mCamera->start();
                        mCamera->searchAndLock();
                        mCameraImageCapture->capture(filename);
                        mCamera->unlock();
                    });
}

garderiew::~garderiew()
{
    delete ui;
}


//////////////////time///////////////
void garderiew::myfunction()

{
    QTime time =QTime::currentTime();

    QString time_text = time.toString("hh:mm:ss");

    ui->time->setText(time_text);
}

void garderiew::on_pb_ajouter_eleve_clicked()
{
    QString Identifiant=ui->id_eleve->text();
    QString Nom=ui->nom_eleve->text();
    QString Prenom=ui->prenom_eleve->text();
    QString Date_naiss=ui->la_date_eleve->text();
    QString Classe=ui->classe_eleve->text();
    QString Sexe=ui->sexe_eleve->text();

    eleve EL1(Identifiant,Nom,Prenom,Date_naiss,Sexe,Classe);
    bool test=EL1.ajouter();
    QMessageBox msgBox;
    if(test)
    { msgBox.setText("ajout avec success !");
        ui->tab_eleves->setModel(EL1.afficher());
        son1->play();

    }
    else
        msgBox.setText("ajout echoué !");
    msgBox.exec();
}

void garderiew::on_reset_ajouter_eleve_clicked()
{
ui->id_eleve->clear();
ui->nom_eleve->clear();
ui->prenom_eleve->clear();
ui->la_date_eleve->clear();
ui->classe_eleve->clear();
ui->sexe_eleve->clear();

}

void garderiew::on_stat_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from eleve WHERE Sexe='Homme'");
    float dispo1=model->rowCount();

   model->setQuery("select * from eleve WHERE Sexe='Femme'");
    float dispo=model->rowCount();

    float total=dispo1+dispo;
        QString a=QString("Homme . " +QString::number((dispo1*100)/total,'f',2)+"%" );
        QString b=QString("Femme .  "+QString::number((dispo*100)/total,'f',2)+"%" );
        QPieSeries *series = new QPieSeries();
        series->append(a,dispo1);
        series->append(b,dispo);
    if (dispo1!=0)
    {QPieSlice *slice = series->slices().at(0);
        slice->setLabelVisible();
        slice->setPen(QPen());}
    if ( dispo!=0)
    {
        QPieSlice *slice1 = series->slices().at(1);
        slice1->setLabelVisible();
    }

    QChart *chart = new QChart();


    chart->addSeries(series);
    chart->setTitle("Pourcentages par rapport au sexe :  "+ QString::number(total));
    chart->legend()->hide();


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->resize(1000,500);
    chartView->show();
}

void garderiew::on_export_but_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                            tr("Excel Files (*.xls)"));
            if (fileName.isEmpty())
                return;

            exportExcel obj(fileName, "mydata", ui->tab_eleves);

            //colums to export
            obj.addField(0, "Identifiant", "char(20)");
            obj.addField(1, "Nom", "char(20)");
            obj.addField(2, "Prenom", "char(20)");
            obj.addField(3, "Date_Naissance", "char(20)");
            obj.addField(4, "Sexe", "char(20)");
            obj.addField(5, "Classe", "char(20)");



            int retVal = obj.export2Excel();
            if( retVal > 0)
            {
                QMessageBox::information(this, tr("Done"),
                                         QString(tr("%1 records exported!")).arg(retVal)
                                         );
            }
}





void garderiew::on_pb_supprimer_clicked()
{
    eleve EL1;
    EL1.setIdentifiant(ui->le_num_supp->text());
    bool test=EL1.supprimer(EL1.getIdentifiant());
    QMessageBox msgBox;
    if(test)
       { msgBox.setText("suppression réussie !");
    ui->tab_eleves->setModel(EL1.afficher());
    son->play();


    }
    else
    msgBox.setText("suppression echouée !");
    msgBox.exec();
}



////////////////mailing///////////////
void garderiew::sendMail()
{//associé a un bouton grace a une fonction predefine par smtp.cpp
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void garderiew::mailSent(QString status)
{//status est une variable de retour
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    son5->play();

}


////////////image////////
void garderiew::on_upload_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this, tr("choose"), "", tr("image (*.png *.jpg *.jpeg *.bmp *.gif)")); //The QFileDialog class provides a dialog that allow users to select files or directories
    if(QString::compare(filename,QString())!=0)
    {
        QImage image;
        bool valid = image.load(filename);
        if(valid)
        {
            ui->image->setPixmap(QPixmap::fromImage(image)); //affichage de l'image
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                                  QObject::tr("Image non effectué.\n"
                                              "Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}


///////////recherche/////////////////
void garderiew::on_cherche_aff_clicked()
{
    eleve EL1;
    EL1=EL1.chercher(ui->chercher_aff->text());


        if(EL1.getIdentifiant()!=""){
    QString input = ui->chercher_aff->text();


        ui->tab_eleves->setModel(EL1.afficher_eleve(input));
        son3->play();
        }
        else //introuvable
        {
            QMessageBox::critical(nullptr, QObject::tr("chercher un eleve"),
                                  QObject::tr("eleve introuvable !.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
}
}


/////////////////tri//////////
void garderiew::on_tri_nom_clicked()
{
    ui->tab_eleves->setModel(EL1.tri_nom());

}

void garderiew::on_tri_prenom_clicked()
{
    ui->tab_eleves->setModel(EL1.tri_Prenom());

}

void garderiew::on_tri_croissant_clicked()
{

        ui->tab_eleves->setModel(EL1.tri_croissant());
}

void garderiew::on_tri_decroissant_clicked()
{
    ui->tab_eleves->setModel(EL1.tri_decroissant());

}

void garderiew::on_tri_identifiant_clicked()
{
    ui->tab_eleves->setModel(EL1.tri_id());
}
///////////////////////chat////////////
void garderiew::on_connecter_clicked()
{
    dumessengerconnectiondialog D(this);
    if(D.exec()==QDialog::Rejected)
    {
        return;

    }
    mSocket->connectToHost(D.hostname(),D.port());
}

void garderiew::on_envoyer_clicked()
{
    QTextStream T(mSocket);
        T<<ui->le_nickname->text()<<": "<<ui->le_message->text();
        mSocket->flush();
        ui->le_message->clear();
        son5->play();
}

void garderiew::on_pb_chercher_mod_clicked()
{
    eleve EL1;
    EL1=EL1.chercher(ui->la_recherche->text());

    if(EL1.getIdentifiant()!="")
    {

        ui->id_eleve_2->setText(EL1.getIdentifiant()) ;
        ui->nom_eleve_2->setText(EL1.getNom()) ;
        ui->prenom_eleve_2->setText (EL1.getPrenom()) ;
       // ui->la_date_eleve_2->setText(EL1.getDat_naiss());
        ui->sexe_eleve_2 ->setText(EL1.getSexe());
        ui->classe_eleve_2->setText(EL1.getClasse());
        ui->tab_eleves->setModel(EL1.afficher());
    }
    else //introuvable
    {
        QMessageBox::critical(nullptr, QObject::tr("chercher un eleve"),
                              QObject::tr("eleve introuvable !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }
}

void garderiew::on_pb_modifier_clicked()
{
    QString Identifiant=ui->id_eleve_2->text();
    QString Nom=ui->nom_eleve_2->text();
    QString Prenom=ui->prenom_eleve_2->text();
    QString Sexe=ui->sexe_eleve_2->text();
    QString Classe=ui->classe_eleve_2->text();
    QString Dat_naiss;
   eleve( Identifiant , Nom, Prenom, Dat_naiss, Sexe, Classe);

    eleve EL1;
    int test=EL1.Existence_eleve(Identifiant);

    if(test==true)
    {int test1=EL1.modifier( Identifiant , Nom, Prenom, Dat_naiss, Sexe, Classe);
        if(test1==true){
            QMessageBox::information(nullptr, QObject::tr("modifier un eleve"),
                                     QObject::tr("produit modifié.\n"
                                                 "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_eleves->setModel(EL1.afficher());
            son2->play();

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("modifier un eleve"),
                                  QObject::tr("Erreur de modification!.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);

        }

    }

    else
    {
        QMessageBox::critical(nullptr, QObject::tr("modifier un produit"),
                              QObject::tr("Erreur !.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    }
}
