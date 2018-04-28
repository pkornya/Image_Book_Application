#include <QtSql>

#include "imagecollection.h"

ImageCollection::ImageCollection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName(":memory");
    if (!db.open())
        qFatal("Failed to open database");

    populateDatabase();
}

void ImageCollection::populateDatabase()
{
    QSqlQuery qry;

    qry.prepare("CREATE TABLE IF NOT EXISTS images "
                "(id INTEGER PRIMARY KEY, data BLOB)");
    if (!qry.exec())
        qFatal("Failed to create table images");

    qry.prepare("CREATE TABLE IF NOT EXISTS tags (id INTEGER, tag VARCHAR(30))");
    if (!qry.exec())
        qFatal("Failed to create table tags");

}

QImage ImageCollection::getImage(int id)
{

}

QList<int> ImageCollection::getIds(QStringList tags)
{

}

QStringList ImageCollection::getTags()
{

}

void ImageCollection::addTag(int id, QString tag)
{

}

void ImageCollection::addImage(QImage image, QStringList tags)
{

}


