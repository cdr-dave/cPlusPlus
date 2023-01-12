//
//  moc_QObject.cpp
//  qt 信号与槽
//
//  Created by cdr on 2022/5/15.
//

#include <stdio.h>
#include "QObject.hpp"


void QObject::moc_callfunc() {
    printf("%s\n", __PRETTY_FUNCTION__);
}

void QObject::sigPrint() {
    printf("%s\n", __PRETTY_FUNCTION__);
}
