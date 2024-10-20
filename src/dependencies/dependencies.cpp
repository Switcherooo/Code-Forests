#include "dependencies.hpp"


namespace dependencies {

Dependencies::dependency ddependency;
vector<Dependencies::dependency> dependencies;
pair<string, int> type;

void add_to_dependency(boost::property_tree::ptree& pt, int num) {
    switch (num) {
        case 1:
            ddependency.from = pt.data();
            break;
        case 2:
            ddependency.to = pt.data();
            break;
        case 3:
            type.second = stoi(pt.data());
            ddependency.types.push_back(type);
            break;
    }
}

void get_data_from_json_rec(boost::property_tree::ptree& pt, int level, string parent, int id) {
    add_to_dependency(pt, id);
    cout << "-------" << id;
    if (id == -1 || id == -2 || ((id >= 28 && id <= 36))) {
    } else
        id = 0;
    int num = 0;

    for (boost::property_tree::ptree::iterator pos = pt.begin();
         pos != pt.end(); num++) {
        if (!pos->first.compare("types")) id = 0;
        if (!pos->first.compare("from")) id = 1;
        if (!pos->first.compare("to")) id = 2;
        if (!parent.compare("types")) {
            type.first = pos->first;
            id = 3;
        }
        if (!parent.compare("dependencies")) {
            dependencies.push_back(ddependency);
            ddependency.types.clear();
        }

        get_data_from_json_rec(pos->second, level + 1, pos->first, id);
        ++pos;

    }

    return;
}

void Dependencies::get_data_from_json(boost::property_tree::ptree& pt, int level, string parent, int id) {
    get_data_from_json_rec(pt, level, parent, id);
    dependencies.push_back(ddependency);
    dependencies.erase(dependencies.begin());
    for (int i = 0; i < (int)dependencies.size(); i++) {
        cout << "from: " << dependencies[i].from << endl;
        cout << "to: " << dependencies[i].to << endl;
        cout << "types: ";
        for (int j = 0; j < (int)dependencies[i].types.size(); j++) {
            cout << dependencies[i].types[j].first << ":" << dependencies[i].types[j].second;
        }
        cout << endl;
    }
}

vector<Dependencies::dependency> Dependencies::get_dependencies() {
    return dependencies;
}

pair<vector<string>, vector<string>> Dependencies::get_dependencies_of_tree(string treename) {
    pair<vector<string>, vector<string>> from_to_dependencies;
    for (int i = 0; i < (int)dependencies.size(); i++) {
        if (!treename.compare(dependencies[i].to)) from_to_dependencies.first.push_back(dependencies[i].from);
        if (!treename.compare(dependencies[i].from)) from_to_dependencies.second.push_back(dependencies[i].to);
    }
    return from_to_dependencies;
}
}