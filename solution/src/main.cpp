#include "solution/client.h"

int main (int argc, char **argv)
{
  ros::init(argc, argv, "solution_node");

  int first_pump = 0; // initializes in pump 0, but could be either
  
  ActionClient client;
  client.init(0); 
  ros::spin();
  return 0;
}
