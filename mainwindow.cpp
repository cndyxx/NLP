
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
#include <QListView>
#include <QStringListModel>


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

QStringList MainWindow::createWordList()
{
    QStringList letters = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};

    QStringList wordList;

    for (int i = 0; i < letters.size(); i++)
    {
        for (int j = 0; j < letters.size(); j++)
        {
            for (int k = 0; k < letters.size(); k++)
            {
                for (int l = 0; l < letters.size(); l++)
                {
                    QString word = letters[i] + letters[j] + letters[k] + letters[l];
                    wordList.append(word);
                }
            }
        }
    }

    return wordList;
}

void MainWindow::searchString(QStringList wordList, QString searchString, int start, int end)
{
    QStringList wordsOfList;
    for (int i = start; i < end; i++)
    {
        if (wordList[i].startsWith(searchString))
        {
            wordsOfList.append(wordList[i]);

        }
    }
    std::mutex mutex;
    mutex.lock();
    combinedWordList.append(wordsOfList);
    mutex.unlock();
}



void MainWindow::search(QString inputString)
{

    int coreCount = QThread::idealThreadCount();
    QStringList testList = createWordList();
    int splitWordList = testList.size() / coreCount;

    qDebug() << "Bitte geben Sie das Suchmuster ein:";
    qDebug() << "Das Suchmuster wurde in den folgenden Ergebnissen gefunden:";

    QThreadPool threadPool;
    threadPool.setMaxThreadCount(coreCount);
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < coreCount; i++)
    {
        int start = i * splitWordList;
        int end = (i + 1) * splitWordList;
        threadPool.start([this, testList, inputString, start, end]() {
            searchString(testList, inputString, start, end);
        });
    }

    threadPool.waitForDone();

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    long long nanoseconds = duration;
    double seconds = static_cast<double>(nanoseconds) / 1e9;

    ui->labelDuration->setText("Dauer: " + QString::number(seconds) + " Sekunden");


    qDebug() << "Dauer:" << seconds << "Sekunden";

}


void MainWindow::on_pushButton_clicked()
{
    QString searchPattern = ui->lineEdit->text();
    search(searchPattern);
    QStringListModel *model = new QStringListModel(this); // Erstelle ein QStringListModel
    model->setStringList(combinedWordList); // Setze die QStringList als Datenquelle für das Model
    ui->listView->setModel(model);
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    combinedWordList.clear();

}

