import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

from launch_ros.actions import Node

n = 15 # number of turtles

def generate_launch_description():
    demo_nodes = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('learning_tf2_py'), 'launch'),
            '/turtle_tf2_demo_launch.py']),
        )
    demo_nodes_list = [demo_nodes]
    for i in range(1,n+1):
        fixed_broadcaster_node = Node(
            package='learning_tf2_py',
            executable='fixed_frame_tf2_broadcaster',
            parameters=[
                {'turtlename': f'turtle{i}', 'childname': f'carrot{i}'}
            ],
            name=f'fixed_broadcaster{i}'
        )
        demo_nodes_list.append(fixed_broadcaster_node)
    return LaunchDescription(
        demo_nodes_list                   
    )