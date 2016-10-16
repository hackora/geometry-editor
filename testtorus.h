#ifndef TESTTORUS_H
#define TESTTORUS_H


#include <parametrics/gmptorus>

#include <memory.h>

class TestTorus : public GMlib::PTorus<float> {
public:
    using PTorus::PTorus;
    ~TestTorus() override;

    void test01();

protected:
    void localSimulate(double dt) override;

private:
    std::unique_ptr<TestTorus>    _torus {nullptr};

}; // END class TestTorus



#endif // TESTTORUS_H
