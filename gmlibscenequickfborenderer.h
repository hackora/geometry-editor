#ifndef GMLIBSCENEQUICKFBORENDERER_H
#define GMLIBSCENEQUICKFBORENDERER_H


// local
#include "inlinefborendertarget.h"

// qt
#include <QSize>
#include <QtQuick/QQuickFramebufferObject>
#include <QOpenGLFunctions>


class Window;
class GMlibSceneQuickFbo;


class GMlibSceneQuickFboRenderer : public QQuickFramebufferObject::Renderer {

public:
    GMlibSceneQuickFboRenderer();

    QOpenGLFramebufferObject*   createFramebufferObject(const QSize &size) override;

    void                        render() override;
    void                        synchronize(QQuickFramebufferObject *item) override;


private:
    QOpenGLFunctions            _gl;
    GMlibSceneQuickFbo*         _item;
    Window*                     _window;
    QSize                       _size;
    InlineFboRenderTarget       _rt;
};


#endif // GMLIBSCENEQUICKFBORENDERER_H
