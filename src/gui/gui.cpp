#include "gui.hpp"

namespace gui {

bool mouse_on_popup = false;
bool dependency_lines_visiblee;
bool show_sizes_branch = false;

bool Gui::get_mouse_on_popup() {
    return mouse_on_popup;
}

bool get_dependency_lines_visible() {
    return dependency_lines_visiblee;
}

void Gui::show_gui(int type, trees::Trees::methods method, trees::Trees::tree tree, string nnamespace, trees::Trees::tree methodlesstree, Ogre::Root* root, pair<vector<string>, vector<string>> from_to_dependencies, Ogre::SceneNode* dependency_lines_node) {
    Ogre::ImGuiOverlay::NewFrame();

    info_branch();
    menu_bar(root, dependency_lines_node);
    popup(type, method, tree, nnamespace, methodlesstree, from_to_dependencies);
}

void Gui::menu_bar(Ogre::Root* root, Ogre::SceneNode* dependency_lines_node) {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Menu")) {
            if (ImGui::MenuItem("Quit", "Esc")) {
                root->queueEndRendering();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Show Dependency Lines", "Space", dependency_lines_node->getAttachedObject(0)->isVisible())) {
                dependency_lines_node->flipVisibility();
            }
            if (ImGui::MenuItem("Show Sizes Window", NULL, &show_sizes_branch)) {
                if(!show_sizes_branch)mouse_on_popup=false;
            }
            ImGui::EndMenu();
        }
    }
}

void Gui::info_branch() {
    const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkSize.x - 10, main_viewport->WorkPos.y + 10), ImGuiCond_Always, ImVec2(1, 0));
    bool branch_open = true;
    if (ImGui::Begin("Info", &branch_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("INFO:");
        ImGui::BulletText("Each grove represents a package.");
        ImGui::BulletText("Each tree on a grove represents a class of this grove/package.");
        ImGui::BulletText("Each individual trunk of a tree represents a method of this tree/class.");
        ImGui::BulletText("Each branch on a trunk represents an argument of this trunk/method.");
        ImGui::BulletText("Red trees are trees with no methods.");
        ImGui::BulletText("Public methods are light blue. Others are blue.");
        ImGui::BulletText("trunk height is calculated from the number of lines of the method.");
        ImGui::BulletText("Pink Lines starting from the top a tree lead to the top of trees/classes that this class is depending on.");
        ImGui::BulletText("Green Lines starting from the top a tree lead to the top of trees/classes that depend on this class.");
        ImGui::Text("CONTROLS:");
        ImGui::BulletText("Left click on a trunk or grove to get information about it.");
        ImGui::BulletText("Right click to rotate camera.");
        ImGui::BulletText("Middle click to move camera.");
        ImGui::BulletText("Mouse wheel to zoom in/out.");
        ImGui::BulletText("Press Space to hide/show the dependency lines.");
        ImGui::End();
    }
}

void Gui::tree_menu(trees::Trees::tree tree, pair<vector<string>, vector<string>> from_to_dependencies) {
    const char* classstr;
    if (tree.mmethods.size() == 0)
        classstr = "Methodless Class";
    else
        classstr = "Class";
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(classstr).x) * 0.5f);
    ImGui::Text("%s", classstr);
    ImGui::Text("Fullname: %s", tree.fullname.c_str());
    if (tree.bases.size() == 0) {
        ImGui::Text("bases: null");
    } else if (ImGui::TreeNode("bases")) {
        for (int k = 0; k < (int)tree.bases.size(); k++) {
            ImGui::Text("%s", tree.bases[k].c_str());
        }
        ImGui::TreePop();
    }
    if (tree.contains.size() == 0) {
        ImGui::Text("contains: null");
    } else if (ImGui::TreeNode("contains")) {
        for (int k = 0; k < (int)tree.contains.size(); k++) {
            ImGui::Text("%s", tree.contains[k].c_str());
        }
        ImGui::TreePop();
    }
    if (tree.ffields.size() == 0) {
        ImGui::Text("fields: null");

    } else if (ImGui::TreeNode("fields")) {
        for (int k = 0; k < (int)tree.ffields.size(); k++) {
            if (ImGui::TreeNode((void*)(intptr_t)k, "%s", tree.ffields[k].fullname.c_str())) {
                ImGui::Text("access: %s", tree.ffields[k].access.c_str());
                ImGui::Text("full_type: %s", tree.ffields[k].full_type.c_str());
                if (ImGui::TreeNode("src_info")) {
                    ImGui::Text("col: %d", tree.ffields[k].ssrc_info.col);
                    ImGui::Text("file: %s", tree.ffields[k].ssrc_info.file.c_str());
                    ImGui::Text("line: %d", tree.ffields[k].ssrc_info.line);
                    ImGui::TreePop();
                }
                ImGui::Text("type: %s", tree.ffields[k].type.c_str());
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
    if (tree.friends.size() == 0) {
        ImGui::Text("friends: null");
    } else if (ImGui::TreeNode("friends")) {
        for (int k = 0; k < (int)tree.friends.size(); k++) {
            ImGui::Text("%s", tree.friends[k].c_str());
        }
        ImGui::TreePop();
    }
    if (tree.mmethods.size() == 0) {
        ImGui::Text("methods: null");
    } else if (ImGui::TreeNode("methods")) {
        for (int k = 0; k < (int)tree.mmethods.size(); k++) {
            ImGui::Text("%s", tree.mmethods[k].fullname.c_str());
        }
        ImGui::TreePop();
    }
    ImGui::Text("name: %s", tree.name.c_str());
    ImGui::Text("namespace: %s", tree.nnamespace.c_str());
    ImGui::Text("nested_parent: %s", tree.nested_parent.c_str());
    if (ImGui::TreeNode("src_info")) {
        ImGui::Text("col: %d", tree.ssrc_info.col);
        ImGui::Text("file: %s", tree.ssrc_info.file.c_str());
        ImGui::Text("line: %d", tree.ssrc_info.line);
        ImGui::TreePop();
    }
    ImGui::Text("structure_type: %s", tree.structure_type.c_str());
    if (tree.template_args.size() == 0) {
        ImGui::Text("template_args: null");
    } else if (ImGui::TreeNode("template_args")) {
        for (int k = 0; k < (int)tree.template_args.size(); k++) {
            ImGui::Text("%s", tree.template_args[k].c_str());
        }
        ImGui::TreePop();
    }
    ImGui::Text("template_parent: %s", tree.template_parent.c_str());
    if (from_to_dependencies.second.size() == 0) {
        ImGui::Text("Classes depending on this class: null");
    } else if (ImGui::TreeNode("Classes depending on this class")) {
        for (int k = 0; k < (int)from_to_dependencies.second.size(); k++) {
            ImGui::Text("%s", from_to_dependencies.second[k].c_str());
        }
        ImGui::TreePop();
    }
    if (from_to_dependencies.first.size() == 0) {
        ImGui::Text("Class is depending on these classes: null");
    } else if (ImGui::TreeNode("Class is depending on these classes")) {
        for (int k = 0; k < (int)from_to_dependencies.first.size(); k++) {
            ImGui::Text("%s", from_to_dependencies.first[k].c_str());
        }
        ImGui::TreePop();
    }
}

void Gui::popup(int type, trees::Trees::methods method, trees::Trees::tree tree, string nnamespace, trees::Trees::tree methodlesstree, pair<vector<string>, vector<string>> from_to_dependencies) {
    if (type == 0) {
        ImGui::OpenPopup(method.fullname.c_str());
        if (ImGui::BeginPopup(method.fullname.c_str(), ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
            const char* methodstr = "Method";
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(methodstr).x) * 0.5f);
            ImGui::Text("%s", methodstr);
            ImGui::Text("Fullname: %s", method.fullname.c_str());
            ImGui::Text("access: %s", method.access.c_str());
            if (method.aargs.size() == 0) {
                ImGui::Text("args: null");

            } else if (ImGui::TreeNode("args")) {
                for (int k = 0; k < (int)method.aargs.size(); k++) {
                    if (ImGui::TreeNode((void*)(intptr_t)k, "%s", method.aargs[k].name.c_str())) {
                        ImGui::Text("full_type: %s", method.aargs[k].full_type.c_str());
                        if (ImGui::TreeNode("src_info")) {
                            ImGui::Text("col: %d", method.aargs[k].ssrc_info.col);
                            ImGui::Text("file: %s", method.aargs[k].ssrc_info.file.c_str());
                            ImGui::Text("line: %d", method.aargs[k].ssrc_info.line);
                            ImGui::TreePop();
                        }
                        ImGui::Text("type: %s", method.aargs[k].type.c_str());
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }

            ImGui::Text("branches: %d", method.branches);

            if (method.ddefinitions.size() == 0) {
                ImGui::Text("definitions: null");

            } else if (ImGui::TreeNode("definitions")) {
                for (int k = 0; k < (int)method.ddefinitions.size(); k++) {
                    if (ImGui::TreeNode((void*)(intptr_t)k, "%s", method.ddefinitions[k].name.c_str())) {
                        ImGui::Text("full_type: %s", method.ddefinitions[k].full_type.c_str());
                        if (ImGui::TreeNode("src_info")) {
                            ImGui::Text("col: %d", method.ddefinitions[k].ssrc_info.col);
                            ImGui::Text("file: %s", method.ddefinitions[k].ssrc_info.file.c_str());
                            ImGui::Text("line: %d", method.ddefinitions[k].ssrc_info.line);
                            ImGui::TreePop();
                        }
                        ImGui::Text("type: %s", method.ddefinitions[k].type.c_str());
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
            }

            ImGui::Text("lines: %d", method.lines);
            ImGui::Text("literals: %d", method.literals);
            ImGui::Text("loops: %d", method.loops);
            ImGui::Text("max_scope: %d", method.max_scope);
            ImGui::Text("method_type: %s", method.method_type.c_str());
            ImGui::Text("name: %s", method.name.c_str());
            ImGui::Text("ret_type: %s", method.ret_type.c_str());
            if (ImGui::TreeNode("src_info")) {
                ImGui::Text("col: %d", method.ssrc_info.col);
                ImGui::Text("file: %s", method.ssrc_info.file.c_str());
                ImGui::Text("line: %d", method.ssrc_info.line);
                ImGui::TreePop();
            }
            ImGui::Text("statements: %d", method.statements);
            if (method.template_args.size() == 0) {
                ImGui::Text("template_args: null");
            } else if (ImGui::TreeNode("template_args")) {
                for (int k = 0; k < (int)method.template_args.size(); k++) {
                    ImGui::Text("%s", method.template_args[k].c_str());
                }
                ImGui::TreePop();
            }
            ImGui::Text("virtual: %s", method.vvirtual ? "true" : "false");
            string classname = "Class: " + tree.fullname;
            if (ImGui::BeginMenu(classname.c_str())) {
                tree_menu(tree, from_to_dependencies);
                ImGui::EndMenu();
            }

            mouse_on_popup = ImGui::IsWindowHovered(ImGuiHoveredFlags_RootAndChildWindows);
            ImGui::EndPopup();
        }
    } else if (type == 1) {
        ImGui::OpenPopup(nnamespace.c_str());
        if (ImGui::BeginPopup(nnamespace.c_str(), ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
            const char* namespacestr = "Namespace";
            ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize(namespacestr).x) * 0.5f);
            ImGui::Text("%s", namespacestr);
            ImGui::Text("Name: %s", nnamespace.c_str());
            mouse_on_popup = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
            ImGui::EndPopup();
        }
    } else if (type == 2) {
        ImGui::OpenPopup(methodlesstree.fullname.c_str());
        if (ImGui::BeginPopup(methodlesstree.fullname.c_str(), ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
            tree_menu(methodlesstree, from_to_dependencies);
            mouse_on_popup = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
            ImGui::EndPopup();
        }
    }
}

vector<int> Gui::sizes_branch(int namespace_height, int tree_size, int branch_size,int max_tree_size) {
    static vector<int> values={0,namespace_height,tree_size,branch_size};
    values[0]=0;
    if (!show_sizes_branch) return values;

    bool branch_open = true;
    if (ImGui::Begin("Sizes", &branch_open, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::SliderInt("Namespace height", &values[1], 1, 20);
        ImGui::SliderInt("Tree size", &values[2], 50, max_tree_size);
        if(values[2]<values[3])values[3]=values[2];
        ImGui::SliderInt("Window size", &values[3], 10, values[2]);

        if (ImGui::Button("Apply")) {
            if (values[1] != namespace_height ||values[2] != tree_size ||values[3] != branch_size) {
                values[0] = 1;
            }
        }
        mouse_on_popup = ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow);
        show_sizes_branch = branch_open;
        if(!branch_open)mouse_on_popup=false;

        ImGui::End();
    }
    return values;
}

}