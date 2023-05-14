#include "Animal.h"


class Wolf : public Animal
{
    public:
        Wolf(Position position, World* world);
        Wolf(Wolf* wolf, Position position);
        Wolf(){};

        void clone(Organism* parent) override;

        template <class Archive> void serialize(Archive& ar, const unsigned int version)
        {
            ar& boost::serialization::base_object<Animal>(*this);
        }
};