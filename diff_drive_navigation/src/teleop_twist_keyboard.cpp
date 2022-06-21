#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>

#define KEYCODE_R 'd'
#define KEYCODE_L 'a'
#define KEYCODE_U 'w'
#define KEYCODE_D 's'
#define KEYCODE_Q 'q'

class TeleopKeyboard {
  public:
    TeleopKeyboard();
    void keyLoop();
    void printInstruction();

  private:
  ros::NodeHandle nh;
  ros::Publisher twist_pub;

  double linear_, angular_, l_scale_, a_scale_;

};

TeleopKeyboard::TeleopKeyboard(){
  linear_ = 0;
  angular_ = 0;
  l_scale_ = 1.0;
  a_scale_ = 1.0;

  nh.param("scale_angular", a_scale_, a_scale_);
  nh.param("scale_linear", l_scale_, l_scale_);
  twist_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
}

void quit(int sig)
{
  (void)sig;
  ros::shutdown();
  exit(0);
}


int main(int argc, char **argv) {

  char c;

  ros::init(argc, argv, "teleop_twist_keyboard");
  TeleopKeyboard teleop_key;

  signal(SIGINT, quit);
  teleop_key.printInstruction();
  teleop_key.keyLoop();

  return 0;
}

int kfd = 0;
struct termios cooked, raw;

void TeleopKeyboard::keyLoop() {
  char c;
  bool dirty=false;

  // get the console in raw mode
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  linear_=angular_=0;

  while (true)
  {
    // get the next event from the keyboard
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }


    if(c=='a'){
      ROS_DEBUG("LEFT");
      angular_ = 1.0;
      dirty = true;
    }
    else if(c=='d'){
      ROS_DEBUG("RIGHT");
      angular_ = -1.0;
      dirty = true;
    }
    else if(c=='w'){
      ROS_DEBUG("UP");
      linear_ = 1.0;
      dirty = true;
    }
    else if(c=='s'){
      ROS_DEBUG("DOWN");
      linear_ = -1.0;
      dirty = true;
    }
    else if(c=='q' || c=='e') {
      linear_=angular_=0;
      l_scale_ = a_scale_ = 1;
      dirty = true;
    }
    else if(c=='z') {
      l_scale_ += 0.1;
      a_scale_ += 0.1;
      dirty = true;
    }
    else if(c=='x') {
      if(l_scale_>=0.1 && a_scale_>=0.1) {
        l_scale_ -= 0.1;
        a_scale_ -= 0.1;
        dirty = true;
      }
    }

    geometry_msgs::Twist twist;
    twist.angular.z = a_scale_*angular_;
    twist.linear.x = l_scale_*linear_;
    if(dirty) {
      twist_pub.publish(twist);
      dirty = false;
    }
  }

}

void TeleopKeyboard::printInstruction(){
  printf("Forward   ->    w\n");
  printf("Backward  ->    s\n");
  printf("Left      ->    a\n");
  printf("Right     ->    d\n");
  printf("Stop      ->    q or e\n");
  printf("SpeedUp   ->    z\n");
  printf("SpeedDown ->    x\n");
  printf("-------------------------------------------------------\n\n\n");
}
