/* 
 * File:   PoseXML.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on July 26, 2013, 11:28 AM
 */

#include "PoseXML.h"


using namespace std;
 


PoseXML::PoseXML() {
}

struct xml_string_writer: pugi::xml_writer
{
    std::string result;

    virtual void write(const void* data, size_t size)
    {
        result += std::string(static_cast<const char*>(data), size);
    }
};

bool PoseXML::SavePosesList(PosesList & Poses, const string & file , const string & key) {
    ofstream myfile;
    xml_string_writer r;
    pugi::xml_document doc;
    
    remove(file.c_str());
    myfile.open(file.c_str());
    if(myfile.fail()) return false;

    pugi::xml_node PosesNode = doc.append_child("Poses");
    for (list<Pose>::iterator iterator = Poses.begin(), end = Poses.end(); iterator != end; ++iterator) {
        pugi::xml_node TempNode = PosesNode.append_child("Pose");
        TempNode.append_attribute("ID") = ((Pose) * iterator).ID.c_str();
        pugi::xml_node TNode = TempNode.append_child("Value");
        TNode.append_child(pugi::node_pcdata).set_value(((Pose) * iterator).value.c_str());
        TNode = TempNode.append_child("Relations");
        for (int i = MyHelper::ChestFrontSlope; i < MyHelper::AnglesCount; i++) {
            pugi::xml_node RNode = TNode.append_child("Relation");
            RNode.append_attribute("ID") = tostr(i).c_str();
            pugi::xml_node RSNode = RNode.append_child("Active");
            RSNode.append_child(pugi::node_pcdata).set_value((tostr(((Pose) * iterator).PoseAngles[static_cast<MyHelper::AnglesID> (i)].active)).c_str());
            RSNode = RNode.append_child("Accuracy");
            RSNode.append_child(pugi::node_pcdata).set_value((tostr(((Pose) * iterator).PoseAngles[static_cast<MyHelper::AnglesID> (i)].accuracy)).c_str());
            RSNode = RNode.append_child("Direction");
            RSNode.append_child(pugi::node_pcdata).set_value((((Pose) * iterator).PoseAngles[static_cast<MyHelper::AnglesID> (i)].direction.toString()).c_str());
            RSNode = RNode.append_child("Value");
            RSNode.append_child(pugi::node_pcdata).set_value((tostr(((Pose) * iterator).PoseAngles[static_cast<MyHelper::AnglesID> (i)].angle)).c_str());
        }
    }
    doc.save(r);
    myfile << encrypt(reinterpret_cast<const unsigned char*>(r.result.c_str()), r.result.length(), key);
    myfile.close();
    //doc.save_file(file.c_str());
}

bool PoseXML::LoadPosesList(PosesList & Poses, const string & file , const string & key) {
    pugi::xml_document doc;
    string r,input;
    ifstream myfile;
    stringstream ss;
    
    myfile.open(file.c_str());
    if (!myfile.is_open()) return false;
    
    ss << myfile.rdbuf();
    r = ss.str();
    myfile.close();
    ss.clear();
    input = decrypt(r,key);
    r.clear();

    if (!doc.load_buffer(input.c_str(),input.length())) return false;
  
    pugi::xml_node poses = doc.child("Poses");
    for (pugi::xml_node pose = poses.child("Pose"); pose; pose = pose.next_sibling("Pose")) {
        Pose temp;
        temp.ID = pose.attribute("ID").as_string();
        temp.value = pose.child_value("Value");
        pugi::xml_node relations = pose.child("Relations");
        for (pugi::xml_node relation = relations.child("Relation"); relation; relation = relation.next_sibling("Relation")) {
            int relationId = relation.attribute("ID").as_int();
            if(relationId > MyHelper::AnglesCount-1)  break;//need error repot
            temp.PoseAngles[static_cast<MyHelper::AnglesID> (relationId)].accuracy = fromstr<double>(relation.child_value("Accuracy"));
            temp.PoseAngles[static_cast<MyHelper::AnglesID> (relationId)].angle = fromstr<double>(relation.child_value("Value"));
            temp.PoseAngles[static_cast<MyHelper::AnglesID> (relationId)].active = fromstr<bool>(relation.child_value("Active"));
            string nvector = relation.child_value("Direction");
            vector <string> fields;
            split(fields, nvector, ",");
            Vector3f direction;
            if (fields[0] != "nan" && fields[1] != "nan" && fields[2] != "nan") {
                direction.x = fromstr<float>(fields[0]);
                direction.y = fromstr<float>(fields[1]);
                direction.z = fromstr<float>(fields[2]);
            }
            temp.PoseAngles[static_cast<MyHelper::AnglesID> (relationId)].direction = direction;
        }
        Poses.Add(temp);
    }
}

PoseXML::~PoseXML() {
}

