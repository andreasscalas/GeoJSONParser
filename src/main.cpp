#include <iostream>
#include "object.h"
#include "utils.h"
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{

    if(argc < 2)
        return 1;
    GeoJSON::Object* object = GeoJSON::parse(argv[1]);
    std::string jsonText = object->toJSON();
    std::ofstream ofs("caccola.json");
    ofs << jsonText;
    ofs.close();

    return 0;
}
