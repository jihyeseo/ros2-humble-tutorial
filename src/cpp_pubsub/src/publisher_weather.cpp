// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <cstdlib>

#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/msg/weather.hpp"  

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class WeatherPublisher : public rclcpp::Node
{
public:
  WeatherPublisher()
  : Node("weather_publisher") 
  {
    weather_publisher_ = this->create_publisher<tutorial_interfaces::msg::Weather>("Weather", 10);

    auto publish_msg = [this]() -> void {

      auto message = tutorial_interfaces::msg::Weather();
      message.rain = small_chance(1);
      message.windy = small_chance(3);
      message.sunny = !small_chance(4);
      message.temperature = measure_temperature(-5, 35);  
      // If it rains or temperature is high, it does not snow.
      message.snow = ((message.rain || (message.temperature > 2) )? false : small_chance(2));
      std::cout << "Publishing Weather: Temperature: " << message.temperature << " with ";
      if (message.rain) {std::cout << "rain, ";}
      if (message.snow) {std::cout << "snow, "; }
      if (message.windy) {std::cout << "wind, "; }
      std::cout << ((message.sunny)? "sunshine ": "cloud ");
      std::cout << std::endl;

      this->weather_publisher_->publish(message);
    };
 
    timer_ = this->create_wall_timer(1s, publish_msg);
  }

private: 
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<tutorial_interfaces::msg::Weather>::SharedPtr weather_publisher_;
  int measure_temperature(int min_temp, int max_temp) {
      srand(time(0));
      int r = rand(); 
      return (r % (max_temp - min_temp)) + min_temp;    
  }
  bool small_chance(int i) {
      srand(time(0) + i);
      int r = rand(); 
      // 20 percent chance
      bool my_bool = (r % 1000)  <= 200;
      return my_bool;
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<WeatherPublisher>());
  rclcpp::shutdown();
  return 0;
}
