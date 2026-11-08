#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileInfo>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusLabel.setMaximumWidth(150);
    statusLabel.setText("length:"+QString::number(0)+"   lines:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(150);
    statusCursorLabel.setText("Ln:"+QString::number(0)+"   Col:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel*author=new QLabel(ui->statusbar);
    author->setText(tr("李维凡"));
    ui->statusbar->addPermanentWidget(author);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dig;
    dig.exec();
}


void MainWindow::on_actionFind_triggered()
{
    SearchDialog dig;
    dig.exec();
}


void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog dig;
    dig.exec();
}


void MainWindow::on_actionNew_triggered()
{
    ui->TextEdit->clear();
    curFilePath = "";
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "打开文件", ".", tr("Text files (*.txt);; All (*.*)"));
    QFile file(filename);

    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "..", "打开文件失败");
        return;
    }

    filePath=filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->TextEdit->insertPlainText(text);
    file.close();

    curFilePath = filename;
    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());
}


void MainWindow::on_actionSave_triggered()
{
    if(curFilePath.isEmpty())
    {
        QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".", tr("Text files (*.txt);; All (*.*)"));
        if (filename.isEmpty())
            return;
        curFilePath = filename;
    }

    QFile file(curFilePath);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "保存文件失败");
        return;
    }
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    file.close();

    this->setWindowTitle(QFileInfo(curFilePath).absoluteFilePath());
}


void MainWindow::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "另存为", ".", tr("Text files (*.txt);; All (*.*)"));
    if (filename.isEmpty())
    {
        return;
    }
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "..", "另存为失败");
        return;
    }
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    file.close();

    filePath=filename;
    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());

}

