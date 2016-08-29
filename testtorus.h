#ifndef TESTTORUS_H
#define TESTTORUS_H


#include <parametrics/gmptorus>


class TestTorus : public GMlib::PTorus<float> {
public:
  using PTorus::PTorus;

  ~TestTorus() override {

    if(m_test01)
      remove(test_01_torus.get());
  }

  void test01() {

    GMlib::Vector<float,3> d = evaluate(0.0f,0.0f,0,0)[0][0];
    test_01_torus = std::make_shared<TestTorus,float,float,float>(1.5f,0.5f,0.5f);

    test_01_torus->translate(d + d.getNormalized()*2.0f);
    test_01_torus->rotate( GMlib::Angle(90), GMlib::Vector<float,3>( 0.0f, 1.0f, 0.0f) );
    test_01_torus->toggleDefaultVisualizer();
    test_01_torus->replot(200,200,1,1);
    insert(test_01_torus.get());

    m_test01 = true;
  }


protected:
  void localSimulate(double dt) override {

    rotate( GMlib::Angle(90) * dt, GMlib::Vector<float,3>( 0.0f, 0.0f, 1.0f ) );
    rotate( GMlib::Angle(180) * dt, GMlib::Vector<float,3>( 1.0f, 1.0f, 0.0f ) );
  }

private:
  bool m_test01 {false};
  std::shared_ptr<TestTorus> test_01_torus {nullptr};

}; // END class TestTorus



#endif // TESTTORUS_H
