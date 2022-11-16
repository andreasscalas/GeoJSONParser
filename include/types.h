#ifndef TYPES_H
#define TYPES_H

namespace GeoJSON
{

    enum class Type{
        FeatureCollection,
        Feature,
        Point,
        MultiPoint,
        LineString,
        MultiLineString,
        Polygon,
        MultiPolygon,
        GeometryCollection
    };
}

#endif // TYPES_H
