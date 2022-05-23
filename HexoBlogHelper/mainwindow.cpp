#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <io.h>
#include <iostream>
#include <QMessageBox>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Path Select Bind
    connect(ui->sourcePathSelectBtn, &QPushButton::clicked, this, &MainWindow::onButtonClickedSelectSourcePath);
    connect(ui->targetPathSelectBtn, &QPushButton::clicked, this, &MainWindow::onButtonClickedSelectTargetPath);

    ui->itemList->setAlignment(Qt::AlignTop);

    // Style
    setStypeSheet(":/qss/generalStyle.qss");

    _generateButton = nullptr;
    _checkAllButton = nullptr;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setStypeSheet(QString resourceFildPath)
{
    QFile styleFile(resourceFildPath);
    styleFile.open(QFile::ReadOnly);
    if (styleFile.isOpen())
    {
        qApp->setStyleSheet(styleFile.readAll());
        styleFile.close();
    }
}

void MainWindow::onButtonClickedSelectSourcePath()
{
    QString filename= QFileDialog::getExistingDirectory(this, "Choose Folder");

    if (filename.isEmpty())
        return;

    ui->sourcePahtLineEdit->setText(filename);

    // Clear Last
    auto verticalLayout = ui->itemList;

    if (_checkAllButton != nullptr)
        verticalLayout->removeWidget(_checkAllButton);

    if (_generateButton != nullptr)
        verticalLayout->removeWidget(_generateButton);

    for (size_t i = 0; i < _targetFiles.size(); i++)
    {
        auto hBoxLayoutPtr = _targetFiles[i]->getHBoxLayout();
        verticalLayout->removeItem(hBoxLayoutPtr);
        delete _targetFiles[i];
    }

    _targetFiles.clear();

    // Generate
    getFileNames(filename.toStdWString(), _targetFiles, L".md");

    // Make New List
    for (size_t i = 0; i < _targetFiles.size(); i++)
    {
        auto hBoxLayoutPtr = _targetFiles[i]->getHBoxLayout();
        verticalLayout->addLayout(hBoxLayoutPtr);
    }

    if (_checkAllButton == nullptr)
    {
        _checkAllButton = new QPushButton();
        _checkAllButton->setText("Check All");
        connect(_checkAllButton, &QPushButton::clicked, this, &MainWindow::onButtonClickedCheckAll);
    }

    if (_generateButton == nullptr)
    {
        _generateButton = new QPushButton();
        _generateButton->setText("Generate");
        connect(_generateButton, &QPushButton::clicked, this, &MainWindow::onButtonClickedGenerateFile);
    }

    verticalLayout->addWidget(_checkAllButton);
    verticalLayout->addWidget(_generateButton);
}

void MainWindow::onButtonClickedSelectTargetPath()
{
    QString filename= QFileDialog::getExistingDirectory(this, "Choose Folder");

    if (filename.isEmpty())
        return;

    _targetPath = filename.toStdWString();
    ui->targetPathLineEdit->setText(filename);
}

void MainWindow::onButtonClickedCheckAll()
{
    for (size_t i = 0; i < _targetFiles.size(); i++)
        _targetFiles[i]->getCheckBox()->setChecked(true);
}

void MainWindow::onButtonClickedGenerateFile()
{
    ui->logTextEdit->clear();

    if (_targetPath.length() == 0)
    {
        ui->logTextEdit->append("Taget Path Not Set");
        return;
    }

    std::vector<SelectItem*> targetItems;

    for (size_t i = 0; i < _targetFiles.size(); i++)
    {
        auto itemPtr = _targetFiles[i];
        if (itemPtr->getCheckBox()->isChecked())
        {
            targetItems.push_back(itemPtr);
        }
    }

    for (size_t i = 0; i < targetItems.size(); i++)
    {
        std::wstring fileName = targetItems[i]->getFileName();
        std::wstring filePath = targetItems[i]->getFilePath();

        std::wstring fileSourceFullPath;
        fileSourceFullPath.assign(filePath).append(L"/").append(fileName);
        std::wstring fileTargetFullPath;
        fileTargetFullPath.assign(_targetPath).append(L"/").append(fileName);

        bool copyFileSuccess = copyFileToPath(QString::fromStdWString(fileSourceFullPath), QString::fromStdWString(fileTargetFullPath), true);
        QString fileCopyLog;
        fileCopyLog.append(copyFileSuccess ? "Success [FileCopy]: " : "Fail [FileCopy]: ")
                 .append(QString::fromStdWString(fileSourceFullPath))
                 .append(" -> ")
                 .append(QString::fromStdWString(fileTargetFullPath))
                 .append('\n');

        ui->logTextEdit->append(fileCopyLog);

        // find resource
        std::wstring resourceSourceFullPath;
        resourceSourceFullPath.assign(filePath).append(L"/").append(L"Resource");
        std::wstring resourceTargetFullPath;
        resourceTargetFullPath.assign(_targetPath).append(L"/").append(fileName.substr(0, fileName.length() - 3));

        bool doMove = QFile::exists(QString::fromStdWString(resourceSourceFullPath));
        if (doMove)
        {
            bool copyResourceSuccess = copyDirectoryFiles(QString::fromStdWString(resourceSourceFullPath), QString::fromStdWString(resourceTargetFullPath), true);

            QString resourceCopyLog;
            resourceCopyLog.append(copyResourceSuccess ? "Success [ResourceCopy]: " : "Fail [ResourceCopy]: ")
                    .append(QString::fromStdWString(resourceSourceFullPath))
                    .append(" -> ")
                    .append(QString::fromStdWString(resourceTargetFullPath))
                    .append('\n');


            ui->logTextEdit->append(resourceCopyLog);
        }
    }
}

bool MainWindow::copyFileToPath(QString sourceDir, QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir)
    {
        return true;
    }
    if (!QFile::exists(sourceDir))
    {
        return false;
    }
    QDir* createfile = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist)
    {
        if(coverFileIfExist)
        {
            createfile->remove(toDir);
        }
    }

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }

    return true;
}

bool MainWindow::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);

    if (targetDir.exists())
        targetDir.removeRecursively();

    if(!targetDir.mkdir(targetDir.absolutePath()))
        return false;

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir())
        {    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else
        {            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName()))
            {
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))
            {
                return false;
            }
        }
    }
    return true;
}

void MainWindow::getFileNames(std::wstring path, std::vector<SelectItem*>& files, const std::wstring suffix)
{
    intptr_t hFile = 0;
    struct _wfinddata_t fileinfo;
    std::wstring p;
    p.assign(path).append(L"/*");

    if ((hFile = _wfindfirst(p.c_str(), &fileinfo)) != -1)
    {
        do
        {
            //如果是目录,递归查找
            //如果不是,把文件绝对路径存入vector中
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (wcscmp(fileinfo.name, L".") != 0 && wcscmp(fileinfo.name, L"..") != 0)
                    getFileNames(p.assign(path).append(L"/").append(fileinfo.name), files, suffix);
            }
            else
            {
                bool success = true;
                std::wstring file_name = fileinfo.name;
                std::wstring file_path = p.assign(path);
                if (suffix != L"")
                {
                    size_t pos = file_name.rfind(suffix);
                    success = pos != std::string::npos;
                }

                if (success)
                {
                    SelectItem* item = new SelectItem(file_name, file_path);
                    files.push_back(item);
                }
            }
        } while (_wfindnext(hFile, &fileinfo) == 0);

        _findclose(hFile);
    }
}

SelectItem::SelectItem(std::wstring name, std::wstring filePath)
{
    _fileName = name;
    _filPath = filePath;

    _hBoxLayout = new QHBoxLayout();
    _checkBox = new QCheckBox();
    _label = new QLabel();

    _label->setText(QString::fromStdWString(_fileName));

    _hBoxLayout->addWidget(_checkBox);
    _hBoxLayout->addWidget(_label);

    _hBoxLayout->setAlignment(Qt::AlignLeft);
}

SelectItem::~SelectItem()
{
    delete _label;
    delete _checkBox;
    delete _hBoxLayout;
}

const std::wstring SelectItem::getFileName() const
{
    return _fileName;
}

const std::wstring SelectItem::getFilePath() const
{
    return _filPath;
}

QCheckBox* SelectItem::getCheckBox()
{
    return _checkBox;
}

QHBoxLayout* SelectItem::getHBoxLayout()
{
    return _hBoxLayout;
}
