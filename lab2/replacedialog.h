#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr,QPlainTextEdit *textEdit=nullptr);
    ~ReplaceDialog();

private slots:
    void on_pbfindnext_clicked();

    void on_pbreplace_clicked();

    void on_pvrepalceall_clicked();

    void on_conceal_clicked();

private:
    Ui::ReplaceDialog *ui;
    QPlainTextEdit * pTextEdit;
};

#endif // REPLACEDIALOG_H
