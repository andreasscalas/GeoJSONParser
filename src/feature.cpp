#include <feature.h>
#include <geometrycollection.h>
#include <linestring.h>
#include <multilinestring.h>
#include <multipoint.h>
#include <multipolygon.h>
#include <point.h>
#include <polygon.h>
#include <sstream>
#include <iostream>
#include <document.h>
#include <stringbuffer.h>
#include <writer.h>

using namespace GeoJSON;
Feature::Feature()
{
    id = "";
    geometry = nullptr;
}

const std::string Feature::getTypeAsString() const
{
    return "Feature";
}

const Type Feature::getType() const
{
    return Type::Feature;
}

const std::string Feature::toJSON()
{
    std::stringstream ss;
    ss << "{";
    if(id.compare("") != 0)
        ss << "\"id\": " << id << ", ";
    ss << "\"type\":\"" << getTypeAsString() << "\", \"properties\": ";
    if(properties.compare("") == 0)
        ss << "null";
    else
        ss << properties;
    ss << ", \"geometry\": ";
    if(geometry != nullptr)
        ss << geometry->toJSON();
    else
        ss << "null";
    ss << "}";
    return ss.str();
}

const std::string &Feature::getProperties() const
{
    return properties;
}

void Feature::setProperties(const std::string &newProperties)
{
    properties = newProperties;
}

int Feature::parse(std::string jsonText)
{
    rapidjson::Document document;
    document.Parse(jsonText.c_str());
    if(document.IsObject())
    {
        rapidjson::Value rootObject = document.GetObject();

        std::string type = rootObject["type"].GetString();
        if(!rootObject.HasMember("type") || !rootObject["type"].IsString() || type.compare("Feature") != 0)
            return 1;
        if(rootObject.HasMember("geometry") && (rootObject["geometry"].IsObject() || rootObject["geometry"].IsNull() ))
        {
            rapidjson::Value jsonGeometry = rootObject["geometry"].GetObject();
            if(jsonGeometry.HasMember("type") && jsonGeometry["type"].IsString())
            {
                std::string jsonType = jsonGeometry["type"].GetString();
                if(jsonType.compare("Point") == 0)
                {
                    geometry = new Point();
                } else if(jsonType.compare("MultiPoint") == 0)
                {
                    geometry = new MultiPoint();
                } else if(jsonType.compare("LineString") == 0)
                {
                    geometry = new LineString();
                } else if(jsonType.compare("MultiLineString") == 0)
                {
                    geometry = new MultiLineString();
                } else if(jsonType.compare("Polygon") == 0)
                {
                    geometry = new Polygon();
                } else if(jsonType.compare("MultiPolygon") == 0)
                {
                    geometry = new MultiPolygon();
                } else if(jsonType.compare("GeometryCollection") == 0)
                {
                    geometry = new GeometryCollection();
                } else
                    return 4;
                rapidjson::StringBuffer sb;
                rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
                jsonGeometry.Accept( writer );
                int retVal = geometry->parse(sb.GetString());
                if(retVal != 0)
                {
                    delete geometry;
                    return 5;
                }
            } else
                return 3;
        } else
            return 2;

        if(rootObject.HasMember("properties") && (rootObject["properties"].IsObject() || rootObject["properties"].IsNull() ))
        {
            rapidjson::Value jsonProperties = rootObject["properties"].GetObject();
            rapidjson::StringBuffer sb;
            rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
            jsonProperties.Accept( writer );
            properties = sb.GetString();
        } else
            return 5;
    }
    return 0;
}

