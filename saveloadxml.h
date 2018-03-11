#ifndef SAVELOADXML_H
#define SAVELOADXML_H

#include <QString>
#include <QWidget>

class Calibrate;

class SaveLoadXML
{
public:
    ~SaveLoadXML();
    SaveLoadXML();
    void saveData(Calibrate*, QString, int, QWidget*);
private:
    QString filter;
    QString fileName;

};

#endif // SAVELOADXML_H
