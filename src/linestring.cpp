#include <linestring.h>
#include <document.h>
#include <sstream>
using namespace GeoJSON;
LineString::LineString()
{

}

const std::vector<Coordinates > &LineString::getCoordinates() const
{
    return coordinates;
}

void LineString::setCoordinates(const std::vector<Coordinates> &newCoordinates)
{
    if(newCoordinates.size() >= 2)
    {
        coordinates = newCoordinates;
    }
}

bool LineString::addCoordinates(Coordinates &newCoordinates)
{
    coordinates.push_back(newCoordinates);
    return true;
}

const std::string LineString::getTypeAsString() const
{
    return "LineString";
}

const Type LineString::getType() const
{
    return Type::LineString;
}

const std::string LineString::toJSON()
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

int LineString::parse(std::string jsonText)
{

    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();
        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("LineString") != 0)
            return 1;
        if(rootObject.HasMember("coordinates") && rootObject["coordinates"].IsArray())
        {
            rapidjson::Value jsonCoordinates = rootObject["coordinates"].GetArray();
            for(auto& positionsArray : jsonCoordinates.GetArray())
                if(positionsArray.IsArray() && positionsArray.Size() >= 2)
                {
                    Coordinates position;
                    if(positionsArray[0].IsDouble())
                        position.longitude = positionsArray[0].GetDouble();
                    else
                        return 4;

                    if(positionsArray[1].IsDouble())
                        position.latitude = positionsArray[1].GetDouble();
                    else
                        return 4;

                    if(positionsArray.Size() > 2)
                    {
                        if(positionsArray[2].IsDouble())
                            position.elevation = positionsArray[2].GetDouble();
                        else
                            return 4;
                    } else
                        position.elevation = -std::numeric_limits<double>::max();
                    coordinates.push_back(position);
                } else
                    return 3;
        } else
            return 2;
    }
    return 0;
}
