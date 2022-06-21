// NOTE: Segfaults after saving one frame



#include <functional>
#include <gazebo/gui/GuiIface.hh>
#include <gazebo/rendering/rendering.hh>
#include <gazebo/gazebo.hh>

namespace gazebo
{
class SystemGUI : public SystemPlugin
{
  /////////////////////////////////////////////
  /// \brief Destructor
public:
  virtual ~SystemGUI()
  {
    this->connections.clear();
    if (this->userCam) {
      this->userCam->EnableSaveFrame(false);
    }
    this->userCam.reset();
  }

  /////////////////////////////////////////////
  /// \brief Called after the plugin has been constructed.
  void Load(int /*_argc*/, char **  /*_argv*/)
  {
    this->connections.push_back(
        event::Events::ConnectPreRender(
          std::bind(&SystemGUI::Update, this)));
  }

  /////////////////////////////////////////////
  // \brief Called once after Load
private:
  void Init()
  {}

  /////////////////////////////////////////////
  /// \brief Called every PreRender event. See the Load function.
  void Update()
  {
    static int i = 0;
    if (!this->userCam) {
      printf("In update: !this->userCam\n");
      // Get a pointer to the active user camera
      this->userCam = gui::get_active_camera();

      // Enable saving frames
      this->userCam->EnableSaveFrame(true);

      // Specify the path to save frames into
      // this->userCam->SetSaveFramePathname("/tmp/gazebo_frames");

      // public: bool SaveFrame(const std::string &_filename);
      this->userCam->SaveFrame(std::string("/tmp/gazebo_frames").append(std::to_string(i)));
    }
    printf("In update\n");
    return;

    // Get scene pointer
    rendering::ScenePtr scene = rendering::get_scene();

    // Wait until the scene is initialized.
    if (!scene || !scene->Initialized()) {
      return;
    }

    // Look for a specific visual by name.
    if (scene->GetVisual("ground_plane")) {
      std::cout << "Has ground plane visual\n";
    }
  }

  /// Pointer the user camera.
private:
  rendering::UserCameraPtr userCam;

  /// All the event connections.
  std::vector<event::ConnectionPtr> connections;
};

// Register this plugin with the simulator
GZ_REGISTER_SYSTEM_PLUGIN(SystemGUI)
}
