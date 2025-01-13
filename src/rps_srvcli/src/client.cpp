#include <chrono>
#include <cinttypes>
#include <memory>

#include "rps_interfaces/srv/rock_paper_scissor.hpp"
#include "rclcpp/rclcpp.hpp"

using RockPaperScissor = rps_interfaces::srv::RockPaperScissor;
using namespace std;

string num_to_hand(int i) {
    i %= 3;
    if (i == 1) {
        return "Rock";
    } else if (i == 2) {
        return "Paper";
    } else {return "Scissor";}
}

void print_winner(int p, int c, int w) {

    if (c == -1) {
        cout << "Computer lost your data. You win the game!" << endl;
        return;  
    }

    cout <<  "You played: " << num_to_hand(request->person_left_hand) << endl;    
    cout <<  "Computer played: " << num_to_hand(myresult_minus_one->computer_left_hand) << endl;
    if (w == 1) {
        cout << "You won" << endl;
    } else if (w == 0) { 
        cout << "Tie" << endl;
    } else { 
        cout << "You lost" << endl;
    }   
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("rps_client");
  auto client = node->create_client<RockPaperScissor>("rock_paper_scissor");
  auto request = make_shared<RockPaperScissor::Request>();

  cout << "What is your name?" << endl;   
  cin >> request->username;  

  int which_game = -1;
  cout << "Play Rock Paper Scissor against the computer. Do you play simple with one hand, or do you play minus-one with two hands? Give me a number." << endl << "(1) simple" << endl << "(2) minus-one" << endl; 
  cin >> which_game;
  request->simple_game = (which_game % 2 == 1); 
  
 // Play simple game forever
 while(request->simple_game) {
    cout << endl << "Choose 1.Rock 2.Paper 3.Scissor" << endl;   
    cin >> request->person_left_hand;  
    request->person_right_hand = -1;
   
    while (!client->wait_for_service(chrono::seconds(1))) {
        if (!rclcpp::ok()) {
        RCLCPP_ERROR(node->get_logger(), "client interrupted while waiting for service to appear.");
        return 1;
        }
        RCLCPP_INFO(node->get_logger(), "waiting for service to appear...");
    }

    auto result_future = client->async_send_request(request);
    if (rclcpp::spin_until_future_complete(node, result_future) !=
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_ERROR(node->get_logger(), "service call failed :(");
        client->remove_pending_request(result_future);
        return 1;
    }
    auto myresult = result_future.get(); 
    print_winner(request->person_left_hand, myresult->computer_left_hand, myresult->you_won);
}

 // Play minus-one forever
 while(!(request->simple_game)) {

    //PHASE1

  cout << endl << "Play Rock Paper Scissor with two hands. What will you play with your left hand? Give me a number. 1.Rock 2.Paper 3.Scissor" << endl; 
  cin >> request->person_left_hand;
  cout << "What will you play with your right hand? Give me a number. 1.Rock 2.Paper 3.Scissor" << endl;   
  cin >> request->person_right_hand;  
   

  while (!client->wait_for_service(chrono::seconds(1))) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(node->get_logger(), "client interrupted while waiting for service to appear.");
      return 1;
    }
    RCLCPP_INFO(node->get_logger(), "waiting for service to appear...");
  }

  auto result_double_hand = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result_double_hand) !=
    rclcpp::FutureReturnCode::SUCCESS) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service rock_paper_scissor_double"); 
      return 1;
    }

  auto myresult_double_hand = result_double_hand.get();
  cout << "You played: " << num_to_hand(request->person_left_hand) << " " << num_to_hand(request->person_right_hand);    
  cout << "Computer played: " << num_to_hand(myresult_double_hand->computer_left_hand) << " " << num_to_hand(myresult_double_hand->computer_right_hand);


  //PHASE2
  cout << "Now you can keep only one hand. Keep 1. left hand or 2. right hand?" << endl; 
  int which_hand;
  cin >> which_hand;
  request->person_left_hand = ((which_hand % 2 == 0)? request->person_right_hand : request->person_left_hand);
  request->person_right_hand = -1;
  
  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result_minus_one = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result_minus_one) !=
    rclcpp::FutureReturnCode::SUCCESS) {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service rock_paper_scissor_minus_one");    // CHANGE
  } 
  
    auto myresult_minus_one = result_minus_one.get();
    print_winner(request->person_left_hand, myresult_minus_one->computer_left_hand, myresult_minus_one->you_won);      
 }

  rclcpp::shutdown();
  return 0;
}