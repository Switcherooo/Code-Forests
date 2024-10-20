#ifndef CLICKABLE_CLICKABLE_HPP
#define CLICKABLE_CLICKABLE_HPP
#include <iostream>
#include <vector>

#include "OGRE/Bites/OgreApplicationContext.h"
#include "OGRE/Bites/OgreInput.h"
#include "OGRE/Ogre.h"

#include "structures/trees.hpp"
#include "structures/groves.hpp"

namespace clickable {

class Clickable {
   public:
    std::pair<int, int> clickstructure(std::vector<std::pair<Ogre::SceneNode*, std::pair<int, int>>> methodnode, std::vector<Ogre::SceneNode*> namespacenode, std::vector<std::pair<Ogre::SceneNode*, int>> methodlesstreenode, const OgreBites::MouseButtonEvent& evt, Ogre::Viewport* viewport, Ogre::Camera* cam);  // function for when you click a method or a namespace. Returns a pair of the type of what was clicked (method or namespace) and its index
    std::pair<trees::Trees::methods, trees::Trees::tree> clickmethod(std::pair<Ogre::SceneNode*, std::pair<int, int>> methodnode);                                                                                                                                                                                           // function for when you click a method. Parameters are the method's scenenode,the tree's index and the method's index all in a pair of scenenode and pair
    trees::Trees::tree clickmethodlesstree(std::pair<Ogre::SceneNode*, int> methodlesstreenode);                                                                                                                                                                                                                  // function for when you click a tree with no methods
    string clicknamespace(Ogre::SceneNode* namespacenode, int namespaceindex);                                                                                                                                                                                                                                             /// function for when you click a namespace
    std::pair<int, int> getclosestclicked(std::vector<std::pair<Ogre::SceneNode*, std::pair<int, int>>> methodnode, std::vector<Ogre::SceneNode*> namespacenode, std::vector<std::pair<Ogre::SceneNode*, int>> methodlesstreenode, Ogre::Camera* cam, Ogre::Ray mouseRay);                                             // Gets the first thing that was clicked so we can't click two or more structures at once. Returns a pair of the type of what was clicked (method or namespace) and its index
    void set_material_before_click(std::pair<int, int> structure_clicked, std::vector<std::pair<Ogre::SceneNode*, std::pair<int, int>>> methodnode, std::vector<Ogre::SceneNode*> namespacenode, std::vector<std::pair<Ogre::SceneNode*, int>> methodlesstreenode);                                                    // set the material of the previously clicked structure to its original
};
}
#endif