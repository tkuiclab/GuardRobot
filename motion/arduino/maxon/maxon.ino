#include <ros.h>
#include <geometry_msgs/Twist.h>
#define RIGHT_PWM  9
#define RIGHT_EN   4
#define RIGHT_DIR  5
#define RIGHT_STOP 6
#define LEFT_PWM   10
#define LEFT_EN    11
#define LEFT_DIR   12
#define LEFT_STOP  13
#define MIN_PWM 25.6
#define MAX_PWM 230.4
#define MAX_SPEED 6

ros::NodeHandle nh;

void MotorControl(float l, float r) {
  // DIR
  int dir_l = (l < 0) ? 0 : 1;
  int dir_r = (r < 0) ? 1 : 0;
  digitalWrite(LEFT_DIR,  dir_l);
  digitalWrite(RIGHT_DIR, dir_r);
  // VEL
  l = constrain(abs(l), 0, MAX_SPEED);
  r = constrain(abs(r), 0, MAX_SPEED);
  float left  = map(l, 0, 100, MIN_PWM, MAX_PWM);
  float right = map(r, 0, 100, MIN_PWM, MAX_PWM);
  analogWrite(LEFT_PWM,  left);
  analogWrite(RIGHT_PWM, right);

  digitalWrite(LEFT_EN,  HIGH);
  digitalWrite(RIGHT_EN, HIGH);
}

void messageCb( const geometry_msgs::Twist& msg) {
  digitalWrite(LEFT_EN,  LOW);
  digitalWrite(RIGHT_EN, LOW);
  float vel = msg.linear.x;
  float yaw = msg.angular.z;

  float left  = vel - yaw;
  float right = vel + yaw;

  MotorControl(left, right);
}

geometry_msgs::Twist vel_msg;
ros::Subscriber<geometry_msgs::Twist> listener("arduino/cmd_vel", messageCb);

int INIT_SPEED = 0;

void setup() {
  // ROS Initial
  nh.initNode();
  nh.subscribe(listener);

  // Right Motor Initial
  pinMode(RIGHT_PWM,  OUTPUT);
  digitalWrite(RIGHT_EN,   LOW);
  digitalWrite(RIGHT_DIR,  0);
  digitalWrite(RIGHT_STOP, LOW);

  // Left Motor Initial
  pinMode(LEFT_PWM,  OUTPUT);
  digitalWrite(LEFT_EN,   LOW);
  digitalWrite(LEFT_DIR,  1);
  digitalWrite(LEFT_STOP, LOW);
}

void loop() {
  nh.spinOnce();
}
