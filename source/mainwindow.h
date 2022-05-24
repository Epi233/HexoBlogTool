#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QFileDialog>
#include <QCheckBox>
#include <QLayout>
#include <QLabel>

QT_BEGIN_NAMESPACE

namespace Ui
{
    class MainWindow;
}

QT_END_NAMESPACE

class SelectItem
{
public:
    SelectItem(std::wstring fileName, std::wstring filePath);
    ~SelectItem();

public:
    const std::wstring getFileName() const;
    const std::wstring getFilePath() const;
    QHBoxLayout* getHBoxLayout();
    QCheckBox* getCheckBox();

private:
    QHBoxLayout* _hBoxLayout;
    QCheckBox* _checkBox;
    QLabel* _label;
    std::wstring _fileName;
    std::wstring _filPath;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::wstring _targetPath;

    std::vector<SelectItem*> _targetFiles;

    QPushButton* _checkAllButton;
    QPushButton* _generateButton;

private:
    void onButtonClickedSelectSourcePath();
    void onButtonClickedSelectTargetPath();
    void onButtonClickedCheckAll();
    void onButtonClickedGenerateFile();

    void setStyleSheet(QString resourceFilePath);

private:
    bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist);
    bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
    void getFileNames(std::wstring path, std::vector<SelectItem*>& files, const std::wstring suffix);
    void processFile(QString sourceDir);
    bool isStrMarkDownImage(QString lineContent, QString* result);

};
#endif // MAINWINDOW_H
