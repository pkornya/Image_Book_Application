#ifndef IMAGECOLLECTION_H
#define IMAGECOLLECTION_H

#include <QDialog>

class ImageCollection
{
public:
    ImageCollection();

    QImage getImage(int id);
    QList<int> getIds(QStringList tags);
    QStringList getTags();

    void addTag(int id, QString tag);
    void addImage(QImage image, QStringList tags);

private:
    void populateDatabase();
};

#endif // IMAGECOLLECTION_H
