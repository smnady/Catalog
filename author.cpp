#include "author.h"

int Author::countOfAuthors = 0;

Author::Author(QString name, int year)
{
    this->name = name;
    this->year = year;
    id = countOfAuthors++;
}

Author::~Author()
{

}

QString Author::getName() const
{
    return name;
}

int Author::getYear() const
{
    return year;
}

void Author::setName(QString name)
{
    this->name = name;
}

void Author::setYear(int year)
{
    this->year = year;
}

int Author::getId() const
{
    return id;
}
