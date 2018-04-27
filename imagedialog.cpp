#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

#include "imagedialog.h"
#include "ui_imagedialog.h"

ImageDialog::ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);

    currentImage = -1;

    updateTags();
    updateImages();

    connect(ui->previousButton, SIGNAL(clicked(bool)),
            this, SLOT(previousClicked()));
    connect(ui->nextButton, SIGNAL(clicked(bool)),
            this, SLOT(nextClicked()));
    connect(ui->addTagButton, SIGNAL(clicked(bool)),
            this, SLOT(addTagClicked()));
    connect(ui->addImageButton, SIGNAL(clicked(bool)),
            this, SLOT(addImageClicked()));
    connect(ui->tagList, SIGNAL(itemSelectionChanged()),
            this, SLOT(tagsChanged()));

}

ImageDialog::~ImageDialog()
{
    delete ui;
}

void ImageDialog::nextClicked()
{
    currentImage = (currentImage + 1) % imageIds.count();
    updateCurrentImage();
}

void ImageDialog::previousClicked()
{
    currentImage--;
    if (currentImage == -1)
        currentImage = imageIds.count() - 1;

    updateCurrentImage();
}

void ImageDialog::tagsChanged()
{
    updateImages();
}

void ImageDialog::addImageClicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                       this, tr("Open file"), QString(),
                       tr("PNG Images (*.png)"));
    if (!fileName.isNull()) {
        QImage image(fileName);
        if (image.isNull()) {
            QMessageBox::warning(this, tr("Image Book"),
                                 tr("Failed to open the file '%1'")
                                 .arg(fileName));
            return;
        }

        images.addImage(image, selectedTags());
        updateImages();
    }
}

void ImageDialog::addTagClicked()
{
    bool ok;
    QString tag = QInputDialog::getText(this, tr("Image Book"), tr("Tag:"),
                                        QLineEdit::Normal, QString(), &ok);

    if (ok) {
        tag = tag.toLower();
        QRegExp regExpr("[a-z]+");
        if (regExpr.exactMatch(tag)) {
            QMessageBox::warning(this, tr("Image Book"),
                                 tr("This is not valid tag. "
                                 "Tags consists of lower case characters a-z."));
            return;
        }
        images.addTag(imageIds[currentImage], tag);
        updateTags();
    }
}

QStringList ImageDialog::selectedTags()
{

}

void ImageDialog::updateImages()
{

}

void ImageDialog::updateTags()
{

}

void ImageDialog::updateCurrentImage()
{

}
