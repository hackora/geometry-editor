#ifndef WINDOW_H
#define WINDOW_H


// qt
#include <QQuickView>

// stl
#include <memory>

class Window : public QQuickView {
  Q_OBJECT
public:
  explicit Window(QWindow *parent = 0);

  void      releasePersistence();

signals:

  // Relay singals from qml side
  void      signKeyPressed( QKeyEvent* event );
  void      signKeyReleased( QKeyEvent* event );
  void      signMouseDoubleClicked( QMouseEvent* event );
  void      signMouseMoved( QMouseEvent* event );
  void      signMousePressed( QMouseEvent* event );
  void      signMouseReleased( QMouseEvent* event );
  void      signWheelEventOccurred( QWheelEvent* event );
};

#endif // WINDOW_H
