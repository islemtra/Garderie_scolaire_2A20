#include "eleve.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include "eleve.h"
#include"exportexcel.h"

eleve::eleve()
{
    Identifiant="";Sexe="";Classe="";
    Nom="";
    Prenom="";
}

eleve::eleve(QString Identifiant ,QString Nom,QString Prenom,QString Dat_naiss,QString Sexe,QString Classe)
{this->Identifiant=Identifiant;
    this->Nom=Nom;
    this->Prenom=Prenom;
    this->Dat_naiss=Dat_naiss;
    this->Sexe=Sexe;
    this->Classe=Classe;

}
QString eleve::getIdentifiant(){return Identifiant;}
QString eleve::getNom(){return Nom;}
QString eleve::getPrenom(){return Prenom;}
QString eleve::getDat_naiss(){return Dat_naiss;}
QString eleve::getSexe(){return Sexe;}
QString eleve::getClasse(){return Classe;}

void eleve::setIdentifiant(QString Identifiant){this->Identifiant=Identifiant;}
void eleve::setNom(QString Nom){this->Nom=Nom;}
void eleve::setPrenom(QString Prenom){this->Prenom=Prenom;}
void eleve::setDat_naiss(QString Dat_naiss){this->Dat_naiss=Dat_naiss;}
void eleve::setSexe(QString Sexe){this->Sexe=Sexe;}
void eleve::setClasse(QString Classe){this->Classe=Classe;}

bool eleve::ajouter(){
    QSqlQuery query;


    query.prepare("INSERT INTO eleve (Identifiant,Nom,Prenom,Dat_naiss,Sexe,Classe)"
                  "VALUES (:Identifiant,:Nom,:Prenom,:Dat_naiss,:Sexe,:Classe)");
    query.bindValue(0, Identifiant);
    query.bindValue(1, Nom);
    query.bindValue(2, Prenom);
    query.bindValue(3, Dat_naiss);
    query.bindValue(4, Sexe);
    query.bindValue(5, Classe);

    return query.exec();
}

bool eleve::supprimer(QString Identifiant){
   bool test=false;
    if (Existence_eleve(Identifiant))
    {QSqlQuery query;

          query.prepare("Delete from eleve where Identifiant=:Identifiant");
          query.bindValue(0, Identifiant);


test=query.exec();
if(!test)
qDebug() << "suppression echouée:" << query.lastError();
else
    qDebug() << "suppression de eleve réussie:" << Identifiant ;
    }
    else
    {
        qDebug() << "la référence du eleve n'existe pas";
    }
    return test;

}


QSqlQueryModel* eleve::afficher()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM eleve");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Classe"));

    return model;
}


bool eleve::modifier(QString Identifiant,QString Nom,QString Prenom,QString Dat_naiss,QString Sexe,QString Classe)
{
    QSqlQuery query;
    query.prepare("update eleve set Identifiant=:Identifiant,Nom=:Nom,Prenom=:Prenom,Dat_naiss=:Dat_naiss,Sexe=:Sexe,Classe=:Classe where Identifiant=:Identifiant ");
    query.bindValue(":Identifiant",Identifiant);
    query.bindValue(":Nom", Nom);
    query.bindValue(":Prenom", Prenom);
    query.bindValue(":Dat_naiss", Dat_naiss);
    query.bindValue(":Sexe", Sexe);
    query.bindValue(":Classe", Classe);
    return    query.exec();
}

bool eleve:: Existence_eleve(const QString& Identifiant) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT Identifiant FROM eleve WHERE Identifiant=:Identifiant");
    checkQuery.bindValue(":Identifiant", Identifiant);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "User not found:" << checkQuery.lastError();
    }

    return exists;
}
eleve eleve::chercher(QString Identifiant){

    eleve EL1;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM eleve WHERE Identifiant = :Identifiant");
    checkQuery.bindValue(":Identifiant", Identifiant);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            EL1.setIdentifiant(checkQuery.value(0).toString());
            EL1.setNom(checkQuery.value(1).toString());
            EL1.setPrenom(checkQuery.value(2).toString());
            EL1.setDat_naiss(checkQuery.value(3).toString());
            EL1.setSexe(checkQuery.value(4).toString());
            EL1.setClasse(checkQuery.value(5).toString());


            return EL1;
        }
    }
    else
    {
        qDebug() << "User not found:" << checkQuery.lastError();
        EL1.setNom("vide");
    }

    return EL1;
}

///////////////////metiers/////////////////////

QSqlQueryModel* eleve::tri_croissant()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM eleve ORDER BY Dat_naiss");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Dat_naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Classe"));

    return model;
}

QSqlQueryModel* eleve::tri_decroissant()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM eleve ORDER BY Dat_naiss DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Dat_naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Classe"));

    return model;
}


QSqlQueryModel* eleve::tri_id()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM eleve ORDER BY Identifiant");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Dat_naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Classe"));

    return model;
}
QSqlQueryModel* eleve::tri_Prenom()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM eleve ORDER BY Prenom");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Dat_naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Classe"));

    return model;
}

QSqlQueryModel* eleve::tri_nom()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM eleve ORDER BY Nom");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Dat_naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Classe"));

    return model;
}




QSqlQueryModel* eleve::afficher_eleve(QString Identifiant)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM eleve WHERE Identifiant=:Identifiant ");
    query.bindValue(":Identifiant",Identifiant);
    QSqlQueryModel* model= new QSqlQueryModel();
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Dat_naiss"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Classe"));

    return model;
}



