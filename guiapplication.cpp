#include "guiapplication.h"

// qt
#include <QOpenGLContext>
#include <QDebug>

// stl
#include <iostream>
#include <cassert>



GuiApplication::GuiApplication(int& argc, char **argv) : QGuiApplication(argc, argv) {

  setApplicationDisplayName( "Hello GMlib ^^," );

  connect( &_window, &Window::sceneGraphInitialized,
           this,     &GuiApplication::onSceneGraphInitialized,
           Qt::DirectConnection );

  connect( this, &GuiApplication::signOnSceneGraphInitializedDone,
           this, &GuiApplication::afterOnSceneGraphInitialized );

  connect( &_window, &Window::sceneGraphInvalidated,
           this,     &GuiApplication::cleanUpGL,
           Qt::DirectConnection );

  connect( this, &QGuiApplication::lastWindowClosed,
           this, &QGuiApplication::quit );

  _window.setSource(QUrl("qrc:///qml/main.qml"));
  _window.show();
}


GuiApplication::~GuiApplication() {


  _scenario.stopSimulation();

  _window.releasePersistence();
  _window.releaseResources();

  std::cout << "Bye bye ^^, ~~ \"emerge --oneshot life\"" << std::endl;
}

void
GuiApplication::onSceneGraphInitialized() {

  // Init the scene object and GMlibs OpenGL backend
  _scenario.initialize();

  // Pring surface format
  qDebug() << _window.format();

  // Init a scenario
  _scenario.initializeScenario();
  _scenario.prepare();

  emit signOnSceneGraphInitializedDone();
}

void
GuiApplication::afterOnSceneGraphInitialized() {

  // Start simulator
  _scenario.startSimulation();
}

void GuiApplication::cleanUpGL() {

  _scenario.cleanUp();
}
