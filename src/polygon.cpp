#include <polygon.h>
#include <document.h>
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
            for(auto& cv : jsonCoordinates.GetArray())
                if(cv.IsArray())
                {
                    std::vector<Coordinates> positionsVector;
                    for(auto& v : cv.GetArray())
                    {

                        if(v.IsArray() && v.Size() >= 2)
                        {
                            Coordinates p;
                            if(v[0].IsDouble())
                                p.longitude = v[0].GetDouble();
                            else
                                return 5;

                            if(v[1].IsDouble())
                                p.latitude = v[1].GetDouble();
                            else
                                return 5;

                            if(v.Size() > 2)
                            {
                                if(v[2].IsDouble())
                                    p.elevation = v[2].GetDouble();
                                else
                                    return 5;
                            } else
                                p.elevation = -std::numeric_limits<double>::max();
                            positionsVector.push_back(p);
                        } else
                            return 4;
                    }
                    coordinates.push_back(positionsVector);
                } else
                    return 3;
        } else
            return 2;
    }
    return 0;
}


