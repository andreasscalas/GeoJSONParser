#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <object.h>
#include <vector>


namespace GeoJSON {

    class Coordinates {
        public:
            double longitude, latitude, elevation;
            bool operator==(Coordinates other)
            {
                return longitude == other.longitude && latitude == other.latitude && elevation == other.elevation;
            }

            bool operator!=(Coordinates other)
            {
                return *this == other;
            }
    };

    class Geometry : public Object {

    };
}
#endif // GEOMETRY_H
