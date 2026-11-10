#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <qmessagebox.h>

ReplaceDialog::ReplaceDialog(QWidget *parent,QPlainTextEdit * TextEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    pTextEdit=TextEdit;
    ui->rddown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_pbfindnext_clicked()
{
    QString target = ui->searchText->text();

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    if (ui->rddown->isChecked()) {
        index = text.indexOf(target, c.position(),
                             ui->checkBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0) {
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    } else if (ui->rbup->isChecked()) {
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


void ReplaceDialog::on_pbreplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->replaceText->text();

    if ((pTextEdit != nullptr) && (target != "") && (to != "")) {
        QString selText = pTextEdit->textCursor().selectedText();

        if (selText == target) {
            pTextEdit->insertPlainText(to);
        }

        on_pbfindnext_clicked();
    }
}


void ReplaceDialog::on_pvrepalceall_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->replaceText->text();

    if ((pTextEdit != nullptr) && (target != "") && (to != "")) {
        QString text = pTextEdit->toPlainText();

        text.replace(target, to, ui->checkBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        pTextEdit->clear();
        pTextEdit->insertPlainText(text);
    }

}


void ReplaceDialog::on_conceal_clicked()
{
    accept();
}

