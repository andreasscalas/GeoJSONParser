#ifndef POINT_H
#define POINT_H

#include <geometry.h>

namespace GeoJSON {
    class Point : public Geometry
    {
    public:
        Point();
        const Coordinates &getCoordinates() const;
        void setCoordinates(const Coordinates &newCoordinates);
        virtual const std::string getTypeAsString() const override;
        virtual const Type getType() const override;
        virtual const std::string toJSON() override;
        virtual int parse(std::string) override;
    protected:
        Coordinates coordinates;
    };
}

#endif // POINT_H
