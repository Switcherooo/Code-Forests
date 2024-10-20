#ifndef GUI_GUI_HPP
#define GUI_GUI_HPP

#include <iostream>
#include <string>

#include <OGRE/Bites/OgreImGuiInputListener.h>
#include <OGRE/Overlay/OgreImGuiOverlay.h>
#include <OGRE/Overlay/imgui.h>
#include "OGRE/Bites/OgreApplicationContext.h"
#include "OGRE/Ogre.h"

#include "dependencies/dependencies.hpp"
#include "structures/trees.hpp"


namespace gui {

class Gui {
   public:
    void show_gui(int type, trees::Trees::methods method, trees::Trees::tree tree, string nnamespace, trees::Trees::tree methodlesstree, Ogre::Root* root, pair<vector<string>, vector<string>> from_to_dependencies, Ogre::SceneNode* dependency_lines_node);  // function that gets called every frame and calls all the other gui functions
    void popup(int type, trees::Trees::methods method, trees::Trees::tree tree, string nnamespace, trees::Trees::tree methodlesstree, pair<vector<string>, vector<string>> from_to_dependencies);                                                               // create a popup when clicking on methods or namespaces
    void menu_bar(Ogre::Root* root, Ogre::SceneNode* dependency_lines_node);                                                                                                                                                                                           // show the menu bar
    void info_branch();                                                                                                                                                                                                                                                // show the branch with the info on the top right
    void tree_menu(trees::Trees::tree tree, pair<vector<string>, vector<string>> from_to_dependencies);                                                                                                                                                       // show the branch with the class information
    vector<int> sizes_branch(int namespace_height, int tree_size, int branch_size, int max_tree_size);                                                                                                                                                         // show the branch that can change the sizes of trees,branches and groves
    bool get_mouse_on_popup();                                                                                                                                                                                                                                         // get a bool that shows if the mouse is hovering a popup so we won't be able to click on stuff behind the popup
};
}
#endif