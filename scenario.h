#ifndef SCENARIO_H
#define SCENARIO_H

// gmlib
namespace GMlib {

  class Scene;
  class Camera;
  class DefaultRenderer;
//  class DefaultSelectRenderer;
  class RenderTarget;
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
  void                                              cleanUp();
  virtual void                                      initializeScenario();

  void                                              startSimulation();
  void                                              stopSimulation();
  void                                              toggleSimulation();

  void                                              render( const QRect& viewport, GMlib::RenderTarget& target );
  void                                              prepare();

protected:
  void                                              timerEvent(QTimerEvent *e) override;

private:
  std::shared_ptr<GMlib::Scene>                     _scene;
  int                                               _timer_id;

  std::shared_ptr<GMlib::DefaultRenderer>           _renderer { nullptr };
  std::shared_ptr<GMlib::Camera>                    _camera   { nullptr };
  QRect                                             _viewport { QRect(0,0,1,1) };

private:
  static std::unique_ptr<Scenario>                  _instance;
public:
  static Scenario&                                  instance();
};

#endif
