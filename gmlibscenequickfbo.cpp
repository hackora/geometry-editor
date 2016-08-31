#include "gmlibscenequickfbo.h"

#include "window.h"
#include "gmlibscenequickfborenderer.h"

GMlibSceneQuickFbo::GMlibSceneQuickFbo() {

  setAcceptedMouseButtons(Qt::AllButtons);
  setFocus(true,Qt::ActiveWindowFocusReason);

  setMirrorVertically(true);

  connect( this, &QQuickItem::windowChanged,
           this, &GMlibSceneQuickFbo::onWindowChanged );

  _prev_time = std_system_clock::now();
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

  connect( window, &Window::beforeRendering,
           this,   &GMlibSceneQuickFbo::updateFps );
}

unsigned int
GMlibSceneQuickFbo::fps() const {

  return _fps_avg;
}

void 
GMlibSceneQuickFbo::updateFps() {

  using namespace std::chrono; 

  auto current_time = system_clock::now();
  auto since_prev   = duration_cast<milliseconds>(current_time -_prev_time);

  const auto fps_interval = 2;
  if(since_prev > seconds(fps_interval)) {
    _prev_time   += seconds(fps_interval);
    _fps_avg      = _fps_counter / fps_interval;
    _fps_counter  = 0;
    emit signFpsUpdated();
  }

  _fps_counter++;
}

