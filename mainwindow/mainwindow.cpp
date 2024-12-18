#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // 連結關閉功能
    connect(ui->actionClose, SIGNAL(triggered(bool)), this, SLOT(close()));

    // 連結儲存功能
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::onSaveFile);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onSaveFile() {
    // 打開儲存檔案的對話框
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Text Files (*.txt);;All Files (*)"));

    // 檢查是否選擇檔案
    if (fileName.isEmpty()) {
        return; // 如果未選擇檔案，直接返回
    }

    QFile file(fileName);

    // 嘗試打開檔案
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file:\n%1").arg(file.errorString()));
        return;
    }

    // 寫入檔案內容
    QTextStream out(&file);
    out << ui->textEdit->toPlainText(); // 假設你的 QTextEdit 名稱為 textEdit
    file.close();

    QMessageBox::information(this, tr("Success"), tr("File saved successfully!"));
}
