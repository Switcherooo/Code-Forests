#ifndef STRUCTURES_TREES_HPP
#define STRUCTURES_TREES_HPP
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
namespace trees {
class Trees {
    public:
    class src_info {
       public:
        int col;
        string file;
        int line;
    };
    class fields {
       public:
        string fullname;
        string access;
        string full_type;
        string name;
        src_info ssrc_info;
        string type;
    };
    class args {
       public:
        string full_type;
        string name;
        src_info ssrc_info;
        string type;
    };
    class definitions {
       public:
        string full_type;
        string name;
        src_info ssrc_info;
        string type;
    };
    class methods {
       public:
        string fullname;
        string access;
        vector<args> aargs;
        int branches;
        vector<definitions> ddefinitions;
        int lines;
        int literals;
        int loops;
        int max_scope;
        string method_type;
        string name;
        string ret_type;
        src_info ssrc_info;
        int statements;
        vector<string> template_args;
        bool vvirtual;
    };

    class tree {
       public:
        string fullname;
        vector<string> bases;
        vector<string> contains;
        vector<fields> ffields;
        vector<string> friends;
        vector<methods> mmethods;
        string name;
        string nnamespace;
        string nested_parent;
        src_info ssrc_info;
        string structure_type;
        vector<string> template_args;
        string template_parent;
    };
    void get_data_from_json(boost::property_tree::ptree& pt, int level, int parentnum, string parent, int id);  // Get structure info from .json file
    void print();
    vector<Trees::tree> get_trees();
    vector<int> get_sorted_methods(int treeindex);  //Sort methods
};
}
#endif
