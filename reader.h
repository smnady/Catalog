#ifndef READER_H
#define READER_H
#include "Person.h"
#include "catalogbook.h"
#include "book.h"
#include <QDataStream>

class CatalogBook;

class Reader : public Person
{
public:
    Reader(QString name = "",
           int year = 0);
    ~Reader();
    bool operator==(const Reader& other) const;
    void serialize(QDataStream &stream) const;
    void deserialize(QDataStream &stream);
    QString getName() const override;
    int getYear() const override;
    void setName(QString name) override;
    void setYear(int year) override;
    void addBook(CatalogBook& book);
    int getId() const;
    QVector<CatalogBook>* getBooks();
    QVector<CatalogBook> books;
private:
    static int countOfReaders;
    int id;
    QString name;
    int year;


};

#endif // READER_H
