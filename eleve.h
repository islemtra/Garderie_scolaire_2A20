#ifndef ELEVE_H
#define ELEVE_H
#include <QString>
#include <QString>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include <QString>

#include"exportexcel.h"
class eleve
{
public:
    eleve();
    eleve(QString,QString,QString,QString,QString,QString);
    QString getIdentifiant();
    QString getNom();
     QString getPrenom();
     QString getDat_naiss();
     QString getSexe();
     QString getClasse();

     void setIdentifiant(QString);
      void setNom(QString);
       void setPrenom(QString);
        void setDat_naiss(QString);
        void setSexe(QString);
        void setClasse(QString);

        bool ajouter();
        bool supprimer(QString);
        bool Existence_eleve(const QString& Identifiant) const;
        bool modifier(QString,QString,QString,QString,QString,QString);
        QSqlQueryModel* afficher();
        QSqlQueryModel* tri_croissant();
        QSqlQueryModel* tri_decroissant();
        QSqlQueryModel* tri_id();
        QSqlQueryModel* tri_nom();
        QSqlQueryModel* tri_Prenom();
        eleve chercher(QString Identifiant);
        QSqlQueryModel* afficher_eleve(QString Identifiant);


private:
 QString Identifiant,Nom,Prenom,Sexe,Classe;
 QString Dat_naiss;

};

#endif // ELEVE_H
