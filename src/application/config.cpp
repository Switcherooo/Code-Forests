#include "application.hpp"

namespace application {

void Application::read_from_config() {

    ifstream configfile(CODECITIES_CONFIG_PATH);
    string varname;
    int varvalue;
    char del;

    while ((configfile >> varname >> del >> varvalue) && (del == '=')) {
        if (!varname.compare("namespace_height"))
            namespace_height = varvalue;
        else if (!varname.compare("tree_size"))
            tree_size = varvalue;
        else if (!varname.compare("branch_size"))
            branch_size = varvalue;
        else if (!varname.compare("space_between"))
            space_between = varvalue;
    }

    if (space_between < 50) space_between = 50;
    if (space_between > 1000) space_between = 1000;
    if (namespace_height < 1) namespace_height = 1;
    if (namespace_height > 20) namespace_height = 20;
    if (tree_size < 50) tree_size = 50;
    if (tree_size > space_between) tree_size = space_between;
    if (branch_size < 10) branch_size = 10;
    if (branch_size > tree_size) branch_size = tree_size;
    max_tree_size = tree_size + tree_size / 2;

    configfile.close();
}
}