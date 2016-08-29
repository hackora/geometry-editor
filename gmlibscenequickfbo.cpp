#include "gmlibscenequickfbo.h"

#include "window.h"
#include "gmlibscenequickfborenderer.h"

GMlibSceneQuickFbo::GMlibSceneQuickFbo() {

  setAcceptedMouseButtons(Qt::AllButtons);
  setFocus(true,Qt::ActiveWindowFocusReason);

  setMirrorVertically(true);

  connect( this, &QQuickItem::windowChanged,
           this, &GMlibSceneQuickFbo::onWindowChanged );
}

QQuickFramebufferObject::Renderer*
GMlibSceneQuickFbo::createRenderer() const {

  return new GMlibSceneQuickFboRenderer();
}

void
GMlibSceneQuickFbo::keyPressEvent(QKeyEvent* event)           { emit signKeyPressed(event); }

void
GMlibSceneQuickFbo::keyReleaseEvent(QKeyEvent* event)         { emit signKeyReleased(event); }

void
GMlibSceneQuickFbo::mousePressEvent(QMouseEvent* event)       { emit signMousePressed(event); }

void
GMlibSceneQuickFbo::mouseReleaseEvent(QMouseEvent* event)     { emit signMouseReleased(event); }

void
GMlibSceneQuickFbo::mouseDoubleClickEvent(QMouseEvent* event) { emit signMouseDoubleClicked(event); }

void
GMlibSceneQuickFbo::mouseMoveEvent(QMouseEvent* event)        { emit signMouseMoved(event); }

void
GMlibSceneQuickFbo::wheelEvent(QWheelEvent* event)            { emit signWheelEventOccurred(event); }

void
GMlibSceneQuickFbo::onWindowChanged(QQuickWindow* w) {

  if(!w) return;

  auto window = static_cast<Window*>(w);

  connect( this,   &GMlibSceneQuickFbo::signKeyPressed,
           window, &Window::signKeyPressed );

  connect( this,   &GMlibSceneQuickFbo::signKeyReleased,
           window, &Window::signKeyReleased );

  connect( this,   &GMlibSceneQuickFbo::signMouseDoubleClicked,
           window, &Window::signMouseDoubleClicked );

  connect( this,   &GMlibSceneQuickFbo::signMouseMoved,
           window, &Window::signMouseMoved );

  connect( this,   &GMlibSceneQuickFbo::signMousePressed,
           window, &Window::signMousePressed );

  connect( this,   &GMlibSceneQuickFbo::signMouseReleased,
           window, &Window::signMouseReleased );

  connect( this,   &GMlibSceneQuickFbo::signWheelEventOccurred,
           window, &Window::signWheelEventOccurred );
}
