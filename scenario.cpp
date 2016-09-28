#include "scenario.h"
#include "testtorus.h"

#include "gmlibsceneloader/gmlibsceneloaderdatadescription.h"

// openddl
#include "openddl/openddl.h"

// gmlib
#include <gmOpenglModule>
#include <gmSceneModule>
#include <gmParametricsModule>

// qt
#include <QTimerEvent>
#include <QDebug>

// stl
#include <cassert>
#include <iostream>
#include <iomanip>






class SimStateLock {
public:
  SimStateLock( Scenario& scenario ) : _scenario{scenario} {

    _state = _scenario.isSimulationRunning();
  }

  ~SimStateLock() {

    if(_state) _scenario.startSimulation();
    else       _scenario.stopSimulation();
  }

  Scenario&   _scenario;
  bool        _state;
};






Scenario::Scenario() : QObject(), _timer_id{0}/*, _select_renderer{nullptr}*/ {

  if(_instance != nullptr) {

    std::cerr << "This version of the Scenario only supports a single instance of the GMlibWraper..." << std::endl;
    std::cerr << "Only one of me(0x" << this << ") please!! ^^" << std::endl;
    assert(!_instance);
    exit(666);
  }

  _instance = std::unique_ptr<Scenario>(this);
}

Scenario::~Scenario() {

  _instance.release();
}

void
Scenario::deinitialize() {

  stopSimulation();

  _scene->remove(_testtorus.get());
  _testtorus.reset();

  _scene->removeLight(_light.get());
  _light.reset();

  _renderer->releaseCamera();
  _scene->removeCamera(_camera.get());

  _renderer.reset();
  _camera.reset();

  _scene->clear();
  _scene.reset();

  // Clean up GMlib GL backend
  GMlib::GL::OpenGLManager::cleanUp();
}

void
Scenario::initialize() {

  // Setup and initialized GMlib GL backend
  GMlib::GL::OpenGLManager::init();

  // Setup and init the GMlib GMWindow
  _scene = std::make_shared<GMlib::Scene>();
}

void
Scenario::initializeScenario() {

  // Insert a light
  auto init_light_pos = GMlib::Point<GLfloat,3>( 2.0, 4.0, 10 );
  _light = std::make_shared<GMlib::PointLight>( GMlib::GMcolor::White, GMlib::GMcolor::White,
                                                GMlib::GMcolor::White, init_light_pos );
  _light->setAttenuation(0.8, 0.002, 0.0008);
  _scene->insertLight( _light.get(), false );

  // Insert Sun
  _scene->insertSun();

  // Default camera parameters
  auto init_viewport_size = 600;
  auto init_cam_pos       = GMlib::Point<float,3>(  0.0f, 0.0f, 0.0f );
  auto init_cam_dir       = GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f );
  auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 0.0f, 1.0f );

  // Projection cam
  _renderer = std::make_shared<GMlib::DefaultRenderer>();
  _camera = std::make_shared<GMlib::Camera>();
  _renderer->setCamera(_camera.get());

  _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
  _camera->setCuttingPlanes( 1.0f, 8000.0f );
  _camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
  _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
  _scene->insertCamera( _camera.get() );
  _renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );

  // Surface
  _testtorus = std::make_shared<TestTorus>();
  _testtorus->toggleDefaultVisualizer();
  _testtorus->replot(200,200,1,1);
  _scene->insert(_testtorus.get());

  _testtorus->test01();
}

std::unique_ptr<Scenario> Scenario::_instance {nullptr};

Scenario&
Scenario::instance() { return *_instance; }

void
Scenario::prepare() { _scene->prepare(); }

void
Scenario::render( const QRect& viewport_in, GMlib::RenderTarget& target ) {

  // Update viewport
  if(_viewport != viewport_in) {

    _viewport = viewport_in;

    const auto& size = _viewport.size();
    _renderer->reshape( GMlib::Vector<int,2>(size.width(),size.height()));
    _camera->reshape( 0, 0, size.width(), size.height() );
  }

  // Render and swap buffers
  _renderer->render(target);
}

void
Scenario::startSimulation() {

  if( _timer_id || _scene->isRunning() )
    return;

  _timer_id = startTimer(16, Qt::PreciseTimer);
  _scene->start();
}

void
Scenario::stopSimulation() {

  if( !_timer_id || !_scene->isRunning() )
    return;

  _scene->stop();
  killTimer(_timer_id);
  _timer_id = 0;
}

void
Scenario::timerEvent(QTimerEvent* e) {

  e->accept();

  _scene->simulate();
  prepare();
}

void
Scenario::toggleSimulation() { _scene->toggleRun(); }

bool
Scenario::isSimulationRunning() {

  return _scene->isRunning();
}

void
Scenario::replotTesttorus() { _testtorus->replot(4, 4, 1, 1); }

void Scenario::load() {

  qDebug() << "Open scene...";
  SimStateLock a(*this);
  stopSimulation();


  auto filename = std::string("gmlib_save.openddl");

  auto is = std::ifstream(filename,std::ios_base::in);
  if(!is.is_open()) {
    std::cerr << "Unable to open " << filename << " for reading..."
              << std::endl;
    return;
  }

  is.seekg( 0, std::ios_base::end );
  auto buff_length = is.tellg();
  is.seekg( 0, std::ios_base::beg );

  std::vector<char> buffer(buff_length);
  is.read(buffer.data(),buff_length);


  std::cout << "Buffer length: " << buff_length << std::endl;

  GMlibSceneLoaderDataDescription gsdd;

  ODDL::DataResult result = gsdd.ProcessText(buffer.data());
  if(result != ODDL::kDataOkay) {

    auto res_to_char = [](auto nr, const ODDL::DataResult& result) {
      return char(((0xff << (8*nr)) & result ) >> (8*nr));
    };

    auto res_to_str = [&res_to_char](const ODDL::DataResult& result) {
      return std::string() + res_to_char(3,result) + res_to_char(2,result) + res_to_char(1,result) + res_to_char(0,result);
    };

    std::cerr << "Data result no A-OK: " << res_to_str(result) << " (" << result << ")" << std::endl;
    return;
  }



  std::cout << "Data result A-OK" << std::endl;
  auto structure = gsdd.GetRootStructure()->GetFirstSubnode();
  while(structure) {


    // Do something ^^,
    // Travers the ODDL structures and build your scene objects


    structure = structure->Next();
  }


  // Load GMlib::SceneObjects into the scene.

}

void
Scenario::save() {

  qDebug() << "Saving scene...";
  SimStateLock a(*this);
  stopSimulation();


  auto filename = std::string("gmlib_save.openddl");

  auto os = std::ofstream(filename,std::ios_base::out);
  if(!os.is_open()) {
    std::cerr << "Unable to open " << filename << " for saving..."
              << std::endl;
    return;
  }


  os << "GMlibVersion { int { 0x"
     << std::setw(6) << std::setfill('0')
     << std::hex << GM_VERSION
     << " } }"
     << std::endl;


  auto &scene = *_scene;
  for( auto i = 0; i < scene.getSize(); ++i ) {

    const auto obj = scene[i];
    save(os,obj);

  }
}

void Scenario::save(std::ofstream &os,
                    const GMlib::SceneObject *obj) {


  auto cam_obj = dynamic_cast<const GMlib::Camera*>(obj);
  if(cam_obj) return;


  os << obj->getIdentity() << std::endl
     << "{" << std::endl;

  saveSO(os,obj);

  auto ptorus_obj = dynamic_cast<const GMlib::PTorus<float>*>(obj);
  if(ptorus_obj)
    savePT(os,ptorus_obj);

  const auto& children = obj->getChildren();
  for(auto i = 0; i < children.getSize(); ++i )
    save(os,children(i));

  os << "}"
     << std::endl;

}

void Scenario::saveSO(std::ofstream &os,
                      const GMlib::SceneObject *obj) {

  os << "SceneObjectData" << std::endl
     << "{" << std::endl;



  os << "setCollapsed( bool {"
     << "  " << ( obj->isCollapsed()?"true":"false")
     << "} )";





  os << "}"
     << std::endl;

}

void Scenario::savePT(std::ofstream &os,
                      const GMlib::PTorus<float> *obj) {

  os << "PTorusData" << std::endl
     << "{" << std::endl;

  os << "}"
     << std::endl;
}


