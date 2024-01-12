#ifndef CATALOG_H
#define CATALOG_H

#include <QWidget>
#include <QFile>
#include <QDataStream>
#include <QIODevice>
#include <QVector>
#include <QListView>
#include <QPushButton>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "author.h"
#include "catalogbook.h"
#include "reader.h"
#include "addbookdialog.h"
#include "addreaderdialog.h"
#include "infobookdialog.h"
#include "readerinfodialog.h"

class Catalog : public QWidget
{
    Q_OBJECT

public:
    Catalog(QWidget *parent = nullptr);
    ~Catalog();



private slots:
    void deleteBook(int bookId);
    void showAddBookDialog();
    void showBookInfoDialog(const QModelIndex& index);

    void showAddReaderDialog();
    void showReaderInfoDialog(const QModelIndex& index);
    // void deleteReader(int readerId);

    void addBook(const CatalogBook& book);
    void addReader(const Reader& reader);
    void saveData();
    void loadData();
    void setType(unsigned short int n);

private:
    QVector<CatalogBook> books;
    QVector<Reader> readers;
    QListView* listView;
    QPushButton* addButton;

    QHBoxLayout* hbox;
    QVBoxLayout* vbox;

    void setupUi();
    void showInfo();
    enum Type {
        BookType,
        ReaderType
    } type;

    QStandardItemModel* bookModel;
    QStandardItemModel* readerModel;
};
#endif // CATALOG_H
