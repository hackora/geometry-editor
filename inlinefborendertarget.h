#ifndef INLINEFBORENDERTARGET_H
#define INLINEFBORENDERTARGET_H

// gmlib
#include <scene/gmrendertarget>

// qt
#include <QOpenGLFunctions>

class InlineFboRenderTarget : public GMlib::RenderTarget {
public:
    explicit InlineFboRenderTarget();

    GLint&                    fbo();

private:
    mutable QOpenGLFunctions  _gl;
    GLint                     _fbo;

    void      doPrepare()  const override;
    void      doBind()   const override;
    void      doUnbind() const override;
    void      doResize()  override;
};

#endif // INLINEFBORENDERTARGET_H
