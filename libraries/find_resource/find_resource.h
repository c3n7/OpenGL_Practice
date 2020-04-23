#ifndef FIND_RESOURCE_H
#define FIND_RESOURCE_H

#include <string>

#define RESOURCES_PATH "@RESOURCES_PATH@"
#define PROJECT_DIRECTORY "@PROJECT_DIRECTORY@"

class Resources {
  public:
    std::string getResourcePath(std::string resource);
    std::string getShaderPath(std::string shader);
};
#endif
