#include "stdafx.h"
#include "ParticleSystem_.h"


ParticleSystem_::ParticleSystem_()
{
}

void ParticleSystem_::initSystem()
{
	srand(time(0));
	perTime = 0.01;

	//base setting
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glEnable(GL_DEPTH_TEST);

	//add the origin
	currentNum = 0;
	particles[currentNum++] = Particle(TYPE1, Vector3(0, 0, 0), Vector3(0, 0, 0), 10000, Vector3(0, 0, 0));

	//create vao,vbo
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)4);
	glEnableVertexAttribArray(0);
	//create shader
	std::vector<GLuint> v;
	v.push_back(Shader::createShader(GL_VERTEX_SHADER, "vertexShader.glsl"));
	v.push_back(Shader::createShader(GL_FRAGMENT_SHADER, "fragmentShader.glsl"));
	programId = Shader::createProgram(v);
}

void ParticleSystem_::updateParticles()
{
	int NUM = currentNum;
	for (int i = 0; i < NUM; i++) {
		switch (particles[i].type)
		{
			case TYPE1: 
			{
				//origin create a new particle
				if (currentNum >= MAX_NUM) continue;
				particles[currentNum++] = Particle(TYPE2, Vector3(0, 0, 0), this->getRandVelocity(), this->getRandTime(),this->getRandSpeed());
				break;
			}
			case TYPE2: 
			{
				//normal particle die with more produce
				//minus time and judge whether delete and create
				particles[i].leftTime -= perTime;
				if (particles[i].leftTime <= 0) {
					Vector3 v = particles[i].position;
					particles[i] = particles[--currentNum];
					/*particles[currentNum++] = Particle(TYPE3, v, this->getRandVelocity(), this->getRandTime());
					particles[currentNum++] = Particle(TYPE3, v, this->getRandVelocity(), this->getRandTime());
					particles[currentNum++] = Particle(TYPE3, v, this->getRandVelocity(), this->getRandTime());
					particles[currentNum++] = Particle(TYPE3, v, this->getRandVelocity(), this->getRandTime());*/
				}
				//update the position and speed
				particles[i].speed.x += particles[i].velocity.x*perTime;
				particles[i].speed.y += particles[i].velocity.y*perTime;
				particles[i].speed.z += particles[i].velocity.z*perTime;
				particles[i].position.x += particles[i].speed.x*perTime;
				particles[i].position.y += particles[i].speed.y*perTime;
				particles[i].position.z += particles[i].speed.z*perTime;
				//if get floor
				if (particles[i].position.y <= 0.0) {
					particles[i].position.y = 0.0;
					particles[i].speed.y *= -0.5;
				}
				break;
			}
			case TYPE3:
			{
				//normal particle
				//minus time and judge whether delete
				particles[i].leftTime -= perTime;
				if (particles[i].leftTime <= 0)
					particles[i] = particles[--currentNum];
				//update the position
				particles[i].position.x += particles[i].velocity.x*0.1;
				particles[i].position.y += particles[i].velocity.y*0.1;
				particles[i].position.z += particles[i].velocity.z*0.1;
			}

		}
	}
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(particles), particles);
}

void ParticleSystem_::setView()
{
	GLfloat cameraPos[3] = { 1,2,4 };

	//set view and projection
	GLfloat mat[16];
	Shader::LookAtMatrix(Vector3(cameraPos[0], cameraPos[1], cameraPos[2]), Vector3(0, 0, 0), Vector3(0, 1, 0), mat);
	glUniformMatrix4fv(glGetUniformLocation(programId, "viewMatrix"), 1, GL_FALSE, mat);
	Shader::frustumMatrix(-1, 1, -1, 1, 1, 200, mat);
	glUniformMatrix4fv(glGetUniformLocation(programId, "projectionMatrix"), 1, GL_FALSE, mat);
}

void ParticleSystem_::render()
{
	glUseProgram(programId);
	glBindVertexArray(VAO);
	this->setView();
	glDrawArrays(GL_POINTS, 0, currentNum);
	this->updateParticles();
}


ParticleSystem_::~ParticleSystem_()
{
}

Vector3 ParticleSystem_::getRandVelocity()
{
	/*float randX = rand()*1.0 / RAND_MAX * 2 - 1;
	float randZ = rand()*1.0 / RAND_MAX * 2 - 1;
	return Vector3(randX,0.1,randZ);*/
	return Vector3(0, -1, 0);
}

float ParticleSystem_::getRandTime()
{
	return 15.0;
}

Vector3 ParticleSystem_::getRandSpeed()
{
	float radius = 1;
	const float PI = 3.14;
	float theta = rand() % 315 * 1.0 / 100 * 2;
	return Vector3(radius * cos(theta), 1, radius * sin(theta));
}
