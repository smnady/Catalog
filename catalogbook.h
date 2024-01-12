#ifndef CATALOGBOOK_H
#define CATALOGBOOK_H
#include <QVector>
#include "book.h"
#include "reader.h"
#include <QMultiMap>
class Reader;

class CatalogBook :  public Book
{

public:
    CatalogBook(QString title = "",
                QString publisher = "",
                int year = 0,
                int pages = 0,
                QString authors = (""),
                int quantity = 0);
    // CatalogBook(const CatalogBook&) = delete;
    // CatalogBook& operator=(const CatalogBook&) = delete;
    ~CatalogBook();
    bool operator==(const CatalogBook& other) const;
    void takeBook();
    void returnBook();
    int getId() const;
    int getQuantity() const;
    int getAvailable() const;
    void setQuantity(int quaintity);
    void setAvailable(int a);
    void setId(int id);
    void serialize(QDataStream &stream) const;
    void deserialize(QDataStream &stream);
    QVector<Reader>* getReaders();
    static QMultiMap<int, int> conMap;
    QVector<Reader> readers;

private:
    int id;
    int quantity;
    int available;
    static int countOfUniqueBooks;
};

#endif // CATALOGBOOK_H
