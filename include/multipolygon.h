#ifndef MULTIPOLYGON_H
#define MULTIPOLYGON_H

#include <geometry.h>
namespace GeoJSON {
    class MultiPolygon : public Geometry
    {
    public:
        MultiPolygon();

        const std::vector<std::vector<std::vector<Coordinates> > > &getCoordinates() const;
        void setCoordinates(const std::vector<std::vector<std::vector<Coordinates> > > &newCoordinates);
        bool addPolygon(std::vector<std::vector<Coordinates> > polygonCoordinates);
        virtual const std::string getTypeAsString() const override;
        virtual const Type getType() const override;
        virtual const std::string toJSON() override;
        virtual int parse(std::string) override;


    protected:
        std::vector<std::vector<std::vector<Coordinates> > > coordinates;
    };
}

#endif // MULTIPOLYGON_H
