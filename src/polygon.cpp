#include <polygon.h>
#include <rapidjson/document.h>
#include <sstream>

using namespace GeoJSON;
Polygon::Polygon()
{

}

const std::vector<std::vector<Coordinates> > &Polygon::getCoordinates() const
{
    return coordinates;
}

void Polygon::setCoordinates(const std::vector<std::vector<Coordinates> > &newCoordinates)
{
    coordinates = newCoordinates;
}

bool Polygon::addBoundary(std::vector<Coordinates> boundary)
{
    if(boundary[0] == boundary.back())
    {
        coordinates.push_back(boundary);
        return true;
    }
    return false;
}

const std::string Polygon::getTypeAsString() const
{
    return "Polygon";
}

const Type Polygon::getType() const
{
    return Type::Polygon;
}

const std::string Polygon::toJSON()
{

    std::stringstream ss;
    ss.precision(15);
    ss << "{\"type\": \"" << getTypeAsString() << "\", \"coordinates\": [";
    for(uint i = 0; i < coordinates.size(); i++)
    {
        ss << "[";
        for(uint j = 0; j < coordinates.at(i).size(); j++)
        {
            ss << "[" << coordinates[i][j].longitude << ", " << coordinates[i][j].latitude;
            if(coordinates[i][j].elevation > -std::numeric_limits<double>::max())
                ss << ", " << coordinates[i][j].elevation;
            ss << "]";
            if(j < coordinates.at(i).size() - 1)
                ss << ",";
        }
        ss << "]";
        if(i < coordinates.size() - 1)
            ss << ",";
    }
    ss << "]}";
    return ss.str();
}

int Polygon::parse(std::string jsonText)
{
    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();
        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("Polygon") != 0)
            return 1;
        if(rootObject.HasMember("coordinates") && rootObject["coordinates"].IsArray())
        {
            rapidjson::Value jsonCoordinates = rootObject["coordinates"].GetArray();
            for(auto& lineStringsPositionsArray : jsonCoordinates.GetArray())
                if(lineStringsPositionsArray.IsArray())
                {
                    std::vector<Coordinates> positionsArray;
                    for(auto& lineStringPositionsArray : lineStringsPositionsArray.GetArray())
                    {

                        if(lineStringPositionsArray.IsArray() && lineStringPositionsArray.Size() >= 2)
                        {
                            Coordinates positions;
                            if(lineStringPositionsArray[0].IsDouble())
                                positions.longitude = lineStringPositionsArray[0].GetDouble();
                            else
                                return 5;

                            if(lineStringPositionsArray[1].IsDouble())
                                positions.latitude = lineStringPositionsArray[1].GetDouble();
                            else
                                return 5;

                            if(lineStringPositionsArray.Size() > 2)
                            {
                                if(lineStringPositionsArray[2].IsDouble())
                                    positions.elevation = lineStringPositionsArray[2].GetDouble();
                                else
                                    return 5;
                            } else
                                positions.elevation = -std::numeric_limits<double>::max();
                            positionsArray.push_back(positions);
                        } else
                            return 4;
                    }
                    coordinates.push_back(positionsArray);
                } else
                    return 3;
        } else
            return 2;
    }
    return 0;
}


