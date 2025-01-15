// Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/subscription_options.hpp"

#include "turtlesim/msg/pose.hpp"

class MinimalSubscriberWithTopicStatistics : public rclcpp::Node
{
public:
  MinimalSubscriberWithTopicStatistics(std::string turtle)
  : Node("turtle_pose_subscriber")
  {
    // manually enable topic statistics via options
    auto options = rclcpp::SubscriptionOptions();
    options.topic_stats_options.state = rclcpp::TopicStatisticsState::Enable;

    // configure the collection window and publish period (default 1s)
    options.topic_stats_options.publish_period = std::chrono::seconds(10);

    // configure the topic name (default '/statistics')
    options.topic_stats_options.publish_topic = "turtle_pose_topic_statistics";

    auto callback = [this](const turtlesim::msg::Pose & msg) {
        this->topic_callback(msg);
      };

    subscription_ = this->create_subscription<turtlesim::msg::Pose>(
      turtle, 10, callback, options);
  }

private:
  void topic_callback(const turtlesim::msg::Pose & msg) const
  {
    RCLCPP_INFO(this->get_logger(), "I heard: '%f'", msg.y);
  }
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{ 
  std::string turtle = "turtlesim1/turtle1/pose";
   
  if (argc == 2) {
    turtle = argv[1];
  }

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriberWithTopicStatistics>(turtle));
  rclcpp::shutdown();
  return 0;
}

// https://docs.ros.org/en/jazzy/Tutorials/Intermediate/Launch/Creating-Launch-Files.html