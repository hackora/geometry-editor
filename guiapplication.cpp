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
           this,     &GuiApplication::onSceneGraphInvalidated,
           Qt::DirectConnection );

  connect( this, &QGuiApplication::lastWindowClosed,
           this, &QGuiApplication::quit );


  connect( &_window, &Window::signKeyPressed,
           this,     &GuiApplication::handleKeyPress );


  connect( &_window, &Window::beforeRendering,
           this,     &GuiApplication::handleGLInputEvents,
	   Qt::DirectConnection );




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

void GuiApplication::onSceneGraphInvalidated() {

  _scenario.deinitialize();
}

void GuiApplication::handleKeyPress( QKeyEvent* e ) {

  if(e->key() == Qt::Key_Q) {
    _window.close();
  }
  else if(e->key() == Qt::Key_P) {
    _input_events.push(std::make_shared<QKeyEvent>(*e));
  }
}

void GuiApplication::handleGLInputEvents() {

  while(!_input_events.empty()) {

    const auto& e  = _input_events.front();
    const auto& ke = std::dynamic_pointer_cast<const QKeyEvent>(e);

    if(ke and ke->key() == Qt::Key_P) {
      qDebug() << "Handling the P button";
      _scenario.replotTesttorus();
    }

    _input_events.pop();
  }
}



