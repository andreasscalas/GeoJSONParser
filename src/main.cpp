#include <iostream>
#include "object.h"
#include "utils.h"
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
    //The test requires a file path as input. No further processing can be done.
    if(argc < 2)
        return 1;

    //The file is parsed into a GeoJSON hierarchy (if possible)
    GeoJSON::Object* object = GeoJSON::parse(argv[1]);

    //If the returned object is not a nullptr it means that the parse was successful
    if(object != nullptr)
    {
        //The GeoJSON object is encoded into a JSON string
        std::string jsonText = object->toJSON();

        //The string is written into the output file. If the output file path is given we use the provided one, otherwise we will write a file in the project build folder called "output.json"
        std::ofstream ofs;
        if(argc > 2)
            ofs.open(argv[2]);
        else
            ofs.open("output.json");
        ofs << jsonText;
        ofs.close();
    }

    return 0;
}
