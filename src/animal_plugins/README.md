This is a tweak from the tutorial https://docs.ros.org/en/humble/Tutorials/Beginner-Client-Libraries/Pluginlib.html

ros2 pkg create --build-type ament_cmake --license Apache-2.0 --dependencies pluginlib --node-name meal_size_node animal_base

ros2 pkg create --build-type ament_cmake --license Apache-2.0 --dependencies animal_base pluginlib --library-name animal_plugins animal_plugins

ros2 run animal_base meal_size_node

Output:

ubuntu@ubuntu:~/ros2_ws$ ros2 run animal_base meal_size_node
A beautiful cat named Semo is here.
A beautiful cat named Nemo is here.
A beautiful fish named Coi is initialized.
Semo cat food: 0.30
Nemo cat food: 0.50
Fish food: 0.01
Semo says Miau.
Semo is now neutered.
Nemo says Miau.
Nemo is now neutered.
Semo says Miau.
Semo is already neutered.
Nemo says Miau.
Nemo is already neutered.
Coi's species fish needs no neutering.
