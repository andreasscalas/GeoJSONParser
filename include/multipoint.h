#ifndef MULTIPOINT_H
#define MULTIPOINT_H

#include <geometry.h>

namespace GeoJSON {

    class MultiPoint : public Geometry
    {
    public:
        MultiPoint();

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

#endif // MULTIPOINT_H
