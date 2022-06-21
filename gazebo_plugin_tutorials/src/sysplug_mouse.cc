// This will show the mouse position when clicked
// gzclient -g build/libsysplug_mouse.so


#include <gazebo/gazebo.hh>
#include <gazebo/gui/GuiIface.hh>
#include <gazebo/rendering/rendering.hh>
#include <gazebo/rendering/UserCamera.hh>
#include <gazebo/gui/MouseEventHandler.hh>


namespace gazebo
{
class SystemGUI : public SystemPlugin
{
public:
  virtual ~SystemGUI()
  {
    gui::MouseEventHandler::Instance()->RemovePressFilter("glwidget");
  }

  void Load(int /*_argc*/, char ** /*_argv*/)
  {
    std::cout << "In Load\n";
    if (!this->userCam) {
      this->userCam = gui::get_active_camera();
    }

    gui::MouseEventHandler::Instance()->AddPressFilter(
        "glwidget", boost::bind(&SystemGUI::OnMousePress, this, _1));
  }

private:
  bool OnMousePress(const common::MouseEvent & _event)
  {
    std::cout << "Mouse press detected: ";
    // ignition::math::Vector2i PressPos() const;
    ignition::math::Vector2i cp = _event.PressPos();
    std::cout << cp << "\n";

    if (!this->userCam) {
      this->userCam = gui::get_active_camera();
    }

    // public: VisualPtr Visual(const ignition::math::Vector2i &_mousePos,
    //             std::string &_mod) const;
    // rendering::VisualPtr vp = userCam->Visual(cp);
    // std::cout << vp << "\n";

    // ignition::math::Vector3d WorldPosition() const;
    ignition::math::Vector3d wp = userCam->WorldPosition();
    std::cout << wp << "\n";

    ignition::math::Pose3d wp_ = userCam->WorldPose();
    std::cout << wp_ << "\n";

    return true;
  }

  rendering::UserCameraPtr userCam;
};

GZ_REGISTER_SYSTEM_PLUGIN(SystemGUI)
}
