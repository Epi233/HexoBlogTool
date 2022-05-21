#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <io.h>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Style
    this->setStyleSheet("QWidget{font-size:20px");

    // Path Select Bind
    connect(ui->pathSelectButton, &QPushButton::clicked, this, &MainWindow::onButtonClickedSelectPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonClickedSelectPath()
{
    QString filename= QFileDialog::getExistingDirectory(this, "Choose Folder");

    if (filename.isEmpty())
        return;

    ui->pathSelectTextArea->setText(filename);

    _fileNames.clear();
    getFileNames(filename.toStdString(), _fileNames);

    for (size_t i = 0; i < _fileNames.size(); i++)
    {
        std::cout << _fileNames[i] << std::endl;
    }
}




void MainWindow::getFileNames(std::string path, std::vector<std::string>& files)
{
    intptr_t hFile = 0;
    struct _finddata_t fileinfo;
    std::string p;

    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            //如果是目录,递归查找
            //如果不是,把文件绝对路径存入vector中
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFileNames(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }
}

SelectItem::SelectItem(QString fileName)
{
    _fileName = fileName;
}
