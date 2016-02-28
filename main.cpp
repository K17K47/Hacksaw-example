/*
 * main.cpp
 *
 *  Created on: 01/11/2014
 *      Author: K17K47
 */

#include<iostream>
#include<hacksaw.h>
#include<rndr/scene.h>
#include<rndr/object.h>
#include<rndr/model.h>
#include<hserr.h>
#include<GLFW.h>
#include<string>
#include<mathHelper.h>

int main(){
	std::cout<<"Initiating Hacksaw\n";

	GLubyte imageData[64][64][3];

	int value;
	for (int row = 0; row < 64; row++) {
			for (int col = 0; col < 64; col++) {
				// Each cell is 8x8, value is 0 or 255 (black or white)
				value = (((row & 0x8) == 0) ^ ((col & 0x8) == 0)) * 255;
				imageData[row][col][0] = (GLubyte)value;
				imageData[row][col][1] = (GLubyte)value;
				imageData[row][col][2] = (GLubyte)value;
			}
	}

	Rndr::glRndr renderer;
	renderer.glInit();

	CLcntxt opencl;
	opencl.init();

	Vector3 vertices[]={Vector3(-1.0,-1.0,0.0), Vector3(1.0,-1.0,0.0), Vector3(0.0, 1.0, 0.0)};
	unsigned int indices[]={0,1,2};
	Vector2 tCoords[]={Vector2(0.0,0.0),Vector2(0.0,4.0),Vector2(2.0,2.0)};

	//Vector3 (*v)[3]=&vertices;
	//unsigned int (*i)[3]=&indices;
	Rndr::Model modelo(3,1,&indices[0],&vertices[0],(Vector3*)0,&tCoords[0], &imageData[0][0][0]);
	Rndr::Object objeto;
	objeto.model=&modelo;
	Vector3 shit(0.0,0.0,0.0);
	double rotation=0.5;
	//Quaternion rot(0.883,0.306,-0.176,0.306);
	Quaternion rot;
	rot=AngleAxis(rotation, Vector3::UnitY());
	objeto.pos=&shit;//&zero;
	objeto.rot=&rot;
	Rndr::Camera cameracena(Vector3(0.0,0.0,-1.0), Quaternion());
	Rndr::Scene cena;
	cena.nObjects=0;
	cena.addObject(&objeto);
	cena.addCamera(&cameracena);
	cena.setActiveCamera(&cameracena);
	renderer.chgScene(&cena);

	real fps=glfwGetTime();
	real timer=fps;
	while(!GLFW::instance()->mayWindowClose(renderer.windowIndex)){
		renderer.render();
		timer=timer+(glfwGetTime()-fps);
		fps=1.0/(glfwGetTime()-fps);
		if(timer>0.5){
			timer=0.0;
			GLFW::instance()->chgWindowTitle(renderer.windowIndex,"FPS:"+std::to_string(fps));
		}
		rotation+=0.001;
		rot=AngleAxis(rotation, Vector3::UnitX())*AngleAxis(rotation, Vector3::UnitY())*AngleAxis(rotation, Vector3::UnitZ());
		fps=glfwGetTime();
	}

	GLFW::instance()->terminate();

	return 0;

}


