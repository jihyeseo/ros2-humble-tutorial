from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node

n = 15 # number of turtles
loop = False

node_list = [
        Node(
            package='turtlesim',
            executable='turtlesim_node',
            name='sim'
        )]

for i in range(1,n+1):
    broadcaster_node = Node(
            package='learning_tf2_py',
            executable='turtle_tf2_broadcaster',
            name=f'broadcaster{i}',
            parameters=[
                {'turtlename': f'turtle{i}'}
            ]
        )
    node_list.append(broadcaster_node)
    
for i in range(2,n+1):
    if (loop and i == 2):
        j = n
    else: j = i - 1
    listener_node = Node(
            package='learning_tf2_py',
            executable='turtle_tf2_listener',
            name=f'listener{i}',
            parameters=[
                {'turtlename': f'turtle{i}', 
                 'target_frame': f'carrot{j}', 'loc':f'{i}'}
            ]
        )
    node_list.append(listener_node)
    
def generate_launch_description():
    return LaunchDescription(node_list)