#ifndef FEATURECOLLECTION_H
#define FEATURECOLLECTION_H

#include <object.h>
#include <feature.h>

#include <vector>
namespace GeoJSON {

    class FeatureCollection : public Object
    {
    public:
        FeatureCollection();
        const std::vector<Feature *> &getFeatures() const;
        void setFeatures(const std::vector<Feature *> &newFeatures);
        bool addFeature(Feature* &newFeature);
        virtual const std::string getTypeAsString() const override;
        virtual const Type getType() const override;
        virtual const std::string toJSON() override;
        virtual int parse(std::string) override;
    protected:
        std::vector<Feature*> features;
    };

}

#endif // FEATURECOLLECTION_H
