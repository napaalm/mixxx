#ifndef TRACKID_H
#define TRACKID_H


#include "util/dbid.h"


class TrackId: public DbId {
public:
    // Inherit constructors from base class
    using DbId::DbId;
};

Q_DECLARE_METATYPE(TrackId)


#endif // TRACKID_H
