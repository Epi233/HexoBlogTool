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
    SelectItem(std::string name);
    ~SelectItem();

public:
    void setCheck(bool check);
    bool isCheck() const;
    const std::string getFileName() const;
    QHBoxLayout* getHBoxLayout();


private:
    QHBoxLayout* _hBoxLayout;
    QCheckBox* _checkBox;
    QLabel* _label;
    std::string _fileName;
    bool _check;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<SelectItem*> _targetFiles;

    void onButtonClickedSelectPath();
    void getFileNames(std::string path, std::vector<SelectItem*>& files, const std::string suffix);

};
#endif // MAINWINDOW_H
