#include "catalogbook.h"
#include <QDebug>

int CatalogBook::countOfUniqueBooks = 0;
QMultiMap<int, int> CatalogBook::conMap;

CatalogBook::CatalogBook(QString title, QString publisher, int year, int pages, QString authors, int quantity)
    : Book(title, publisher, year, pages, authors),
      quantity(quantity) {
    available = quantity;
    id = countOfUniqueBooks++;
}

CatalogBook::~CatalogBook() {

}
bool CatalogBook::operator==(const CatalogBook& other) const {
    return (this->getId() == other.getId());
}
void CatalogBook::serialize(QDataStream &stream) const
{
    stream << title << publisher << year << pages << authors << quantity << id;

    int numReaders = readers.size();
    stream << numReaders;
    for (const Reader reader : readers) {
        stream << reader.getId();
    }

    qDebug() << "Book saved, id = " << id << ", title: " << title;
}

void CatalogBook::deserialize(QDataStream &stream)
{

    stream >> title >> publisher >> year >> pages >> authors >> quantity >> id;

    available = quantity;

    int numReaders;
    stream >> numReaders;
    for (int i = 0; i < numReaders; ++i) {
        int readerId;
        stream >> readerId;
        conMap.insert(id, readerId);
    }
}

QVector<Reader>* CatalogBook::getReaders()
{
    return &readers;
}

void CatalogBook::takeBook()
{
    available--;
}

void CatalogBook::returnBook()
{
    available++;
}

int CatalogBook::getId() const
{
    return id;
}

int CatalogBook::getQuantity() const
{
    return quantity;
}

int CatalogBook::getAvailable() const
{
    return available;
}

void CatalogBook::setQuantity(int quaintity)
{
    this->quantity = quaintity;
}

void CatalogBook::setAvailable(int a)
{
    available = a;
}

void CatalogBook::setId(int id)
{
    this->id = id;
}

