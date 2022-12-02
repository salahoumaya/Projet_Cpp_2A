#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "partenaires.h"
#include <QMainWindow>
#include<QtPrintSupport/QPrinter>
#include "smtp.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_addpart_clicked();

    void on_supp_clicked();

    void on_pushButton_clicked();

    void on_btnrecherche_clicked();

    void on_comboBox_highlighted(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pdf_clicked();

    void sendMail();

    void mailSent(QString);

    void browse();

private:
    Ui::MainWindow *ui;
    partenaires p;
   QStringList files;
};
#endif // MAINWINDOW_H
