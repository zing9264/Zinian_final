#ifndef WIDGET_H
#define WIDGET_H

#include <QApplication>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QImage>
#include <QDebug>
#include <QElapsedTimer>
#include <QPixmap>

#include <QVector>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>
//copy------------------
#include <QClipboard>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
//copy------------------
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define Height 600
#define Width 1000

bool accuracy();

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);

    void paintEvent(QPaintEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void addLine(QPoint pos);

    QVector<QVector<QPoint> > _lines;

   private:
    QPushButton *OK;
    QPushButton *Clear;
    QPushButton *OCR;
    int erase,copy;
    bool show_OCR;
    QVBoxLayout *mainLayout;
    QHBoxLayout *btnLayout;
    QLineEdit *editor;
    QPushButton *setContentBtn;
    QPushButton *getContentBtn;
    QPushButton *cleanCopy;
    QPushButton *backSpace;
signals:

public slots:
    void Clear_clicked();
    void OK_clicked();
    void OCR_clicked();
    void setClipboardContent();
    void getClipboardContent();
    void cleanClipboardContent();
    void backSpaceClipboardContent();

};

#endif
