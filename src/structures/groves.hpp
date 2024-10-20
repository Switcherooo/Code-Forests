#ifndef STRUCTURES_GROVES_HPP
#define STRUCTURES_GROVES_HPP

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
namespace 
{
class Groves {
   public:
    vector<int> make_namespace_sizes();                                                     // return a vector of the size of one side of each grove. indexes are the same as in the vector of namespaces
    int get_base_namespace_size(vector<int> namespace_sizes);                               // return the size of the one big base grove
    vector<int> get_sorted_size_indexes(vector<int> namespace_sizes, int currentdepth);     // return a vector of the namespace indexes sorted decreasing sizes
    int get_namespace_depth(string nnamespace);                                             // get depth of a namespace
    void create_namespaces();                                                               // add all namespaces to a vector and also add each namespace number of trees in a vector. indexes are the same as in the vector of namespaces
    int get_parent_index(string nnamespace);                                                // get the index of the parent of namespace nnamespace
    vector<string> get_namespaces();                                                        // get the vector of the namespaces
    vector<int> get_namespace_num_of_structures();                                          // get the vector of the numbers of trees inside each namespace. indexes are the same as in the vector of namespaces
    int get_num_of_children_namespaces(string nnamespace);                                  // get number of children namespaces of a namespace
    int get_sum_of_two_biggest_namespaces(string nnamespace, vector<int> namespace_sizes);  // get the sum of the 2 biggest namespaces
};
}
#endif