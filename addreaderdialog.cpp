#include "addreaderdialog.h"
#include "ui_addreaderdialog.h"

AddReaderDialog::AddReaderDialog(QWidget *parent) :
    QDialog(parent)
{
    vbox = new QVBoxLayout(this);

    nameEdit = new QLineEdit(this);
    yearEdit = new QLineEdit(this);

    QHBoxLayout* hb1 = new QHBoxLayout();
    hb1->addWidget(new QLabel("Имя: ", this));
    hb1->addWidget(nameEdit);

    vbox->addItem(hb1);

    QHBoxLayout* hb2 = new QHBoxLayout();
    hb2->addWidget(new QLabel("Год рождения: ", this));
    hb2->addWidget(yearEdit);

    vbox->addItem(hb2);

    saveButton = new QPushButton("Сохранить", this);
    connect(saveButton, &QPushButton::clicked, this, &AddReaderDialog::saveReader);

    vbox->addWidget(saveButton);

    setWindowTitle("Добавление читателя в каталог");
    setLayout(vbox);
}

AddReaderDialog::~AddReaderDialog()
{

}

void AddReaderDialog::setTitles(Reader *reader)
{
    setWindowTitle("Редактирование");
    nameEdit->setText(reader->getName());
    yearEdit->setText(QString::number(reader->getYear()));

    curReader = reader;

    disconnect(saveButton, &QPushButton::clicked, this, &AddReaderDialog::saveReader);
    connect(saveButton, &QPushButton::clicked, this, &AddReaderDialog::setChanges);
    show();
}

void AddReaderDialog::saveReader()
{
    QString name = nameEdit->text();
    unsigned int year = yearEdit->text().toUInt();
    Reader reader(name, year);

    emit readerAdded(reader);

    accept();
}

void AddReaderDialog::setChanges()
{
    curReader->setName(nameEdit->text());
    curReader->setYear(yearEdit->text().toInt());

    emit dialogClosed();
    close();
}
