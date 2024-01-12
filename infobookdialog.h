#ifndef INFOBOOKDIALOG_H
#define INFOBOOKDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QPixmap>
#include <QIcon>
#include <QLabel>
#include <QString>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include "catalogbook.h"
#include "catalog.h"
#include "reader.h"

namespace Ui {
class InfoBookDialog;
}

class InfoBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoBookDialog(QWidget *parent = nullptr);
    ~InfoBookDialog();
    void showInfo(CatalogBook* book, QVector<Reader> &readers);
    void setChanging();
    void releaseBook();
    void deleteBook();
private slots:
    void onDialogClosed();
    void giveOutBook();
signals:
    void dialogClosed();
    void deleteB(int bookId);
    void updateCatalog();
private:
    QVBoxLayout* vbox;
    QHBoxLayout* hbox;
    QHBoxLayout* hb1;
    QVector<Reader>* readersList;
    QComboBox* readersBox;
    QPushButton* giveOut;
    QPushButton* changeButton;
    QLabel* label;
    CatalogBook* currentBook;
    bool changing;
    QVector<Reader>* rlist;
    QVector<Reader>* currentReaders;
    QVector<QLabel*> labels;
    QLabel* labelInfo;
    QPushButton* deleteButton;
};

#endif // INFOBOOKDIALOG_H
