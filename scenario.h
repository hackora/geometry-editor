#ifndef SCENARIO_H
#define SCENARIO_H

// local
class TestTorus;

// gmlib
namespace GMlib {

class Scene;
class SceneObject;
class Camera;
class PointLight;
class DefaultRenderer;
class DefaultSelectRenderer;
class RenderTarget;

template <typename T>
class Array;

template <typename T, int n>
class Vector;

template <typename T, int n>
class Point;

template <typename T>
class PTorus;

template <typename T>
class PSphere;
}

// qt
#include <QObject>
#include <QRect>

// stl
#include <iostream>
#include <memory>

#include <vector>

// openddl
#include "openddl/openddl.h"


class Scenario: public QObject {
    Q_OBJECT
public:
    explicit Scenario();
    virtual ~Scenario();

    void                                              initialize();
    void                                              deinitialize();
    virtual void                                      initializeScenario();

    void                                              startSimulation();
    void                                              stopSimulation();
    void                                              toggleSimulation();
    bool                                              isSimulationRunning();

    void                                              render( const QRect& viewport, GMlib::RenderTarget& target );
    void                                              prepare();

    void                                              load();

    void                                              save();

    void                                              frontView();

    void                                              topView();

    void                                              sideView();

    void                                              toggleSelection(bool var);

    GMlib::Array<GMlib::SceneObject*>                 selectedObjects();

    void                                              addtoSelection(GMlib::SceneObject* obj);

    void                                              removefromSelection(GMlib::SceneObject* obj);

    void                                              cycleSelection(bool forward);

    GMlib::SceneObject*                               findSceneObject(const QPoint& pos);

    const GMlib::Point <int ,2>                       fromQtToGMlibViewPoint(const  QPoint& pos);

    void                                              moveCamera(QPoint current, QPoint previous);

    void                                              rotateCamera(QPoint current, QPoint previous);

    void                                              moveCameraWheel(QPoint delta);

    void                                              rotateSelectedObjects(QPoint current, QPoint previous);

    void                                              translateSelectedObjects(QPoint current, QPoint previous);

    void                                              scaleSelectedObjects(QPoint current, QPoint previous);

    void                                              addSphere();

    void                                              addPTorus();

    void                                              clearScene();

    void                                              addPCylinder();

    void                                              addPCone();

    void                                              addPBentHorns();

    void                                              addPApple();

    void                                              addPlane();

    void                                              addSeaShell();

    void                                              addKleinsBottle();

    void                                              addBoysSurface();

private:
    void                                              save( std::ofstream& os, const GMlib::SceneObject* obj);

    void                                              saveSO( std::ofstream& os, const GMlib::SceneObject* obj);

    void                                              savePT( std::ofstream& os, const GMlib::PTorus<float>* obj);

    void                                              visit(ODDL::Structure* T);

    void                                              preorder(ODDL::Structure* T);


protected:
    void                                              timerEvent(QTimerEvent *e) override;

private:
    std::shared_ptr<GMlib::Scene>                     _scene;
    int                                               _timer_id;

    std::shared_ptr<GMlib::DefaultRenderer>           _renderer { nullptr };
    std::shared_ptr<GMlib::DefaultSelectRenderer>     _select_renderer { nullptr };
    std::shared_ptr<GMlib::Camera>                    _camera   { nullptr };
    QRect                                             _viewport { QRect(0,0,1,1) };

    std::shared_ptr<GMlib::PointLight>                _light;
    std::vector<std::unique_ptr<GMlib::SceneObject>>  _scene_vector;


private:
    static std::unique_ptr<Scenario>                  _instance;
public:
    static Scenario&                                  instance();
};

#endif
