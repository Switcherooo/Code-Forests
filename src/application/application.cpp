#include "application.hpp"


namespace application {

Application::Application(const char* argv[]) {
    file = argv[1];
}

bool Application::check_position_valid(int x, int z, int parentindex) {
    vector<string> nsp = groves.get_namespaces();
    for (int i = 0; i < (int)groves.get_namespaces().size(); i++) {
        if (groves.get_parent_index(nsp[i]) != -1 &&
                !nsp[groves.get_parent_index(nsp[i])].compare(nsp[parentindex]) &&
                x >= namespacenode[i]->getPosition().x - namespacenode[i]->getScale().x && 
                x <= namespacenode[i]->getPosition().x + namespacenode[i]->getScale().x && 
                z >= namespacenode[i]->getPosition().z - namespacenode[i]->getScale().z && 
                z <= namespacenode[i]->getPosition().z + namespacenode[i]->getScale().z) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Application::setup_branches(SceneNode* node, int num_of_args) {
    if (num_of_args == 0) return;
    SceneNode* branchnode;
    Entity* branchentity;
    for (int i = 0; i < num_of_args; i++) {
        branchnode = scnMgr->getRootSceneNode()->createChildSceneNode();
        branchentity = scnMgr->createEntity("cube.mesh");
        branchentity->setMaterialName("Branch");
        branchentity->setCastShadows(false);
        switch (i % 4) {
            case 0:
                branchnode->setScale(branch_size, node->getScale().y / (2 * (((num_of_args - 1) / 4) + 1)) - node->getScale().y / 20, 3);
                branchnode->setPosition(node->getPosition().x, node->getPosition().y + (i / 4) * branchnode->getScale().y * 2 + (i / 4) * 3 * node->getScale().y / 20 - node->getScale().y / 2 + branchnode->getScale().y, node->getPosition().z + node->getScale().z + branchnode->getScale().z);
                break;
            case 1:
                if ((num_of_args - 1) % 4 >= 1)
                    branchnode->setScale(3, node->getScale().y / (2 * (((num_of_args - 1) / 4) + 1)) - node->getScale().y / 20, branch_size);
                else
                    branchnode->setScale(3, node->getScale().y / (2 * ((num_of_args - 1) / 4)) - node->getScale().y / 20, branch_size);
                branchnode->setPosition(node->getPosition().x + node->getScale().x + branchnode->getScale().x, node->getPosition().y + (i / 4) * branchnode->getScale().y * 2 + (i / 4) * 3 * node->getScale().y / 20 - node->getScale().y / 2 + branchnode->getScale().y, node->getPosition().z);
                break;
            case 2:
                if ((num_of_args - 1) % 4 >= 2)
                    branchnode->setScale(branch_size, node->getScale().y / (2 * (((num_of_args - 1) / 4) + 1)) - node->getScale().y / 20, 3);
                else
                    branchnode->setScale(branch_size, node->getScale().y / (2 * ((num_of_args - 1) / 4)) - node->getScale().y / 20, 3);
                branchnode->setPosition(node->getPosition().x, node->getPosition().y + (i / 4) * branchnode->getScale().y * 2 + (i / 4) * 3 * node->getScale().y / 20 - node->getScale().y / 2 + branchnode->getScale().y, node->getPosition().z - node->getScale().z - branchnode->getScale().z);
                break;
            case 3:
                if ((num_of_args - 1) % 4 == 3)
                    branchnode->setScale(3, node->getScale().y / (2 * (((num_of_args - 1) / 4) + 1)) - node->getScale().y / 20, branch_size);
                else
                    branchnode->setScale(3, node->getScale().y / (2 * ((num_of_args - 1) / 4)) - node->getScale().y / 20, branch_size);
                branchnode->setPosition(node->getPosition().x - node->getScale().x - branchnode->getScale().x, node->getPosition().y + (i / 4) * branchnode->getScale().y * 2 + (i / 4) * 3 * node->getScale().y / 20 - node->getScale().y / 2 + branchnode->getScale().y, node->getPosition().z);
                break;
        }

        branchnode->attachObject(branchentity);
        branchnodes.push_back(make_pair(branchnode, node));
    }
}

void Application::setup_namespace(int i) {
    if (i == -1) {
        node = scnMgr->getRootSceneNode()->createChildSceneNode();
        entity = scnMgr->createEntity("cube.mesh");
        entity->getMesh()->buildEdgeList();
        entity->setMaterialName("Base");
        node->setScale(
            tree_size * base_namespace_size + space_between * base_namespace_size / 2,
            namespace_height,
            tree_size * base_namespace_size + space_between * base_namespace_size / 2);
        node->setPosition(0, namespace_height * (-2), 200);
        node->attachObject(entity);
        basenamespacenode = node;
    } else {
        SceneNode* parentnamespacenode;
        sorted_size_indexes = groves.get_sorted_size_indexes(namespace_sizes, currentdepth);
        parent = groves.get_parent_index(groves.get_namespaces()[sorted_size_indexes[current_sorted_size_index]]);

        node = scnMgr->getRootSceneNode()->createChildSceneNode();
        entity = scnMgr->createEntity("cube.mesh");
        switch (currentdepth % 3) {
            case 0:
                entity->setMaterialName("Namespace");
                break;
            case 1:
                entity->setMaterialName("Namespace2");
                break;
            case 2:
                entity->setMaterialName("Namespace3");
                break;
        }

        node->setScale(
            tree_size * namespace_sizes[sorted_size_indexes[current_sorted_size_index]] + space_between * (namespace_sizes[sorted_size_indexes[current_sorted_size_index]]) / 2,
            namespace_height,
            tree_size * namespace_sizes[sorted_size_indexes[current_sorted_size_index]] + space_between * (namespace_sizes[sorted_size_indexes[current_sorted_size_index]]) / 2);

        if (parent == -1)
            parentnamespacenode = basenamespacenode;
        else
            parentnamespacenode = namespacenode[parent];
            
            //Top Left
        if (previousnode == NULL) 
            node->setPosition(parentnamespacenode->getPosition().x - parentnamespacenode->getScale().x + node->getScale().x, namespace_height * 2 * (currentdepth - 1), parentnamespacenode->getPosition().z - parentnamespacenode->getScale().z + node->getScale().z);

            //Bottom right
        else if (previousnode->getPosition().x + previousnode->getScale().x + node->getScale().x * 2 > parentnamespacenode->getPosition().x + parentnamespacenode->getScale().x && previousnode->getPosition().z + previousnode->getScale().z + node->getScale().z * 2 <= parentnamespacenode->getPosition().z + parentnamespacenode->getScale().z)
            node->setPosition(parentnamespacenode->getPosition().x + parentnamespacenode->getScale().x - node->getScale().x, namespace_height * 2 * (currentdepth - 1), previousnode->getPosition().z + previousnode->getScale().z + node->getScale().z);

            //Bottom left
        else if (previousnode->getPosition().z + previousnode->getScale().z + node->getScale().z * 2 > parentnamespacenode->getPosition().z + parentnamespacenode->getScale().z)
            node->setPosition(previousnode->getPosition().x - previousnode->getScale().x - node->getScale().x, namespace_height * 2 * (currentdepth - 1), parentnamespacenode->getPosition().z + parentnamespacenode->getScale().z - node->getScale().z)
            //Top right
        else  
            node->setPosition(previousnode->getPosition().x + previousnode->getScale().x + node->getScale().x, namespace_height * 2 * (currentdepth - 1), parentnamespacenode->getPosition().z - parentnamespacenode->getScale().z + node->getScale().z);

        node->attachObject(entity);
        namespacenode[sorted_size_indexes[current_sorted_size_index]] = node;
        previousnode = node;
        grovesspawned++;
    }
}

void Application::setup_tree(int treeindex, int methodindex, vector<int> sortedmethodindexes, int parentindex) {
    int tempcount = 0;
    node = scnMgr->getRootSceneNode()->createChildSceneNode();
    entity = scnMgr->createEntity("cube.mesh");

    if (methodindex == 0)
        node->setScale(tree_size, tree_size / 2, tree_size);
    else
        node->setScale(tree_size, (trees.get_trees()[treeindex].mmethods[sortedmethodindexes[methodindex - 1]].lines * 10) + tree_size / 2, tree_size);

    if (methodindex == 0) {
        entity->setMaterialName("Methodless_Tree");
        height = previousnode->getPosition().y + previousnode->getScale().y + node->getScale().y;
    } else {
        entity->setMaterialName("Non_Public_Method");
        if (!trees.get_trees()[treeindex].mmethods[sortedmethodindexes[methodindex - 1]].access.compare("public")) entity->setMaterialName("Public_Method");
        if (methodindex == 1)
            height +=
                previousnode->getPosition().y + previousnode->getScale().y + node->getScale().y;
        else
            height +=
                node->getScale().y + (trees.get_trees()[treeindex].mmethods[sortedmethodindexes[methodindex - 2]].lines * 10) + tree_size / 2;
    }
    if (parentindex == -1) {
        if (previousnodetree == NULL) {  //Top left
            node->setPosition(previousnode->getPosition().x - previousnode->getScale().x + node->getScale().x + node->getScale().x / 2, height, previousnode->getPosition().z - previousnode->getScale().z + node->getScale().z + node->getScale().z / 2);
        } else {
            if ((trees_in_namespace_count / namespace_sizes[sorted_size_indexes[current_sorted_size_index]]) % 2 == 0) {
                if (trees_in_namespace_count % namespace_sizes[sorted_size_indexes[current_sorted_size_index]] == 0) {  //Bottom
                    node->setPosition(previousnodetree->getPosition().x, height, previousnodetree->getPosition().z + 2 * node->getScale().z + space_between);
                } else {  //Right
                    node->setPosition(previousnodetree->getPosition().x + 2 * node->getScale().x + space_between, height, previousnodetree->getPosition().z);
                }
            } else {
                if (trees_in_namespace_count % namespace_sizes[sorted_size_indexes[current_sorted_size_index]] == 0) {  //Bottom
                    node->setPosition(previousnodetree->getPosition().x, height, previousnodetree->getPosition().z + 2 * node->getScale().z + space_between);
                } else {  //Left
                    node->setPosition(previousnodetree->getPosition().x - 2 * node->getScale().x - space_between, height, previousnodetree->getPosition().z);
                }
            }
        }

        node->attachObject(entity);
        if (methodindex != 0) {
            methodnode.push_back(make_pair(node, make_pair(treeindex, sortedmethodindexes[methodindex - 1])));
            setup_branches(node, trees.get_trees()[treeindex].mmethods[sortedmethodindexes[methodindex - 1]].aargs.size());
        } else {
            methodlesstreenode.push_back(make_pair(node, treeindex));
        }
    } else {
        for (int i = 0; i < namespace_sizes[parentindex] * namespace_sizes[parentindex]; i++) {
            if (i == 0) {  //Top left
                node->setPosition(previousnode->getPosition().x - previousnode->getScale().x + node->getScale().x + node->getScale().x / 2, height, previousnode->getPosition().z - previousnode->getScale().z + node->getScale().z + node->getScale().z / 2);
            } else {
                if ((i / namespace_sizes[parentindex]) % 2 == 0) {
                    if (i % namespace_sizes[parentindex] == 0) {  //Bottom
                        node->setPosition(previousnodetree->getPosition().x, height, previousnodetree->getPosition().z + 2 * node->getScale().z + space_between);
                    } else {  //Right
                        node->setPosition(previousnodetree->getPosition().x + 2 * node->getScale().x + space_between, height, previousnodetree->getPosition().z);
                    }
                } else {
                    if (i % namespace_sizes[parentindex] == 0) {  //Bottom
                        node->setPosition(previousnodetree->getPosition().x, height, previousnodetree->getPosition().z + 2 * node->getScale().z + space_between);
                    } else {  //Right
                        node->setPosition(previousnodetree->getPosition().x - 2 * node->getScale().x - space_between, height, previousnodetree->getPosition().z);
                    }
                }
            }

            if (check_position_valid(node->getPosition().x, node->getPosition().z, parentindex)) {
                if (tempcount >= trees_in_namespace_count) {
                    node->attachObject(entity);
                    if (methodindex != 0) {
                        methodnode.push_back(make_pair(node, make_pair(treeindex, sortedmethodindexes[methodindex - 1])));
                        setup_branches(node, trees.get_trees()[treeindex].mmethods[sortedmethodindexes[methodindex - 1]].aargs.size());

                    } else {
                        methodlesstreenode.push_back(make_pair(node, treeindex));
                    }
                    break;
                }
                tempcount++;
            }
            previousnodetree = node;
        }
    }
}

int Application::get_top_method_node(int treeindex) {
    int maxheight = 0;
    Vector3 position;
    int index;
    for (int i = 0; i < (int)methodnode.size(); i++) {
        if (methodnode[i].second.first == treeindex) {
            if (methodnode[i].first->getPosition().y + methodnode[i].first->getScale().y > maxheight) {
                index = i;
                maxheight = methodnode[i].first->getPosition().y + methodnode[i].first->getScale().y;
            }
        }
    }
    return index;
}

void Application::setup_dependency_line(int dependencyindex, ManualObject* manualObject) {
    bool found_from = false, found_to = false;
    Vector3 from_pos = Vector3(0, 0, 0), to_pos = Vector3(0, 0, 0);
    for (int i = 0; i < (int)dependencies_positions.size(); i++) {
        if (!found_from && !strcmp(dependencies.get_dependencies()[dependencyindex].from.c_str(), dependencies_positions[i].first.c_str())) {
            from_pos = dependencies_positions[i].second;
            found_from = true;
        }
        if (!found_to && !strcmp(dependencies.get_dependencies()[dependencyindex].to.c_str(), dependencies_positions[i].first.c_str())) {
            to_pos = dependencies_positions[i].second;
            found_to = true;
        }
        if (found_from && found_to) break;

    }
    for (int i = 0; i < (int)methodlesstreenode.size(); i++) {
        if (found_from && found_to) break;
        if (!found_from && !strcmp(dependencies.get_dependencies()[dependencyindex].from.c_str(), trees.get_trees()[methodlesstreenode[i].second].fullname.c_str())) {
            from_pos = Vector3(methodlesstreenode[i].first->getPosition().x, methodlesstreenode[i].first->getPosition().y + methodlesstreenode[i].first->getScale().y, methodlesstreenode[i].first->getPosition().z);
            found_from = true;
            dependencies_positions.push_back(make_pair(dependencies.get_dependencies()[dependencyindex].from, from_pos));
        }
        if (!found_to && !strcmp(dependencies.get_dependencies()[dependencyindex].to.c_str(), trees.get_trees()[methodlesstreenode[i].second].fullname.c_str())) {
            to_pos = Vector3(methodlesstreenode[i].first->getPosition().x, methodlesstreenode[i].first->getPosition().y + methodlesstreenode[i].first->getScale().y, methodlesstreenode[i].first->getPosition().z);
            found_to = true;
            dependencies_positions.push_back(make_pair(dependencies.get_dependencies()[dependencyindex].to, to_pos));
        }
    }
    for (int i = 0; i < (int)top_method_nodes.size(); i++) {
        if (found_from && found_to) break;
        if (!found_from && !strcmp(dependencies.get_dependencies()[dependencyindex].from.c_str(), trees.get_trees()[methodnode[top_method_nodes[i]].second.first].fullname.c_str())) {
            from_pos = Vector3(methodnode[top_method_nodes[i]].first->getPosition().x, methodnode[top_method_nodes[i]].first->getPosition().y + methodnode[top_method_nodes[i]].first->getScale().y, methodnode[top_method_nodes[i]].first->getPosition().z);

            found_from = true;
            dependencies_positions.push_back(make_pair(dependencies.get_dependencies()[dependencyindex].from, from_pos));
        }
        if (!found_to && !strcmp(dependencies.get_dependencies()[dependencyindex].to.c_str(), trees.get_trees()[methodnode[top_method_nodes[i]].second.first].fullname.c_str())) {
            to_pos = Vector3(methodnode[top_method_nodes[i]].first->getPosition().x, methodnode[top_method_nodes[i]].first->getPosition().y + methodnode[top_method_nodes[i]].first->getScale().y, methodnode[top_method_nodes[i]].first->getPosition().z);
            found_to = true;
            dependencies_positions.push_back(make_pair(dependencies.get_dependencies()[dependencyindex].to, to_pos));
        }
    }
    if(!found_from || !found_to) return;
    manualObject->begin("DependencyLine", Ogre::RenderOperation::OT_LINE_STRIP, CODEFORESTS_RESOURCE_GROUP);
    manualObject->position(from_pos);
    from_pos.y += 150;
    manualObject->position(from_pos);
    to_pos.y += 150;
    manualObject->position(Vector3((to_pos.x + from_pos.x) / 2, (to_pos.y + from_pos.y) / 2, (to_pos.z + from_pos.z) / 2));
    manualObject->end();
    manualObject->begin("DependencyLine2", Ogre::RenderOperation::OT_LINE_STRIP, CODEFORESTS_RESOURCE_GROUP);
    manualObject->position(Vector3((to_pos.x + from_pos.x) / 2, (to_pos.y + from_pos.y) / 2, (to_pos.z + from_pos.z) / 2));
    manualObject->position(to_pos);
    to_pos.y -= 150;
    manualObject->position(to_pos);

    manualObject->end();
}

void Application::change_branch_size() {
    for (int i = 0; i < (int)branchnodes.size(); i++) {
        if (branchnodes[i].first->getScale().x == 3) branchnodes[i].first->setScale(branchnodes[i].first->getScale().x, branchnodes[i].first->getScale().y, branch_size);
        if (branchnodes[i].first->getScale().z == 3) branchnodes[i].first->setScale(branch_size, branchnodes[i].first->getScale().y, branchnodes[i].first->getScale().z);
    }
}

void Application::change_tree_size() {
    for (int i = 0; i < (int)methodnode.size(); i++) {
        methodnode[i].first->setScale(tree_size, methodnode[i].first->getScale().y, tree_size);
    }
    for (int i = 0; i < (int)methodlesstreenode.size(); i++) {
        methodlesstreenode[i].first->setScale(tree_size, methodlesstreenode[i].first->getScale().y, tree_size);
    }
    for (int i = 0; i < (int)branchnodes.size(); i++) {
        if (branchnodes[i].first->getPosition().x == branchnodes[i].second->getPosition().x && branchnodes[i].first->getPosition().z > branchnodes[i].second->getPosition().z)
            branchnodes[i].first->setPosition(branchnodes[i].first->getPosition().x, branchnodes[i].first->getPosition().y, branchnodes[i].second->getPosition().z + branchnodes[i].second->getScale().z);
        else if (branchnodes[i].first->getPosition().x == branchnodes[i].second->getPosition().x && branchnodes[i].first->getPosition().z < branchnodes[i].second->getPosition().z)
            branchnodes[i].first->setPosition(branchnodes[i].first->getPosition().x, branchnodes[i].first->getPosition().y, branchnodes[i].second->getPosition().z - branchnodes[i].second->getScale().z);
        else if (branchnodes[i].first->getPosition().z == branchnodes[i].second->getPosition().z && branchnodes[i].first->getPosition().x > branchnodes[i].second->getPosition().x)
            branchnodes[i].first->setPosition(branchnodes[i].second->getPosition().x + branchnodes[i].second->getScale().x, branchnodes[i].first->getPosition().y, branchnodes[i].first->getPosition().z);
        else if (branchnodes[i].first->getPosition().z == branchnodes[i].second->getPosition().z && branchnodes[i].first->getPosition().x < branchnodes[i].second->getPosition().x)
            branchnodes[i].first->setPosition(branchnodes[i].second->getPosition().x - branchnodes[i].second->getScale().x, branchnodes[i].first->getPosition().y, branchnodes[i].first->getPosition().z);
    }
}

void Application::change_namespace_height(int height_difference) {
    namespace_height = height_difference + namespace_height;
    basenamespacenode->setScale(basenamespacenode->getScale().x, namespace_height, basenamespacenode->getScale().z);
    for (int i = 0; i < (int)namespacenode.size(); i++) {
        namespacenode[i]->setScale(namespacenode[i]->getScale().x, namespace_height, namespacenode[i]->getScale().z);
        namespacenode[i]->setPosition(namespacenode[i]->getPosition().x, namespacenode[i]->getPosition().y + (groves.get_namespace_depth(groves.get_namespaces()[i]) * height_difference * 2), namespacenode[i]->getPosition().z);
    }
    for (int i = 0; i < (int)methodnode.size(); i++) {
        methodnode[i].first->setPosition(methodnode[i].first->getPosition().x, methodnode[i].first->getPosition().y + (groves.get_namespace_depth(trees.get_trees()[methodnode[i].second.first].nnamespace) * height_difference * 2), methodnode[i].first->getPosition().z);
    }
    for (int i = 0; i < (int)methodlesstreenode.size(); i++) {
        methodlesstreenode[i].first->setPosition(methodlesstreenode[i].first->getPosition().x, methodlesstreenode[i].first->getPosition().y + (groves.get_namespace_depth(trees.get_trees()[methodlesstreenode[i].second].nnamespace) * height_difference * 2), methodlesstreenode[i].first->getPosition().z);
    }
    for (int i = 0; i < (int)branchnodes.size(); i++) {
        branchnodes[i].first->setPosition(branchnodes[i].first->getPosition().x, branchnodes[i].second->getPosition().y, branchnodes[i].first->getPosition().z);
    }
}
void Application::setup() {
    read_from_config();
    grovesspawned = 0;
    treesspawned = 0;
    trees_in_namespace_count = 0;
    currentdepth = 0;
    current_sorted_size_index = 0;
    height = 0;

    structure_clicked.first = -1;
    structure_clicked.second = -1;
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(file, pt);
    trees.get_data_from_json(pt, 0, -1, "", 0);
    dependencies.get_data_from_json(pt, 0, "", 0);

    root = getRoot();
    root->initialise(false);

    createWindow("Code Forests", 1280, 720);

    locateResources();
    initialiseRTShaderSystem();
    loadResources();

    root->addFrameListener(this);
    addInputListener(this);
    scnMgr = root->createSceneManager();
    RTShader::ShaderGenerator* shadergen =
        RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);

    scnMgr->setAmbientLight(ColourValue(0.2, 0.2, 0.2));
    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);
    Light* light = scnMgr->createLight("DirectionalLight");
    light->setType(Light::LT_DIRECTIONAL);
    light->setDiffuseColour(0.6, 0.6, 0.6);
    Light* light2 = scnMgr->createLight("PointLight");
    light2->setType(Light::LT_POINT);
    Light* light3 = scnMgr->createLight("DirectionalLight2");
    light3->setType(Light::LT_DIRECTIONAL);
    light3->setDiffuseColour(0.6, 0.6, 0.6);
    Light* light4 = scnMgr->createLight("PointLight2");
    light4->setType(Light::LT_POINT);
    light4->setDiffuseColour(0.5, 0.5, 0.5);

    center = scnMgr->getRootSceneNode()->createChildSceneNode();
    center->setPosition(0, 0, 0);
    camNode = center->createChildSceneNode();
    cam = scnMgr->createCamera("Main Camera");
    cam->setNearClipDistance(5);
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
    center->pitch(Degree(-40));
    center->yaw(Degree(30));
    center->roll(Degree(15));
    viewport = getRenderWindow()->addViewport(cam);
    camNode->setPosition(700, 300, 2000);
    lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->attachObject(light);
    lightNode->setDirection(1, -1, -1);
    lightNode2 = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode2->attachObject(light2);
    lightNode3 = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode3->attachObject(light3);
    lightNode3->setDirection(-1, -1, -1);
    lightNode4 = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode4->attachObject(light4);

    scnMgr->setSkyBox(true, "Examples/CloudyNoonSkyBox");

    namespace_sizes = groves.make_namespace_sizes();
    base_namespace_size = groves.get_base_namespace_size(namespace_sizes);
    lightNode2->setPosition(0 - (tree_size * base_namespace_size + space_between * base_namespace_size / 2), -15000, 0 - (tree_size * base_namespace_size + space_between * base_namespace_size / 2));
    lightNode4->setPosition(0, 1500, 0);
    namespacenode.resize(groves.get_namespaces().size());

    vector<int> sorted_method_indexes;
    auto* overlay = new Ogre::ImGuiOverlay();
    overlay->show();
    assert(overlay->isInitialised());
    Ogre::OverlayManager::getSingleton().addOverlay(overlay);
    auto* system = Ogre::OverlaySystem::getSingletonPtr();
    assert(system);

    scnMgr->addRenderQueueListener(system);
    ImGuiInputListener* imgui_input_listener = new ImGuiInputListener;
    addInputListener(imgui_input_listener);

    int previousnamespacesetup = -1;
    for (int i = 0; i < (int)groves.get_namespaces().size(); i++) {
        cout << groves.get_namespaces()[i]
             << groves.get_namespace_num_of_structures()[i] << "   " << groves.get_parent_index(groves.get_namespaces()[i]) << "  " << groves.get_num_of_children_namespaces(groves.get_namespaces()[i]) << "   "
             << namespace_sizes[i] << " " << base_namespace_size << endl;
    }

    setup_namespace(-1);
    while (grovesspawned != (int)groves.get_namespaces().size()) {
        for (int i = 0; i < (int)groves.get_namespaces().size(); i++) {
            if (groves.get_namespace_depth(groves.get_namespaces()[i]) == currentdepth) {
                if (previousnamespacesetup != -1 && groves.get_parent_index(groves.get_namespaces()[i]) != groves.get_parent_index(groves.get_namespaces()[previousnamespacesetup])) previousnode = NULL;
                setup_namespace(i);
                previousnamespacesetup = i;
                for (int j = 0; j < (int)trees.get_trees().size(); j++) {
                    if (!trees.get_trees()[j].nnamespace.compare(groves.get_namespaces()[sorted_size_indexes[current_sorted_size_index]])) {
                        sorted_method_indexes = trees.get_sorted_methods(j);
                        for (int k = 0; k < (int)trees.get_trees()[j].mmethods.size() + 1;
                             k++) {
                            if (k == 0 && trees.get_trees()[j].mmethods.size() > 0) k++;

                            if (!groves.get_num_of_children_namespaces(groves.get_namespaces()[sorted_size_indexes[current_sorted_size_index]])) {
                                setup_tree(j, k, sorted_method_indexes, -1);
                            }
                        }
                        previousnodetree = node;
                        trees_in_namespace_count++;
                    }
                    height = 0;
                }
                current_sorted_size_index++;
            }

            previousnodetree = NULL;
            trees_in_namespace_count = 0;
        }
        current_sorted_size_index = 0;
        currentdepth++;
        previousnode = NULL;
        previousnamespacesetup = -1;
    }
    currentdepth = 0;
    for (int i = 0; i < (int)groves.get_namespaces().size(); i++) {
        for (int j = 0; j < (int)trees.get_trees().size(); j++) {
            if (!trees.get_trees()[j].nnamespace.compare(groves.get_namespaces()[i])) {
                sorted_method_indexes = trees.get_sorted_methods(j);
                for (int k = 0; k < (int)trees.get_trees()[j].mmethods.size() + 1; k++) {
                    if (k == 0 && trees.get_trees()[j].mmethods.size() > 0) k++;
                    previousnode = namespacenode[i];
                    if (groves.get_num_of_children_namespaces(groves.get_namespaces()[i])) {
                        setup_tree(j, k, sorted_method_indexes, i);
                    }
                }
                previousnodetree = node;

                trees_in_namespace_count++;
            }
            height = 0;
        }
        previousnodetree = NULL;
        trees_in_namespace_count = 0;
    }

    cout << "Rendered Groves." << endl;
    MaterialPtr ManualObjectMaterial = MaterialManager::getSingleton().create("manual1Material", "General");

    ManualObjectMaterial->setReceiveShadows(true);
    ManualObjectMaterial->getTechnique(0)->setLightingEnabled(true);
    ManualObjectMaterial->getTechnique(0)->getPass(0)->setDiffuse(0.1, 0.4, 0.1, 0);
    ManualObjectMaterial->getTechnique(0)->getPass(0)->setAmbient(0.1, 0.4, 0.1);
    ManualObjectMaterial->getTechnique(0)->getPass(0)->setSelfIllumination(0.1, 0.4, 0.1);

    ManualObject* manualObject = scnMgr->createManualObject("manual1");
    dependency_lines_node = scnMgr->getRootSceneNode()->createChildSceneNode("manual1_node");

    for (int i = 0; i < (int)methodnode.size(); i++) {
        top_method_nodes.push_back(get_top_method_node(methodnode[i].second.first));
    }
    cout<<"Setting dependency lines..."<<endl;
    for (int i = 0; i < (int)dependencies.get_dependencies().size(); i++) {
        setup_dependency_line(i, manualObject);

        cout << i << " / " << dependencies.get_dependencies().size() << endl;
    }
    dependency_lines_node->attachObject(manualObject);
}

bool Application::frameStarted(const FrameEvent& evt) {
    ApplicationContext::frameStarted(evt);
    gui.show_gui(structure_clicked.first, clicked_method.first, clicked_method.second, clicked_namespace, clicked_methodlesstree, root, from_to_dependencies, dependency_lines_node);
    changed_sizes = gui.sizes_branch(namespace_height, tree_size, branch_size, max_tree_size);

    if (changed_sizes[0] == 1) {
        if (changed_sizes[1] != namespace_height) {
            change_namespace_height(changed_sizes[1] - namespace_height);
        }
        if (changed_sizes[2] != tree_size) {
            tree_size = changed_sizes[2];
            change_tree_size();
        }
        if (changed_sizes[3] != branch_size) {
            branch_size = changed_sizes[3];
            change_branch_size();
        }
        cout << "applied changes" << endl;
    }
    return true;
}

}