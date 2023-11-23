#include "all.h"
#include "student.h"

student::student() {
    studentBasic.loadFromFile("image/Stu.png");
    student1Front.loadFromFile("image/Stu1-1.png");
    student1Back.loadFromFile("image/Stu1-2.png");
    student2Front.loadFromFile("image/Stu2-1.png");
    student2Back.loadFromFile("image/Stu2-2.png");
    student3Front.loadFromFile("image/Stu3-1.png");
    student3Back.loadFromFile("image/Stu3-2.png");
}

void student::initiallize() {
    student1Sprite.setTexture(student1Front);
    student2Sprite.setTexture(student2Front);
    student3Sprite.setTexture(student3Front);

    student1Sprite.setPosition(85, 430);
    student1Sprite.setScale(1.8, 2.0);

    student2Sprite.setPosition(550, 430);
    student2Sprite.setScale(1.8, 2.0);

    student3Sprite.setPosition(1015, 430);
    student3Sprite.setScale(1.8, 2.0);

    studentTime = 0.0f;
}

void student::studentMove(float elapsedTime, bool isTeacherVisible) {
    if (!isTeacherVisible) {
        studentTime += elapsedTime;
        if (studentTime > 0.2) {
            student1Sprite.setTexture(student1Back);
            student2Sprite.setTexture(student2Back);
        }

        if (studentTime > 0.4) {
            student1Sprite.setTexture(student1Front);
            student2Sprite.setTexture(student2Front);
            studentTime = 0.0;
        }
    }
    else {
        student1Sprite.setTexture(studentBasic);
        student2Sprite.setTexture(studentBasic);
    }
}

void student::isSpaceStudent(float spaceTime) {
    if (spaceTime > 0.2) {
        student3Sprite.setTexture(student3Front);
    }

    if (spaceTime > 0.4) {
        student3Sprite.setTexture(student3Back);
    }
}


void student::isNotSpaceStudent() {
    student3Sprite.setTexture(studentBasic);
}

Sprite student::getStudent1Sprite() {
    return student1Sprite;
}

Sprite student::getStudent2Sprite() {
    return student2Sprite;
}

Sprite student::getStudent3Sprite() {
    return student3Sprite;
}