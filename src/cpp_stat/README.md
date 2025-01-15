Have tutles move automatically as in https://docs.ros.org/en/jazzy/Tutorials/Intermediate/Launch/Creating-Launch-Files.html

Using the tutorial https://docs.ros.org/en/jazzy/Tutorials/Advanced/Topic-Statistics-Tutorial/Topic-Statistics-Tutorial.html


usage example:

ubuntu@ubuntu:~/ros2_ws$ ros2 topic list
/parameter_events
/rosout
/turtle_pose_topic_statistics
/turtlesim1/turtle1/cmd_vel
/turtlesim1/turtle1/color_sensor
/turtlesim1/turtle1/pose
/turtlesim2/turtle1/cmd_vel
/turtlesim2/turtle1/color_sensor
/turtlesim2/turtle1/pose


ros2 run cpp_stat turtle_pose_stat turtlesim1/turtle1/pose
 

ubuntu@ubuntu:~/ros2_ws$ ros2 run cpp_stat turtle_pose_stat turtlesim1/turtle1/pose
[INFO] [1736969767.652359961] [turtle_pose_subscriber]: I heard: '3.876245'
[INFO] [1736969767.669993332] [turtle_pose_subscriber]: I heard: '3.848793'
[INFO] [1736969767.685985442] [turtle_pose_subscriber]: I heard: '3.821825'
[INFO] [1736969767.701249129] [turtle_pose_subscriber]: I heard: '3.795365'
[INFO] [1736969767.716593026] [turtle_pose_subscriber]: I heard: '3.769434'
[INFO] [1736969767.732912304] [turtle_pose_subscriber]: I heard: '3.744053'
[INFO] [1736969767.749902379] [turtle_pose_subscriber]: I heard: '3.719245'
[INFO] [1736969767.765505278] [turtle_pose_subscriber]: I heard: '3.695028'
[INFO] [1736969767.781760181] [turtle_pose_subscriber]: I heard: '3.671424'


ubuntu@ubuntu:~/ros2_ws$ ros2 topic list
/parameter_events
/rosout
/turtle_pose_topic_statistics
/turtlesim1/turtle1/cmd_vel
/turtlesim1/turtle1/color_sensor
/turtlesim1/turtle1/pose
/turtlesim2/turtle1/cmd_vel
/turtlesim2/turtle1/color_sensor
/turtlesim2/turtle1/pose
ubuntu@ubuntu:~/ros2_ws$ 

ubuntu@ubuntu:~/ros2_ws$ ros2 topic echo turtle_pose_topic_statistics
measurement_source_name: turtle_pose_subscriber
metrics_source: message_age
unit: ms
window_start:
  sec: 1736969825
  nanosec: 79187453
window_stop:
  sec: 1736969835
  nanosec: 79890511
statistics:
- data_type: 1
  data: 0.6932547213114754
- data_type: 3
  data: 75.625149
- data_type: 2
  data: 0.160751
- data_type: 5
  data: 610.0
- data_type: 4
  data: 4.356863259380049
---
measurement_source_name: turtle_pose_subscriber
metrics_source: message_period
unit: ms
window_start:
  sec: 1736969825
  nanosec: 79187453
window_stop:
  sec: 1736969835
  nanosec: 79890511
statistics:
- data_type: 1
  data: 15.87687097865354
- data_type: 3
  data: 18.955881
- data_type: 2
  data: 0.008375
- data_type: 5
  data: 609.0
- data_type: 4
  data: 1.738848006955486
---
