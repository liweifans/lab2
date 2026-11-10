#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <qmessagebox.h>

SearchDialog::SearchDialog(QWidget *parent,QPlainTextEdit * TextEdit)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    pTextEdit=TextEdit;
    ui->rbdown->setChecked(true);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_pbfindnext_clicked()
{
    QString target = ui->searchText->text();

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    if (ui->rbdown->isChecked()) {
        index = text.indexOf(target, c.position(),
                             ui->checkBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    } else if (ui->rdup->isChecked()) {
        index = text.lastIndexOf(target, c.position() - 1,
                                 ui->checkBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            c.setPosition(index + target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    }
    if (index < 0) {
        QMessageBox msg(this);
        msg.setWindowTitle("jishiben");
        msg.setText(QString("找不到 ") + target);
        msg.setWindowFlag(Qt::Drawer);
        msg.setIcon(QMessageBox::Information);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }

}


void SearchDialog::on_pbconceal_clicked()
{
    accept();
}

