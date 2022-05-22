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

    auto verticalLayout = ui->itemList;
    for (size_t i = 0; i < _targetFiles.size(); i++)
    {
        auto hBoxLayoutPtr = _targetFiles[i]->getHBoxLayout();
        verticalLayout->removeItem(hBoxLayoutPtr);
        delete _targetFiles[i];
    }

    _targetFiles.clear();

    getFileNames(filename.toStdString(), _targetFiles, ".md");

    for (size_t i = 0; i < _targetFiles.size(); i++)
    {
        auto hBoxLayoutPtr = _targetFiles[i]->getHBoxLayout();
        verticalLayout->addLayout(hBoxLayoutPtr);
    }
}




void MainWindow::getFileNames(std::string path, std::vector<SelectItem*>& files, const std::string suffix)
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
                    getFileNames(p.assign(path).append("\\").append(fileinfo.name), files, suffix);
            }
            else
            {
                bool success = true;
                std::string file_name = fileinfo.name;
                std::string file_full_path = p.assign(path).append("\\").append(fileinfo.name);
                if (suffix != "")
                {
                    size_t pos = file_name.rfind(suffix);
                    success = pos != std::string::npos;
                }

                if (success)
                {
                    SelectItem* item = new SelectItem(file_full_path);
                    files.push_back(item);
                }
            }
        } while (_findnext(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }
}

SelectItem::SelectItem(std::string name)
{
    _check = false;
    _fileName = name;

    _hBoxLayout = new QHBoxLayout();
    _checkBox = new QCheckBox();
    _label = new QLabel();

    _label->setText(QString::fromLocal8Bit(_fileName));

    _hBoxLayout->addWidget(_checkBox);
    _hBoxLayout->addWidget(_label);
}

SelectItem::~SelectItem()
{
    delete _label;
    delete _checkBox;
    delete _hBoxLayout;
}

void SelectItem::setCheck(bool check)
{
    _check = check;
}

bool SelectItem::isCheck() const
{
    return _check;
}

const std::string SelectItem::getFileName() const
{
    return _fileName;
}

QHBoxLayout* SelectItem::getHBoxLayout()
{
    return _hBoxLayout;
}
