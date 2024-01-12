#include "reader.h"
#include <QDebug>
int Reader::countOfReaders = 0;

Reader::Reader(QString name, int year)
{
    this->name = name;
    this->year = year;
    id = countOfReaders++;
}

Reader::~Reader()
{

}
bool Reader::operator==(const Reader& other) const {
    return (this->getId() == other.getId());
}
void Reader::serialize(QDataStream &stream) const
{
    stream << name << year << id;
    qDebug() << "Reader saved, id = " << id << ", name: " << name;
}

void Reader::deserialize(QDataStream &stream)
{
    stream >> name >> year >> id;
}

QString Reader::getName() const
{
    return name;
}

int Reader::getYear() const
{
    return year;
}

void Reader::setName(QString name)
{
    this->name = name;
}

void Reader::setYear(int year)
{
    this->year = year;
}

void Reader::addBook(CatalogBook& book)
{
    books.push_back(book);
}

int Reader::getId() const
{
    return id;
}

QVector<CatalogBook>* Reader::getBooks()
{
    return &books;
}
