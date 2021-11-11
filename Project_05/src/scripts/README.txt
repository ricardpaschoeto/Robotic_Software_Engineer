- gmmapping package (Mapping)

With this package we can create a map from the environment using slam and teleoperating
the robot around.

- turtlebot simulator (Probabilistic localization)

Inside this package we can find the amcl_demo.launch responsible to apply the monte carlo
algorithm localization

- turtlebot_rviz_launchers (Navigation)

Inside this package we can find the view_navigation launch file, responsible to launch
rviz to process the navigation.

- add_markers

Package responsible for managing the markers used as virtual objects. There is a class add_markers.cpp
that subscribe odometry to monitoring the movement from robot and verify if reached the pickup and
dropoff zones

- pick_objects

Package responsible to give the pickup and dropoff positions to robot and signaling when he reach the
objectives.
