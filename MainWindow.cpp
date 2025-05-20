//
// Created by ash on 5/19/25.
//


#include "MainWindow.h"
#include "Logger.h"
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(central);

    QHBoxLayout *h1 = new QHBoxLayout();
    selectTextButton = new QPushButton("Select keywords", this);
    textFileLine = new QLineEdit(this);
    textFileLine->setReadOnly(true);
    h1->addWidget(selectTextButton);
    h1->addWidget(textFileLine);
    vLayout->addLayout(h1);
    connect(selectTextButton, &QPushButton::clicked, this, &MainWindow::onSelectTextFile);

    QHBoxLayout *h2 = new QHBoxLayout();
    selectKeywordsButton = new QPushButton("Select textfile", this);
    keywordsFileLine = new QLineEdit(this);
    keywordsFileLine->setReadOnly(true);
    h2->addWidget(selectKeywordsButton);
    h2->addWidget(keywordsFileLine);
    vLayout->addLayout(h2);
    connect(selectKeywordsButton, &QPushButton::clicked, this, &MainWindow::onSelectKeywordsFile);

    processButton = new QPushButton("Find frequency", this);
    vLayout->addWidget(processButton);
    connect(processButton, &QPushButton::clicked, this, &MainWindow::onProcessFiles);

    setCentralWidget(central);
    resize(800, 200);
    setWindowTitle("Word Frequency Analyzer");
}

void MainWindow::onSelectTextFile() {
    QString file = QFileDialog::getOpenFileName(this, "Выберите текстовый файл", "",
                                                "Text Files (*.txt);;All Files (*)");
    if (!file.isEmpty()) {
        textFileLine->setText(file);
        Logger::log("Selected text file: " + file.toStdString());
    }
}

void MainWindow::onSelectKeywordsFile() {
    QString file = QFileDialog::getOpenFileName(this, "Выберите файл ключевых слов", "",
                                                "Text Files (*.txt);;All Files (*)");
    if (!file.isEmpty()) {
        keywordsFileLine->setText(file);
        Logger::log("Selected keywords file: " + file.toStdString());
    }
}

void MainWindow::onProcessFiles() {
    if (textFileLine->text().isEmpty() || keywordsFileLine->text().isEmpty()) {
        Logger::log("Ошибка: не выбраны файлы", "ERROR");
        return;
    }

    std::string result = processor.processFiles(
        textFileLine->text().toStdString(),
        keywordsFileLine->text().toStdString()
    );

    Logger::log("Processing complete.");
    QMessageBox::information(this, "Результат", QString::fromStdString(result));
}
