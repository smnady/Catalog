#include "readerinfodialog.h"
#include "ui_readerinfodialog.h"
#include "addreaderdialog.h"

void ReaderInfoDialog::onDialogClosed()
{
    emit dialogClosed();
    close();
}

ReaderInfoDialog::ReaderInfoDialog(QWidget *parent) :
    QDialog(parent)
{
    ("QDialog { background-color: #f0f0f0; }"
                  "QLabel { font-size: 14px; color: #333; }"
                  "QPushButton { font-size: 14px; color: #fff; background-color: #4CAF50; border: 1px solid #45a049; padding: 5px 10px; }"
                  "QPushButton:hover { background-color: #45a049; }");

    vbox = new QVBoxLayout(this);
    setLayout(vbox);
    setWindowTitle("Информация о читателе");
    resize(400, 300);
    show();
}

ReaderInfoDialog::~ReaderInfoDialog()
{

}

void ReaderInfoDialog::showInfo(Reader* reader)
{
    nameLabel = new QLabel("Имя: " + reader->getName());
    yearLabel = new QLabel("Год рождения: " + QString::number(reader->getYear()));
    vbox->addWidget(nameLabel);
    vbox->addWidget(yearLabel);
    vbox->addWidget(new QLabel("Id: " + QString::number(reader->getId())));
    QVector<CatalogBook>* bs = reader->getBooks();
    if (bs->size() > 0) {
        vbox->addWidget(new QLabel("Взятые книги: ", this));
        for (int i = 0; i < bs->size(); i++) {
            vbox->addWidget(new QLabel(QString::number(i+1) + "). " + (*bs)[i].getTitle() + ", " + (*bs)[i].getAuthors()));
        }
    }

    QPushButton* changeButton = new QPushButton("Редактировать");
    vbox->addWidget(changeButton);
    currentReader = reader;

    connect(changeButton, &QPushButton::clicked, this, &ReaderInfoDialog::setChanging);
}

void ReaderInfoDialog::setChanging()
{
    AddReaderDialog* dialog = new AddReaderDialog(this);
    connect(dialog, &AddReaderDialog::dialogClosed, this, &ReaderInfoDialog::onDialogClosed);
    dialog->setTitles(currentReader);
    dialog->show();
}
