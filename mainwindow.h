#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>

#include "chess.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_pushButton_process_clicked();

private:
    Chess chess;
    QImage image;
    QString m_label_Count;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
