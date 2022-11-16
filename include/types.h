#ifndef TYPES_H
#define TYPES_H

namespace GeoJSON
{

    /**
     * @brief The Type enum lists the types of GeoJSON Objects
     */
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
