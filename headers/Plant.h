#pragma once
#include "Organism.h"
#include "World.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>

class Plant : public Organism
{
	public:
		Plant(int power, int initiative, int liveLength, int powerToReproduce, World* world, Position position);
        Plant(){};

		virtual void action() override;
		virtual void clone(Organism* parent) = 0; //TODO sprawdzić czy musi być overrdie

        template <class Archive> void serialize(Archive& ar, const unsigned int version)
        {
            ar& boost::serialization::base_object<Organism>(*this);
        }
};
