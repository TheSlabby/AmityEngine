#include <iostream>
#include "Application.hpp"

int main()
{
    Core::Application app(/*width*/800, /*height*/600);
    app.init();
    
    return app.run();
}