#include "evenement.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QDate>
Evenement::Evenement()
{
NumEvent=0;type="";nbinvit=0;heure="";duree=0;lieu="";
}
Evenement::Evenement(int NumEvent,QString type,int nbinvit,QDate date,QString heure,int duree,QString lieu)
{
    this->NumEvent=NumEvent;
    this->type=type;
    this->nbinvit=nbinvit;
    this->date=date;
    this->heure=heure;
    this->duree=duree;
    this->lieu=lieu;

}
int Evenement::getNumEvent(){return NumEvent;}
QString Evenement::gettype(){return type;}
int Evenement::getnbinvit(){return nbinvit;}
QDate Evenement::getdate(){return date;}
QString Evenement::getheure(){return heure;}
int Evenement::getduree(){return duree;}
QString Evenement::getlieu(){return lieu;}
void Evenement::setNumEvent(int NumEvent) { this->NumEvent=NumEvent; }
void Evenement::settype(QString type){ this->type=type;}
void Evenement::setnbinvit(int nbinvit){this->nbinvit=nbinvit;}
void Evenement::setdate(QDate date){ this->date=date;}
void Evenement::setheure(QString heure){ this->heure=heure;}
void Evenement::setduree(int duree){this->duree=duree;}
void Evenement::setlieu(QString lieu){this->lieu=lieu;}
bool Evenement::ajouter()
{
    QSqlQuery query;
    QString NumEvent1=QString::number(NumEvent);
      QString nbinvit1=QString::number(nbinvit);
        QString duree_string=QString::number(duree);
        query.prepare("INSERT INTO EVENEMENT (NUMEVENT,TYPE,NBINVIT,JOUR,HEURE,DUREE,LIEU) "
                      "VALUES (:numevent, :type, :nbinvit, :jour, :heure, :duree, :lieu)");


          query.bindValue(":numevent", NumEvent1);
          query.bindValue(":type",type);
          query.bindValue(":nbinvit", nbinvit1);
          query.bindValue(":jour", date);
          query.bindValue(":heure",heure);
          query.bindValue(":duree",duree_string);
          query.bindValue(":lieu", lieu);


          return query.exec();



}
bool Evenement::supprimer(int NumEvent)
{QSqlQuery query;
    QString res=QString::number(NumEvent);
    query.prepare("DELETE FROM EVENEMENT where numevent=:res");
    query.bindValue(0,res);
      return query.exec();

}
QSqlQueryModel *Evenement::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
  model->setQuery("SELECT* FROM EVENEMENT");
  model->setHeaderData(0,Qt::Horizontal, QObject::tr("numevent"));
  model->setHeaderData(1,Qt::Horizontal, QObject::tr("type"));
  model->setHeaderData(2,Qt::Horizontal, QObject::tr("nbinvit"));
  model->setHeaderData(3,Qt::Horizontal, QObject::tr("jour"));
  model->setHeaderData(4,Qt::Horizontal, QObject::tr("heure"));
  model->setHeaderData(5,Qt::Horizontal, QObject::tr("duree"));
  model->setHeaderData(6,Qt::Horizontal, QObject::tr("lieu"));
    return model;
  }
bool Evenement::modifier()
 {
    QSqlQuery query;

    QString NumEvent1=QString::number(NumEvent);
      QString nbinvit1=QString::number(nbinvit);
        QString duree_string=QString::number(duree);
        query.prepare("UPDATE EVENEMENT set  NUMEVENT=:numevent, TYPE=:type, NBINVIT=:nbinvit , JOUR=:jour,HEURE=:heure,DUREE=:duree,LIEU=:lieu WHERE NUMEVENT=:numevent ");
        query.bindValue(":numevent", NumEvent1);
        query.bindValue(":type",type);
        query.bindValue(":nbinvit", nbinvit1);
        query.bindValue(":jour", date);
        query.bindValue(":heure",heure);
        query.bindValue(":duree",duree_string);
        query.bindValue(":lieu", lieu);
        return query.exec();

 }
QSqlQueryModel* Evenement::rechercher(int NumEvent)
{

    QString res=QString::number( NumEvent);
    QSqlQueryModel* model = new QSqlQueryModel();

     model->setQuery("SELECT * FROM EVENEMENT WHERE NUMEVENT like '%"+res+"%'  ");

   return model;
}

QSqlQueryModel* Evenement::rechercherlieu(QString lieu)
{


    QSqlQueryModel* model = new QSqlQueryModel();

     model->setQuery("SELECT * FROM EVENEMENT WHERE LIEU like '%"+lieu+"%'  ");

   return model;
}
QSqlQueryModel* Evenement::recherchertype(QString type)
{


    QSqlQueryModel* model = new QSqlQueryModel();

     model->setQuery("SELECT * FROM EVENEMENT WHERE TYPE like '%"+type+"%'  ");

   return model;
}
QSqlQueryModel* Evenement::Trier(QString croissance,QString critere)
{
    QSqlQueryModel *modal=new QSqlQueryModel();

    if(critere == "NumEvent" && croissance == "ASC")
        modal->setQuery("select * from EVENEMENT order by NUMEVENT ASC ");
    else if(critere == "NumEvent" && croissance == "DESC")
        modal->setQuery("select * from EVENEMENT order by NUMEVENT  DESC ");

    else if(critere == "lieu" && croissance == "ASC")
        modal->setQuery("select * from EVENEMENT order by LIEU ASC ");
    else if(critere == "lieu" && croissance == "DESC")
        modal->setQuery("select * from EVENEMENT order by LIEU DESC ");

    else if(critere == "type" && croissance == "ASC")
        modal->setQuery("select * from EVENEMENT order by TYPE ASC ");
    else if(critere == "type" && croissance == "DESC")
        modal->setQuery("select * from EVENEMENT order by TYPE DESC ");

    else if(critere == "nbinvit" && croissance == "ASC")
        modal->setQuery("select * from EVENEMENT order by NBINVIT ASC ");
    else if(critere == "nbinvit" && croissance == "DESC")
        modal->setQuery("select * from EVENEMENT order by NBINVIT DESC ");



    else if(critere == "NumEvent" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by NUMEVENT");
    else if(critere == "NumEvent" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by NUMEVENT");

    else if(critere == "lieu" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by LIEU");
    else if(critere == "lieu" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by LIEU");

    else if(critere == "type" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by TYPE");
    else if(critere == "Prenom" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by TYPE");

    else if(critere == "nbinvit" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by NBINVIT");
    else if(critere == "nbinvit" && croissance == "")
        modal->setQuery("select * from EVENEMENT order by NBINVIT");

    return  modal;
}
