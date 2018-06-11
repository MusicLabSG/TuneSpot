/*
 * File:    NotesDb.cpp
 * Author:  Spiros
 *
 * Created on Jun 10, 2018, 5:28 PM
 */

#include "NotesDb.h"

#include <QSql>
#include <QDir>
#include <QSqlDatabase>

NotesDb::NotesDb() {
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");

    QString db_path = QDir::currentPath();
    db_path.append("databse.db");
    mydb.setDatabaseName(db_path);

    if (mydb.open()) {
        //todo
    }
}
