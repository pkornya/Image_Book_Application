#include "imagedialog.h"
#include "ui_imagedialog.h"

#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>

ImageDialog::ImageDialog(QWidget *parent) : // OK
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

void ImageDialog::nextClicked() // OK
{
    currentImage = (currentImage + 1) % imageIds.count();
    updateCurrentImage();
}

void ImageDialog::previousClicked() // OK
{
    currentImage--;
    if (currentImage == -1)
        currentImage = imageIds.count() - 1;

    updateCurrentImage();
}

void ImageDialog::tagsChanged() // OK
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

void ImageDialog::addTagClicked()   // OK
{
    bool ok;
    QString tag = QInputDialog::getText(this, tr("Image Book"), tr("Tag:"),
                                        QLineEdit::Normal, QString(), &ok);

    if (ok) {
        tag = tag.toLower();
        QRegExp regExpr("[a-z]+");
        if (!regExpr.exactMatch(tag)) {
            QMessageBox::warning(this, tr("Image Book"),
                                 tr("This is not valid tag. "
                                 "Tags consists of lower case characters a-z."));
            return;
        }
        images.addTag(imageIds[currentImage], tag);
        updateTags();
    }
}

QStringList ImageDialog::selectedTags() // OK
{
    QStringList result;
    foreach(QListWidgetItem *item, ui->tagList->selectedItems())
        result << item->text();
    return result;
}

void ImageDialog::updateImages()
{
    int id;
    if (currentImage != -1)
        id = imageIds[currentImage];
    else
        id = -1;

    imageIds = images.getIds(selectedTags());
    currentImage = imageIds.indexOf(id);
    if (currentImage == -1 && !imageIds.isEmpty())
        currentImage = 0;

    ui->label->setText(QString::number(imageIds.count()));

    updateCurrentImage();
}

void ImageDialog::updateTags()  // OK
{
    QStringList selection = selectedTags();

    QStringList tags = images.getTags();
    ui->tagList->clear();
    ui->tagList->addItems(tags);

    for(int i = 0; i < ui->tagList->count(); ++i)
        if(selection.contains(ui->tagList->item(i)->text()))
            ui->tagList->item(i)->setSelected(true);
}

void ImageDialog::updateCurrentImage()
{
    if (currentImage == -1) {
        ui->imageLabel->setPixmap(QPixmap());
        ui->imageLabel->setText(tr("No image"));

        ui->addTagButton->setEnabled(false);
        ui->nextButton->setEnabled(false);
        ui->previousButton->setEnabled(false);
    }
    else {
        int width = ui->imageLabel->width();
        int height = ui->imageLabel->height();
        QImage image = images.getImage(imageIds[currentImage])
                       .scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

        ui->imageLabel->setPixmap(QPixmap::fromImage(image));
        ui->imageLabel->setText("");
        ui->addTagButton->setEnabled(true);
        ui->nextButton->setEnabled(true);
        ui->previousButton->setEnabled(true);
    }
}

ImageDialog::~ImageDialog() // OK
{
    delete ui;
}
