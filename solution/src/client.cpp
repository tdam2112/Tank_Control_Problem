#include "solution/client.h"
#include "tank/TankAction.h"

ActionClient::ActionClient() : ac("tank_server", true)
{
    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer();
    ROS_INFO("Action server started, sending goal.");
}

void ActionClient::sendGoal(){
    ac.sendGoal(goal, 
                boost::bind(&ActionClient::doneCb, this, _1, _2),
                Client::SimpleActiveCallback(),
                boost::bind(&ActionClient::feedbackCb, this, _1));
}

void ActionClient::init(int pump)
{
    cooldown_pump = (pump == 0) ? 0 : 1;
    goal.pump_number = pump;
    sendGoal();
}

void ActionClient::doneCb(const actionlib::SimpleClientGoalState& state, const tank::TankResultConstPtr& result)
{
    ROS_INFO("Finished in state [%s]", state.toString().c_str());
    ROS_INFO_STREAM("Result" << *result << "\n");
    ros::shutdown();
}

void ActionClient::feedbackCb(const tank::TankFeedbackConstPtr& feedback)
{
    //ROS_INFO_STREAM("Feedback: " << *feedback << "\n");

  if(feedback->current_level >= 50 && !goal.empty_tank && ros::ok()){
    cooldown_pump = goal.pump_number;
    ROS_INFO_STREAM("tank is full! shutting off pump "<< cooldown_pump <<" for cooldown");
    goal.empty_tank = 1;
    sendGoal();

    }
  else if(feedback->current_level <= 0 && goal.empty_tank && ros::ok()){

    goal.empty_tank = 0;
    goal.pump_number = (cooldown_pump == 0) ? 1 : 0;
            
    ROS_INFO_STREAM("tank is empty! switching to pump " << goal.pump_number << " and refilling");
    sendGoal();
    }
}


