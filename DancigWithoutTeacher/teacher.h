#pragma once
#include "all.h"
#include <random>

class teacher {
private:
	Texture teacherFrontTexture;
	Texture teacherBackTexture;
	Texture teacherSideTexture;

	Sprite teacherSprite;

	float showTeacherTimer;
	float showTeacherSideTimer;
	bool showTeacher;
	bool showTeacherSide;
	float teacherSideTime;
	float teacherBackTime;
	float teacherFrontTime;

	Clock clock;

	bool isTeacherVisible;

public:
	teacher();

	void teacherTurnTime(float elapsedTime);
};