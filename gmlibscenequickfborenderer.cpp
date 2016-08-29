#include "gmlibscenequickfborenderer.h"

#include "scenario.h"
#include "gmlibscenequickfbo.h"

//qt
#include <QOpenGLFramebufferObjectFormat>
#include <QQuickWindow>

GMlibSceneQuickFboRenderer::GMlibSceneQuickFboRenderer() {

  _gl.initializeOpenGLFunctions();
}

QOpenGLFramebufferObject*
GMlibSceneQuickFboRenderer::createFramebufferObject(const QSize& size)  {

  _size = size;

  QOpenGLFramebufferObjectFormat format;
  format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
  return new QOpenGLFramebufferObject(size, format);
}

void
GMlibSceneQuickFboRenderer::render() {

  // Pick up the FBO set by the QQuickFrameBufferObject upon the render() call
  _gl.glGetIntegerv(GL_FRAMEBUFFER_BINDING,&_rt.fbo());

  // Prepare render and camera
  auto &scenario = Scenario::instance();
  scenario.render(QRect(QPoint(0,0),QSize(_size)),_rt);

  // Not necessary, but for clarity let's restore the full GL state as we entered the render() method
  _gl.glBindFramebuffer(GL_FRAMEBUFFER,_rt.fbo());

  // Restore to QML's GLState;
  // we do not know what GMlib has done
  _item->window()->resetOpenGLState();

  // Throttle
  update();
}

void
GMlibSceneQuickFboRenderer::synchronize(QQuickFramebufferObject* item) {

  _item = static_cast<GMlibSceneQuickFbo*>(item);
}
