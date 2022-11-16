#include <multipoint.h>
#include <document.h>
#include <sstream>

using namespace GeoJSON;
MultiPoint::MultiPoint()
{

}


const std::vector<Coordinates > &MultiPoint::getCoordinates() const
{
    return coordinates;
}

void MultiPoint::setCoordinates(const std::vector<Coordinates> &newCoordinates)
{
    if(newCoordinates.size() >= 2)
    {
        coordinates = newCoordinates;
    }
}

bool MultiPoint::addCoordinates(Coordinates &newCoordinates)
{
    coordinates.push_back(newCoordinates);
    return true;
}

const std::string MultiPoint::getTypeAsString() const
{
    return "MultiPoint";
}

const Type MultiPoint::getType() const
{
    return Type::MultiPoint;
}

const std::string MultiPoint::toJSON()
{
    std::stringstream ss;
    ss.precision(15);
    ss << "{\"type\": \"" << getTypeAsString() << "\", \"coordinates\": [";
    for(uint i = 0; i < coordinates.size(); i++)
    {
        ss << "[" << coordinates[i].longitude << ", " << coordinates[i].latitude;
        if(coordinates[i].elevation > -std::numeric_limits<double>::max())
            ss << ", " << coordinates[i].elevation;
        ss << "]";
        if(i < coordinates.size() - 1)
            ss << ",";
    }
    ss << "]}";
    return ss.str();

}

int MultiPoint::parse(std::string jsonText)
{

    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();
        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("MultiPoint") != 0)
            return 1;
        if(rootObject.HasMember("coordinates") && rootObject["coordinates"].IsArray())
        {
            rapidjson::Value jsonCoordinates = rootObject["coordinates"].GetArray();
            for(auto& v : jsonCoordinates.GetArray())
                if(v.IsArray() && v.Size() >= 2)
                {
                    Coordinates p;
                    if(v[0].IsDouble())
                        p.longitude = v[0].GetDouble();
                    else
                        return 4;

                    if(v[1].IsDouble())
                        p.latitude = v[1].GetDouble();
                    else
                        return 4;

                    if(v.Size() > 2)
                    {
                        if(v[2].IsDouble())
                            p.elevation = v[2].GetDouble();
                        else
                            return 4;
                    } else
                        p.elevation = -std::numeric_limits<double>::max();
                    coordinates.push_back(p);
                } else
                    return 3;
        } else
            return 2;
    }
    return 0;
}

