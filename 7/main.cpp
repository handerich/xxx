#include "gun.h"
#include "soldier.h"
#include <iostream>
#include <filesystem>

using namespace std;

void test()
{
    Soldier sanduo("xusanduo");
    sanduo.addGun(new Gun("AK47"));
    sanduo.addBulletToGun(20);
    sanduo.fire();
}

int main()
{
    cout << "This is a test string..." << endl;
    test();
    return 0;
}