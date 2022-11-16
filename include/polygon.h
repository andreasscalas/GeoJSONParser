#ifndef POLYGON_H
#define POLYGON_H

#include <geometry.h>
namespace GeoJSON {
    class Polygon : public Geometry
    {
    public:
        Polygon();
        const std::vector<std::vector<Coordinates> > &getCoordinates() const;
        void setCoordinates(const std::vector<std::vector<Coordinates> > &newCoordinates);
        bool addBoundary(std::vector<Coordinates> boundary);
        virtual const std::string getTypeAsString() const override;
        virtual const Type getType() const override;
        virtual const std::string toJSON() override;
        virtual int parse(std::string) override;

    protected:
        std::vector<std::vector<Coordinates> > coordinates;
    };
}

#endif // POLYGON_H
