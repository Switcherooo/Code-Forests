#include "application/application.hpp"


int driver(int argc, const char *argv[]) {
    try {
        if(argc<=1) return 0;
    	application::Application app{argv};
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e) {
        std::cerr << "Invalid execution, got error: " << e.what() << "\n";
        std::cerr << "Proper usage: " << argv[0] << " example.json" << "\n";

        return 1;
    }

    return 0;
}
