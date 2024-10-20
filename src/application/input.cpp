#include "application.hpp"
#include "gui/gui.hpp"

namespace application {

bool Application::keyPressed(const KeyboardEvent& evt) {
    if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    if (evt.keysym.sym == OgreBites::SDLK_SPACE) {
        dependency_lines_node->flipVisibility();
    }
    return true;
}

bool Application::mouseWheelRolled(const MouseWheelEvent& evt) {
    camNode->translate(camNode->getOrientation() * Vector3(0, 0, -100 * evt.y));

    return true;
}

bool Application::mousePressed(const MouseButtonEvent& evt) {
    clickable::Clickable Clickable;

    if (evt.button == OgreBites::ButtonType::BUTTON_LEFT) {
        Clickable.set_material_before_click(structure_clicked, methodnode, namespacenode, methodlesstreenode);
        if (!gui.get_mouse_on_popup()) structure_clicked = Clickable.clickstructure(methodnode, namespacenode, methodlesstreenode, evt, viewport, cam);
        if (structure_clicked.first == 0) {
            lightNode2->setPosition(methodnode[structure_clicked.second].first->getPosition());
            clicked_method = Clickable.clickmethod(methodnode[structure_clicked.second]);
            from_to_dependencies = dependencies.get_dependencies_of_tree(trees.get_trees()[methodnode[structure_clicked.second].second.first].fullname);
        } else if (structure_clicked.first == 1) {
            lightNode2->setPosition(namespacenode[structure_clicked.second]->getPosition());
            clicked_namespace = Clickable.clicknamespace(namespacenode[structure_clicked.second], structure_clicked.second);
        } else if (structure_clicked.first == 2) {
            lightNode2->setPosition(methodlesstreenode[structure_clicked.second].first->getPosition());
            clicked_methodlesstree = Clickable.clickmethodlesstree(methodlesstreenode[structure_clicked.second]);
            from_to_dependencies = dependencies.get_dependencies_of_tree(trees.get_trees()[methodlesstreenode[structure_clicked.second].second].fullname);

        } else
            lightNode2->setPosition(0, -10000, 0);
    } else if (evt.button == OgreBites::ButtonType::BUTTON_RIGHT) {
        rotating_camera = true;
    }

    else if (evt.button == OgreBites::ButtonType::BUTTON_MIDDLE) {
        moving_camera = true;
    }
    return true;
}

bool Application::mouseReleased(const MouseButtonEvent& evt) {
    if (evt.button == OgreBites::ButtonType::BUTTON_RIGHT) {
        rotating_camera = false;
    }

    else if (evt.button == OgreBites::ButtonType::BUTTON_MIDDLE) {
        moving_camera = false;
    }
    return true;
}

bool Application::mouseMoved(const MouseMotionEvent& evt) {
    if (rotating_camera) {
        camNode->pitch(Degree(evt.yrel * -0.1));
        camNode->yaw(Degree(evt.xrel * -0.1));
        camNode->roll(Degree(evt.xrel * -0.05 + evt.yrel * -0.05));
    }
    if (moving_camera) {
        camNode->translate(camNode->getOrientation() * Vector3(-1 * evt.xrel, evt.yrel, 0));
    }
    return true;
}
}