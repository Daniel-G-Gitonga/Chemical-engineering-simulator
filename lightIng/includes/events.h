#pragma once
#include <iostream>

enum EventType{NONE = 0, MOUSE_MOVED_EVENT, KEY_PRESSED_EVENT};

class Event{
public:
virtual EventType eventType() const = 0 ;
virtual std::string eventToString() const = 0;

virtual ~Event () {}
};

class MouseEvents: public Event{
public:
 MouseEvents(double x_pos, double y_pos) : x(x_pos), y(y_pos) {}
 EventType   eventType() const override {
    return MOUSE_MOVED_EVENT;
}
 std::string eventToString() const override{
    return "MOUSE_MOVED_";
}

double x = double();
double y = double();


};

class KeyEvents: public Event{
public:
 KeyEvents(int key_pressed, int scancode, int action, int mods) : key_pressed_code(key_pressed), scancode_c(scancode), action_c(action), mods_c(mods){
        }

 int key_pressed_code;
 int scancode_c;
 int action_c;
 int mods_c;
 
EventType   eventType() const override {
    return KEY_PRESSED_EVENT;
}
std::string eventToString() const override{
    return "key  pressed _" ;
}

};