#include "infobookdialog.h"
#include "addbookdialog.h"

InfoBookDialog::InfoBookDialog(QWidget *parent) :
    QDialog(parent)
{
    setStyleSheet("QDialog { background-color: #f0f0f0; }"
                  "QLabel { font-size: 14px; color: #333; }"
                  "QPushButton { font-size: 14px; color: #fff; background-color: #4CAF50; border: 1px solid #45a049; padding: 5px 10px; }"
                  "QPushButton:hover { background-color: #45a049; }");

    labelInfo = new QLabel("Книгу взяли: ", this);
    vbox = new QVBoxLayout(this);
    hb1 = new QHBoxLayout();
    hbox = new QHBoxLayout();
    readersBox = new QComboBox(this);
    label = new QLabel("Назначить книгу: ", this);
    giveOut = new QPushButton("Выдать", this);
    changeButton = new QPushButton("Редактировать", this);
    changing = false;
    QPixmap del("://delete-icon.png");
    QIcon deleteIcon = QIcon(del);
    deleteButton = new QPushButton(deleteIcon, "", this);
    deleteButton->setStyleSheet("QPushButton {"
                                "    background-color: #f0f0f0;"  // Цвет фона
                                "    border: 1px solid #f0f0f0;"              // Цвет текста
                                "    padding: 5px 10px;"
                                "}"
                                "QPushButton:hover {"
                                "    background-color: #fff;"  // Цвет фона при наведении
                                "}"
                                "QPushButton:pressed {"
                                "    background-color: #fff;"  // Цвет фона при нажатии
                                "}");
    deleteButton->setFixedSize(30, 30);
    deleteButton->setToolTip("Удалить книгу");
    setWindowTitle("Информация о книге");
    setLayout(vbox);
    resize(400, 300);
    show();
}

InfoBookDialog::~InfoBookDialog()
{

}

void InfoBookDialog::showInfo(CatalogBook* book, QVector<Reader> &readers)
{
    if (book == NULL) {
        vbox->addWidget(new QLabel("Ошибка при получении информации о книге"));
    }
    else {
        rlist = &readers;
        currentBook = book;

        vbox->addWidget(new QLabel("Название: " + book->getTitle()));
        vbox->addWidget(new QLabel("Автор: " + book->getAuthors()));
        vbox->addWidget(new QLabel("Год издания книги: " + QString::number(book->getYear())));
        vbox->addWidget(new QLabel("Количество страниц: " + QString::number(book->getPages())));
        vbox->addWidget(new QLabel("Издательство: " + book->getPublisher()));
        vbox->addWidget(new QLabel("Кол-во экземпляров: " + QString::number(book->getQuantity())));
        vbox->addWidget(new QLabel("Кол-во свободных экземпляров: " + QString::number(book->getAvailable())));
        vbox->addWidget(new QLabel("Id: " + QString::number(book->getId())));
        vbox->addWidget(labelInfo);
        QVector<Reader>* rs = book->getReaders();
        for (int i = 0; i < rs->size(); ++i) {
            QHBoxLayout* hbox = new QHBoxLayout(this);
            Reader& r = (*rs)[i];
            QString name = r.getName();
            QString year = QString::number(r.getYear());
            QLabel* readerLabel = new QLabel(name + ", " + year);
            QPushButton* releaseButton = new QPushButton("Освободить книгу");

            releaseButton->setProperty("reader", QVariant::fromValue(r.getId()));

            connect(releaseButton, &QPushButton::clicked, this, &InfoBookDialog::releaseBook);

            hbox->addWidget(readerLabel);
            hbox->addWidget(releaseButton);
            vbox->addLayout(hbox);

            qDebug() << name << ", " << year;
        }

        int i = 0;
        foreach (const Reader &reader, readers)
            readersBox->insertItem(i++, reader.getName(), reader.getId());
        hb1->addWidget(label);
        hb1->addWidget(readersBox);
        hb1->addWidget(giveOut);
        hb1->setSpacing(10);

        vbox->addItem(hb1);
        hbox->addWidget(changeButton);
        hbox->addSpacing(7);
        hbox->addWidget(deleteButton);

        vbox->addItem(hbox);

        connect(deleteButton, &QPushButton::clicked, this, &InfoBookDialog::deleteBook);
        connect(giveOut, &QPushButton::clicked, this, &InfoBookDialog::giveOutBook);
        connect(changeButton, &QPushButton::clicked, this, &InfoBookDialog::setChanging);
    }
}

void InfoBookDialog::setChanging() {
    AddBookDialog* dialog = new AddBookDialog(this);
    connect(dialog, &AddBookDialog::dialogClosed, this, &InfoBookDialog::onDialogClosed);
    dialog->setTitles(currentBook);
    qDebug() << "Button changes";
    dialog->show();
}

void InfoBookDialog::onDialogClosed()
{
    emit dialogClosed();
}

void InfoBookDialog::giveOutBook()
{
    int selectedReaderId = readersBox->currentData().toInt();

    for (int i = 0; i < rlist->size(); i++) {
        if ((*rlist)[i].getId() == selectedReaderId) {
            if (currentBook->getAvailable() > 0) {

                Reader& reader = (*rlist)[i];

                (*currentBook->getReaders()).append(reader);
                currentBook->takeBook();
                (*(reader.getBooks())).append(*currentBook);

                qDebug() << "Книга выдана: " << reader.getName();
                qDebug() << "Иформация о выданной книге: " << currentBook->getTitle() << ", ID: " << currentBook->getId();

                qDebug() << "Количество читателей, взявших книгу: " << (*currentBook->getReaders()).size();
                break;
            }
        }
    }
    InfoBookDialog* newDialog = new InfoBookDialog();
    newDialog->showInfo(currentBook, *rlist);
    this->close();
}

void InfoBookDialog::releaseBook()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if (senderButton) {
        int readerId = senderButton->property("reader").value<int>();
        for (int i = 0; i < (*currentBook->getReaders()).size(); i++) {
            if (readerId == (&(*currentBook->getReaders())[i])->getId()) {
                qDebug() << "Книгу вернул: " << (*currentBook->getReaders())[i].getName();
                qDebug() << "Количество книг у читателя до возврата книги:  "
                         << (*(*currentBook->getReaders())[i].getBooks()).size();
                currentBook->getReaders()->remove(i);
                currentBook->returnBook();
                break;
            }
        }
        for (int i = 0; i < rlist->size(); i++) {
            if ((*rlist)[i].getId() == readerId) {
                Reader& reader = (*rlist)[i];
                reader.getBooks()->removeOne(*currentBook);
                break;
            }
        }
    }
    InfoBookDialog* newDialog = new InfoBookDialog();
    newDialog->showInfo(currentBook, *rlist);
    this->close();
}
void InfoBookDialog::deleteBook()
{
    for (int i = 0; i < rlist->size(); i++) {
        Reader& reader = (*rlist)[i];
        reader.getBooks()->removeOne(*currentBook);
    }
    QTimer::singleShot(0, this, [this]() {
        emit deleteB(currentBook->getId());
        delete this;
    });
}
