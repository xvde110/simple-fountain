#pragma once
#include "shader.h"
#include <list>
#include <time.h>

#define TYPE1 1
#define TYPE2 2
#define TYPE3 3
#define MAX_NUM 1000

struct Particle {
	//type
	GLint type;
	//position in 3d
	Vector3 position;
	//direction
	Vector3 velocity;
	//lefttime
	float leftTime;
	//speed
	Vector3 speed;
	Particle(int t,Vector3 pos,Vector3 vel,float time,Vector3 sp)
	{
		type = t; position = pos; velocity = vel; leftTime = time; speed = sp;
	}
	Particle(){}
};


class ParticleSystem_
{
public:
	ParticleSystem_();
	void initSystem();
	void updateParticles();
	void setView();
	void render();
	~ParticleSystem_();
private:
	GLuint VAO, VBO;
	GLuint programId;
	Particle particles[MAX_NUM];
	int currentNum;
	float perTime;
	Vector3 getRandVelocity();
	float getRandTime();
	Vector3 getRandSpeed();
};

