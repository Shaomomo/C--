#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include "boussolle.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Boussolle BS;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QString mess ;
    bool EtatReception = false ;
    QThread MaThread ;
    string Latt ;
    string longitude ;
    string parametre ;

};

#endif // MAINWINDOW_H
