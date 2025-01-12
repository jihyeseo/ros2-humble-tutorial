#include <animal_base/pet.hpp>
#include <cmath>
#include <iostream>

namespace animal_plugins
{
  class Cat : public animal_base::Pet
  {
    public:
      static const std::string species;
      void initialize(double w, double a, std::string c, std::string n) override
      {
        std::cout << "A beautiful " << species << " named " << n << " is here." << std::endl;
        weight = w; age=a;color=c;name=n;
      }

      void neuter() override
      {
        if (neutered) { std::cout << name << " is already neutered."<< std::endl; return; }
        std::cout << name << " is now neutered."<< std::endl; 
        neutered = true;
        return;
      }
      void talk() override {std::cout << name << " says Miau." << std::endl; return; }
      double meal_size() override { return weight * .1; }

    protected:
      double weight;
      double age; 
      std::string color;
      std::string name;
      bool neutered=false; 
  };

  class Fish : public animal_base::Pet
  {
    public:
      static const std::string species; 
      void initialize(double w, double a, std::string c, std::string n) override
      {
        std::cout << "A beautiful " << species << " named " << n << " is initialized." << std::endl;
        weight = w; age=a;color=c;name=n;
      }

      void neuter() override
      {
        std::cout << name << "'s species " << species << " needs no neutering."<< std::endl; return;
      }
      void talk() override { return; }
      double meal_size() override { return weight * .2; }

    protected:
      double weight;
      double age; 
      std::string color;
      std::string name; 
  };
}

const std::string animal_plugins::Fish::species = "fish";
const std::string animal_plugins::Cat::species = "cat";

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(animal_plugins::Cat, animal_base::Pet)
PLUGINLIB_EXPORT_CLASS(animal_plugins::Fish, animal_base::Pet)
