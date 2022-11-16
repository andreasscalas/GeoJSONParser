#ifndef MULTILINESTRING_H
#define MULTILINESTRING_H

#include <geometry.h>

namespace GeoJSON {
    class MultiLineString : public Geometry
    {
    public:
        MultiLineString();
        const std::vector<std::vector<Coordinates> > &getCoordinates() const;
        void setCoordinates(const std::vector<std::vector<Coordinates> > &newCoordinates);
        bool addCoordinatesVector(std::vector<Coordinates> &newCoordinatesVector) ;
        virtual const std::string getTypeAsString() const override;
        virtual const Type getType() const override;
        virtual const std::string toJSON() override;
        virtual int parse(std::string) override;

    protected:
        std::vector<std::vector<Coordinates> > coordinates;
    };
}
#endif // MULTILINESTRING_H
