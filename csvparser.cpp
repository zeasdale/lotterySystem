#include "csvparser.h"

CsvParser::CsvParser()
{}

QStringList * CsvParser::importCsv(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Open csv file failed!";
        QStringList *error = new QStringList;
        return error; // 返回一个指针
    }
    QStringList *qlist = new QStringList();
    QStringList  strlist;
    QTextStream  in(&file);
    while (!in.atEnd()) {
        QString fileLine = in.readLine();
        strlist = fileLine.split(",", QString::SkipEmptyParts);
        qlist->append(strlist);
    }
    for (int i = 0; i < qlist->size(); i++) {
        qDebug() << qlist->at(i);
    }
    file.close();
    return qlist;
}
//导出csv文件
void CsvParser::exportCsv(QString fileName, QStringList *srcList)
{
    //打开.csv文件
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file for writing: "
                 << qPrintable(file.errorString());
        return;
    }
    QTextStream out(&file);
    //获取表格内容
    QStringList  rowlist;
    int row = srcList->size();//表格总行数
    for(int i = 0; i < row; i ++) {
        QString temp = srcList->at(i);
        rowlist = temp.split(",");
        for(int col = 0; col < rowlist.size(); col++) {
            out << rowlist.at(col) << ",";// 写入文件
        }
        out << "\n";
    }
    file.close();
}
