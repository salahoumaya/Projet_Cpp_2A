#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"evenement.h"
#include<QString>
#include"mainwindow.h"
#include <QMessageBox>
#include<QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabEvenement->setModel(EV.afficher());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{  int NumEvent=ui->leNumEvent->text().toInt();


   QString type=ui->letype->text();
   int  nbinvit=ui->lenbinvit->text().toInt();
    QDate date=ui->dateEdit->date();
     QString heure=ui->leheure->text();
    int duree=ui->leduree->text().toInt();
      QString lieu=ui->lelieu->text();
      Evenement EV(NumEvent,type,nbinvit,date,heure,duree,lieu);
      QMessageBox msgbox;
      bool test=EV.ajouter();
      if (test){
          msgbox.setText("ajout avec succes");
          ui->tabEvenement->setModel(EV.afficher());
      }
      else msgbox.setText("echec d'ajout");
      msgbox.exec();
}
void MainWindow::on_mdf_clicked()
{
    int NumEvent=ui->leNumEvent->text().toInt();
    QString type=ui->letype->text();
       int  nbinvit=ui->lenbinvit->text().toInt();
        QDate date=ui->dateEdit->date();
         QString heure=ui->leheure->text();
        int duree=ui->leduree->text().toInt();
          QString lieu=ui->lelieu->text();
          Evenement EV(NumEvent,type,nbinvit,date,heure,duree,lieu);

          QMessageBox msgbox;
          bool test=EV.modifier();
          if (test){
              msgbox.setText("modif avec succes");
              ui->tabEvenement->setModel(EV.afficher());
          }
          else msgbox.setText("echec de modif");
          msgbox.exec();}

void MainWindow::on_pb_supprimer_clicked()
{
    int NumEvent=ui->lineEdit_6->text().toInt();
    bool test=EV.supprimer(NumEvent);
   if(test)
    {QMessageBox::information(nullptr,QObject::tr("OK"),
                              QObject::tr("suppression effectue\n click cancel to exit."),QMessageBox::Cancel);
     ui->tabEvenement->setModel(EV.afficher());
    }
      else  {QMessageBox::critical(nullptr,QObject::tr("NOT OK"),
                                      QObject::tr("suppression non effectue\n click cancel to exit."),QMessageBox::Cancel);}


}


void MainWindow::on_prechercher_clicked()
{
    int NumEvent=ui->rechercher->text().toInt();

         ui->tableView->setModel(EV.rechercher(NumEvent));


}




void MainWindow::on_recherchelieu_textChanged(const QString &arg1)
{
    QString lieu=ui->recherchelieu->text();

           ui->tableViewlieu->setModel(EV.rechercherlieu(arg1));
}



void MainWindow::on_comboBox_highlighted(const QString &arg1)
{

      Evenement e;
        QString type="";

        if(ui->radioButton->isChecked())
            type="ASC";
        else if(ui->radioButton_2->isChecked())
            type="DESC";

        if(arg1 != "Choisir")
            ui->tabletri->setModel(e.Trier(type,arg1));

        else  ui->tabletri->setModel(e.afficher());

    }

    //choisir radio button ascendant
    void MainWindow::on_radioButton_clicked()
    {
        Evenement e;
        QString type="";


        if(ui->radioButton->isChecked())
            type="ASC";
        else if(ui->radioButton_2->isChecked())
            type="DESC";

        if(ui->comboBox->currentText() != "Choisir")
            ui->tabletri->setModel(e.Trier(type,ui->comboBox->currentText()));

        else  ui->tabletri->setModel(e.afficher());
    }


    //choisir radio button descendant
    void MainWindow::on_radioButton_2_clicked()
    {
        Evenement e;
        QString type="";

        if(ui->radioButton->isChecked())
            type="ASC";
        else if(ui->radioButton_2->isChecked())
            type="DESC";

        if(ui->comboBox->currentText() != "Choisir")
            ui->tabletri->setModel(e.Trier(type,ui->comboBox->currentText()));


        else  ui->tabletri->setModel(e.afficher());
    }






void MainWindow::on_recherchertype_textChanged(const QString &arg1)
{
    QString type=ui->recherchelieu->text();

           ui->tableViewtype->setModel(EV.recherchertype(arg1));
}
