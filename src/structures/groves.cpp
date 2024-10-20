#include "groves.hpp"
#include "trees.hpp"

namespace groves {

vector<string> namespaces;
vector<int> namespace_num_of_structures;
    trees::Trees trees;

void Groves::create_namespaces() {
    bool alreadyin = 0;
    for (int i = 0; i < (int)trees.get_trees().size(); i++) {
        for (int j = 0; j < (int)namespaces.size(); j++) {
            if ((!namespaces[j].compare(trees.get_trees()[i].nnamespace))) {
                namespace_num_of_structures[j]++;
                alreadyin = 1;
                break;
            }
        }
        if (!alreadyin) {
            namespaces.push_back(trees.get_trees()[i].nnamespace);
            namespace_num_of_structures.push_back(1);
        }
        alreadyin = 0;
    }
}

int Groves::get_sum_of_two_biggest_namespaces(string nnamespace, vector<int> namespace_sizes) {
    int biggest = 0;
    int secondbiggest = 0;
    for (int i = 0; i < (int)namespace_sizes.size(); i++) {
        if (get_namespace_depth(get_namespaces()[i]) == get_namespace_depth(nnamespace) + 1 && ((int)get_namespaces()[i].find(nnamespace) != -1 || !nnamespace.compare("base"))) {
            if (namespace_sizes[i] > biggest) {
                secondbiggest = biggest;
                biggest = namespace_sizes[i];
            } else if (namespace_sizes[i] > secondbiggest)
                secondbiggest = namespace_sizes[i];
        }
    }
    return biggest + secondbiggest;
}
vector<int> Groves::make_namespace_sizes() {
    int currentdepth = 0, max;
    int value = 0;
    vector<int> namespace_sizes;
    namespace_sizes.resize(get_namespaces().size());
    for (int i = 0; i < (int)get_namespaces().size(); i++) {
        if (get_namespace_depth(get_namespaces()[i]) > currentdepth)
            currentdepth = get_namespace_depth(get_namespaces()[i]);
    }
    max = currentdepth;
    while (currentdepth > -1) {
        for (int i = 0; i < (int)get_namespaces().size(); i++) {
            if (get_namespace_depth(get_namespaces()[i]) == currentdepth && currentdepth == max) {
                value = ceil(sqrt(get_namespace_num_of_structures()[i]));
                namespace_sizes[i] = value;
            } else if (get_namespace_depth(get_namespaces()[i]) == currentdepth) {
                for (int j = 0; j < (int)get_namespaces().size(); j++) {
                    if (get_namespace_depth(get_namespaces()[j]) == currentdepth + 1 && (int)get_namespaces()[j].find(get_namespaces()[i]) != -1) {
                        if (namespace_sizes[j] == 0)
                            value += pow(ceil(sqrt(get_namespace_num_of_structures()[j])), 2) + 1;
                        else
                            value += pow(namespace_sizes[j], 2) + 1;
                    }
                }
                value += get_namespace_num_of_structures()[i];
                value = ceil(sqrt(value));
                if (value > get_sum_of_two_biggest_namespaces(get_namespaces()[i], namespace_sizes))
                    namespace_sizes[i] = value;
                else
                    namespace_sizes[i] = get_sum_of_two_biggest_namespaces(get_namespaces()[i], namespace_sizes);
            }
            value = 0;
        }
        currentdepth--;
    }
    return namespace_sizes;
}

int Groves::get_base_namespace_size(vector<int> namespace_sizes) {
    float value = 0;
    for (int i = 0; i < (int)get_namespaces().size(); i++) {
        if (get_parent_index(get_namespaces()[i]) == -1) {
            value += pow(namespace_sizes[i], 2);
        }
    }

    value = ceil(value / 8);
    if (value > get_sum_of_two_biggest_namespaces("base", namespace_sizes))
        return value;
    else
        return get_sum_of_two_biggest_namespaces("base", namespace_sizes);
}
vector<int> Groves::get_sorted_size_indexes(vector<int> namespace_sizes, int currentdepth) {
    int currentmax = 0, indexes_found = 0, grovesindepth = 0;
    vector<int> sorted_size_indexes;
    for (int i = 0; i < (int)namespace_sizes.size(); i++) {
        if (namespace_sizes[i] > currentmax) currentmax = namespace_sizes[i];
        if (get_namespace_depth(get_namespaces()[i]) == currentdepth) grovesindepth++;
    }
    while (indexes_found != grovesindepth) {
        for (int i = 0; i < (int)namespace_sizes.size(); i++) {
            if (namespace_sizes[i] == currentmax && get_namespace_depth(get_namespaces()[i]) == currentdepth) {
                sorted_size_indexes.push_back(i);
                indexes_found++;
            }
        }
        currentmax--;
    }

    return sorted_size_indexes;
}
int Groves::get_namespace_depth(string nnamespace) {
    int count = 0;
    for (int i = 0; i < (int)nnamespace.size(); i++) {
        if (nnamespace[i] == ':') count++;
    }
     if (nnamespace.size()==0) return 1;
    return count / 2;
}
int Groves::get_parent_index(string nnamespace) {
    int currentdepth = get_namespace_depth(nnamespace);
    if (currentdepth <= 1) return -1;
    for (int i = 0; i < (int)namespaces.size(); i++) {
        if (get_namespace_depth(namespaces[i]) == currentdepth - 1 && (int)nnamespace.find(namespaces[i]) != -1)
            return i;
    }
    return -1;
}
vector<string> Groves::get_namespaces() { return namespaces; }
vector<int> Groves::get_namespace_num_of_structures() {
    return namespace_num_of_structures;
}
int Groves::get_num_of_children_namespaces(string nnamespace) {
    int count = 0;
    for (int i = 0; i < (int)namespaces.size(); i++) {
        if (get_parent_index(namespaces[i]) != -1)
            if (!namespaces[get_parent_index(namespaces[i])].compare(nnamespace)) count++;
    }
    return count;
}

}