#include "mainwindow.h"

#include <QDebug>
#include <QVector4D>

MainWindow::MainWindow(QWindow* parent) :
    QWindow(parent),
    controller(this)
{
    controller.setKmhMaxSpeed(250);
}

void MainWindow::setPresentation(Q3DSPresentation *_presentation)
{
    qDebug() << "Presentation loaded";
    if (_presentation == nullptr)
    {
        qDebug() << "presentation is null";
        return;
    }
    controller.setPresentation(_presentation);
}

void MainWindow::onPresentationReady()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->key() - 48 << "pressed";

    switch (event->key())
    {
        case Qt::Key_1:
            controller.setKmhUnits();
            break;

        case Qt::Key_2:
            controller.setMphUnits();
            break;

        case Qt::Key_3:
            controller.demoAnim();
            break;

        case Qt::Key_4:
            controller.leftLayout();
            break;

        case Qt::Key_5:
            controller.centralLayout();
            break;

        case Qt::Key_6:
            controller.rightLayout();
            break;

        case Qt::Key_7:
            controller.toggleVisibility();
            break;

        case Qt::Key_Plus:
            controller.speedUp();
            break;

        case Qt::Key_Minus:
            controller.slowDown();
            break;

        default:
            break;
    }
}
