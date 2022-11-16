#include <multilinestring.h>
#include <document.h>
#include <sstream>

using namespace GeoJSON;
MultiLineString::MultiLineString()
{

}

const std::vector<std::vector<Coordinates> > &MultiLineString::getCoordinates() const
{
    return coordinates;
}

void MultiLineString::setCoordinates(const std::vector<std::vector<Coordinates> > &newCoordinates)
{
    coordinates = newCoordinates;
}

bool MultiLineString::addCoordinatesVector(std::vector<Coordinates> &newCoordinatesVector)
{
    if(newCoordinatesVector.size() >= 2)
    {
        this->coordinates.push_back(newCoordinatesVector);
        return true;
    }
    return false;
}

const std::string MultiLineString::getTypeAsString() const
{
    return "MultiLineString";

}

const Type MultiLineString::getType() const
{
    return Type::MultiLineString;

}

const std::string MultiLineString::toJSON()
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

int MultiLineString::parse(std::string jsonText)
{
    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();
        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("MultiLineString") != 0)
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
                            Coordinates position;
                            if(lineStringPositionsArray[0].IsDouble())
                                position.longitude = lineStringPositionsArray[0].GetDouble();
                            else
                                return 5;

                            if(lineStringPositionsArray[1].IsDouble())
                                position.latitude = lineStringPositionsArray[1].GetDouble();
                            else
                                return 5;

                            if(lineStringPositionsArray.Size() > 2)
                            {
                                if(lineStringPositionsArray[2].IsDouble())
                                    position.elevation = lineStringPositionsArray[2].GetDouble();
                                else
                                    return 5;
                            } else
                                position.elevation = -std::numeric_limits<double>::max();
                            positionsArray.push_back(position);
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
