#ifndef BOOK_H
#define BOOK_H

#include <QString>
#include <QObject>
#include <QVector>

class Book
{
public:
    Book(QString title = "",
         QString publisher = "",
         int year = 0,
         int pages = 0,
         QString authors = "");
    QString getTitle() const;
    QString getPublisher() const;
    QString getAuthors() const;
    int getYear() const;
    int getPages() const;
    void setTitle(QString title);
    void setPublisher(QString pubisher);
    void setAutours(QString authors);
    void setYear(int year);
    void setPages(int pages);
    void addAuthor(QString author);

    QString title;
    QString publisher;
    QString authors;
    int year;
    int pages;
};

#endif // BOOK_H
