#include <point.h>
#include <rapidjson/document.h>
#include <sstream>
using namespace GeoJSON;
Point::Point()
{
     coordinates.longitude = -std::numeric_limits<double>::max();
     coordinates.latitude = -std::numeric_limits<double>::max();
     coordinates.elevation = -std::numeric_limits<double>::max();
}

const Coordinates &Point::getCoordinates() const
{
    return coordinates;
}

void Point::setCoordinates(const Coordinates &newCoordinates)
{
    coordinates = newCoordinates;
}

const std::string Point::getTypeAsString() const
{
    return "Point";
}

const Type Point::getType() const
{
    return Type::Point;
}

const std::string Point::toJSON()
{
    std::stringstream ss;
    ss.precision(15);
    ss << "{\"type\": \"" << getTypeAsString() << "\", \"coordinates\": [" << coordinates.longitude << ", " << coordinates.latitude;
    if(coordinates.elevation > -std::numeric_limits<double>::max())
        ss << ", " << coordinates.elevation;
    ss << "]}";
    return ss.str();
}

int Point::parse(std::string jsonText)
{
    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();
        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("Point") != 0)
            return 1;
        if(rootObject.HasMember("coordinates") && rootObject["coordinates"].IsArray())
        {
            rapidjson::Value jsonCoordinates = rootObject["coordinates"].GetArray();
            if(jsonCoordinates.Size() >= 2)
            {
                if(jsonCoordinates[0].IsDouble())
                    coordinates.longitude = jsonCoordinates[0].GetDouble();
                else
                    return 4;

                if(jsonCoordinates[1].IsDouble())
                    coordinates.latitude = jsonCoordinates[1].GetDouble();
                else
                    return 4;

                if(jsonCoordinates.Size() > 2)
                {
                    if(jsonCoordinates[2].IsDouble())
                        coordinates.elevation = jsonCoordinates[2].GetDouble();
                    else
                        return 4;
                }
            } else
                return 3;
        } else
            return 2;
    }

    return 0;
}
