//
// Created by ash on 5/19/25.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include "TextProcessor.h"
#include "Logger.h"


class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private slots:
    void onSelectTextFile();
    void onSelectKeywordsFile();
    void onProcessFiles();
private:
    QPushButton *selectTextButton;
    QLineEdit   *textFileLine;
    QPushButton *selectKeywordsButton;
    QLineEdit   *keywordsFileLine;
    QPushButton *processButton;
    TextProcessor processor;
};




#endif //MAINWINDOW_H
