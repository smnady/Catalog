#ifndef AUTHOR_H
#define AUTHOR_H
#include "Person.h"
#include "book.h"

class Author : public Person
{
public:
    Author(QString name, int year);
    ~Author();
    QString getName() const override;
    int getYear() const override;
    void setName(QString name) override;
    void setYear(int year) override;
    int getId() const;
private:
    static int countOfAuthors;
    int id;
    QString name;
    int year;
};

#endif // AUTHOR_H
