#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graph_parse.h"
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

void MainWindow::on_pushButton_clicked()
{
    QString text = ui->plainTextEdit_2->toPlainText();
    ui->plainTextEdit->setPlainText(text);
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

void MainWindow::on_pushButton_10_clicked(){ // Post Search
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    Graph g = Graph_Parse(x);
    text = ui->lineEdit->text();
    string str = text.toStdString();
    vector<Post*> answer = Post_Search(str, g.Posts);
    string output;
    for (int k = 0; k < answer.size(); k++)
    {
        output += "The Post's body is: " + answer[k]->Body + "\n" + "The Post's topics are: ";

        for (int z = 0; z < answer[k]->Topics.size(); z++)
        {
            output += answer[k]->Topics[z] + "    ";
        }
        output += "\n\n===============================\n\n";
    }
    QString Result = QString::fromStdString(output);
    ui->plainTextEdit_2->setPlainText(Result);
}

void MainWindow::on_pushButton_11_clicked(){ // Most Influencer
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    Graph g = Graph_Parse(x);
    vector<vector<int>> matrix = g.Adjacency_Matrix;
    int index = getMostInfluencerUser(matrix);

    string output; output = "The Node with the most followers is\n\tid: " + g.users[index]->id + "\n\tname: " + g.users[index]->name;
    QString Result = QString::fromStdString(output);
    ui->plainTextEdit_2->setPlainText(Result);
}

void MainWindow::on_pushButton_12_clicked(){ // Most Active
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    Graph g = Graph_Parse(x);
    vector<vector<int>> matrix = g.Adjacency_Matrix;
    int index = getMostActiveUser(matrix);

    string output;
    output = "The Node with the most follows is\n\tid: " + g.users[index]->id + "\n\tname: " + g.users[index]->name;
    QString Result = QString::fromStdString(output);
    ui->plainTextEdit_2->setPlainText(Result);
}

void MainWindow::on_pushButton_13_clicked(){ // People you may know
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    Graph g = Graph_Parse(x);
    vector<vector<int>> matrix = g.Adjacency_Matrix;
    string output;
    for(int i=0; i < g.users.size(); i++){
        vector<int> people_u_may_know = get_suggested_users(stoi(g.users[i]->id), g.Adjacency_Matrix);
        output += "For User ID: " + g.users[i]->id;
        if (people_u_may_know.size() != 0)
        {
            output +="\nList of People you may know: \n";
            for (int j : people_u_may_know)
            {
                output += "        User of Id: " + g.users[j]->id + ", Name: " + g.users[j]->name + "\n";
            }
        }
        else
        {
            output += "\tThere isn't suggested peaple\n";
        }
        output += "\n======================\n";

    }

    QString Result = QString::fromStdString(output);
    ui->plainTextEdit_2->setPlainText(Result);
}

void MainWindow::on_pushButton_14_clicked(){ // Mutal Followers
    QString text = ui->plainTextEdit->toPlainText();
    string x = text.toStdString();
    Graph g = Graph_Parse(x);
    vector<vector<int>> matrix = g.Adjacency_Matrix;
    text = ui->lineEdit_2->text();
    string user_1 = text.toStdString();
    text = ui->lineEdit_3->text();
    string user_2 = text.toStdString();
    string output;
    if(stoi(user_1)<= g.users.size() && stoi(user_2) <= g.users.size() && user_1 != user_2){
        vector<int> result = mutual_followers(stoi(user_1), stoi(user_2), matrix);
        if (result.size() != 0)
        {
            output = "Mutual Friends for users of id " + user_1 + " & " + user_2 + " are: \n";
            for (int i : result)
            {
                output += "        User of Id: " + g.users[i]->id + ", Name: " + g.users[i]->name + "\n";
            }
        }
        else
        {
            output += "There isn't mutual followers.\n";
        }

        QString Result = QString::fromStdString(output);
        ui->plainTextEdit_2->setPlainText(Result);
    }
    else{
        output = "Please enter a valid User ID";
        QString Result = QString::fromStdString(output);
        ui->plainTextEdit_2->setPlainText(Result);
    }
}
