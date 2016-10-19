#include "scenario.h"
#include "testtorus.h"
#include <math.h>

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
#include <QPoint>

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

Scenario::Scenario() : QObject(), _timer_id{0}, _select_renderer{nullptr} {

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

    _scene->removeLight(_light.get());
    _light.reset();

    _renderer->releaseCamera();
    _scene->removeCamera(_camera.get());
    _camera.reset();

    _renderer.reset();
    _select_renderer.reset();

    _scene->clear();
    _scene_vector.clear();
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
    _select_renderer = std::make_shared<GMlib::DefaultSelectRenderer>();
    _camera = std::make_shared<GMlib::Camera>();
    _renderer->setCamera(_camera.get());

    _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    _camera->setCuttingPlanes( 1.0f, 8000.0f );
    _camera->rotateGlobal( GMlib::Angle(-45), GMlib::Vector<float,3>( 1.0f, 0.0f, 0.0f ) );
    _camera->translateGlobal( GMlib::Vector<float,3>( 0.0f, -20.0f, 20.0f ) );
    _scene->insertCamera( _camera.get());
    _renderer->reshape( GMlib::Vector<int,2>(init_viewport_size, init_viewport_size) );
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

/**
 * Visit every ODDL structure, incomplete at the moment loads very basic files.
 */

void Scenario::visit(ODDL::Structure* T){

    /*    if(T->GetStructureType()==int(GMStructTypes::GMlibCamera))
        qDebug()<<"This is Camera"<<T->GetStructureType();
    if(T->GetStructureType()==int(GMStructTypes::GMlibVersion))
        qDebug()<<"This is GMlibVersion"<<T->GetStructureType();
    if(T->GetStructureType()==int(GMStructTypes::GMlibSceneObjectData))
        qDebug()<<"This is SceneObjectData"<<T->GetStructureType();
    if(T->GetStructureType()==int(GMStructTypes::GMlibSet))
        qDebug()<<"This is set"<<T->GetStructureType();
    if(T->GetStructureType()==int(GMStructTypes::GMlibPoint))
        qDebug()<<"This is point"<<T->GetStructureType();
    if(T->GetStructureType()==int(GMStructTypes::GMlibVector))
        qDebug()<<"This is vector"<<T->GetStructureType();
    if(T->GetStructureType()==int(ODDL::kDataFloat))
        qDebug()<<"This is float"<<T->GetStructureType();
*/

    if(T->GetStructureType()==int(GMStructTypes::GMlibCamera)){

        auto camera_obj= new GMlib::Camera;
        qDebug()<<"I created a new camera"<<&camera_obj;
        //camera_obj->set(point,vector,vector);
        auto structure1 = T->GetNextNode(T);
        auto structure = structure1->GetNextNode(structure1);
        while(structure){

            if(structure->GetStructureType()==int(GMStructTypes::GMlibSet)){

                // Insert a light
                auto init_light_pos = GMlib::Point<GLfloat,3>( 2.0, 4.0, 10 );
                _light = std::make_shared<GMlib::PointLight>( GMlib::GMcolor::White, GMlib::GMcolor::White,
                                                              GMlib::GMcolor::White, init_light_pos );
                _light->setAttenuation(0.8, 0.002, 0.0008);
                _scene->insertLight( _light.get(), false );

                // Insert Sun
                _scene->insertSun();
                qDebug()<<"light and sun inserted";

                qDebug()<<"Setting the camera...";
                auto init_viewport_size = 600;
                auto init_cam_pos       = GMlib::Point<float,3>(  0.0f, 0.0f, 0.0f );
                auto init_cam_dir       = GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f );
                auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 0.0f, 1.0f );


                // Projection cam
                camera_obj->set(init_cam_pos,init_cam_dir,init_cam_up);
                qDebug()<<"Camera Set";
                _scene->insertCamera(camera_obj);
                qDebug()<<"Camera inserted";

            }
            structure=structure->Next();
        }
    }
}

/**
 * Preorder Traversal Algorithm
 * for ODDL structures (O(n))
 */

void Scenario::preorder(ODDL::Structure* T){

    if (T==nullptr) return;
    visit (T);
    preorder(T->GetNextNode(T));
    preorder(T->Next());
}

/**
 * Load Scene
 */

void Scenario::load() {

    qDebug() << "Open scene...";
    SimStateLock a(*this);
    stopSimulation();

    auto filename = std::string("/home/ghada/Documents/C++/GM_lib/source/geometry-editor/gmlib_scene.openddl");

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

    qDebug()<< gsdd.GetErrorLine();

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

    // Do something ^^,
    // Travers the ODDL structures and build your scene objects

    preorder(structure);




    // Load GMlib::SceneObjects into the scene.

}


/**
 * Save Scene
 */

void Scenario::save() {

    qDebug() << "Saving scene...";
    SimStateLock a(*this);
    stopSimulation();


    auto filename = std::string("/home/ghada/Documents/C++/GM_lib/source/geometry-editor/save.openddl");

    auto os = std::ofstream(filename,std::ios_base::out);
    if(!os.is_open()) {
        std::cerr << "Unable to open " << filename << " for saving..."
                  << std::endl;
        return;
    }


    os << "GMlibVersion { int32 { 0x"
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
       << "} )"<< std::endl;;

    os << "set { Point {" << std::endl
       << "  " << obj->getGlobalPos()<<"}"<< std::endl
       << "Vector {" << std::endl
       << "  " << obj->getGlobalDir()<< std::endl
       << "}"<< std::endl
       << "Vector {" << std::endl
       << "  " << obj->getGlobalSide()<< std::endl
       << "}"<< std::endl;

    os << "}" << std::endl;


}

void Scenario::savePT(std::ofstream &os,
                      const GMlib::PTorus<float> *obj) {

    os << "PTorusData" << std::endl
       << "{" << std::endl;
    os << "}"
       << std::endl;
}

/**
 * Multiple Views
 */

void Scenario::frontView() {

    auto cameraPos= _camera->getPos().getLength();
    auto init_cam_pos       = GMlib::Point<float,3>(  cameraPos, 0.0f, 0.0f );
    auto init_cam_dir       = GMlib::Vector<float,3>( -1.0f, 0.0f, 0.0f );
    auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 0.0f, 1.0f );
    _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    _camera->updateCameraOrientation();
}

void Scenario::topView() {

    auto cameraPos= _camera->getPos().getLength();
    auto init_cam_pos       = GMlib::Point<float,3>(  0.0f, 0.0f, cameraPos );
    auto init_cam_dir       = GMlib::Vector<float,3>( 0.0f, 0.0f, -1.0f );
    auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 1.0f, 0.0f );
    _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    _camera->updateCameraOrientation();
}

void Scenario::sideView() {

    auto cameraPos= _camera->getPos().getLength();
    auto init_cam_pos       = GMlib::Point<float,3>(  0.0f, cameraPos, 0.0f );
    auto init_cam_dir       = GMlib::Vector<float,3>( 0.0f, -1.0f, 0.0f );
    auto init_cam_up        = GMlib::Vector<float,3>(  0.0f, 0.0f, 1.0f );
    _camera->set(init_cam_pos,init_cam_dir,init_cam_up);
    _camera->updateCameraOrientation();
}

/**
 * Convert QPoint
 * to GMlib Point
 */

const GMlib::Point <int ,2> Scenario::fromQtToGMlibViewPoint(const  QPoint& pos){

    int x = pos.x();
    int y = _camera->getViewportH() -pos.y()-1;
    auto gm_point = GMlib::Point <int ,2>(x,y);
    return(gm_point);
}

/**
 * Select objects from
 * the scene
 */

GMlib::SceneObject* Scenario::findSceneObject(const  QPoint& pos) {

    _select_renderer->setCamera( _camera.get());
    _select_renderer->reshape( GMlib::Vector<int,2>(_viewport.width(), _viewport.height()));
    _select_renderer->prepare();
    _select_renderer->select(0);
    auto gm_point = fromQtToGMlibViewPoint(pos);
    auto sel_obj = _select_renderer->findObject(gm_point(0),gm_point(1));
    _select_renderer->releaseCamera();
    if(sel_obj != nullptr) {
        toggleSelection(false);
        addtoSelection(sel_obj);
    }
    return sel_obj;
}

/**
 * Select All objects
 */

void Scenario::toggleSelection(bool var){

    GMlib::Array<const GMlib::SceneObject*> arr;
    _scene->getRenderList(arr,_camera.get());
    for(int j=0;j<arr.getSize();++j){
        if(arr[j]->getName() != _camera->getName()){
            _scene->find(arr[j]->getName())->setSelected(var);
            _scene->updateSelection(_scene->find(arr[j]->getName()));
        }
    }
}

void Scenario::addtoSelection(GMlib::SceneObject* obj){
    obj->setSelected(true);
    _scene->updateSelection(obj);
}
void Scenario::removefromSelection(GMlib::SceneObject* obj){
    obj->setSelected(false);
    _scene->updateSelection(obj);
}

/**
 * Cycles between the objects, however the camera is also part of this cycling.
 * Would be better if the camera was not part of the _scene Array
 *
 */
void Scenario::cycleSelection(bool forward){
    if(_scene->getSize()){
        GMlib::Array<GMlib::SceneObject*> s_objs = _scene->getSelectedObjects();
        if(s_objs.size() > 1 || s_objs.empty()){
            _scene->clearSelection();
            addtoSelection((*_scene)[0]);
        }
        else{
            int i;
            auto obj = s_objs[0];
            for(i=0;i<_scene->getSize();++i){
                if((*_scene)[i]->getName() == obj->getName())
                    break;
            }
            _scene->clearSelection();
            if(forward){
                if(i+1 == _scene->getSize())
                    i=-1;
                (*_scene)[i+1]->setSelected(true);
                _scene->updateSelection((*_scene)[i+1]);
            }
            else{
                if(i-1 < 0)
                    i=_scene->getSize();
                (*_scene)[i-1]->setSelected(true);
                _scene->updateSelection((*_scene)[i-1]);
            }
        }
    }
}

/**
 * Return array of selected objects
 */

GMlib::Array<GMlib::SceneObject*> Scenario::selectedObjects(){

    GMlib::Array<GMlib::SceneObject*> sel_obj = _scene->getSelectedObjects();
    return(sel_obj);
}


/**
 * Camera Control
 * mouse event
 */

void Scenario::moveCamera(QPoint current, QPoint previous){

    auto gm_current = fromQtToGMlibViewPoint(current);
    auto gm_previous = fromQtToGMlibViewPoint(previous);
    float s = 0.025;
    GMlib::Vector<float,3> d = s * float(gm_current(0) -gm_previous(0))*_camera->getSide()  -  s * float(gm_current(1)-gm_previous(1))*_camera->getUp();
    _camera->move(d);
}

/**
 * Camera Control
 * rotation
 */

void Scenario::rotateCamera(QPoint current, QPoint previous){

    auto w = _camera->getViewportW();
    auto h = _camera->getViewportH();

    auto gm_current = fromQtToGMlibViewPoint(current);
    auto gm_previous = fromQtToGMlibViewPoint(previous);
    float dx = gm_current(0) -gm_previous(0);
    float dy = gm_current(1)-gm_previous(1);
    float len = sqrt(pow(dx,2) + pow(dy,2));
    auto v_rot = (dx)*_camera->getUp() - (dy)*_camera->getSide();
    auto a = 2* M_PI*sqrt(pow(dx/w,2) + pow(dy/h,2));
    if (len > 1e-6){

        _camera->rotateGlobal(a,GMlib::Point<float,3> (0,0,0),v_rot);
        _camera->updateCameraOrientation();
    }
}


/**
 * Camera Control
 * Wheel event (Zoom in /Zoom out)
 */

void Scenario::moveCameraWheel(QPoint delta){

    auto h = float(delta.y())/8;
    GMlib::Vector<float,3> v = _camera->getDir();
    GMlib::Vector<float,3> d(v[0]*h,v[1]*h,v[2]*h);
    _camera->move(d);
}

/**
 * Object Manipulation
 * Rotate Selected Object(s)
 */

void Scenario::rotateSelectedObjects(QPoint current, QPoint previous ){
    auto objs = _scene->getSelectedObjects();
    auto w = _camera->getViewportW();
    auto h = _camera->getViewportH();

    auto gm_current = fromQtToGMlibViewPoint(current);
    auto gm_previous = fromQtToGMlibViewPoint(previous);

    auto v_rot = (gm_current(0) -gm_previous(0))*_camera->getUp() - (gm_current(1)-gm_previous(1))*_camera->getSide();
    auto a = 2* M_PI * sqrt(pow((float(gm_current(0) -gm_previous(0))/w),2) + pow((float(gm_current(1)-gm_previous(1))/h),2));
    auto condition = sqrt(pow((float(gm_current(0) -gm_previous(0))),2) + pow((float(gm_current(1)-gm_previous(1))),2));

    if (condition > 1e-6){

        if (objs.getSize()==1){
            //qDebug()<<"one object";
            objs[0]->rotateGlobal(a,v_rot);
        }

        else if (objs.getSize()>1){

            GMlib::SceneObject* obj = objs[0];
            auto sphere = obj->getSurroundingSphere();

            for(int i =1;i<objs.getSize();++i){
                GMlib::SceneObject* obj = objs[i];
                sphere.operator +=(obj->getSurroundingSphere());
            }
            for(int i =0;i<objs.getSize();++i){
                GMlib::SceneObject* obj = objs[i];
                if (obj->getParent()==nullptr)
                    _scene->find(obj->getName())->rotateGlobal(a,sphere.getPos(),v_rot);
            }
            //qDebug()<<"many objects";
        }
        else
            //qDebug()<<"no object";
            return;
    }

}

/**
 * Object Manipulation
 * Translate Selected Object(s)
 */

void Scenario::translateSelectedObjects(QPoint current, QPoint previous){
    auto objs = _scene->getSelectedObjects();
    auto gm_current = fromQtToGMlibViewPoint(current);
    auto gm_previous = fromQtToGMlibViewPoint(previous);
    float s = 0.025;
    GMlib::Vector<float,3> v_tran = s* float(gm_current(1)-gm_previous(1))*_camera->getUp() - s * float(gm_current(0) -gm_previous(0))*_camera->getSide();

    for(int i =0;i<objs.getSize();++i){
        //Makes sure that we do not translate the children relative to the parent while translate the parent
        if (_scene->find(objs[i]->getName())->getParent()==nullptr)
            //_scene->find(obj->getName())->translateGlobal(0.025*v_tran,true);
            _scene->find(objs[i]->getName())->move(v_tran);
    }
}

/**
 * Object Manipulation
 * Scale Selected Object(s)
 */

void Scenario::scaleSelectedObjects(QPoint current, QPoint previous){
    auto objs = _scene->getSelectedObjects();
    auto gm_current = fromQtToGMlibViewPoint(current);
    auto gm_previous = fromQtToGMlibViewPoint(previous);

    for(int i =0;i<objs.getSize();++i){
        if (_scene->find(objs[i]->getName())->getParent()==nullptr){
            auto dh = _camera->deltaTranslate(objs[i]);
            auto d = dh*(gm_current(0) -gm_previous(0))*_camera->getSide()  -  dh*(gm_current(1)-gm_previous(1))*_camera->getUp();
            if(d.getLength()<1000){
                _scene->find(objs[i]->getName())->scale(1.0f+ d(1));
            }
        }
    }
}

/**
 * Clear Scene
 *
 */

void Scenario::clearScene(){

    _scene->clear();
    _scene_vector.clear();
}

/**
 * Add objects
 * This way of doing it is not very good, it is prone to memory leaks[fixed for now]
 */

void Scenario::addSphere(){

    auto obj = std::make_unique<GMlib::PSphere<float>>(1);
    obj->toggleDefaultVisualizer();
    obj->replot(50,50,10,10);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}

void Scenario::addPTorus(){

    auto obj = std::make_unique<GMlib::PTorus<float>>();
    obj->toggleDefaultVisualizer();
    obj->replot(200,200,1,1);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}

void Scenario::addPCylinder(){

    auto obj = std::make_unique<GMlib::PCylinder<float>>(4);
    obj->toggleDefaultVisualizer();
    obj->replot(200,200,1,1);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}

void Scenario::addPCone(){

    auto obj = std::make_unique<GMlib::PCone<float>>(1);
    obj->toggleDefaultVisualizer();
    obj->replot(200,200,1,1);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}

void Scenario::addPBentHorns(){

    auto obj = std::make_unique<GMlib::PBentHorns<float>>();
    obj->toggleDefaultVisualizer();
    obj->replot(200,200,1,1);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}

void Scenario::addPApple(){

    auto obj = std::make_unique<GMlib::PApple<float>>(1);
    obj->toggleDefaultVisualizer();
    obj->replot(50,50,1,1);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}

void Scenario::addPlane(){
    auto obj = std::make_unique<GMlib::PPlane<float>>(GMlib::Point<float,3>(0,0,0),GMlib::Vector<float,3>(1,0,0),GMlib::Vector<float,3>(0,0,1));
    obj->toggleDefaultVisualizer();
    obj->replot(20,20,20,20);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}
void Scenario::addSeaShell(){
    auto obj = std::make_unique<GMlib::PSeashell<float>>();
    obj->toggleDefaultVisualizer();
    obj->replot(20,20,20,20);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}
void Scenario::addKleinsBottle(){
    auto obj = std::make_unique<GMlib::PKleinsBottle<float>>();
    obj->toggleDefaultVisualizer();
    obj->replot(20,20,20,20);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}
void Scenario::addBoysSurface(){
    auto obj = std::make_unique<GMlib::PBoysSurface<float>>();
    obj->toggleDefaultVisualizer();
    obj->replot(20,20,20,20);
    _scene->insert(obj.get());
    obj->setSelected(true);
    _scene->updateSelection(obj.get());
    _scene_vector.push_back(std::move(obj));
}
