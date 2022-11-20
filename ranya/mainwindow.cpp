#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"evenement.h"
#include "qrcode.h"
#include<QString>
#include"mainwindow.h"
#include <iostream>
#include <iostream>
#include <ostream>
#include "piechart.h"
#include <QMessageBox>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlError>
#include <QTextStream>
#include <QFileDialog>
#include <QPrinter>
#include <QTextDocument>
#include <fstream>
#include <windows.h>
#include <QTextStream>
#include <QPixmap>
#include <QPainter>
#include "connection.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabEvenement->setModel(EV.afficher());
    /*ui->Stat->addWidget(EV.stat_type(), 0, 0);
    ui->Stat->addWidget(EV.stat_date(), 0, 0);
    ui->Stat->addWidget(EV.stat_date_type(), 0, 0);*/
 EV.stat_type()->setParent(ui->stat);
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
      if (test){   ui->tabEvenement->setModel(EV.afficher());
           EV.stat_type()->setParent(ui->stat);
          msgbox.setText("ajout avec succes");

      }
      else msgbox.setText("echec d'ajout");
      msgbox.exec();
}
void MainWindow::on_tabEvenement_clicked(const QModelIndex &index)
{
   QString select=ui->tabEvenement->model()->data(index).toString();
   QSqlQuery qry;


   qry.prepare("select * from EVENEMENT where NUMEVENT LIKE '"+select+"'");

   if(qry.exec())
   {
       while(qry.next())
       {
           //Remplir tous les champs par les données concernées

           ui->leNumEvent->setText(qry.value(0).toString());
           ui->letype->setText(qry.value(1).toString());
           ui->lenbinvit->setText(qry.value(2).toString());
           ui->ledate->setText(qry.value(3).toString());
           ui->leheure->setText(qry.value(4).toString());
           ui->leduree->setText(qry.value(5).toString());
           ui->lelieu->setText(qry.value(6).toString());
}
}
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
                   EV.stat_type()->setParent(ui->stat);
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
          EV.stat_type()->setParent(ui->stat);
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




void MainWindow::on_pdf_clicked()
{

     QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
            if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }
     QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tabEvenement->model()->rowCount();
                    const int columnCount =ui->tabEvenement->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("eleve")
                            <<  "</head>\n"
                            "<body bgcolor=#e2fdec link=#5000A0>\n"
                                "<h1  style='color:#1e114b'>>Liste des Evenements</h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";

                    // headers
                        out << "<thead><tr bgcolor=#f8fcd6>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tabEvenement->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tabEvenement->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tabEvenement->isColumnHidden(column)) {
                                       QString data = ui->tabEvenement->model()->data(ui->tabEvenement->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";



            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);



            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            document->print(&printer);

        }





//calendrier
void MainWindow::on_calendarWidget_selectionChanged()
{
    ui->dateEdit_5->setDate(ui->calendarWidget->selectedDate());

        QDate date=ui->dateEdit_5->date();

        QDate datet;
        datet=date;

        QSqlQuery qry;


        qry.prepare("select * from EVENEMENT ");

        if(qry.exec())
        {
            while(qry.next())
            {
                //Remplir tous les champs par les données concernées
    datet=date;
    if(qry.value(3)==datet)
    {
                ui->numevent_cal->setText(qry.value(0).toString());
                ui->type_cal->setText(qry.value(1).toString());
                ui->nbinvit_cal->setText(qry.value(2).toString());
                ui->date_cal->setText(qry.value(3).toString());
                ui->heure_cal->setText(qry.value(4).toString());
                ui->duree_cal->setText(qry.value(5).toString());
                ui->lieu_cal->setText(qry.value(6).toString());
    }//fin if
    }//fin while
    }//fin if qry
    }//fin fnt



void MainWindow::on_qrcode_button_clicked()
{
    using namespace qrcodegen;

    ///////////////// data collecting ////////////////////////
    QTableView tabEvenement;
    QSqlQueryModel * Mod=new  QSqlQueryModel();
    QString value=ui->num->text();
           Connection c;

         QSqlQuery qry;




         qry.prepare("select * from EVENEMENT where NUMEVENT='"+value+"'");
         qry.exec();
         Mod->setQuery(qry);
         tabEvenement.setModel(Mod);


        /* QSqlQueryModel * model=new QSqlQueryModel();
       model->setQuery("SELECT* FROM EVENEMENT");*/

        QString NUMEVENT = tabEvenement.model()->data(tabEvenement.model()->index(0, 0)).toString().simplified();
        QString TYPE = tabEvenement.model()->data(tabEvenement.model()->index(0, 1)).toString().simplified();
        QString NBINVIT = tabEvenement.model()->data(tabEvenement.model()->index(0, 2)).toString().simplified();
        QString DATE = tabEvenement.model()->data(tabEvenement.model()->index(0, 3)).toString().simplified();
        QString HEURE = tabEvenement.model()->data(tabEvenement.model()->index(0, 4)).toString().simplified();
        QString DUREE = tabEvenement.model()->data(tabEvenement.model()->index(0, 5)).toString().simplified();
        QString LIEU = tabEvenement.model()->data(tabEvenement.model()->index(0, 6)).toString().simplified();



    QString text = NUMEVENT+"\n"+TYPE+"\n"+NBINVIT+"\n"+DATE+"\n"+HEURE+"\n"+DUREE+"\n"+LIEU+"\n";
      // Create the QR Code object
      QrCode qr = QrCode::encodeText( text.toUtf8().data(), QrCode::Ecc::MEDIUM );

      qint32 sz = qr.getSize();
      QImage im(sz,sz, QImage::Format_RGB32);
        QRgb black = qRgb( 191,112,105 );
        QRgb white = qRgb(255,255,255);
      for (int y = 0; y < sz; y++)
        for (int x = 0; x < sz; x++)
          im.setPixel(x,y,qr.getModule(x, y) ? black : white );
      ui->qraff->setPixmap( QPixmap::fromImage(im.scaled(200,200,Qt::KeepAspectRatio,Qt::FastTransformation),Qt::MonoOnly) );
}









