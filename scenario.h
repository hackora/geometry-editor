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
  class RenderTarget;

  template <typename T>
  class PTorus;
}

// qt
#include <QObject>
#include <QRect>

// stl
#include <iostream>
#include <memory>

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

  void                                              render( const QRect& viewport, GMlib::RenderTarget& target );
  void                                              prepare();

  void                                              replotTesttorus();

  void         save();

private:
  void         save( std::ofstream& os, const GMlib::SceneObject* obj);

  void         saveSO( std::ofstream& os, const GMlib::SceneObject* obj);
  void         savePT( std::ofstream& os, const GMlib::PTorus<float>* obj);


protected:
  void                                              timerEvent(QTimerEvent *e) override;

private:
  std::shared_ptr<GMlib::Scene>                     _scene;
  int                                               _timer_id;

  std::shared_ptr<GMlib::DefaultRenderer>           _renderer { nullptr };
  std::shared_ptr<GMlib::Camera>                    _camera   { nullptr };
  QRect                                             _viewport { QRect(0,0,1,1) };

  std::shared_ptr<GMlib::PointLight>                _light;
  std::shared_ptr<TestTorus>                        _testtorus;

private:
  static std::unique_ptr<Scenario>                  _instance;
public:
  static Scenario&                                  instance();
};

#endif
