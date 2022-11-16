#include <utils.h>
#include <featurecollection.h>
#include <feature.h>
#include <point.h>
#include <multipoint.h>
#include <linestring.h>
#include <multilinestring.h>
#include <polygon.h>
#include <multipolygon.h>
#include <geometrycollection.h>

#include <document.h>
#include <fstream>
#include <istreamwrapper.h>
#include <stringbuffer.h>
#include <writer.h>

GeoJSON::Object * GeoJSON::parse(std::string jsonFile)
{

    std::ifstream ifs(jsonFile);
    Object* root = nullptr;
    if(ifs.is_open())
    {
        rapidjson::IStreamWrapper isw(ifs);
        rapidjson::Document document;
        document.ParseStream(isw);
        if(document.IsObject())
        {
            rapidjson::Value rootObject = document.GetObject();
            if(rootObject.HasMember("type") && rootObject["type"].IsString())
            {
                std::string type = rootObject["type"].GetString();
                if(type.compare("FeatureCollection") == 0)
                {
                    root = new FeatureCollection();
                } else if(type.compare("Feature") == 0)
                {
                    root = new Feature();
                } else if(type.compare("Point") == 0)
                {
                    root = new Point();
                } else if(type.compare("MultiPoint") == 0)
                {
                    root = new MultiPoint();
                } else if(type.compare("LineString") == 0)
                {
                    root = new LineString();
                } else if(type.compare("MultiLineString") == 0)
                {
                    root = new MultiLineString();
                } else if(type.compare("Polygon") == 0)
                {
                    root = new Polygon();
                } else if(type.compare("MultiPolygon") == 0)
                {
                    root = new MultiPolygon();
                } else if(type.compare("GeometryCollection") == 0)
                {
                    root = new GeometryCollection();
                }
                rapidjson::StringBuffer sb;
                rapidjson::Writer<rapidjson::StringBuffer> writer( sb );
                rootObject.Accept( writer );
                root->parse(sb.GetString());

            }
        }
        ifs.close();
    }
    return root;

}
