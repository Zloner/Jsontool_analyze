#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "main_json.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//“解析”按钮触发程序
void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();

    //  获取输入框的内容
    QString content = ui->textEdit->toPlainText();
    string s = content.toStdString();

    //中间处理过程
    QString result;

    Json v;

    v.parse(s);
    cout << v.str_p() << endl;

    result = QString::fromStdString(v.str_f());

    //  将获取的内容用append输出到TextBrowser
    ui->textBrowser->append(result);    // 将结果输出到结果区域
}

//生成文件按钮
void MainWindow::on_pushButton_3_clicked()
{
    ofstream fout("test.json", ios::out);

    if(!fout)
     {
        ui->textBrowser->clear();
        ui->textBrowser->append("cannot open the file\n");
    }
    //读取输出框内容
    QString out = ui->textBrowser->toPlainText();
    string o = out.toStdString();

    fout << o << endl;

    ui->textBrowser->clear();
    ui->textBrowser->append("File generated successfully\n");
}

//读取json文件
void MainWindow::on_pushButton_5_clicked()
{
    ui->textBrowser->clear();

    //获取文件路径
    QString path = ui->textEdit_2->toPlainText();
    string p = path.toStdString();

    //  获取json文件的内容
    ifstream fin(p, ios::in);

    if(!fin)
     {
        ui->textBrowser->clear();
        ui->textBrowser->append("cannot read the file\n");
    }

    stringstream  ss;

    ss << fin.rdbuf();
    const string& str = ss.str();

    QString content = QString::fromStdString(str);

    string s = content.toStdString();

    //中间处理过程
    QString result;

    Json v;

    v.parse(s);
    cout << v.str_p() << endl;

    result = QString::fromStdString(v.str_f());

    //  将获取的内容用append输出到TextBrowser
    ui->textBrowser->append(result);    // 将结果输出到结果区域
}
