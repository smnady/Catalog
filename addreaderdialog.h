#ifndef ADDREADERDIALOG_H
#define ADDREADERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "reader.h"

namespace Ui {
class AddReaderDialog;
}

class AddReaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddReaderDialog(QWidget *parent = nullptr);
    ~AddReaderDialog();
    void setTitles(Reader* reader);
signals:
    void readerAdded(const Reader& reader);
    void dialogClosed();
private slots:
    void saveReader();
    void setChanges();
private:
    QPushButton* saveButton;
    QVBoxLayout* vbox;
    QLineEdit* nameEdit;
    QLineEdit* yearEdit;
    Reader* curReader;
};

#endif // ADDREADERDIALOG_H
