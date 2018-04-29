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
    QSqlQuery qry;

    if (tags.count() == 0)
        qry.prepare("SELECT images.id FROM images");
    else
        qry.prepare("SELECT id FROM tags WHERE tag IN ('" +
                     tags.join("','") + "') GROUP BY id");
    if(!qry.exec())
        qFatal("Failed to get IDs");

    QList<int> result;
    while(qry.next())
        result << qry.value(0).toInt();

    return result;
}

QStringList ImageCollection::getTags()
{
    QSqlQuery qry;
    qry.prepare("SELECT DISTINCT tag FROM tags");
    if(!qry.exec())
        qFatal("Failed to get tags");

    QStringList result;
    while (qry.next())
        result << qry.value(0).toString();

    return result;
}

void ImageCollection::addTag(int id, QString tag)
{
    QSqlQuery qry;

    qry.prepare("INSERT INTO tags (id, tag) VALUES (:id, :tag)");
    qry.bindValue(":id", id);
    qry.bindValue(":tag", tag);
    if(!qry.exec())
        qFatal("Failed to add tag");
}

void ImageCollection::addImage(QImage image, QStringList tags)
{

}


