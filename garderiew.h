#ifndef GARDERIEW_H
#define GARDERIEW_H

#include <QDialog>

#include"eleve.h"
#include"enseignant.h"

#include <QSound>
#include <QtWidgets/QApplication>
#include"exportexcel.h"
#include <QtCharts>
#include <QLineSeries>
#include <QChartView>
#include "smtp.h"
#include "dumessengerconnectiondialog.h"
#include "ui_dumessengerconnectiondialog.h"
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMenu>
#include <QMainWindow>

#include <QSound>
#include <QtWidgets/QApplication>
#include"exportexcel.h"
#include <QtCharts>
#include <QLineSeries>
#include <QChartView>
#include "smtp.h"
#include "dumessengerconnectiondialog.h"
#include "ui_dumessengerconnectiondialog.h"
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QMenu>


namespace Ui {
class garderiew;
class QCamera;
class QCameraViewfinder;
class QCameraImageCapture;
class  QMenu;
class QAction;
class QVBoxLayout;
}

class garderiew : public QDialog
{
    Q_OBJECT

public:
    explicit garderiew(QWidget *parent = nullptr);
    ~garderiew();

private slots:
    void myfunction();


    void on_reset_ajouter_eleve_clicked();

    void on_stat_clicked();

    void on_export_but_clicked();

    void on_tri_croissant_clicked();

    void on_tri_decroissant_clicked();

    void on_pb_modifier_clicked();

    void on_pb_supprimer_clicked();


    void sendMail();
    void mailSent(QString);


    void on_upload_clicked();

    void on_pb_ajouter_eleve_clicked();

    void on_cherche_aff_clicked();

    void on_tri_nom_clicked();

    void on_tri_prenom_clicked();

    void on_tri_identifiant_clicked();

    void on_connecter_clicked();

    void on_envoyer_clicked();

    void on_pb_chercher_mod_clicked();


    void on_pb_ajouter_ens_clicked();

    void on_reset_ajouter_ens_2_clicked();

    void on_cherche_aff_enseignant_par_matiere_clicked();

    void on_tri_nom_2_clicked();

    void on_tri_prenom_2_clicked();

    void on_tri_date_naiss_ens_clicked();

    void on_tri_croissant_nb_clicked();

    void on_tri_decroissant_nb_clicked();

    void on_export_but_enseignant_clicked();

    void on_stat_enseignant_clicked();

    void on_pb_supprimer_enseignant_clicked();

    void on_pb_chercher_enseignant_clicked();

    void on_pb_modifie_enseignant_clicked();



private:
    Ui::garderiew *ui;


    eleve EL1;
    enseignant EN1;
     QTimer *timer;
     QSound *son;
     QSound *son1;
     QSound *son2;
     QSound *son3;
     QSound *son4;
     QSound *son5;

     QTcpSocket *mSocket;

            QCamera *mCamera;
            QCameraViewfinder *mCameraViewfinder;
            QCameraImageCapture *mCameraImageCapture;
            QVBoxLayout *mLayout;
            QMenu *mOptionMenu;
            QAction *mTurnOnAction;
            QAction *mTurnOffAction;
            QAction *mCaptureAction;


          //  QByteArray data; // variable contenant les données reçues
};

#endif // GARDERIEW_H
