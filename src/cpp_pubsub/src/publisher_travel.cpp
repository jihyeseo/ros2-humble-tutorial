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
#include "std_msgs/msg/bool.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher") 
  {
    publisher_ = this->create_publisher<std_msgs::msg::Bool>("Travel", 10);
    timer_ = this->create_wall_timer(
      1s, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    // set the new temperature every repeat_count th times. Publish same measurements repeat_count times.
    
    auto message = std_msgs::msg::Bool();    
    message.data = check_discount();
    RCLCPP_INFO(this->get_logger(), "The train tickets is '%s' today", (message.data? "discounted" : "expensive"));
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_;
  
  bool check_discount() {
      srand(time(0));
      return (rand() % 3 == 0);    
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
