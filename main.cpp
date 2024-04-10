#include <iostream>
#include <graphics.h>
#include <math.h>
#include <conio.h>
#include <dos.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <fstream>
#include "figure.h"
#include <bits/stdc++.h>
#include <sstream>
#include <vector> 
#include <ctime>
#include "obst.h"
#include <cstdlib>

using namespace std;	

	
int main(){
	
	initwindow(600,600,"Robot"); 
    moveto(0,0);          
    setcolor(3);
    srand((time(0)));
  
  	//differentes variables
	float x, y;
	float Rr=0.05;
	float Dx, Dy, Dr;
	float Dt=0.1, D=0.05;
	float Dg, Dd, Rc, alpha,Dalpha,wg=0, wd=0, wr, w0Max=10, Dw0Max=2;
	float R0=0.02;
	float Dist,Disttarget, Vr,foverlap,foverlaptarget;
	int instant=0,in=0;
	float tx=450,ty=300;
	int counter=0;
	char mode;
	float thetangle=0.0;
	int cpt=0;
	
	//vecteur pour stocker les obstacles et les coordonnées du robot
	vector<obstacle> otab;
	otab=obs();
	vector<string> gl;
	
	vector<ligne> lgn;
	
	
	x=180.00;y=300.00;
	//c is the robot
	cercle c= cercle(x,y,30);
	//t is the target
	target t(tx,ty,35);
	//o is the obstacle for automatic
	obstacle o(300,300,35);

	bool targetdestroyed=false;
	bool moveforward=true;
	bool turn=false;
	int p=0;
	
	cout<<"Press M for manual mode, Press A for automatic mode"<<endl;
	while(1){
		cin>>mode;
		if(mode=='m' || mode=='M'){
			break;
		}else if(mode=='a' || mode=='A'){
			break;
		}else cout<<"wrong input try again"<<endl;
	}
		 
		   
	 if(mode=='m' || mode=='M'){
	 
	while(1){
	setactivepage(p);
	setvisualpage(1-p);
	cleardevice();
	
	//pour afficher les obstacles 
	for(int i=0;i<otab.size();i++){
		setcolor(RED);
		circle(otab.at(i).x1,otab.at(i).y1,otab.at(i).radius);
		//nom et numéro de l'obstacle
		string txt="obs:";
		std::ostringstream oss;
		oss << txt << i;
		string pl=oss.str(); 
		outtextxy(otab.at(i).x1,otab.at(i).y1,(char*)pl.c_str());
		if(inCollision(c,otab.at(i))==true) {
	 		cout<<"cercle is in collision with obstacle num: "<<i<<endl;
		
			Dist=sqrt((c.x1-otab.at(i).x1)*(c.x1-otab.at(i).x1)+(c.y1-otab.at(i).y1)*(c.y1-otab.at(i).y1));
			foverlap= 0.5*(Dist- c.radius - otab.at(i).radius);
			
			c.x1-=foverlap*(c.x1-otab.at(i).x1)/Dist;
			c.y1-=foverlap*(c.y1-otab.at(i).y1)/Dist;
			
			wd=0;wg=0;
			}
		if(inCollision(t,otab[i])==true) {
			//pour etre sure que la cible ne soit pas dans un obstacle
			Disttarget=sqrt((t.x1-otab.at(i).x1)*(t.x1-otab.at(i).x1)+(t.y1-otab.at(i).y1)*(t.y1-otab.at(i).y1));
			foverlaptarget= 0.5*(Disttarget- t.radius - otab.at(i).radius);
			
			t.x1-=foverlaptarget*(t.x1-otab.at(i).x1)/Disttarget;
			t.y1-=foverlaptarget*(t.y1-otab.at(i).y1)/Disttarget;
			
			
			}
		}
		
		
	//cible t
	setcolor(YELLOW);
	circle(t.x1,t.y1,t.radius);
	if(targetdestroyed==false) {
	outtextxy(t.x1,t.y1,"target");
	}if(inCollision(c,t)==true){
		//si il y'a collision on génère une nouvelle cible
		int h=0;
		int randX = rand()%(550-50 + 1) +50;
		int randY = rand()%(550-50 + 1) +50;
	
		t.x1=randX;t.y1=randY;
	
	targetdestroyed=true;
		
	}if(targetdestroyed==true){
		outtext("Target Destroyed!");
		targetdestroyed=false;
	}
	
	
	


 if(GetKeyState(VK_UP) & 0x8000) {
	//to move forth

	moveforward=true;
	cout<<"key up"<<endl;
	wd+=2; if(wd>w0Max) wd=w0Max;
	wg+=2; if(wg>w0Max) wg=w0Max;

	cout<<"wd:" <<wd << " wg:" <<wg <<endl;
    cout<<c.x1<<" : "<<c.y1<<endl;
	cout<<"dd: "<<Dd<<" dg: "<<Dg<<endl;
 
	}
	else if(GetKeyState(VK_DOWN) & 0x8000) {
	//to move back
	moveforward=false;
	cout<<"key down"<<endl;
	wd-=2; if(wd<-10) wd=-10;
	wg-=2; if(wg<-10) wg=-10;

	cout<<"wd:" <<wd << " wg:" <<wg <<endl;
    cout<<c.x1<<" : "<<c.y1<<endl;
	cout<<"dd: "<<Dd<<" dg: "<<Dg<<endl;
 	 }
	 else if(GetKeyState(VK_LEFT) & 0x8000) {
	 	
	 	//to rotate LEFT
	 turn=true;	
	 	cout<<"key LEFT"<<endl;
	 if(turn==true){
	 	wg+=0.003;	if(wd<-10) wd=-10;
		wd-=0.003; if(wg>w0Max) wg=w0Max;
	 	turn=false;
	 
	 }
	 } 
	 else if(GetKeyState(VK_RIGHT) & 0x8000) {
	 	//to rotate RIGHT
	 	cout<<"key RIGHT"<<endl;
	 
	wg-=0.003; if(wg<-10) wg=-10;
	wd+=0.003; if(wd>w0Max) wd=w0Max;

	 }
	 
	Dt=0.1;
	Dd=wd*Dt*R0; Dg=wg*Dt*R0;
	Dr=(Dd+Dg)/2;
	Dalpha=(Dd-Dg)/D;
	Rc=(D*(Dd+Dg))/(2*(Dd-Dg));
	alpha=alpha+Dalpha;
	Vr=Dr/Dt;
	wr=Dalpha/Dt;
	Dr=pow((R0/2)*(wg*cos(alpha)+wd*cos(alpha)),2) +pow((R0/2)*(wg*sin(alpha)+wd*sin(alpha)),2);
	 
    Dx =Dr*cos(alpha);
	Dy =Dr*sin(alpha);
	
	//on verifie si le robot avance ou recule
	if(moveforward==true){
		c.x1+=Dx;c.y1+=Dy;
	}
	else{
	c.x1-=Dx;c.y1-=Dy;
	} 
	
	//ligne qui montre le sens du robot
	line(c.x1, c.y1, c.x1+c.radius*cos(alpha), c.y1+c.radius*sin(alpha));
	setcolor(3);
	circle(c.x1,c.y1,c.radius);
	
	setcolor(WHITE);
	
	//points qui montrent les dernières positions du robot
	ligne lg(c.x1, c.y1, c.x1+1, c.y1+1);
	
	if(cpt>100){
		lgn.push_back(lg);
		cpt=0;	
	}
	if(lgn.size()>50) lgn.erase(lgn.begin());
	
	for(int i=0;i<lgn.size();i++){
		line(lgn.at(i).x1,lgn.at(i).y1,lgn.at(i).x2,lgn.at(i).y2);
	}
	
	
	//les x et y du robot
	std::ostringstream oss;
	oss <<"x:"<< c.x1<<" y:"<<c.y1;
	string pl=oss.str(); 
	outtextxy(400,10,(char*)pl.c_str());
		
	//les vitesses du robot
	std::ostringstream osss;
	osss <<"wg:"<< wg<<" wd:"<<wd;
	string pl1=osss.str(); 
	outtextxy(400,20,(char*)pl1.c_str());
	
	//on insere les coordonnées du robot dans le vecteur	
	std::ostringstream os1;
	os1 <<" X: "<<c.x1<<" Y: "<<c.y1<<" VDG: "<<w0Max<<" VDD: "<<w0Max<<" WG: "<<wg<<" WD: "<<wd;
	string pld=os1.str(); 
		
	gl.push_back(pld);
	if(in>1000){
		gl.erase(gl.begin());
		in--;
	}
	p=1-p;
	instant++;in++;cpt++;
	
	if(GetKeyState(VK_SPACE)& 0x8000) break;
	delay(0);	 
	}
}

else if(mode=='a' || mode=='A'){
		while(1){
	setactivepage(p);
	setvisualpage(1-p);
	cleardevice();
	collider coll(c.x1,c.y1,33);

	
	setcolor(YELLOW);
	circle(t.x1,t.y1,t.radius);
	if(targetdestroyed==false) {
	outtextxy(t.x1,t.y1,"target");
	}if(inCollision(c,t)==true){
		t.x1=t.y1=t.radius=0;
	targetdestroyed=true;
	
		
	}if(targetdestroyed==true){
		outtext("Target Destroyed!");
		
	}
	setcolor(RED);
	circle(o.x1,o.y1,o.radius);
	if(inCollision(c,o)==true) {
	 cout<<"cercle is in collision with obstacle "<<endl;
		
			Dist=sqrt((c.x1-o.x1)*(c.x1-o.x1)+(c.y1-o.y1)*(c.y1-o.y1));
			foverlap= 0.5*(Dist- c.radius - o.radius);
			
			c.x1-=foverlap*(c.x1-o.x1)/Dist;
			c.y1-=foverlap*(c.y1-o.y1)/Dist;
			
			wd=0;wg=0;
		}
		
	


    Dt=0.1;
	Dd=wd*Dt*R0; Dg=wg*Dt*R0;
	Dr=(Dd+Dg)/2;
	Dalpha=(Dd-Dg)/D;
	Rc=(D*(Dd+Dg))/(2*(Dd-Dg));
	alpha=alpha+Dalpha;
	Vr=Dr/Dt;
	wr=Dalpha/Dt;
	Dr=pow((R0/2)*(wg*cos(alpha)+wd*cos(alpha)),2) +pow((R0/2)*(wg*sin(alpha)+wd*sin(alpha)),2);
	 
    Dx =Dr*cos(alpha);
	Dy =Dr*sin(alpha);
	
	Vector2D<double> p1(c.x1,c.y1);
    Vector2D<double> p2(t.x1, t.y1);
	Vector2D<double> p3(c.x1+c.radius*cos(alpha),c.y1+c.radius*sin(alpha));
  
	 
	float thetangle=  Vector2D<double>::angle(p2-p1, p3-p1);
	
	static int k=0;
	
	
	cout<<"thetangle: "<<thetangle<<"  k: "<<k<<endl;

		if(inCollision(coll,o)==true) {
			k=0;
			if(thetangle==0&k==0){
            		wd=0;	if(wg<-10) wg=-10;
					wg-=1; if(wd>w0Max) wd=w0Max;
				}
				else if(thetangle<1.5708){
                	wd=0;	if(wg<-10) wg=-10;
					wg-=1; if(wd>w0Max) wd=w0Max;
				}
				else  if(thetangle>1.5708&k<50){
					wd=wg=10;
					k++;
				}
				else{
					wd=wg=0;
				}	
			}
			else{
				if(thetangle<=0.1){
						wg=wd=10;
						}
				else if(thetangle!=0&k<400){
						wg=wd=10;
						k++;
						}
				else if(thetangle!=0&k==400){
                        if(thetangle>0.1){
                        	wd=1;
							wg=0;
						}
						else{
							wd=wg=0;
						}	
					}  
}
 		c.x1 += Dx;
		c.y1 += Dy;
		
		setcolor(YELLOW);
		line(c.x1, c.y1, c.x1+c.radius*cos(alpha), c.y1+c.radius*sin(alpha));
		setcolor(3);
	 	circle(c.x1,c.y1,c.radius);
	 
			setcolor(WHITE);
	
	//points qui montrent les dernières positions du robot
	ligne lg(c.x1, c.y1, c.x1+1, c.y1+1);
	
	if(cpt>100){
		lgn.push_back(lg);
		cpt=0;	
	}
	if(lgn.size()>50) lgn.erase(lgn.begin());
	
	for(int i=0;i<lgn.size();i++){
		line(lgn.at(i).x1,lgn.at(i).y1,lgn.at(i).x2,lgn.at(i).y2);
	}
	

		
		//les x et y du robot
		std::ostringstream oss;
		oss <<"x:"<< c.x1<<" y:"<<c.y1;
		string pl=oss.str(); 
		outtextxy(400,10,(char*)pl.c_str());
		
		//les vitesses du robot
		std::ostringstream osss;
		osss <<"wg:"<< wg<<" wd:"<<wd;
		string pl1=osss.str(); 
		outtextxy(400,20,(char*)pl1.c_str());
		
		//on insere les coordonnées du robot dans le vecteur	
		std::ostringstream os1;
		os1 <<" X: "<<c.x1<<" Y: "<<c.y1<<" VDG: "<<w0Max<<" VDD: "<<w0Max<<" WG: "<<wg<<" WD: "<<wd;
		string pld=os1.str(); 
		
		gl.push_back(pld);
		if(in>1000){
			gl.erase(gl.begin());
			in--;
		}
	p=1-p;
	instant++;in++;cpt++;
	if(GetKeyState(VK_SPACE)& 0x8000) break;
	delay(0);	 
	}
}
	//on insère les dernières coordonnées du robot dans un fichier .pts (1000 dernieres coordonnées maximum)
	ofstream MyFile;
  	MyFile.open("points.pts");
  	for(int i=0;i<gl.size();i++) {
  	std::ostringstream os4;
	os4 <<"instant: "<<i;
	string pldw=os4.str(); 
	
	string sdf= pldw +gl.at(i);
	MyFile << sdf<<endl;	
  	}
  	
	MyFile.close();
	
	return 0;
}

