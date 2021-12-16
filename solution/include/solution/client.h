#pragma once
#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include "tank/TankAction.h"

typedef actionlib::SimpleActionClient<tank::TankAction> Client;

class ActionClient
{
public:
  ActionClient();

  void sendGoal();
  void init(int pump);
  void doneCb(const actionlib::SimpleClientGoalState& state, const tank::TankResultConstPtr& result);
  void feedbackCb(const tank::TankFeedbackConstPtr& feedback);

private:
  Client ac;
  tank::TankGoal goal;
  tank::TankFeedback feedback;
  tank::TankResult result;
  int32_t cooldown_pump;
};
