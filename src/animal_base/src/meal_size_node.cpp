#include <pluginlib/class_loader.hpp>
#include <animal_base/pet.hpp>

int main(int argc, char** argv)
{
  // To avoid unused parameter warnings
  (void) argc;
  (void) argv;

  pluginlib::ClassLoader<animal_base::Pet> poly_loader("animal_base", "animal_base::Pet");

  try
  {
    std::shared_ptr<animal_base::Pet> semo_cat = poly_loader.createSharedInstance("animal_plugins::Cat");
    semo_cat->initialize(3, 12, "three colors", "Semo");
    std::shared_ptr<animal_base::Pet> nemo_cat = poly_loader.createSharedInstance("animal_plugins::Cat");
    nemo_cat->initialize(5, 16, "orange white", "Nemo");

    std::shared_ptr<animal_base::Pet> fish = poly_loader.createSharedInstance("animal_plugins::Fish");
    fish->initialize(0.03, 0.2, "gray", "Coi");

    printf("Semo cat food: %.2f\n", semo_cat->meal_size());
    printf("Nemo cat food: %.2f\n", nemo_cat->meal_size());    
    printf("Fish food: %.2f\n", fish->meal_size());   
    semo_cat->talk();
    semo_cat->neuter();
    nemo_cat->talk();
    nemo_cat->neuter();  
    semo_cat->talk();
    semo_cat->neuter();
    nemo_cat->talk();
    nemo_cat->neuter();      
    fish->talk();
    fish->neuter();        
  }
  catch(pluginlib::PluginlibException& ex)
  {
    printf("The plugin failed to load for some reason. Error: %s\n", ex.what());
  }

  return 0;
}
