#ifndef GEOMETRYCOLLECTION_H
#define GEOMETRYCOLLECTION_H

#include <geometry.h>

namespace GeoJSON {

class GeometryCollection : public Geometry
{
public:
    GeometryCollection();
    const std::vector<Geometry *> &getGeometries() const;
    void setGeometries(const std::vector<Geometry *> &newGeometries);
    bool addGeometry(Geometry* newGeometry);
    virtual const std::string getTypeAsString() const override;
    virtual const Type getType() const override;
    virtual const std::string toJSON() override;
    virtual int parse(std::string) override;

protected:
    std::vector<Geometry*> geometries;
};

}

#endif // GEOMETRYCOLLECTION_H
