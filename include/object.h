#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <types.h>

namespace GeoJSON {

class Object
{
public:
    virtual ~Object() {};
    virtual const std::string getTypeAsString() const = 0;
    virtual const Type getType() const = 0;
    virtual const std::string toJSON()  = 0;
    virtual int parse(std::string) = 0;
};

}
#endif // OBJECT_H
