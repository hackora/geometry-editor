#include "guiapplication.h"

// qt
#include <QOpenGLContext>
#include <QDebug>
#include<QQuickItem>

// stl
#include <iostream>
#include <cassert>

//GMlib
#include <core/gmpoint>



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

    connect( &_window, &Window::beforeRendering,
             this,     &GuiApplication::handleGLButtonEvents,
             Qt::DirectConnection );

    connect( &_window, &Window::signMousePressed,
             this,     &GuiApplication::handleMouseClick );

    connect( &_window, &Window::signMouseMoved,
             this,     &GuiApplication::handleMouseMove );

    connect( &_window, &Window::signMouseClickMoved,
             this,     &GuiApplication::handleMouseClickMove );

    connect( &_window, &Window::signWheelEventOccurred,
             this,     &GuiApplication::handleWheelMove );

    _window.setSource(QUrl("qrc:///qml/main.qml"));

    QQuickItem* item = _window.rootObject();

    connect( item, SIGNAL(buttonClicked(QString)),
             this,     SLOT(handleGUIButtons(QString)));

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
    else {
        _input_events.push(std::make_shared<QKeyEvent>(*e));
    }
}

void GuiApplication::handleGLInputEvents() {

    while(!_input_events.empty()) {

        const auto& e  = _input_events.front();
        const auto& ke = std::dynamic_pointer_cast<const QKeyEvent>(e);

        if(ke){
            if(ke->key() == Qt::Key_P) {
                //replot_Torus?
            }
            else if(ke->key() == Qt::Key_S && ke->modifiers()== Qt::ControlModifier) {
                _scenario.save();
            }
            else if(ke->key() == Qt::Key_O) {
                _scenario.load();
            }
            else if(ke->key() == Qt::Key_A) {
                _toggle = !_toggle;
                _scenario.toggleSelection(_toggle);
            }
            else if(ke->key() == Qt::Key_R){
                _modes.scaleMode=false;
                _modes.transMode=false;
                _modes.toggleRot();
            }
            else if(ke->key() == Qt::Key_T){
                _modes.scaleMode=false;
                _modes.rotMode=false;
                _modes.toggleTrans();
            }
            else if(ke->key() == Qt::Key_S){
                _modes.rotMode=false;
                _modes.transMode=false;
                _modes.toggleScale();
            }
            else if(ke->key() == Qt::Key_Escape){
                _modes.allOff();
            }
            else if(ke->key() == Qt::Key_1) {
                _scenario.frontView();
            }
            else if(ke->key() == Qt::Key_2) {
                _scenario.sideView();
            }
            else if(ke->key() == Qt::Key_3) {
                _scenario.topView();
            }
            else if(ke->key() == Qt::Key_Left){
                _scenario.cycleSelection(true);
            }
            else if(ke->key() == Qt::Key_Right){
                _scenario.cycleSelection(false);
            }
        }
        _input_events.pop();
    }
}

void GuiApplication::handleMouseClick( QMouseEvent* e  ) {

    if( e->buttons() == Qt::LeftButton && _modes.noMode()) {
        _scenario.findSceneObject(e->pos());

    }
    if( e->buttons() == Qt::RightButton && !_modes.noMode()) {
        _modes.allOff();

    }
    else if (e->buttons() == Qt::MiddleButton){
        _previous = e->pos();
    }

}

void GuiApplication::handleMouseClickMove(QMouseEvent* e) {

    if(_previous.isNull())
        _previous = e->pos();
    if (e->buttons()== Qt::MiddleButton && QGuiApplication::keyboardModifiers().testFlag(Qt::ControlModifier) )
        _scenario.moveCamera(e->pos(),_previous);

    else if(e->buttons()== Qt::MiddleButton){
        _scenario.rotateCamera(e->pos(),_previous);
    }
    _previous = e->pos();
}

void GuiApplication::handleMouseMove( QHoverEvent* e) {

    if(_previous.isNull())
        _previous = e->pos();

    if(_modes.rotMode){
        _scenario.rotateSelectedObjects(e->pos(),_previous);
    }

    else if(_modes.transMode){
        _scenario.translateSelectedObjects(e->pos(),_previous);
    }

    else if(_modes.scaleMode){
        _scenario.scaleSelectedObjects(e->pos(),_previous);
    }
     _previous = e->pos();
}

void GuiApplication::handleWheelMove( QWheelEvent* e  ) {

    _scenario.moveCameraWheel(e->angleDelta());

}

void GuiApplication::handleGUIButtons(const QString &in){

    _button_events.push(std::make_shared<const QString >(in));

}

void GuiApplication::handleGLButtonEvents() {

    while(!_button_events.empty()) {

        auto e  = _button_events.front();
        const QString ke = *std::dynamic_pointer_cast<const QString>(e);

        if (!QString::compare(ke,"sphere")){

            _scenario.addSphere();

        }

        else if(!QString::compare(ke,"torus")){

            _scenario.addPTorus();

        }

        else if(!QString::compare(ke,"cylinder")){

            _scenario.addPCylinder();

        }

        else if(!QString::compare(ke,"cone")){

            _scenario.addPCone();

        }

        else if(!QString::compare(ke,"benthorns")){

            _scenario.addPBentHorns();

        }

        else if(!QString::compare(ke,"apple")){

            _scenario.addPApple();

        }

        else if(!QString::compare(ke,"plane")){

            _scenario.addPlane();

        }

        else if(!QString::compare(ke,"seashell")){

            _scenario.addSeaShell();

        }

        else if(!QString::compare(ke,"kleinsbottle")){

            _scenario.addKleinsBottle();

        }

        else if(!QString::compare(ke,"boyssurface")){

            _scenario.addBoysSurface();

        }

        else if(!QString::compare(ke,"clear")){

            _scenario.clearScene();

        }

        _button_events.pop();
    }

}

