#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include "imagecollection.h"

#include <QDialog>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent = 0);
    ~ImageDialog();

private slots:
    void nextClicked();
    void previousClicked();
    void tagsChanged();

    void addImageClicked();
    void addTagClicked();

private:
    QStringList selectedTags();

    void updateImages();
    void updateTags();
    void updateCurrentImage();

private:
    Ui::ImageDialog *ui;
    QList<int> imageIds;
    int currentImage;
    ImageCollection images;
};

#endif // IMAGEDIALOG_H
