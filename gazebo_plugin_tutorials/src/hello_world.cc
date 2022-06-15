// gazebo.hh does not include rendering.hh or sensors.hh or physics.hh
// bcz those shoul be included on a case-by-case basis
#include <gazebo/gazebo.hh>


// All gazebo plugins must be in namespace gazebo
namespace gazebo
{

// Must inherit from a plugin type.
class WorldPluginTutorial: public WorldPlugin
{
public:
    WorldPluginTutorial(): WorldPlugin()
    {
        printf("Helloworld\n");
    }
    void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) { }
};

// Plugin must be registered w/ this macro
// There are matching register plugin for each plugin type
GZ_REGISTER_WORLD_PLUGIN(WorldPluginTutorial)

}
