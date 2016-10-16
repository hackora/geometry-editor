#include "guiapplication.h"

// gmlib
#include <core/gmglobal>

// stl
#include <stdexcept>

int main(int argc, char *argv[]) try {

    // Print C++ version
    std::cout << "C++ version: " << __cplusplus << std::endl;

    // Checking Qt Development Framework Version
    if( QT_VERSION < QT_VERSION_CHECK( 5, 0, 0 ) ) {

        std::cerr
                << "Qt version " << QT_VERSION_STR << " not supported."
                << " At least version 5.0.0 of the Qt Development Framework is needed."
                << " Please provided the necessary Qt Development Framework libraries."
                << std::endl;
        return 1;
    }
    else
        std::cout << "Qt Development Framework version: " <<  QT_VERSION_STR << std::endl;


    // Checking GMlib Version
    if( GM_VERSION < GM_VERSION_CHECK( 0, 5, 0 ) ) {

        std::cerr
                << "GMlib version " << GM_VERSION_STR << " not supported."
                << " At least GMlib version 0.5.0 needed. Please Rebuild GMlib"
                << std::endl;
        return 1;
    }
    else
        std::cout << "GMlib version: " << GM_VERSION_STR << std::endl;

    // Create the application object
    GuiApplication a(argc, argv);

    // Start the app, and return control to the Qt system.
    return a.exec();
}
catch(const std::invalid_argument& e) {
    std::cerr << "std::invlid_argument " << e.what() << std::endl;
    exit(1);
}
catch(const std::exception& e) {
    std::cerr << "std::exception : " << e.what() << std::endl;
    exit(1);
}
catch(...) {
std::cerr << "exception!!" << std::endl;
exit(1);
}
