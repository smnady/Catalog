#include "book.h"

Book::Book(QString title, QString publisher,int year, int pages, QString authors)
{
    this->title = title;
    this->publisher = publisher;
    this->year = year;
    this->pages = pages;
    this->authors = authors;
}

QString Book::getTitle() const
{
    return title;
}

QString Book::getPublisher() const
{
    return publisher;
}

QString Book::getAuthors() const
{
    return authors;
}

int Book::getYear() const
{
    return year;
}

int Book::getPages() const
{
    return pages;
}

void Book::setTitle(QString title)
{
    this->title = title;
}

void Book::setPublisher(QString pubisher)
{
    this->publisher = publisher;
}

void Book::setAutours(QString authors)
{
    this->authors = authors;
}

void Book::setYear(int year)
{
    this->year = year;
}

void Book::setPages(int pages)
{
    this->pages = pages;
}

void Book::addAuthor(QString author)
{
    authors.append(author);
}
