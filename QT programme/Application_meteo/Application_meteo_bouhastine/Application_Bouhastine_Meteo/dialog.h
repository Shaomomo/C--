#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "threadmeteowu.h"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_pushButton_Rechercher_clicked();
    void afficherResultat();
    void on_graphicsView_rubberBandChanged(const QRect &viewportRect, const QPointF &fromScenePoint, const QPointF &toScenePoint);


private:
    Ui::Dialog *ui;
    QGraphicsScene scene;
    ThreadMeteoWU * maThread;

};

#endif // DIALOG_H
