#ifndef UTILS_H
#define UTILS_H

#include <object.h>

namespace GeoJSON {

    /**
     * @brief GeoJSON::parse method that parse a GeoJSON file and creates a hierarchy of GeoJSON objects (one GeoJSON object that can contain other objects depending on the type).
     * @param jsonFile the path of the file to be parsed.
     * @return a pointer to the created GeoJSON object.
     */
    Object* parse(std::string jsonText);

}
#endif // UTILS_H
