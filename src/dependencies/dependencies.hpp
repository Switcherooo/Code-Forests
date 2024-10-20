#ifndef DEPENDENCIES_HPP
#define DEPENDENCIES_HPP
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#ifdef _MSC_VER
#include <boost/config/compiler/visualc.hpp>
#endif


#include <boost/foreach.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>
#include <string>
#include <vector>


using namespace std;
namespace dependencies {
class Dependencies {
   public:
    class dependency {
       public:
        string from;
        string to;
        vector<pair<string, int>> types;
    };
    void get_data_from_json(boost::property_tree::ptree& pt, int level, string parent, int id);  //Get dependencies from .json file
    vector<Dependencies::dependency> get_dependencies();                                         //Returns dependency vector
    pair<vector<string>, vector<string>> get_dependencies_of_tree(string treename);              //Get inbound and outbound dependencies of a given tree
};
}
#endif