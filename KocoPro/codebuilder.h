#ifndef CODEBUILDER_H
#define CODEBUILDER_H

#include <QApplication>
#include <vector>
#include <QGraphicsScene>
#include <QtDebug>
#include "dataandalgorithm.h"

using namespace std;

class codebuilder
{
public:
    codebuilder();
    void __init__();

    bool building();
public:
    vector<QString> Context;
    vector<Segment> BuildLines;
    vector<int> WainingLines;
};

#endif // CODEBUILDER_H
