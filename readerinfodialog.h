#ifndef READERINFODIALOG_H
#define READERINFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "reader.h"
#include <catalogbook.h>

namespace Ui {
class ReaderInfoDialog;
}

class ReaderInfoDialog : public QDialog
{
    Q_OBJECT
private slots:
    void onDialogClosed();
signals:
    void dialogClosed();
public:
    explicit ReaderInfoDialog(QWidget *parent = nullptr);
    ~ReaderInfoDialog();
    void showInfo(Reader* reader);
    void setChanging();

private:
    QVBoxLayout* vbox;
    QLabel* nameLabel;
    QLabel* yearLabel;
    Reader* currentReader;
};

#endif // READERINFODIALOG_H
