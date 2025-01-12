#ifndef ANIMAL_BASE_PET_HPP
#define ANIMAL_BASE_PET_HPP

#include <string>

namespace animal_base
{
  class Pet
  {
    public:
      virtual void initialize(double weight, double age, std::string color, std::string name) = 0;
      virtual void neuter() = 0;
      virtual void talk() = 0;
      virtual double meal_size() = 0;
      virtual ~Pet(){}

    protected:
      Pet(){}     
  };
}  // namespace animal_base

#endif  // ANIMAL_BASE_PET_HPP
