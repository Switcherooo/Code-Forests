#include "trees.hpp"
#include "groves.hpp"

namespace trees {

Trees::tree btree;
Trees::fields fieldd;
Trees::methods method;
Trees::args arg;
Trees::definitions definition;
vector<Trees::tree> trees;
bool vvirtual;

void add_to_tree(boost::property_tree::ptree& pt, int num) {
    switch (num) {
        case 1:
            btree.bases.push_back(pt.data());
            break;
        case 2:
            btree.contains.push_back(pt.data());
            break;
        case 3:
            btree.friends.push_back(pt.data());
            break;
        case 4:
            btree.name = pt.data();
            break;
        case 5:
            btree.nnamespace = pt.data();
            break;
        case 6:
            btree.nested_parent = pt.data();
            break;
        case 7:
            btree.structure_type = pt.data();
            break;
        case 8:
            btree.template_args.push_back(pt.data());
            break;
        case 9:
            btree.template_parent = pt.data();
            break;
        case 10:
            btree.ffields[btree.ffields.size() - 1].access = pt.data();
            break;
        case 11:
            btree.ffields[btree.ffields.size() - 1].full_type =
                pt.data();
            break;
        case 12:
            btree.ffields[btree.ffields.size() - 1].name = pt.data();
            break;
        case 13:
            btree.ffields[btree.ffields.size() - 1].type = pt.data();
            break;
        case 14:
            btree.ffields[btree.ffields.size() - 1].ssrc_info.col =
                stoi(pt.data());
            break;
        case 15:
            btree.ffields[btree.ffields.size() - 1].ssrc_info.file =
                pt.data();
            break;
        case 16:
            btree.ffields[btree.ffields.size() - 1].ssrc_info.line =
                stoi(pt.data());
            break;
        case 17:
            btree.mmethods[btree.mmethods.size() - 1].access =
                pt.data();
            break;
        case 18:
            btree.mmethods[btree.mmethods.size() - 1].branches =
                stoi(pt.data());
            break;
        case 19:
            btree.mmethods[btree.mmethods.size() - 1].lines =
                stoi(pt.data());
            break;
        case 20:
            btree.mmethods[btree.mmethods.size() - 1].literals =
                stoi(pt.data());
            break;
        case 21:
            btree.mmethods[btree.mmethods.size() - 1].loops =
                stoi(pt.data());
            break;
        case 22:
            btree.mmethods[btree.mmethods.size() - 1].max_scope =
                stoi(pt.data());
            break;
        case 23:
            btree.mmethods[btree.mmethods.size() - 1].method_type =
                pt.data();
            break;
        case 24:
            btree.mmethods[btree.mmethods.size() - 1].name = pt.data();
            break;
        case 25:
            btree.mmethods[btree.mmethods.size() - 1].ret_type =
                pt.data();
            break;
        case 26:
            btree.mmethods[btree.mmethods.size() - 1].statements =
                stoi(pt.data());
            break;
        case 27:
            if (!pt.data().compare("true"))
                btree.mmethods[btree.mmethods.size() - 1].vvirtual =
                    true;
            else
                btree.mmethods[btree.mmethods.size() - 1].vvirtual =
                    false;
            break;
        case 28:
            btree.mmethods[btree.mmethods.size() - 1]
                .aargs[btree.mmethods[btree.mmethods.size() - 1]
                           .aargs.size() -
                       1]
                .full_type = pt.data();
            break;
        case 29:
            btree.mmethods[btree.mmethods.size() - 1]
                .aargs[btree.mmethods[btree.mmethods.size() - 1]
                           .aargs.size() -
                       1]
                .type = pt.data();
            break;
        case 30:
            btree.mmethods[btree.mmethods.size() - 1]
                .aargs[btree.mmethods[btree.mmethods.size() - 1]
                           .aargs.size() -
                       1]
                .ssrc_info.col = stoi(pt.data());
            break;
        case 31:
            btree.mmethods[btree.mmethods.size() - 1]
                .aargs[btree.mmethods[btree.mmethods.size() - 1]
                           .aargs.size() -
                       1]
                .ssrc_info.file = pt.data();
            break;
        case 32:
            btree.mmethods[btree.mmethods.size() - 1]
                .aargs[btree.mmethods[btree.mmethods.size() - 1]
                           .aargs.size() -
                       1]
                .ssrc_info.line = stoi(pt.data());
            break;
        case 33:
            btree.mmethods[btree.mmethods.size() - 1]
                .ddefinitions[btree.mmethods[btree.mmethods.size() - 1]
                                  .ddefinitions.size() -
                              1]
                .full_type = pt.data();
            break;
        case 34:
            btree.mmethods[btree.mmethods.size() - 1]
                .ddefinitions[btree.mmethods[btree.mmethods.size() - 1]
                                  .ddefinitions.size() -
                              1]
                .type = pt.data();
            break;
        case 35:
            btree.mmethods[btree.mmethods.size() - 1]
                .ddefinitions[btree.mmethods[btree.mmethods.size() - 1]
                                  .ddefinitions.size() -
                              1]
                .ssrc_info.col = stoi(pt.data());
            break;
        case 36:
            btree.mmethods[btree.mmethods.size() - 1]
                .ddefinitions[btree.mmethods[btree.mmethods.size() - 1]
                                  .ddefinitions.size() -
                              1]
                .ssrc_info.file = pt.data();
            break;
        case 37:
            btree.mmethods[btree.mmethods.size() - 1]
                .ddefinitions[btree.mmethods[btree.mmethods.size() - 1]
                                  .ddefinitions.size() -
                              1]
                .ssrc_info.line = stoi(pt.data());
            break;
        case 38:
            btree.mmethods[btree.mmethods.size() - 1].ssrc_info.col =
                stoi(pt.data());
            break;
        case 39:
            btree.mmethods[btree.mmethods.size() - 1].ssrc_info.file =
                pt.data();
            break;
        case 40:
            btree.mmethods[btree.mmethods.size() - 1].ssrc_info.line =
                stoi(pt.data());
            break;
        case 41:
            btree.mmethods[btree.mmethods.size() - 1]
                .template_args.push_back(pt.data());
            break;
        case 42:
            btree.ssrc_info.col = stoi(pt.data());
            break;
        case 43:
            btree.ssrc_info.file = pt.data();
            break;
        case 44:
            btree.ssrc_info.line = stoi(pt.data());
            break;
    }
}
std::string indent(int level) {
    std::string s;
    for (int i = 0; i < level; i++) s += "  ";
    return s;
}

int qq = 0;
void get_data_from_json_rec(boost::property_tree::ptree& pt, int level, int parentnum, string parent, int id) {
    add_to_tree(pt, id);
    cout << "-------" << id;
    if (id == -1 || id == -2 || ((id >= 28 && id <= 36))) {
    } else
        id = 0;
    bool q;
    q = true;
    if (pt.empty()) {
        if (q) std::cout << "\"" << pt.data() << "\"";

    }

    else {
        if (q) std::cout << std::endl;

        if (q) std::cout << indent(level) << "{" << std::endl;
        int num = 0;

        for (boost::property_tree::ptree::iterator pos = pt.begin(); pos != pt.end(); num++) {
            if (!pos->first.compare("bases") ||
                !pos->first.compare("contains") ||
                !pos->first.compare("fields") ||
                !pos->first.compare("friends") ||
                !pos->first.compare("methods") ||
                (!pos->first.compare("src_info") && (id == 6 || id == 25)) ||
                !pos->first.compare("template_args") ||
                !pos->first.compare("args") ||
                !pos->first.compare("definitions"))
                id = 0;
            if (!parent.compare("bases")) id = 1;
            if (!parent.compare("contains")) id = 2;
            if (!parent.compare("friends")) id = 3;
            if (!pos->first.compare("name") && num == 5) id = 4;
            if (!pos->first.compare("namespace")) id = 5;
            if (!pos->first.compare("nested_parent")) id = 6;
            if (!pos->first.compare("structure_type")) id = 7;
            if (!parent.compare("template_args") && parentnum == 10) id = 8;
            if (!pos->first.compare("template_parent")) id = 9;
            if (!parent.compare("fields")) {
                fieldd.fullname = pos->first;
                btree.ffields.push_back(fieldd);
            }
            if (!parent.compare(fieldd.fullname)) {
                if (!pos->first.compare("access")) id = 10;
                if (!pos->first.compare("full_type")) id = 11;
                if (!pos->first.compare("name")) id = 12;
                if (!pos->first.compare("type")) id = 13;
            }
            if (!pos->first.compare("col") && parentnum == 3) id = 14;
            if (!pos->first.compare("file") && parentnum == 3) id = 15;
            if (!pos->first.compare("line") && parentnum == 3) id = 16;
            if (!parent.compare("methods")) {
                method.fullname = pos->first;
                btree.mmethods.push_back(method);
            }
            if (!parent.compare(method.fullname)) {
                if (!pos->first.compare("access")) id = 17;
                if (!pos->first.compare("branches")) id = 18;
                if (!pos->first.compare("lines")) id = 19;
                if (!pos->first.compare("literals")) id = 20;
                if (!pos->first.compare("loops")) id = 21;
                if (!pos->first.compare("max_scope")) id = 22;
                if (!pos->first.compare("method_type")) id = 23;
                if (!pos->first.compare("name")) id = 24;
                if (!pos->first.compare("ret_type")) id = 25;
                if (!pos->first.compare("statements")) id = 26;
                if (!pos->first.compare("virtual")) id = 27;
            }
            if (!parent.compare("args")) {
                arg.name = pos->first;
                btree.mmethods[btree.mmethods.size() - 1]
                    .aargs.push_back(arg);
                id = -1;
            }
            if (!parent.compare(arg.name) &&
                (id == -1 || (id >= 28 && id <= 31))) {
                if (!pos->first.compare("name")) id = -1;
                if (!pos->first.compare("full_type")) id = 28;
                if (!pos->first.compare("type")) id = 29;
                if (!pos->first.compare("src_info")) id = -1;
            }
            if (!pos->first.compare("col") && id == -1 && !parent.compare("src_info")) id = 30;
            if (!pos->first.compare("file") && id == 30) id = 31;
            if (!pos->first.compare("line") && id == 31) id = 32;
            if (!parent.compare("definitions")) {
                definition.name = pos->first;
                btree.mmethods[btree.mmethods.size() - 1]
                    .ddefinitions.push_back(definition);
                id = -2;
            }
            if (!parent.compare(definition.name) &&
                (id == -2 || (id >= 33 && id <= 36))) {
                if (!pos->first.compare("name")) id = -2;
                if (!pos->first.compare("full_type")) id = 33;
                if (!pos->first.compare("type")) id = 34;
                if (!pos->first.compare("src_info")) id = -2;
            }
            if (!pos->first.compare("col") && id == -2 && !parent.compare("src_info")) id = 35;
            if (!pos->first.compare("file") && id == 35) id = 36;
            if (!pos->first.compare("line") && id == 36) id = 37;
            if (!pos->first.compare("col") && parentnum == 11) id = 38;
            if (!pos->first.compare("file") && parentnum == 11) id = 39;
            if (!pos->first.compare("line") && parentnum == 11) id = 40;
            if (!parent.compare("template_args") && parentnum == 13)
                id = 41;
            if (!pos->first.compare("col") && parentnum == 8) id = 42;
            if (!pos->first.compare("file") && parentnum == 8) id = 43;
            if (!pos->first.compare("line") && parentnum == 8) id = 44;

            if (!parent.compare("structures")) {
                trees.push_back(btree);
                btree.bases.clear();
                btree.contains.clear();
                btree.ffields.clear();
                btree.friends.clear();
                btree.mmethods.clear();
                btree.template_args.clear();
                btree.fullname = pos->first;

            }

            get_data_from_json_rec(pos->second, level + 1, num, pos->first, id);
            ++pos;

            if (pos != pt.end()) {
                if (q) std::cout << ",";
            }
            if (q) std::cout << std::endl;
        }
        if (q) std::cout << indent(level) << " }";
    }

    if (q) std::cout << std::endl;
    return;
}

void Trees::get_data_from_json(boost::property_tree::ptree& pt, int level, int parentnum, string parent, int id) {
    groves::Groves groves;
    get_data_from_json_rec(pt, level, parentnum, parent, id);
    trees.push_back(btree);
    trees.erase(trees.begin());
    groves.create_namespaces();
}
void Trees::print() {
    for (int i = 0; i < (int)trees.size(); i++) {
        cout << "----------------------------------- " << trees[i].fullname
             << endl;
        cout << "bases: ";
        for (int j = 0; j < (int)trees[i].bases.size(); j++) {
            cout << trees[i].bases[j];
        }
        cout << endl;
        cout << "contains: ";
        for (int j = 0; j < (int)trees[i].contains.size(); j++) {
            cout << trees[i].contains[j];
        }
        cout << endl;
        cout << "fields: ";
        for (int j = 0; j < (int)trees[i].ffields.size(); j++) {
            cout << "+++++++++++ " << trees[i].ffields[j].fullname << endl;
            cout << "++++ access: " << trees[i].ffields[j].access << endl;
            cout << "++++ full_type: " << trees[i].ffields[j].full_type
                 << endl;
            cout << "++++ name: " << trees[i].ffields[j].name << endl;
            cout << "++++ src_info: " << endl;
            cout << "++++=== col: " << trees[i].ffields[j].ssrc_info.col
                 << endl;
            cout << "++++=== file: " << trees[i].ffields[j].ssrc_info.file
                 << endl;
            cout << "++++=== line: " << trees[i].ffields[j].ssrc_info.line
                 << endl;
            cout << "++++ type: " << trees[i].ffields[j].type << endl;
        }
        if (trees[i].ffields.size() == 0) cout << endl;
        cout << "friends: ";
        for (int j = 0; j < (int)trees[i].friends.size(); j++) {
            cout << trees[i].friends[j];
        }
        cout << endl;
        cout << "methods: ";
        for (int j = 0; j < (int)trees[i].mmethods.size(); j++) {
            cout << "]]]]]]]]]]] " << trees[i].mmethods[j].fullname << endl;
            cout << "]]]]] access: " << trees[i].mmethods[j].access << endl;
            cout << "]]]]] args: ";
            for (int k = 0; k < (int)trees[i].mmethods[j].aargs.size(); k++) {
                cout << "]]]]]''''''''''' "
                     << trees[i].mmethods[j].aargs[k].name << endl;
                cout << "]]]]]'''''' full_type: "
                     << trees[i].mmethods[j].aargs[k].full_type << endl;
                cout << "]]]]]''''''=== col: "
                     << trees[i].mmethods[j].aargs[k].ssrc_info.col << endl;
                cout << "]]]]]''''''=== file: "
                     << trees[i].mmethods[j].aargs[k].ssrc_info.file
                     << endl;
                cout << "]]]]]''''''=== line: "
                     << trees[i].mmethods[j].aargs[k].ssrc_info.line
                     << endl;
                cout << "]]]]]'''''' type: "
                     << trees[i].mmethods[j].aargs[k].type << endl;
            }
            if (trees[i].mmethods[j].aargs.size() == 0) cout << endl;
            if (trees[i].mmethods.size() == 0) cout << endl;
            cout << "]]]]] branches: " << trees[i].mmethods[j].branches
                 << endl;
            cout << "]]]]] definitions: ";
            for (int k = 0; k < (int)trees[i].mmethods[j].ddefinitions.size();
                 k++) {
                cout << "]]]]]<<<<<<<<<<<< "
                     << trees[i].mmethods[j].ddefinitions[k].name << endl;
                cout << "]]]]]<<<<<< full_type: "
                     << trees[i].mmethods[j].ddefinitions[k].full_type
                     << endl;
                cout << "]]]]]<<<<<<=== col: "
                     << trees[i].mmethods[j].ddefinitions[k].ssrc_info.col
                     << endl;
                cout << "]]]]]<<<<<<=== file: "
                     << trees[i].mmethods[j].ddefinitions[k].ssrc_info.file
                     << endl;
                cout << "]]]]]<<<<<<=== line: "
                     << trees[i].mmethods[j].ddefinitions[k].ssrc_info.line
                     << endl;
                cout << "]]]]]<<<<<< type: "
                     << trees[i].mmethods[j].ddefinitions[k].type << endl;
            }
            if (trees[i].mmethods[j].ddefinitions.size() == 0) cout << endl;
            cout << "]]]]] lines: " << trees[i].mmethods[j].lines << endl;
            cout << "]]]]] literals: " << trees[i].mmethods[j].literals
                 << endl;
            cout << "]]]]] loops: " << trees[i].mmethods[j].loops << endl;
            cout << "]]]]] max_scope: " << trees[i].mmethods[j].max_scope
                 << endl;
            cout << "]]]]] method_type: "
                 << trees[i].mmethods[j].method_type << endl;
            cout << "]]]]] name: " << trees[i].mmethods[j].name << endl;
            cout << "]]]]] ret_type: " << trees[i].mmethods[j].ret_type
                 << endl;
            cout << "]]]]]=== col: " << trees[i].mmethods[j].ssrc_info.col
                 << endl;
            cout << "]]]]]=== file: " << trees[i].mmethods[j].ssrc_info.file
                 << endl;
            cout << "]]]]]=== line: " << trees[i].mmethods[j].ssrc_info.line
                 << endl;
            cout << "]]]]] statements: " << trees[i].mmethods[j].statements
                 << endl;
            cout << "]]]]]] template_args: ";
            for (int k = 0; k < (int)trees[i].mmethods[j].template_args.size();
                 k++) {
                cout << trees[i].mmethods[j].template_args[k];
            }
            cout << endl;
            cout << "]]]]] vvirtual: " << trees[i].mmethods[j].vvirtual
                 << endl;
        }
        if (trees[i].mmethods.size() == 0) cout << endl;

        cout << "name: " << trees[i].name << endl;
        cout << "namespace: " << trees[i].nnamespace << endl;
        cout << "nested_parent: " << trees[i].nested_parent << endl;
        cout << "src_info: " << endl;
        cout << "=== col: " << trees[i].ssrc_info.col << endl;
        cout << "=== file: " << trees[i].ssrc_info.file << endl;
        cout << "=== line: " << trees[i].ssrc_info.line << endl;
        cout << "structure_type: " << trees[i].structure_type << endl;
        cout << "template_args: ";
        for (int j = 0; j < (int)trees[i].template_args.size(); j++) {
            cout << trees[i].template_args[j];
        }
        cout << endl;
        cout << "template_parent: " << trees[i].template_parent << endl;
    }
}

vector<Trees::tree> Trees::get_trees() { return trees; }

vector<int> Trees::get_sorted_methods(int treeindex) {
    vector<int> sorted_method_indexes;

    for (int i = 0; i < (int)trees[treeindex].mmethods.size(); i++) {
        if (!trees[treeindex].mmethods[i].access.compare("public")) sorted_method_indexes.push_back(i);
    }
    for (int i = 0; i < (int)trees[treeindex].mmethods.size(); i++) {
        if (trees[treeindex].mmethods[i].access.compare("public")) sorted_method_indexes.push_back(i);
    }

    return sorted_method_indexes;
}

}