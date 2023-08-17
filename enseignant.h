#ifndef ENSEIGNANT_H
#define ENSEIGNANT_H


#include <QString>
#include <QString>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QString>

#include"exportexcel.h"
class enseignant
{
public:
    enseignant();
    enseignant(QString,QString,QString,QString,QString,int,QString,QString);
    QString getIdentifiant();
    QString getNom();
     QString getPrenom();
     QString getDate_naiss();
    QString getMatiere();
     int getNb_Classe();
     QString getRemarque();
      QString getSexe();

     void setIdentifiant(QString);
      void setNom(QString);
       void setPrenom(QString);
        void setDate_naiss(QString);
           void setMatiere(QString);
        void setNb_Classe(int);
        void setRemarque(QString);
        void setSexe(QString);


        bool ajouter();
        bool supprimer(QString);
        bool Existence_enseignant(const QString& Identifiant) const;
        bool modifier(QString,QString,QString,QString,QString,int,QString,QString);
        QSqlQueryModel* afficher();
        QSqlQueryModel* tri_croissant();
        QSqlQueryModel* tri_decroissant();
        QSqlQueryModel* tri_date_naiss();
        QSqlQueryModel* tri_nom();
        QSqlQueryModel* tri_prenom();
        enseignant chercher(QString Matiere);
         enseignant chercher2(QString Identifiant);
        QSqlQueryModel* afficher_enseignant(QString Identifiant);
          QSqlQueryModel* afficher_enseignant2(QString Identifiant);


private:
 QString Identifiant,Nom,Prenom,Sexe,Remarque,Date_naiss,Matiere;
 int Nb_Classe ;

};
#endif // ENSEIGNANT_H
