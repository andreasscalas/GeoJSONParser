#include <featurecollection.h>
#include <document.h>
#include <sstream>
#include <stringbuffer.h>
#include <writer.h>


using namespace GeoJSON;

FeatureCollection::FeatureCollection()
{

}

const std::vector<Feature *> &FeatureCollection::getFeatures() const
{
    return features;
}

void FeatureCollection::setFeatures(const std::vector<Feature *> &newFeatures)
{
    features = newFeatures;
}

bool FeatureCollection::addFeature(Feature *&newFeature)
{
    this->features.push_back(newFeature);
    return true;
}

const std::string FeatureCollection::getTypeAsString() const
{
    return "FeatureCollection";
}

const Type FeatureCollection::getType() const
{
    return Type::FeatureCollection;
}

const std::string FeatureCollection::toJSON()
{
    std::stringstream ss;
    ss << "{\"type\": \"" << getTypeAsString() << "\", \"features\": [";
    for(uint i = 0; i < features.size(); i++)
    {
        ss << features.at(i)->toJSON();
        if(i < features.size() - 1)
            ss << ",";
    }
    ss << "]}";
    return ss.str();
}

int FeatureCollection::parse(std::string jsonText)
{
    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();

        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("FeatureCollection") != 0)
            return 1;
        if(rootObject.HasMember("features") && rootObject["features"].IsArray())
        {
            rapidjson::Value jsonFeatures = rootObject["features"].GetArray();
            for (rapidjson::Value::ConstValueIterator itr = jsonFeatures.Begin(); itr != jsonFeatures.End(); ++itr)
            {
                if(itr->HasMember("type") && (*itr )["type"].IsString())
                {
                    std::string featureType = (*itr )["type"].GetString();
                    if(featureType.compare("Feature") == 0)
                    {
                        features.push_back(new Feature());
                        rapidjson::StringBuffer sb;
                        rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
                        itr->Accept( writer );
                        features.back()->parse(sb.GetString());
                    } else
                        return 4;


                } else
                    return 3;
            }

        } else
            return 2;
    }
    return 0;
}
