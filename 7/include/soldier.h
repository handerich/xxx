#pragma once
#include <iostream>
#include "gun.h"
using namespace std;

class Soldier
{
public:
    Soldier(string name);
    ~Soldier();
    void addBulletToGun(int num);
    bool fire();
    void addGun(Gun * _ptr_gun);

private:
    string _name;
    Gun * _ptr_gun;

};