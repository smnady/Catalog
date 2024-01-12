#ifndef ADDBOOKDIALOG_H
#define ADDBOOKDIALOG_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "catalogbook.h"

namespace Ui {
class AddBookDialog;
}

class AddBookDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddBookDialog(QWidget *parent = nullptr);
    void setTitles(CatalogBook* book);
    ~AddBookDialog();
signals:
    void bookAdded(const CatalogBook& book);
    void dialogClosed();
private slots:
    void saveBook();
    void setChanges();
private:
    QPushButton* saveButton;
    QLineEdit* titleLineEdit;
    QLineEdit* publisherLineEdit;
    QLineEdit* yearLineEdit;
    QLineEdit* pagesLineEdit;
    QLineEdit* authorsLineEdit;
    QLineEdit* quantityLineEdit;
    CatalogBook* curBook;
};

#endif // ADDBOOKDIALOG_H
