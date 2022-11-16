#ifndef FEATURE_H
#define FEATURE_H

#include <object.h>
#include <geometry.h>
#include <vector>

namespace GeoJSON {
    class Feature : public GeoJSON::Object
    {
    public:
        Feature();
        virtual const std::string getTypeAsString() const override;
        virtual const Type getType() const override;
        virtual const std::string toJSON() override;
        const std::string &getProperties() const;
        void setProperties(const std::string &newProperties);
        virtual int parse(std::string) override;

    protected:
        Geometry* geometry;
        std::string id;
        std::string properties;
    };
}

#endif // FEATURE_H
