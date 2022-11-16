#ifndef LINESTRING_H
#define LINESTRING_H

#include <geometry.h>

namespace GeoJSON
{
    class LineString : public Geometry
    {
    public:
        LineString();
        virtual const std::vector<Coordinates > &getCoordinates() const ;
        virtual void setCoordinates(const std::vector<Coordinates > &newCoordinates) ;
        virtual bool addCoordinates(Coordinates &newCoordinates) ;
        virtual const std::string getTypeAsString() const override;
        virtual const Type getType() const override;
        virtual const std::string toJSON() override;
        virtual int parse(std::string) override;
    protected:
        std::vector<Coordinates> coordinates;
    };
}

#endif // LINESTRING_H
