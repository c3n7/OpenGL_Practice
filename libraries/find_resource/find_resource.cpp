#include "find_resource.h"

std::string Resources::getResourcePath(std::string resource) {
    return RESOURCES_PATH + resource;
}

std::string Resources::getShaderPath(std::string shader) {
    return PROJECT_DIRECTORY + shader;
}
