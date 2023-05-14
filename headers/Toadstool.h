#include "Plant.h"

class Toadstool : public Plant
{
    public:
        Toadstool(Position position, World* world);
        Toadstool(Toadstool* toadstool, Position position);
        Toadstool(){};

        void clone(Organism* parent) override;

        template <class Archive> void serialize(Archive& ar, const unsigned int version)
        {
            ar& boost::serialization::base_object<Plant>(*this);
        }
};