
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <iostream>
#include <QListView>
#include <QStringListModel>
#include <QThread>
#include <iostream>
#include <QThreadPool>
#include <QDebug>




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStringList createWordList();
    void searchString(QStringList wordList, QString searchString, int start, int end);

    void search(QString inputString);

private slots:


    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

signals:
     void wordListUpdated(QStringList words);
private:
    Ui::MainWindow *ui;
    QString searchPattern;
    QStringList combinedWordList;

};

#endif // MAINWINDOW_H
