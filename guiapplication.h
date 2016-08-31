#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include "scenario.h"
#include "window.h"

// qt
#include <QGuiApplication>

// stl
#include <memory>
#include <queue>




class GuiApplication : public QGuiApplication {
  Q_OBJECT
public:
  explicit GuiApplication(int& argc, char** argv);
  ~GuiApplication();

private:
  Window                                      _window;
  Scenario                                    _scenario;

  std::queue<std::shared_ptr<QInputEvent>>    _input_events;
  

private slots:
  void                                        handleGLInputEvents();
  void                                        handleKeyPress( QKeyEvent* );

  virtual void                                onSceneGraphInitialized();
  virtual void                                afterOnSceneGraphInitialized();

  virtual void                                onSceneGraphInvalidated();


signals:
  void                                        signOnSceneGraphInitializedDone();
};

#endif // GUIAPPLICATION_H
