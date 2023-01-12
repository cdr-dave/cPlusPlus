//
//  QObject.hpp
//  qt 信号与槽
//
//  Created by cdr on 2022/5/15.
//

#ifndef QObject_hpp
#define QObject_hpp
#include "QDef.h"
#include <stdio.h>

class QObject {
Q_OBJECT
public:
    QObject();
    ~QObject();
    
    void mainFunc();
    
signals:
    void sigPrint();
    
public slots:
    void sloPrint();
};

#endif /* QObject_hpp */
