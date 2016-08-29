#ifndef GMLIBSCENEQUICKFBO
#define GMLIBSCENEQUICKFBO

// qt
#include <QtQuick/QQuickFramebufferObject>

// stl
#include <chrono>

class GMlibSceneQuickFbo : public QQuickFramebufferObject {
  Q_OBJECT

public:
  GMlibSceneQuickFbo();

  Renderer*         createRenderer() const override;


protected:
  void              keyPressEvent(QKeyEvent *event) override;
  void              keyReleaseEvent(QKeyEvent *event) override;
  void              mousePressEvent(QMouseEvent *event) override;
  void              mouseReleaseEvent(QMouseEvent *event) override;
  void              mouseDoubleClickEvent(QMouseEvent *event) override;
  void              mouseMoveEvent(QMouseEvent *event) override;
  void              wheelEvent(QWheelEvent *event) override;


private slots:
  void              onWindowChanged( QQuickWindow* window );


signals:
  void              signKeyPressed( QKeyEvent* event );
  void              signKeyReleased( QKeyEvent* event );
  void              signMouseDoubleClicked( QMouseEvent* event );
  void              signMouseMoved( QMouseEvent* event );
  void              signMousePressed( QMouseEvent* event );
  void              signMouseReleased( QMouseEvent* event );
  void              signWheelEventOccurred( QWheelEvent* event);
};

#endif
