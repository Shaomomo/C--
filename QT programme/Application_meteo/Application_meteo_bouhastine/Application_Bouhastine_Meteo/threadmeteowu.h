#ifndef THREADMETEOWU_H
#define THREADMETEOWU_H
#include <iostream>
#include <string>
#include "meteowu.h"
#include "QMutex.h"
using namespace std;



#include <QThread>

class ThreadMeteoWU : public QThread
{
    Q_OBJECT
public:
    explicit ThreadMeteoWU(QObject *parent = 0);
protected:
    void run();
   // QMutex ;


signals:

public slots:


};

// Partage des variables globales
extern string ville;
extern string pays;
extern ConditionsActuelles CA;
extern ConditionsAVenir CF[4];
//extern QMutex ;

#endif // THREADMETEOWU_H
