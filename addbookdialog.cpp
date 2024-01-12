#include "addbookdialog.h"
#include "ui_addbookdialog.h"
#include "infobookdialog.h"

AddBookDialog::AddBookDialog(QWidget *parent) :
    QDialog(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    titleLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Название:", this));
    layout->addWidget(titleLineEdit);

    publisherLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Издатель:", this));
    layout->addWidget(publisherLineEdit);

    yearLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Год издания:", this));
    layout->addWidget(yearLineEdit);

    pagesLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Количество страниц:", this));
    layout->addWidget(pagesLineEdit);

    authorsLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Автор(ы):", this));
    layout->addWidget(authorsLineEdit);

    quantityLineEdit = new QLineEdit(this);
    layout->addWidget(new QLabel("Количество в наличии:", this));
    layout->addWidget(quantityLineEdit);

    saveButton = new QPushButton("Сохранить", this);
    connect(saveButton, &QPushButton::clicked, this, &AddBookDialog::saveBook);
    layout->addWidget(saveButton);

    setWindowTitle("Добавление книги в каталог");
}
void AddBookDialog::setTitles(CatalogBook *book) {
    setWindowTitle("Редактирование");
    titleLineEdit->setText(book->getTitle());
    publisherLineEdit->setText(book->getPublisher());
    yearLineEdit->setText(QString::number(book->getYear()));
    pagesLineEdit->setText(QString::number(book->getPages()));
    authorsLineEdit->setText(book->getAuthors());
    quantityLineEdit->setText(QString::number(book->getQuantity()));
    curBook = book;
    disconnect(saveButton, &QPushButton::clicked, this, &AddBookDialog::saveBook);
    connect(saveButton, &QPushButton::clicked, this, &AddBookDialog::setChanges);
    show();
}
/*AddBookDialog::AddBookDialog(QWidget *parent, const CatalogBook& book)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    titleLineEdit = new QLineEdit(this);
    titleLineEdit->setText(book.getTitle());
    layout->addWidget(new QLabel("Название:", this));
    layout->addWidget(titleLineEdit);

    publisherLineEdit = new QLineEdit(this);
    publisherLineEdit->setText(book.getPublisher());
    layout->addWidget(new QLabel("Издатель:", this));
    layout->addWidget(publisherLineEdit);

    yearLineEdit = new QLineEdit(this);
    yearLineEdit->setText(QString::number(book.getYear()));
    layout->addWidget(new QLabel("Год издания:", this));
    layout->addWidget(yearLineEdit);

    pagesLineEdit = new QLineEdit(this);
    pagesLineEdit->setText(QString::number(book.getPages()));
    layout->addWidget(new QLabel("Количество страниц:", this));
    layout->addWidget(pagesLineEdit);

    authorsLineEdit = new QLineEdit(this);
    authorsLineEdit->setText(book.getAuthors().join(", "));
    layout->addWidget(new QLabel("Автор(ы):", this));
    layout->addWidget(authorsLineEdit);

    quantityLineEdit = new QLineEdit(this);
    quantityLineEdit->setText(QString::number(book.getQuantity()));
    layout->addWidget(new QLabel("Количество в наличии:", this));
    layout->addWidget(quantityLineEdit);

    saveButton = new QPushButton("Сохранить", this);
    connect(saveButton, &QPushButton::clicked, [=]() {
        setChanges(const_cast<CatalogBook&>(book));
        accept();
    });
    layout->addWidget(saveButton);
} */

AddBookDialog::~AddBookDialog()
{
}

void AddBookDialog::saveBook()
{
    QString title = titleLineEdit->text();
    QString publisher = publisherLineEdit->text();
    int year = yearLineEdit->text().toInt();
    int pages = pagesLineEdit->text().toInt();
    QString authors = authorsLineEdit->text();
    int quantity = quantityLineEdit->text().toInt();
    CatalogBook book(title, publisher, year, pages, authors, quantity);

    emit bookAdded(book);

    accept();
}

void AddBookDialog::setChanges()
{
    curBook->setTitle(titleLineEdit->text());
    curBook->setPublisher(publisherLineEdit->text());
    curBook->setYear(yearLineEdit->text().toInt());
    curBook->setPages(pagesLineEdit->text().toInt());
    curBook->setAutours(authorsLineEdit->text());
    curBook->setQuantity(quantityLineEdit->text().toInt());

    emit dialogClosed();
    close();
}
