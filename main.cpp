#include "mainwindow.h"

#include <QGuiApplication>
#include <QtStudio3D/Q3DSViewerSettings>
#include <QtStudio3D/Q3DSPresentation>
#include <QtStudio3D/Q3DSSurfaceViewer>
#include <QOpenGLContext>
#include <QDebug>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QSize size(1200, 620);
    MainWindow window;

    window.resize(size);
    window.setSurfaceType(QSurface::OpenGLSurface);
    window.create();
    Q3DSSurfaceViewer viewer;
    QOpenGLContext context;

    context.setFormat(window.format());
    context.create();

    window.connect(&viewer, &Q3DSSurfaceViewer::presentationLoaded, [&window, &viewer]()
    {
        window.setPresentation(viewer.presentation());
    });

    window.connect(&viewer, &Q3DSSurfaceViewer::presentationReady, &window, &MainWindow::onPresentationReady);

    viewer.presentation()->setSource(QUrl(QStringLiteral("qrc:/speedometer/speedometer.uia")));
    viewer.setUpdateInterval(0);
    viewer.settings()->setShowRenderStats(false);
    viewer.settings()->setScaleMode(Q3DSViewerSettings::ScaleModeCenter);
    viewer.create(&window, &context);
    window.show();
    return app.exec();
}
