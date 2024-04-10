#include <iostream>


class figure{
	public:
		float x1,y1;
	
};
class cercle:public figure{
	public:
		float radius;
		cercle(float x1,float y1, float radius){
			this->x1=x1;
			this->y1=y1;
			this->radius=radius;
		}
};

class obstacle:public figure{
public:
		float radius;
		obstacle(float x1,float y1, float radius){
			this->x1=x1;
			this->y1=y1;
			this->radius=radius;
		}
		obstacle(){
		}
		
	
};

class target:public figure{
public:
		float radius;
		target(float x1,float y1, float radius){
			this->x1=x1;
			this->y1=y1;
			this->radius=radius;
		}
		target(){
		}
		
	
};

class collider:public figure{
public:
		float radius;
		collider(float x1,float y1, float radius){
			this->x1=x1;
			this->y1=y1;
			this->radius=radius;
		}
		collider(){
		}
		
	
};

class ligne:public figure{
	public:
		float x2,y2;
		ligne(float x1,float y1,float x2,float y2){
			this->x1=x1;
			this->y1=y1;
			this->x2=x2;
			this->y2=y2;
			
		}
		ligne(){
			
		}
};



