#ifndef PERSON_H
#define PERSON_H
#include <QString>

class Person {
public:
    virtual ~Person() = default;
    virtual QString getName() const = 0;
    virtual int getYear() const = 0;
    virtual void setName(QString name) = 0;
    virtual void setYear(int year) = 0;

protected:
    QString name;
    int year;
};

#endif // PERSON_H
