#include <cinttypes>
#include <memory>
#include <unordered_map>
#include "rps_interfaces/srv/rock_paper_scissor.hpp"
#include "rclcpp/rclcpp.hpp"

using RockPaperScissor = rps_interfaces::srv::RockPaperScissor;
using namespace std;

rclcpp::Node::SharedPtr g_node = nullptr;

int random_int(int i=0, int among = 3) {
    srand(time(0)+i);
    int r = rand();
    return r % among;    
}

int set_you_won(int c, int p) {
  int diff = c - p;
  if (diff % 3 == 0) {return 0;  }
  else if ((diff + 1) % 3 == 0) {return 1;  }
  else {return -1;  }
}

unordered_map<string, long int> game_data;

void handle_service(
  const shared_ptr<rmw_request_id_t> request_header,
  const shared_ptr<RockPaperScissor::Request> request,
  const shared_ptr<RockPaperScissor::Response> response)
{
  (void)request_header;
  RCLCPP_INFO(
    g_node->get_logger(),
    "request from:  %s %ld %ld %d", request->username.c_str(), request->person_left_hand, request->person_right_hand , request->simple_game);
    
    // Handle one-hand game
    if (request->simple_game) {
        response->computer_left_hand = random_int(0);
        response->computer_right_hand = -1;
        response->you_won = set_you_won(response->computer_left_hand, request->person_left_hand);
        return;
    }

    // Handle minus-one game
    if (request->person_right_hand != -1) {
        // PHASE 1 of minus one 
        response->computer_left_hand = random_int(0);
        // Set left and right hands to be always different. Otherwise, disadvantage (a dumb move)
        response->computer_right_hand = (response->computer_left_hand + random_int(0, 2) + 1) % 3;

        // Record the game data for the phase 2. Randomly choose left or right hand 
        // TODO smarter strategy (also consider the hands by the player to decide best strategy)
        game_data[request->username] = ((random_int(0, 2) == 1)? response->computer_left_hand : response->computer_right_hand);
        return;
    }

    // phase2 of minus-one
    if (game_data.count(request->username)) {
        response->computer_left_hand = game_data[request->username];
        response->you_won = set_you_won(response->computer_left_hand, request->person_left_hand); 
    }
    else {
        response->computer_left_hand = -1; // Set with invalid value
        RCLCPP_INFO(g_node->get_logger(), "Oh, I lost game data of %s ", request->username.c_str());           
    }
    return;

}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  g_node = rclcpp::Node::make_shared("rps_service");
  auto server = g_node->create_service<RockPaperScissor>("rock_paper_scissor", &handle_service);
  rclcpp::spin(g_node);
  rclcpp::shutdown();
  g_node = nullptr;
  return 0;
}