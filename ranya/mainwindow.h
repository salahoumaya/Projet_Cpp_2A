#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"evenement.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_prechercher_clicked();



void on_recherchelieu_textChanged(const QString &arg1);

    void on_comboBox_highlighted(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

 void on_mdf_clicked();

 void on_recherchertype_textChanged(const QString &arg1);

 void on_pdf_clicked();



 void on_calendarWidget_selectionChanged();

 void on_qrcode_button_clicked();





 void on_tabEvenement_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    Evenement EV;
};

#endif // MAINWINDOW_H
