#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <types.h>

namespace GeoJSON {

class Object
{
public:
    virtual ~Object() {};

    /**
     * @brief getTypeAsString interface for obtaining the GeoJSON object type as a string
     * @return the string representing the GeoJSON type
     */
    virtual const std::string getTypeAsString() const = 0;

    /**
     * @brief getType interface for obtaining the GeoJSON object type as enumerated value
     * @return the enumerated value representing the GeoJSON type
     */
    virtual const Type getType() const = 0;

    /**
     * @brief toJSON interface for encoding the GeoJSON object into a JSON string.
     * @return the JSON string following the GeoJSON structure.
     */
    virtual const std::string toJSON()  = 0;

    /**
     * @brief parse interface for parsing a string representing a GeoJSON object.
     * @return a value representing the error code (0 represents correct parsing, other values are object type dependent).
     */
    virtual int parse(std::string) = 0;
};

}
#endif // OBJECT_H
