#include "enseignant.h"
#include <QSqlQuery>
#include <QDebug>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include "enseignant.h"
#include"exportexcel.h"

enseignant::enseignant()
{
    Identifiant="";Sexe="";Nb_Classe=0;
    Nom="";
    Prenom="";
    Matiere="";
  Remarque="";
}

enseignant::enseignant(QString Identifiant ,QString Nom,QString Prenom,QString Date_naiss,QString Matiere,int Nb_Classe,QString Remarque,QString Sexe)
{this->Identifiant=Identifiant;
    this->Nom=Nom;
    this->Prenom=Prenom;
    this->Date_naiss=Date_naiss;
    this->Sexe=Sexe;
    this->Matiere=Matiere;
    this->Nb_Classe=Nb_Classe;
    this->Remarque=Remarque;


}
QString enseignant::getIdentifiant(){return Identifiant;}
QString enseignant::getNom(){return Nom;}
QString enseignant::getPrenom(){return Prenom;}
QString enseignant::getDate_naiss(){return Date_naiss;}
QString enseignant::getSexe(){return Sexe;}
QString enseignant::getMatiere(){return Matiere;}
int enseignant::getNb_Classe(){return Nb_Classe;}
QString enseignant::getRemarque(){return Remarque;}

void enseignant::setIdentifiant(QString Identifiant){this->Identifiant=Identifiant;}
void enseignant::setNom(QString Nom){this->Nom=Nom;}
void enseignant::setPrenom(QString Prenom){this->Prenom=Prenom;}
void enseignant::setDate_naiss(QString Date_naiss){this->Date_naiss=Date_naiss;}
void enseignant::setSexe(QString Sexe){this->Sexe=Sexe;}
void enseignant::setMatiere(QString Matiere){this->Matiere=Matiere;}
void enseignant::setNb_Classe(int Nb_Classe){this->Nb_Classe=Nb_Classe;}
void enseignant::setRemarque(QString Remarque){this->Remarque=Remarque;}

bool enseignant::ajouter(){
    QSqlQuery query;


    query.prepare("INSERT INTO enseignant (Identifiant,Nom,Prenom,Date_naiss,Matiere,Nb_Classe,Remarque,Sexe)"
                  "VALUES (:Identifiant,:Nom,:Prenom,:Date_naiss,:Matiere,:Nb_Classe,:Remarque,:Sexe)");
    query.bindValue(0, Identifiant);
    query.bindValue(1, Nom);
    query.bindValue(2, Prenom);
    query.bindValue(3, Date_naiss);
    query.bindValue(4, Matiere);
    query.bindValue(5, Nb_Classe);
query.bindValue(6, Remarque);
query.bindValue(7, Sexe);
    return query.exec();
}

bool enseignant::supprimer(QString Identifiant){
   bool test=false;
    if (Existence_enseignant(Identifiant))
    {QSqlQuery query;

          query.prepare("Delete from enseignant where Identifiant=:Identifiant");
          query.bindValue(0, Identifiant);


test=query.exec();
if(!test)
qDebug() << "suppression echouée:" << query.lastError();
else
    qDebug() << "suppression de enseignant réussie:" << Identifiant ;
    }
    else
    {
        qDebug() << "la référence du enseignant n'existe pas";
    }
    return test;

}


QSqlQueryModel* enseignant::afficher()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM enseignant");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Matiere enseignée"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb_Classe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));

    return model;
}


bool enseignant::modifier(QString Identifiant ,QString Nom,QString Prenom,QString Date_naiss,QString Matiere,int Nb_Classe,QString Remarque,QString Sexe){
    QSqlQuery query;
    query.prepare("update enseignant set Identifiant=:Identifiant,Nom=:Nom,Prenom=:Prenom,Date_naiss=:Date_naiss,Matiere=:Matiere,Nb_Classe=:Nb_Classe,Remarque=:Remarque,Sexe=:Sexe where Identifiant=:Identifiant ");
    query.bindValue(0, Identifiant);
    query.bindValue(1, Nom);
    query.bindValue(2, Prenom);
    query.bindValue(3, Date_naiss);
    query.bindValue(4, Matiere);
    query.bindValue(5, Nb_Classe);
query.bindValue(6, Remarque);
query.bindValue(7, Sexe);
    return    query.exec();
}

bool enseignant:: Existence_enseignant(const QString& Identifiant) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT Identifiant FROM enseignant WHERE Identifiant=:Identifiant");
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
enseignant enseignant::chercher(QString Matiere){

    enseignant EN1;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM enseignant WHERE Matiere = :Matiere");
    checkQuery.bindValue(":Matiere", Matiere);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            EN1.setIdentifiant(checkQuery.value(0).toString());
            EN1.setNom(checkQuery.value(1).toString());
            EN1.setPrenom(checkQuery.value(2).toString());
            EN1.setDate_naiss(checkQuery.value(3).toString());
             EN1.setMatiere(checkQuery.value(4).toString());
            EN1.setNb_Classe(checkQuery.value(5).toInt());
            EN1.setRemarque(checkQuery.value(6).toString());
            EN1.setSexe(checkQuery.value(7).toString());


            return EN1;
        }
    }
    else
    {
       // qDebug() << "User not found:" << checkQuery.lastError();
        //EL1.setNom("vide");
    }

    return EN1;
}

enseignant enseignant::chercher2(QString Identifiant){

    enseignant EN1;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT * FROM enseignant WHERE Identifiant = :Identifiant");
    checkQuery.bindValue(":Identifiant", Identifiant);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            EN1.setIdentifiant(checkQuery.value(0).toString());
            EN1.setNom(checkQuery.value(1).toString());
            EN1.setPrenom(checkQuery.value(2).toString());
            EN1.setDate_naiss(checkQuery.value(3).toString());
              EN1.setMatiere(checkQuery.value(4).toString());

            EN1.setNb_Classe(checkQuery.value(5).toInt());
            EN1.setRemarque(checkQuery.value(6).toString());
            EN1.setSexe(checkQuery.value(7).toString());


            return EN1;
        }
    }
    else
    {
        qDebug() << "User not found:" << checkQuery.lastError();
        EN1.setNom("vide");
    }

    return EN1;
}
///////////////////metiers/////////////////////

QSqlQueryModel* enseignant::tri_croissant()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM enseignant ORDER BY Nb_Classe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Matiere enseignée"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb_Classe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));

    return model;
}

QSqlQueryModel* enseignant::tri_decroissant()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM enseignant ORDER BY Nb_Classe DESC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Matiere enseignée"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb_Classe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));;

    return model;
}


QSqlQueryModel* enseignant::tri_nom()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM enseignant ORDER BY Nom");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Matiere enseignée"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb_Classe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));

    return model;
}
QSqlQueryModel* enseignant::tri_prenom()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM enseignant ORDER BY Prenom");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Matiere enseignée"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb_Classe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));

    return model;
}

QSqlQueryModel* enseignant::tri_date_naiss()
{
    QSqlQueryModel* model=new  QSqlQueryModel();

    model->setQuery("SELECT * FROM enseignant ORDER BY Date_naiss");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Matiere enseignée"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb_Classe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));

    return model;
}




QSqlQueryModel* enseignant::afficher_enseignant(QString Identifiant)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM enseignant WHERE Identifiant=:Identifiant ");
    query.bindValue(":Identifiant",Identifiant);
    QSqlQueryModel* model= new QSqlQueryModel();
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Matiere enseignée"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb_Classe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));

    return model;
}
QSqlQueryModel* enseignant::afficher_enseignant2(QString Matiere)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM enseignant WHERE Matiere=:Matiere ");
    query.bindValue(":Matiere",Matiere);
    QSqlQueryModel* model= new QSqlQueryModel();
    query.exec();
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Date_Naissance"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Matiere enseignée"));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr("Nb_Classe"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Sexe"));

    return model;
}


