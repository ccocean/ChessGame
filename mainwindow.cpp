#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QUrl>
#include <QList>
#include <QtGui/QPixmap>
#include <QtGui/QDragEnterEvent>
#include <QtGui/QDropEvent>
#include <QMimeData>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label_Board->installEventFilter(this);
    ui->label_Board->setAcceptDrops(true);
    chess=Chess();
    //connect(ui->pushButton_process, SIGNAL(clicked()), this, SLOT());
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->label_Board)
    {
        if(event->type()==QEvent::DragEnter)
        {
            // [[2]]: 当拖放时鼠标进入label时, label接受拖放的动作
            QDragEnterEvent *dee = dynamic_cast<QDragEnterEvent *>(event);
            dee->acceptProposedAction();
            return true;
        }
        else if(event->type()==QEvent::Drop)
        {
            // [[3]]: 当放操作发生后, 取得拖放的数据
            QDropEvent *de = dynamic_cast<QDropEvent *>(event);
            QList<QUrl> urls = de->mimeData()->urls();

            if (urls.isEmpty()) { return true; }
            QString path = urls.first().toLocalFile();

            // [[4]]: 在label上显示拖放的图片
            //QImage image(path); // QImage对I/O优化过, QPixmap对显示优化
            image=QImage(path);
            if (!image.isNull())
            {
                image = image.scaled(ui->label_Board->size(),
                                     Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
                ui->label_Board->setPixmap(QPixmap::fromImage(image));
            }
            chess.initImg(image);
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_process_clicked()
{
    //QMessageBox(QMessageBox::Warning,"Information","Really to clear data?",QMessageBox::Yes|QMessageBox::No,NULL);
    chess.startProc();
    m_label_Count="Count: ";
    m_label_Count+=QString::number(chess.getCount(),10);
    ui->label_Count->setText(m_label_Count);
    ui->label_Board->update();
}
