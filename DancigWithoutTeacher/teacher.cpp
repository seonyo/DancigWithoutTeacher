#pragma once
#include "all.h"
#include "teacher.h"

teacher::teacher(){
	teacherFrontTexture.loadFromFile("image/SMS.png");
	teacherBackTexture.loadFromFile("image/SMS_Back");
	teacherSideTexture.loadFromFile("image/SMS_Side");

	teacherSprite.setTexture(teacherBackTexture);
	teacherSprite.setPosition(1200, 80);
	teacherSprite.setScale(1.3, 1.4);

	showTeacher = false;
	showTeacherTimer = 0.0f;
	showTeacherSideTimer = 0.0f;
	showTeacherSide = false;
	teacherSideTime = 0.25f;

    isTeacherVisible = false;
}

void teacher::teacherTurnTime(float elapsedTime) {
    if (!showTeacher && showTeacherTimer >= teacherBackTime) {
        showTeacher = true;
        teacherSprite.setTexture(teacherSideTexture);
        showTeacherTimer = 0.0f;

        if (!showTeacherSide) {
            showTeacherSide = true;
            showTeacherSideTimer = 0.0f;
        }
    }

    showTeacherTimer += elapsedTime;

    if (showTeacherSide) {
        showTeacherSideTimer += elapsedTime;
    }

    if (showTeacherSide && showTeacherSideTimer >= teacherSideTime) {
        teacherSprite.setTexture(teacherFrontTexture);
        showTeacherSide = false;
        isTeacherVisible = true;
    }

    if (showTeacher && showTeacherTimer >= teacherFrontTime) {
        showTeacher = false;
        isTeacherVisible = false;
        teacherSprite.setTexture(teacherBackTexture);
        showTeacherTimer = 0.0f;
    }

}