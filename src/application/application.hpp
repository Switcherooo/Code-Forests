#ifndef APPLICATION_APPLICATION_HPP
#define APPLICATION_APPLICATION_HPP

#include <stdio.h>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <OGRE/Overlay/OgreFontManager.h>
#include <OGRE/Overlay/OgreOverlayManager.h>
#include <OGRE/Overlay/OgreOverlaySystem.h>
#include <OgreConfigFile.h>
#include <OgreException.h>
#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include <OgreRoot.h>
#include "OGRE/Bites/OgreApplicationContext.h"
#include "OGRE/Bites/OgreApplicationContextBase.h"
#include "OGRE/Bites/OgreInput.h"
#include "OGRE/Ogre.h"
#include "OGRE/OgrePrerequisites.h"
#include "OGRE/RTShaderSystem/OgreRTShaderSystem.h"

#include "clickable/clickable.hpp"
#include "dependencies/dependencies.hpp"
#include "gui/gui.hpp"
#include "structures/groves.hpp"
#include "structures/trees.hpp"







using namespace Ogre;
using namespace OgreBites;
using namespace std;

namespace application {

class Application : public ApplicationContext, public InputListener {
   public:

    Application(const char* argv[]);
    virtual ~Application() {}

    const char* file;
    Root* root;
    SceneManager* scnMgr;
    SceneNode* camNode;
    SceneNode* center;
    SceneNode *lightNode, *lightNode2, *lightNode3, *lightNode4;
    Viewport* viewport;
    Camera* cam;
    Mesh* cube;

    vector<pair<SceneNode*, pair<int, int>>> methodnode;
    vector<pair<SceneNode*, int>> methodlesstreenode;
    vector<pair<SceneNode*, SceneNode*>> branchnodes;
    vector<SceneNode*> namespacenode;
    SceneNode* dependency_lines_node;
    SceneNode* basenamespacenode;
    Entity *entity, *entity2;
    SceneNode *node, *node2, *previousnode = NULL, *previousnodetree = NULL;
    vector<int> namespace_sizes, sorted_size_indexes;
    vector<int> top_method_nodes;
    vector<pair<string,Vector3>> dependencies_positions;
    pair<vector<string>,vector<string>> from_to_dependencies;
    dependencies::Dependencies dependencies;
    gui::Gui gui;
    groves::Groves groves;
    trees::Trees trees;

    bool moving_camera = false;
    bool rotating_camera = false;
    int base_namespace_size;
    int parent;
    int grovesspawned;
    int treesspawned;
    int trees_in_namespace_count;
    int currentdepth;
    int current_sorted_size_index;
    int height;
    int namespace_height;
    int tree_size;
    int branch_size;
    int space_between;
    int max_tree_size;

    vector<int> changed_sizes;
    pair<int, int> structure_clicked;
    pair<trees::Trees::methods, trees::Trees::tree> clicked_method;
    string clicked_namespace;
    trees::Trees::tree clicked_methodlesstree;

    bool frameStarted(const FrameEvent& evt);                                                               //Start next frame
    void setup_namespace(int i);                                                                            //Setup the namespace with index i from vector of namespaces
    void setup_tree(int treeindex, int methodindex, std::vector<int> sortedmethodindexes, int parentindex); //Setup the tree's base with index treeindex from vector of trees and index methodindex from vector of this tree's methods and index parentindex which shows the namespace parent of the tree. sortedmethodindexes is the vector of the sorted method indexes that will be used so that the public methods are first
    void setup_branches(SceneNode* node, int num_of_args);                                                  //Setup the branches on methodnode node. num_of_args is the number of arguments of this method and also the number of branches to setup 
    void setup_dependency_line(int dependencyindex, ManualObject* manualObject);                            //Setup the dependency line with index dependencyindex. All the lines belong to the one object manualObject
    int get_top_method_node(int treeindex);                                                                 //Returns tree's top method index
    bool check_position_valid(int x, int y, int parentindex);                                               //Verify tree placement
    void setup();                                                                                           //Init
    void change_branch_size();                                                                              //Modify branch size
    void change_tree_size();                                                                                //Modify tree height
    void change_namespace_height(int height_difference);                                                    //Modify grove height by height_difference
    void read_from_config();
    bool keyPressed(const KeyboardEvent& evt);
    bool mouseWheelRolled(const MouseWheelEvent& evt);
    bool mousePressed(const MouseButtonEvent& evt);
    bool mouseReleased(const MouseButtonEvent& evt);
    bool mouseMoved(const MouseMotionEvent& evt);
};
}
#endif