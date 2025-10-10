#pragma once
#include <string>

namespace Core {

// MODEL CONFIG
struct ModelConfig
{
    std::string modelPath;
    float scale {1.0f};
    float brightness {1.0f};
};

}