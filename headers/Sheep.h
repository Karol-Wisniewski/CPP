#include "Animal.h"

class Sheep : public Animal
{
    public:
        Sheep(Position position, World* world);
        Sheep(Sheep* sheep, Position position);
        Sheep(){};

        void clone(Organism* parent) override;

        template <class Archive> void serialize(Archive& ar, const unsigned int version)
        {
            ar& boost::serialization::base_object<Animal>(*this);
        }
};