#include <multipolygon.h>
#include <rapidjson/document.h>
#include <sstream>

using namespace GeoJSON;
MultiPolygon::MultiPolygon()
{

}

const std::vector<std::vector<std::vector<Coordinates> > > &MultiPolygon::getCoordinates() const
{
    return coordinates;
}

void MultiPolygon::setCoordinates(const std::vector<std::vector<std::vector<Coordinates> > > &newCoordinates)
{
    coordinates = newCoordinates;
}

bool MultiPolygon::addPolygon(std::vector<std::vector<Coordinates> > polygonCoordinates)
{
    for(std::vector<Coordinates> boundary : polygonCoordinates)
    {
        if(boundary[0] != boundary.back())
           return false;
    }
    coordinates.push_back(polygonCoordinates);
    return true;
}

const std::string MultiPolygon::getTypeAsString() const
{
    return "Multipolygon";
}

const Type MultiPolygon::getType() const
{
    return Type::MultiPolygon;
}

const std::string MultiPolygon::toJSON()
{

    std::stringstream ss;
    ss.precision(15);
    ss << "{\"type\": \"" << getTypeAsString() << "\", \"coordinates\": [";
    for(uint i = 0; i < coordinates.size(); i++)
    {
        ss << "[";
        for(uint j = 0; j < coordinates.at(i).size(); j++)
        {
            ss << "[";
            for(uint k = 0; k < coordinates.at(i).at(j).size(); k++)
            {
                ss << "[" << coordinates[i][j][k].longitude << ", " << coordinates[i][j][k].latitude;
                if(coordinates[i][j][k].elevation > -std::numeric_limits<double>::max())
                    ss << ", " << coordinates[i][j][k].elevation;
                ss << "]";
                if(k < coordinates.at(i).at(j).size() - 1)
                    ss << ",";
            }
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

int MultiPolygon::parse(std::string jsonText)
{
    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();
        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("MultiPolygon") != 0)
            return 1;
        if(rootObject.HasMember("coordinates") && rootObject["coordinates"].IsArray())
        {
            rapidjson::Value jsonCoordinates = rootObject["coordinates"].GetArray();
            for(auto& polygonPositionsArray : jsonCoordinates.GetArray())
                if(polygonPositionsArray.IsArray())
                {

                    std::vector<std::vector<Coordinates> > positionsArrayOfArrays;
                    for(auto& boundaryPositionsArray : polygonPositionsArray.GetArray())
                        if(boundaryPositionsArray.IsArray())
                        {
                            std::vector<Coordinates> positionsArray;
                            for(auto& v : boundaryPositionsArray.GetArray())
                            {

                                if(v.IsArray() && v.Size() >= 2)
                                {
                                    Coordinates p;
                                    if(v[0].IsDouble())
                                        p.longitude = v[0].GetDouble();
                                    else
                                        return 6;

                                    if(v[1].IsDouble())
                                        p.latitude = v[1].GetDouble();
                                    else
                                        return 6;

                                    if(v.Size() > 2)
                                    {
                                        if(v[2].IsDouble())
                                            p.elevation = v[2].GetDouble();
                                        else
                                            return 6;
                                    } else
                                        p.elevation = -std::numeric_limits<double>::max();
                                    positionsArray.push_back(p);
                                } else
                                    return 5;
                            }
                            positionsArrayOfArrays.push_back(positionsArray);
                        } else
                            return 4;

                    coordinates.push_back(positionsArrayOfArrays);
                } else
                    return 3;

        } else
            return 2;
    }
    return 0;
}
