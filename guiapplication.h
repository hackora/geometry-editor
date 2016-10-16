#ifndef GUIAPPLICATION_H
#define GUIAPPLICATION_H

#include "scenario.h"
#include "window.h"

// qt
#include <QGuiApplication>

// stl
#include <memory>
#include <queue>


struct ManipulationModes
{
    bool rotMode;
    bool transMode;
    bool scaleMode;
    ManipulationModes() : rotMode{false}, transMode{false}, scaleMode{false} {}
    void toggleRot() {rotMode = !rotMode;}
    void toggleTrans() {transMode = !transMode;}
    void toggleScale() {scaleMode = !scaleMode;}
    bool noMode() {if(rotMode || transMode || scaleMode ){return false;}else{return true;}}
    void allOff() {rotMode=false;scaleMode=false;transMode=false;}
};


class GuiApplication : public QGuiApplication {
    Q_OBJECT
public:
    explicit GuiApplication(int& argc, char** argv);
    ~GuiApplication();

private:
    Window                                      _window;
    Scenario                                    _scenario;

    std::queue<std::shared_ptr<QInputEvent>>    _input_events;

    std::queue<std::shared_ptr<const QString>>  _button_events;

    QPoint                                      _previous{0,0};
    bool                                        _toggle={false};
    ManipulationModes                           _modes;



private slots:
    void                                        handleGLInputEvents();
    void                                        handleGLButtonEvents();
    void                                        handleKeyPress( QKeyEvent* );
    void                                        handleMouseClick( QMouseEvent* );
    void                                        handleMouseMove( QHoverEvent* );
    void                                        handleWheelMove( QWheelEvent* );
    void                                        handleMouseClickMove( QMouseEvent* );

    virtual void                                onSceneGraphInitialized();
    virtual void                                afterOnSceneGraphInitialized();

    virtual void                                onSceneGraphInvalidated();

signals:
    void                                        signOnSceneGraphInitializedDone();

public slots:
    void                                        handleGUIButtons(const QString &in);
};

#endif // GUIAPPLICATION_H
