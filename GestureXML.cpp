/* 
 * File:   GestureXML.cpp
 * Author: Nicholas Hadjiminas
 * 
 * Created on July 25, 2013, 11:11 AM
 */

#include "GestureXML.h"

GestureXML::GestureXML() {
}

struct xml_string_writer: pugi::xml_writer
{
    std::string result;

    virtual void write(const void* data, size_t size)
    {
        result += std::string(static_cast<const char*>(data), size);
    }
};

bool GestureXML::SaveGesturesList(GesturesList & Gestures, const string & file , const string & key){
    ofstream myfile;   
    xml_string_writer r;
    pugi::xml_document doc;
    
    remove(file.c_str());
    myfile.open(file.c_str());
    if(myfile.fail()) return false;

    pugi::xml_node GesturesNode = doc.append_child("Gestures");
    for (list<Gesture>::const_iterator iterator = Gestures.begin(), end = Gestures.end(); iterator != end; ++iterator){
    
    pugi::xml_node TempNode = GesturesNode.append_child("Gesture");
         TempNode.append_attribute("ID") = (tostr(((Gesture) * iterator).ID)).c_str();
    pugi::xml_node TNode = TempNode.append_child("Value");
         TNode.append_child(pugi::node_pcdata).set_value(((Gesture) * iterator).value.c_str());     
         TNode = TempNode.append_child("StartPose");
         TNode.append_child(pugi::node_pcdata).set_value(((Gesture) * iterator).StartPose.c_str());  
         TNode = TempNode.append_child("Voice");
         TNode.append_child(pugi::node_pcdata).set_value(((Gesture) * iterator).Voice.c_str()); 
         TNode = TempNode.append_child("EndPose");
         TNode.append_child(pugi::node_pcdata).set_value(((Gesture) * iterator).EndPose.c_str()); 
         TNode = TempNode.append_child("EndPoseHold");
         TNode.append_child(pugi::node_pcdata).set_value((tostr(((Gesture) * iterator).EndPoseHold)).c_str()); 
         TNode = TempNode.append_child("MaxDuration");
         TNode.append_child(pugi::node_pcdata).set_value((tostr(((Gesture) * iterator).MaxDuration)).c_str()); 
    }
    doc.save(r);
    myfile << encrypt(reinterpret_cast<const unsigned char*>(r.result.c_str()), r.result.length(),key);
    myfile.close();
    //doc.save_file(file.c_str());
}

bool GestureXML::LoadGesturesList(GesturesList & Gestures,  const string & file , const string & key){
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
    
    pugi::xml_node gestures = doc.child("Gestures");
    for (pugi::xml_node gesture = gestures.child("Gesture"); gesture; gesture = gesture.next_sibling("Gesture"))
    {
        Gesture temp;
        temp.ID = gesture.attribute("ID").as_string();
        temp.value = gesture.child_value("Value");
        temp.StartPose = gesture.child_value("StartPose");
        temp.Voice = gesture.child_value("Voice");
        temp.EndPose =  gesture.child_value("EndPose");
        temp.EndPoseHold = fromstr<double>(gesture.child_value("EndPoseHold"));
        temp.MaxDuration = fromstr<float>(gesture.child_value("MaxDuration"));
        Gestures.Add(temp);
    }
}

GestureXML::~GestureXML() {
}

