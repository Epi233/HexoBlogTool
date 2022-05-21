#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QFileDialog>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class SelectItem
{
public:
    SelectItem(QString fileName);

private:
    QCheckBox* _checkBox;
    QString _fileName;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<std::string> _fileNames;

    void onButtonClickedSelectPath();
    void getFileNames(std::string path, std::vector<std::string>& files);

};
#endif // MAINWINDOW_H
