#include "catalog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

Catalog::Catalog(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("QWidget { background-color: #f0f0f0; }"
                  "QLabel { font-size: 14px; color: #333; }"
                  "QPushButton { font-size: 14px; color: #fff; background-color: #4CAF50; border: 1px solid #45a049; padding: 5px 10px; }"
                  "QPushButton:hover { background-color: #45a049; }"
                  "QListView {show-decoration-selected: 1; }"
                  "QListView::item { height: 30px; border-radius: 5px; }"
                  "QListView::item:alternate {background: #6a6ea9; height: 25px;}"
                  "QListView::item:selected {border: 1px solid #6a6ea9;}"
                  "QListView::item:selected:!active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ABAFE5, stop: 1 #8588B2);}"
                  "QListView::item:selected:active {background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #6a6ea9, stop: 1 #888dd9);}"
                  "QListView::item:hover { background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #FAFBFE, stop: 1 #DCDEF1);}"
                  );

    type = BookType;
    hbox = new QHBoxLayout();
    vbox = new QVBoxLayout(this);
    vbox->addLayout(hbox);

    QPushButton* bookButton = new QPushButton("Книги", this);
    hbox->addWidget(bookButton);
    QPushButton* readerButton = new QPushButton("Читатели", this);
    hbox->addWidget(readerButton);
    QPixmap savePix("://save.png");
    QPushButton* saveButton = new QPushButton(QIcon(savePix), "", this);
    saveButton->setToolTip("Сохранить данные");
    hbox->addWidget(saveButton);

    connect(saveButton, &QPushButton::clicked, this, &Catalog::saveData);
    connect(bookButton, &QPushButton::clicked, this, [this]() { Catalog::setType(1); });
    connect(readerButton, &QPushButton::clicked, this, [this]() { Catalog::setType(2); });

    addButton = new QPushButton(this);
    listView = new QListView(this);
    vbox->addWidget(listView);

    bookModel = new QStandardItemModel(this);
    readerModel = new QStandardItemModel(this);

    vbox->addWidget(addButton);



    loadData();
    setupUi();
    showInfo();
}

Catalog::~Catalog()
{
}

void Catalog::setupUi()
{
    switch (type) {
    case BookType:
        addButton->setText("Добавить книгу");

        disconnect(listView, &QListView::doubleClicked, this, &Catalog::showReaderInfoDialog);
        disconnect(addButton, &QPushButton::clicked, this, &Catalog::showAddReaderDialog);

        connect(addButton, &QPushButton::clicked, this, &Catalog::showAddBookDialog);
        connect(listView, &QListView::doubleClicked, this, &Catalog::showBookInfoDialog);
        break;
    case ReaderType:
        addButton->setText("Добавить читателя");

        disconnect(listView, &QListView::doubleClicked, this, &Catalog::showBookInfoDialog);
        disconnect(addButton, &QPushButton::clicked, this, &Catalog::showAddBookDialog);

        connect(addButton, &QPushButton::clicked, this, &Catalog::showAddReaderDialog);
        connect(listView, &QListView::doubleClicked, this, &Catalog::showReaderInfoDialog);
        break;
    }
}

void Catalog::showInfo()
{
    switch (type) {
    case BookType:
        bookModel = new QStandardItemModel(this);

        foreach (const CatalogBook& book, books) {
            QStandardItem* item = new QStandardItem(book.getTitle() + ", " + book.getAuthors());
            item->setData(QVariant::fromValue(book.getId()), Qt::UserRole+1);
            bookModel->appendRow(item);
        }

        listView->setModel(bookModel);

        break;
    case ReaderType:
        readerModel = new QStandardItemModel(this);

        foreach (const Reader& reader, readers) {
            QStandardItem* item = new QStandardItem(reader.getName() + ", " + QString::number(reader.getYear()));
            item->setData(QVariant::fromValue(reader.getId()), Qt::UserRole + 1);
            readerModel->appendRow(item);
        }

        listView->setModel(readerModel);

        break;
    default:
        break;
    }
}

void Catalog::showAddBookDialog()
{
    AddBookDialog* dialog = new AddBookDialog(this);
    connect(dialog, &AddBookDialog::bookAdded, this, &Catalog::addBook);
    dialog->exec();
}
void Catalog::showAddReaderDialog()
{
    AddReaderDialog* dialog = new AddReaderDialog(this);
    connect(dialog, &AddReaderDialog::readerAdded, this, &Catalog::addReader);
    dialog->exec();
}

void Catalog::showBookInfoDialog(const QModelIndex& index)
{
    if(index.isValid()) {
        QVariant itemData = index.data(Qt::UserRole + 1);
        int id = itemData.toInt();
        CatalogBook* catalogBook;
        for (int i = 0; i < books.size(); i++){
            if(books[i].getId()==id) {
                catalogBook = &books[i];
                qDebug() << "Book found, id: " << books[i].getId();
                break;
            }
        }
        for (int i = 0; i < (*catalogBook->getReaders()).size(); i++)
            qDebug() << (*catalogBook->getReaders())[i].getName();
        InfoBookDialog* infoBookDialog = new InfoBookDialog(this);
        connect(infoBookDialog, &InfoBookDialog::dialogClosed, this, &Catalog::showInfo);
        connect(infoBookDialog, &InfoBookDialog::deleteB, this, &Catalog::deleteBook);
        infoBookDialog->showInfo(catalogBook, readers);
    }
}

void Catalog::showReaderInfoDialog(const QModelIndex& index)
{
    if(index.isValid()) {
        QVariant itemData = index.data(Qt::UserRole + 1);
        int id = itemData.toUInt();
        Reader* reader;
        for (int i = 0; i < readers.size(); i++) {
            if (readers[i].getId()==id) {
                reader = &readers[i];
                qDebug() << "Reader found, id: " << reader->getId();
                break;
            }
        }
        ReaderInfoDialog* infoDialog = new ReaderInfoDialog(this);
        connect(infoDialog, &ReaderInfoDialog::dialogClosed, this, &Catalog::showInfo);
        infoDialog->showInfo(reader);
    }
}

void Catalog::deleteBook(int bookId)
{
    CatalogBook* curBook;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].getId() == bookId) {
            curBook = &books[i];
            break;
        }
    }
    books.removeOne(*curBook);
    showInfo();
}

void Catalog::addBook(const CatalogBook &book)
{
    books.append(book);

    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(listView->model());
    if(model) {
        model->appendRow(new QStandardItem(book.getTitle()));
    }
}

void Catalog::addReader(const Reader &reader)
{
    readers.append(reader);

    QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(listView->model());
    if(model) {
        model->appendRow(new QStandardItem(reader.getName()));
    }
}

void Catalog::saveData()
{
    QFile file("booksData.dat");
    if (!file.open(QIODevice::WriteOnly))
        return;

    QDataStream out(&file);

    out.setVersion(QDataStream::Qt_4_0);

    foreach (const CatalogBook &book, books) {
        book.serialize(out);
    }

    file.close();

    QFile rfile("readersData.dat");
    if (!rfile.open(QIODevice::WriteOnly))
        return;

    QDataStream rout(&rfile);

    rout.setVersion(QDataStream::Qt_4_0);

    foreach (const Reader &reader, readers)
        reader.serialize(rout);
}

void Catalog::loadData()
{
    QFile rfile("readersData.dat");
    if (!rfile.open(QIODevice::ReadOnly))
        return;

    QDataStream rin(&rfile);
    rin.setVersion((QDataStream::Qt_4_0));

    while (!rin.atEnd()) {
        Reader reader("", 0);
        reader.deserialize(rin);
        readers.append(reader);
    }

    QFile file("booksData.dat");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_0);

    while(!in.atEnd()) {
        CatalogBook book("", "", 0, 0, "", 0);
        book.deserialize(in);
        books.append(book);
    }
    file.close();
    for (auto it = CatalogBook::conMap.begin(); it != CatalogBook::conMap.end(); ++it) {

        int bookId = it.key();
        int readerId = it.value();

        CatalogBook* book = nullptr;
        for (auto& b : books) {
            if (b.getId() == bookId) {
                book = &b;
                break;
            }
        }

        Reader* reader;
        for (auto& r : readers) {
            if (r.getId() == readerId) {
                reader = &r;
                break;
            }
        }

        (*book->getReaders()).append(*reader);
        book->takeBook();
        (*reader->getBooks()).append(*book);

    }
}

void Catalog::setType(unsigned short n)
{
    switch (n) {
    case 1:
        type = BookType;
        break;
    case 2:
        type = ReaderType;
        break;
    default:
        type = BookType;
        break;
    }
    setupUi();
    showInfo();
}



