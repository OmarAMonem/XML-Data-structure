#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "xml.h"
#include "Compression.h"

#include <string>
#include <iostream>
#include <QSaveFile>
#include <fstream>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select a file", "C://");
    QFile file(file_name);
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning!", "file is not opening");
    }
    QTextStream in(&file);
    QString text = in.readAll();
    ui->plainTextEdit->setPlainText(text);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString file_name = QFileDialog::getSaveFileName(this, "Select a file", "C://", tr("All files (*.*);;XML files (*.xml);;Text files (*.txt);;JSON Files(*.json)"));
    QFile file(file_name);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning!", "file is not Saved");
    }
    QTextStream out(&file);
    QString text = ui->plainTextEdit_2->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_pushButton_4_clicked() // Validation
{
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    string Result = validate(x);
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);
}

void MainWindow::on_pushButton_9_clicked() // Prettify
{
    QString text = ui->plainTextEdit->toPlainText();
    string x = minify(minify(text.toStdString(), " ", "\n"));
    Tree t = parse(x);
    string Result = t.prettify();
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);
}

void MainWindow::on_pushButton_5_clicked() // XML TO JSON
{
    QString text = ui->plainTextEdit->toPlainText();
    string x = minify(minify(text.toStdString(), " ", "\n"));
    Tree t = parse(x);
    string Result = t.XMLToJson();
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);
}

void MainWindow::on_pushButton_8_clicked() // Compress
{
    QMessageBox::warning(this, "Warning!", "file is Saved in The Same Directory As .exe file");
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    string Result = Huffman_encoding(x);
    vector<uint8_t> Result2 = toBinary(Result);
    const std::vector<uint8_t> buffer(Result2); // let's assume that it's filled with values
    std::ofstream out("file.huff", std::ios::out | std::ios::binary);
    out.write(reinterpret_cast<const char *>(buffer.data()), buffer.size());
    out.close();
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);
}

void MainWindow::on_pushButton_7_clicked() // Minify
{
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    string Result = minify(minify(x, " ", "\n"));
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);
}

void MainWindow::on_pushButton_6_clicked() // Decompress
{
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    string Result = decoding(main_root, x);
    QString str = QString::fromStdString(Result);
    ui->plainTextEdit_2->setPlainText(str);
}
