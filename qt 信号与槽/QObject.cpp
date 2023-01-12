//
//  QObject.cpp
//  qt 信号与槽
//
//  Created by cdr on 2022/5/15.
//

#include "QObject.hpp"
#include <stdio.h>

QObject::QObject() {
    printf("%s\n", __PRETTY_FUNCTION__);
}


QObject::~QObject() {
    printf("%s\n", __PRETTY_FUNCTION__);
}

void QObject::mainFunc() {
    printf("%s\n", __PRETTY_FUNCTION__);
    emit sigPrint();
}

void sloPrint() {
    printf("%s\n", __PRETTY_FUNCTION__);
}
