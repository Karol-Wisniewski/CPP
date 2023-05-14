#include "Plant.h"

class Grass : public Plant
{
    public:
        Grass(Position position, World* world);
        Grass(Grass* grass, Position position);
        Grass(){};

        void clone(Organism* parent) override;

        template <class Archive> void serialize(Archive& ar, const unsigned int version)
        {
            ar& boost::serialization::base_object<Plant>(*this);
        }
};

