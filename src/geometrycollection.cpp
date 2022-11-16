#include <geometrycollection.h>
#include <linestring.h>
#include <multilinestring.h>
#include <multipoint.h>
#include <multipolygon.h>
#include <point.h>
#include <polygon.h>
#include <document.h>
#include <sstream>
#include <stringbuffer.h>
#include <writer.h>

using namespace GeoJSON;
GeometryCollection::GeometryCollection()
{

}

bool GeometryCollection::addGeometry(Geometry* newGeometry)
{
    this->geometries.push_back(newGeometry);
    return true;
}

const std::string GeometryCollection::getTypeAsString() const
{
    return "GeometryCollection";
}

const Type GeometryCollection::getType() const
{
    return Type::GeometryCollection;
}

const std::string GeometryCollection::toJSON()
{

    std::stringstream ss;
    ss << "{\"type\": \"" << getTypeAsString() << "\", \"geometries\": [";
    for(uint i = 0; i < geometries.size(); i++)
    {
        ss << geometries.at(i)->toJSON();
        if(i < geometries.size() - 1)
            ss << ",";
    }
    ss << "]}";
    return ss.str();
}

int GeometryCollection::parse(std::string jsonText)
{
    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();
        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("GeometryCollection") != 0)
            return 1;
        if(rootObject.HasMember("geometries") && rootObject["geometries"].IsArray())
        {
            rapidjson::Value jsonGeometries = rootObject["geometries"].GetArray();
            for(auto& jsonGeometry : jsonGeometries.GetArray())
            {
                if(jsonGeometry.HasMember("type") && jsonGeometry["type"].IsString())
                {
                    std::string jsonType = jsonGeometry["type"].GetString();
                    if(jsonType.compare("Point") == 0)
                    {

                        geometries.push_back(new Point());
                    } else if(jsonType.compare("MultiPoint") == 0)
                    {
                        geometries.push_back(new MultiPoint());
                    } else if(jsonType.compare("LineString") == 0)
                    {
                        geometries.push_back(new LineString());
                    } else if(jsonType.compare("MultiLineString") == 0)
                    {
                        geometries.push_back(new MultiLineString());
                    } else if(jsonType.compare("Polygon") == 0)
                    {
                        geometries.push_back(new Polygon());
                    } else if(jsonType.compare("MultiPolygon") == 0)
                    {
                        geometries.push_back(new MultiPolygon());
                    } else if(jsonType.compare("GeometryCollection") == 0)
                    {
                        geometries.push_back(new GeometryCollection());
                    } else
                        return 4;
                    rapidjson::StringBuffer sb;
                    rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
                    jsonGeometry.Accept( writer );
                    geometries.back()->parse(sb.GetString());
                } else
                    return 3;
            }
        } else
            return 2;
    }
    return 0;
}

const std::vector<Geometry *> &GeometryCollection::getGeometries() const
{
    return geometries;
}

void GeometryCollection::setGeometries(const std::vector<Geometry *> &newGeometries)
{
    geometries = newGeometries;
}
