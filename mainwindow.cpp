#include "mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWindow* parent) :
    QWindow(parent),
    presentation(nullptr)
{

}

void MainWindow::setPresentation(Q3DSPresentation *_presentation)
{
    qDebug() << "Presentation loaded";
    if (_presentation == nullptr)
    {
        qDebug() << "presentation is null";
        return;
    }
    presentation = _presentation;
}

void MainWindow::onPresentationReady()
{

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(!presentation) return;

    qDebug() << event->key() - 48 << "pressed";

    switch (event->key())
    {
        case Qt::Key_1:
        presentation->setAttribute("Slide","playmode",QVariant("Looping"));
        presentation->setDataInputValue("CurrentSlide", "Left");
            break;

        case Qt::Key_2:
        presentation->setDataInputValue("CurrentSlide", "Mid");
            break;

        case Qt::Key_3:
        presentation->setDataInputValue("CurrentSlide", "Right");
            break;

        case Qt::Key_4:
                presentation->setDataInputValue("arrowAnim", 1.0, true);
            break;

        default:
            break;
    }
}
