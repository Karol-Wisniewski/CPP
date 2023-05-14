#pragma once
#include "Organism.h"
#include "World.h"
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

using namespace std;

class Animal : public Organism
{
	public:
		Animal(int power, int initiative, int liveLength, int powerToReproduce, World* world, Position position);
        Animal(){};

		virtual void action() override;
		virtual void clone(Organism* parent) = 0;

        template <class Archive> void serialize(Archive& ar, const unsigned int version)
        {
            ar& boost::serialization::base_object<Organism>(*this);
        }
};