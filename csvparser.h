#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QtDebug>

class CsvParser
{
public:

    CsvParser();
    QStringList* importCsv(QString fileName);
    void exportCsv(QString fileName, QStringList *srcList);

};

#endif // CSVPASER_H
