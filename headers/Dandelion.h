#include "Plant.h"

class Dandelion : public Plant
{
    public:
        Dandelion(Position position, World* world);
        Dandelion(Dandelion* dandelion, Position position);
        Dandelion(){};

        void clone(Organism* parent) override;

        template <class Archive> void serialize(Archive& ar, const unsigned int version)
        {
            ar& boost::serialization::base_object<Plant>(*this);
        }
};