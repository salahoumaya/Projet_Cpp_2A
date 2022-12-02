#include "mainwindow.h"
#include<QTextStream>
#include "partenaires.h"
#include<QMessageBox>
#include"connection.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<QtPrintSupport/QPrinter>
#include<QTextDocument>
#include <QIntValidator>
#include<QValidator>
#include<QSqlQueryModel>
#include<QSqlError>
#include<QSettings>
//#include "exportexcelobject.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableau->setModel(p.afficher());
    ui->tablerech->setModel(p.afficher1());

    connect(ui->sendbtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->browsebtn, SIGNAL(clicked()), this, SLOT(browse()));

    //maps
    QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                       QCoreApplication::organizationName(), QCoreApplication::applicationName());

    ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://accounts.google.com/v3/signin/identifier?dsh=S-855206879%3A1669964938157820&continue=https%3A%2F%2Fmail.google.com%2Fmail%2F&rip=1&sacu=1&service=mail&flowName=GlifWebSignIn&flowEntry=ServiceLogin&ifkv=ARgdvAsbUlfuPhNB15tn6ODRKk5QfH2o2DOJ_-y_PVqfpqV_tfdDWg_DVE2Nddd3Kh7_5PZexuee");
    //maps


    ui->axWidget->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");

}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_addpart_clicked()
{
    int id=ui->edid->text().toInt();
    QString nomentr=ui->edentremprise->text();
    QString nom=ui->ednom->text();
    QString prenom=ui->edprenom->text();
    QString service=ui->edservice->text();
    QString email=ui->edemail->text();
        int numeros=ui->ednumeros->text().toInt();
        partenaires p (id,nomentr,nom,prenom,service,email,numeros);
        bool test=p.ajouter();
        QMessageBox msgbox;
        if(test)
        {   msgbox.setText("ajout avec succes");


           ui->tableau->setModel(p.afficher());

        }
        else
        {msgbox.setText("echec d'ajout ");
            msgbox.exec();
        }

}


void MainWindow::on_supp_clicked()
{
    partenaires p;
    p.setid(ui->supid->text().toInt());
    bool test=p.supprimer(p.getid());
QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("sup avc succe");
       ui->tableau->setModel(p.afficher());

    }
    else
      msgbox.setText("echec de supp");
    msgbox.exec();

}


void MainWindow::on_pushButton_clicked()
{

    int id=ui->edid->text().toInt();
              QString nomentr=ui->edentremprise->text();
              QString nom=ui->ednom->text();
              QString prenom=ui->edprenom->text();
              QString service=ui->edservice->text();
              QString email=ui->edemail->text();
                  int numeros=ui->ednumeros->text().toInt();
           partenaires p (id,nomentr,nom,prenom,service,email,numeros);
                  QString res = QString::number(id);
                  QString resn1 = QString::number(numeros);
            QSqlQuery quer;

            quer.prepare("update PARTENAIRE set NOMENTREPRISE='"+nomentr+"' ,nom='"+nom+"', prenom='"+prenom+"', service='"+service+"', email='"+email+"', numeros='"+resn1+"' where id='"+res+"'");
              if(quer.exec())
              {

                  ui->tableau->setModel(p.afficher());

               QMessageBox::information(nullptr,QObject::tr("OK"),
                                        QObject::tr("modification effectué \n"
                                                    "Click Cancel to exit."),QMessageBox::Cancel);
              }
              else
                  QMessageBox::critical(nullptr,QObject::tr("not OK"),
                                        QObject::tr("modification non effectué \n"
                                                    "Click Cancel to exit."),QMessageBox::Cancel);
    /*  int id=ui->edid->text().toInt();
          QString nomentr=ui->edentremprise->text();
          QString nom=ui->ednom->text();
          QString prenom=ui->edprenom->text();
          QString service=ui->edservice->text();
          QString email=ui->edemail->text();
              int numeros=ui->ednumeros->text().toInt();
              partenaires p (id,nomentr,nom,prenom,service,email,numeros);

              QMessageBox msgbox;
              bool test=p.modifier();
              if (test){
                  msgbox.setText("modif avec succes");
                  ui->tableau->setModel(p.afficher());
              }
              else msgbox.setText("echec de modif");
              msgbox.exec();




    * int id=ui->edid->text().toInt();
    QString nomentr=ui->edentremprise->text();
    QString nom=ui->ednom->text();
    QString prenom=ui->edprenom->text();
    QString service=ui->edservice->text();
    QString email=ui->edemail->text();
        int numeros=ui->ednumeros->text().toInt();
        partenaires p (id,nomentr,nom,prenom,service,email,numeros);
    *
    * QItemSelectionModel *select = ui->tableau->selectionModel();
              ui->edid->setText(select->selectedRows(0).value(0).data().toString());
               ui->edentremprise->setText(select->selectedRows(1).value(0).data().toString());
               ui->ednom->setText(select->selectedRows(2).value(0).data().toString());
              ui->edprenom->setText(select->selectedRows(3).value(0).data().toString());
              ui->edservice->setText(select->selectedRows(4).value(0).data().toString());
              ui->edemail->setText(select->selectedRows(4).value(0).data().toString());
              ui->ednumeros->setText(select->selectedRows(4).value(0).data().toString());*/
            //  p.modifier();
    /*partenaires p;
    p.setid(ui->edid->text().toInt());
    p.setemail(ui->edemail->text());
    bool test=p.modemail(p.getemail(),p.getid());
QMessageBox msgbox;
    if(test)
    {
        msgbox.setText("mod avc succe");
       ui->tableau->setModel(p.afficher());

    }
    else
      msgbox.setText("echec de mod");
    msgbox.exec();


   QSqlQuery q;
    QString m=ui->edemail->text();
    int res=ui->edid->text().toInt();
    //Marqueurs ?
    q.exec("UPDATE PARTENAIRE SET email=? WHERE id =?");
    q.addBindValue(m);
    q.addBindValue(res);
    ui->tableau->setModel(p.afficher());*/

}

void MainWindow::on_btnrecherche_clicked()
{
    partenaires p;
           QString n=ui->edrecherche->text();
           ui->tablerech->setModel(p.recherche(n));
}

void MainWindow::on_comboBox_highlighted(const QString &arg1)
{

          partenaires p;
            QString type="";

            if(ui->radioButton->isChecked())
                type="ASC";
            else if(ui->radioButton_2->isChecked())
                type="DESC";

            if(arg1 != "Choisir")
                ui->tableau->setModel(p.trier(type,arg1));

            else  ui->tableau->setModel(p.afficher());


}

void MainWindow::on_radioButton_clicked()
{
    partenaires p;
            QString type="";


            if(ui->radioButton->isChecked())
                type="ASC";
            else if(ui->radioButton_2->isChecked())
                type="DESC";

            if(ui->comboBox->currentText() != "Choisir")
                ui->tableau->setModel(p.trier(type,ui->comboBox->currentText()));

            else  ui->tableau->setModel(p.afficher());
}

void MainWindow::on_radioButton_2_clicked()
{
    partenaires p;
            QString type="";

            if(ui->radioButton->isChecked())
                type="ASC";
            else if(ui->radioButton_2->isChecked())
                type="DESC";

            if(ui->comboBox->currentText() != "Choisir")
                ui->tableau->setModel(p.trier(type,ui->comboBox->currentText()));


            else  ui->tableau->setModel(p.afficher());
}

void MainWindow::on_pdf_clicked()
{

    QString strStream;
      QTextStream out(&strStream);

   const int rowCount = ui->tableau->model()->rowCount();
   const int columnCount = ui->tableau->model()->columnCount();
   out <<  "<html>\n"
           "<head>\n"
   "<meta Content=\"Text/html; charset=Windows-1251\">\n"
   <<  QString("<title>%1</title>\n").arg("strTitle")
   <<  "</head>\n"
  "<body bgcolor=#ffffff link=#5000A0>\n"

  //     "<align='right'> " << datefich << "</align>"
     "<center> <H1>Liste Des Partenaires  </H1></br></br><table border=1 cellspacing=0 cellpadding=2>\n";

             // headers
    out << "<thead><tr bgcolor=#f0f0f0> <th>Numero</th>";
   for (int column = 0; column < columnCount; column++)
   if (!ui->tableau->isColumnHidden(column))
       out << QString("<th>%1</th>").arg(ui->tableau->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

                                           // data table
           for (int row = 0; row < rowCount; row++) {
            out << "<tr> <td bkcolor=0>" << row+1 <<"</td>";
              for (int column = 0; column < columnCount; column++) {
            if (!ui->tableau->isColumnHidden(column)) {
     QString data = ui->tableau->model()->data(ui->tableau->model()->index(row, column)).toString().simplified();
     out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                                   }
                                               }
                      out << "</tr>\n";
                                           }
                            out <<  "</table> </center>\n"
                                    "</body>\n"
                                  "</html>\n";
      QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Sauvegarder en PDF", QString(), "*.pdf");
                    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

                   QPrinter printer (QPrinter::PrinterResolution);
                    printer.setOutputFormat(QPrinter::PdfFormat);
                   printer.setPaperSize(QPrinter::A4);
                  printer.setOutputFileName(fileName);

                   QTextDocument doc;
                    doc.setHtml(strStream);
                    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
                    doc.print(&printer);
}


//mailing
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("agbemavoharold@gmail.com",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("agbemavoharold@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("agbemavoharold@gmail.com", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
    ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
