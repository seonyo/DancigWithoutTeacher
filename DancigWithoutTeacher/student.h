#pragma once
#include "all.h"

class student {
private:
    Texture studentBasic;
    Texture student1Front;
    Texture student1Back;
    Texture student2Front;
    Texture student2Back;
    Texture student3Front;
    Texture student3Back;

    Sprite student1Sprite;
    Sprite student2Sprite;
    Sprite student3Sprite;

    float studentTime;

public:
    student();
    void initiallize();
    void studentMove(float elapsedTime, bool isTeacherVisible);
    void isSpaceStudent(float spaceTime);
    void isNotSpaceStudent();
    Sprite getStudent1Sprite();
    Sprite getStudent2Sprite();
    Sprite getStudent3Sprite();

};