#include "clickable.hpp"

namespace clickable {

std::string original_material_before_click;
trees::Trees trees;

std::pair<int, int> Clickable::clickstructure(std::vector<std::pair<Ogre::SceneNode*, std::pair<int, int>>> methodnode, std::vector<Ogre::SceneNode*> namespacenode,std::vector<std::pair<Ogre::SceneNode*,int>> methodlesstreenode, const OgreBites::MouseButtonEvent& evt, Ogre::Viewport* viewport, Ogre::Camera* cam) {
    Ogre::Ray mouseRay = cam->getCameraToViewportRay((float)evt.x / (float)viewport->getActualWidth(), (float)evt.y / (float)viewport->getActualHeight());
    std::pair<int, int> closestclicked = getclosestclicked(methodnode, namespacenode,methodlesstreenode ,cam, mouseRay);
    return closestclicked;
}

std::pair<trees::Trees::methods, trees::Trees::tree> Clickable::clickmethod(std::pair<Ogre::SceneNode*, std::pair<int, int>> methodnode) {

    std::pair<trees::Trees::methods, trees::Trees::tree> method_tree_pair;
    original_material_before_click = static_cast<Ogre::Entity*>(methodnode.first->getAttachedObject(0))->getSubEntity(0)->getMaterialName();
    if (!original_material_before_click.compare("Non_Public_Method"))
        static_cast<Ogre::Entity*>(methodnode.first->getAttachedObject(0))->setMaterialName("Non_Public_Method_Clicked");
    else if (!original_material_before_click.compare("Public_Method"))
        static_cast<Ogre::Entity*>(methodnode.first->getAttachedObject(0))->setMaterialName("Public_Method_Clicked");
    method_tree_pair.first=trees.get_trees()[methodnode.second.first].mmethods[methodnode.second.second];
    method_tree_pair.second=trees.get_trees()[methodnode.second.first];
    return method_tree_pair;
}

string Clickable::clicknamespace(Ogre::SceneNode* namespacenode, int namespaceindex) {
    groves::Groves groves;
    original_material_before_click = static_cast<Ogre::Entity*>(namespacenode->getAttachedObject(0))->getSubEntity(0)->getMaterialName();
    static_cast<Ogre::Entity*>(namespacenode->getAttachedObject(0))->setMaterialName("Namespace_Clicked");
    return groves.get_namespaces()[namespaceindex];
}

trees::Trees::tree Clickable::clickmethodlesstree(std::pair<Ogre::SceneNode*,int> methodlesstreenode){
    original_material_before_click = static_cast<Ogre::Entity*>(methodlesstreenode.first->getAttachedObject(0))->getSubEntity(0)->getMaterialName();
    static_cast<Ogre::Entity*>(methodlesstreenode.first->getAttachedObject(0))->setMaterialName("Methodless_Tree_Clicked");
    return trees.get_trees()[methodlesstreenode.second];
}

std::pair<int, int> Clickable::getclosestclicked(std::vector<std::pair<Ogre::SceneNode*, std::pair<int, int>>> methodnode, std::vector<Ogre::SceneNode*> namespacenode,std::vector<std::pair<Ogre::SceneNode*,int>> methodlesstreenode ,Ogre::Camera* cam, Ogre::Ray mouseRay) {
    std::pair<int, int> pair_type_index;  // <type,index> pair
    pair_type_index.first = -1;
    pair_type_index.second = -1;
    Ogre::Real min = -1;
    for (int i = 0; i < (int)methodnode.size(); i++) {

        if (mouseRay.intersects(methodnode[i].first->_getWorldAABB()).first) {
            if (min < 0 || cam->getRealPosition().squaredDistance(mouseRay.getPoint(mouseRay.intersects(methodnode[i].first->_getWorldAABB()).second)) < min) {
                min = cam->getRealPosition().squaredDistance(mouseRay.getPoint(mouseRay.intersects(methodnode[i].first->_getWorldAABB()).second));
                pair_type_index.first = 0;
                pair_type_index.second = i;
            }
        }
    }
    for (int i = 0; i < (int)namespacenode.size(); i++) {

        if (mouseRay.intersects(namespacenode[i]->_getWorldAABB()).first) {
            if (min < 0 || cam->getRealPosition().squaredDistance(mouseRay.getPoint(mouseRay.intersects(namespacenode[i]->_getWorldAABB()).second)) < min) {
                min = cam->getRealPosition().squaredDistance(mouseRay.getPoint(mouseRay.intersects(namespacenode[i]->_getWorldAABB()).second));
                pair_type_index.first = 1;
                pair_type_index.second = i;
            }
        }
    }

    for (int i = 0; i < (int)methodlesstreenode.size(); i++) {

        if (mouseRay.intersects(methodlesstreenode[i].first->_getWorldAABB()).first) {
            if (min < 0 || cam->getRealPosition().squaredDistance(mouseRay.getPoint(mouseRay.intersects(methodlesstreenode[i].first->_getWorldAABB()).second)) < min) {
                min = cam->getRealPosition().squaredDistance(mouseRay.getPoint(mouseRay.intersects(methodlesstreenode[i].first->_getWorldAABB()).second));
                pair_type_index.first = 2;
                pair_type_index.second = i;
            }
        }
    }

    return pair_type_index;
}

void Clickable::set_material_before_click(std::pair<int, int> structure_clicked, std::vector<std::pair<Ogre::SceneNode*, std::pair<int, int>>> methodnode, std::vector<Ogre::SceneNode*> namespacenode, std::vector<std::pair<Ogre::SceneNode*,int>> methodlesstreenode) {
    if (structure_clicked.first == 0) {
        static_cast<Ogre::Entity*>(methodnode[structure_clicked.second].first->getAttachedObject(0))->setMaterialName(original_material_before_click);
    } 
    else if (structure_clicked.first == 1) {
        static_cast<Ogre::Entity*>(namespacenode[structure_clicked.second]->getAttachedObject(0))->setMaterialName(original_material_before_click);
    }
    else if (structure_clicked.first == 2) {
        static_cast<Ogre::Entity*>(methodlesstreenode[structure_clicked.second].first->getAttachedObject(0))->setMaterialName(original_material_before_click);
    }
}
}