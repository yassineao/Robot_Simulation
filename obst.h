#include <iostream>
#include<fstream>
#include <cstring>
#include <stdlib.h>
#include <vector> 
using namespace std;

	vector<obstacle>  obs(){
	//	string f[13];
		vector<string>f;
		string linex="";
		
	vector<obstacle> otab;
	int vx=0;int i=0;
	ifstream file("obstacle.obs");
	while(getline(file,linex)){
		f.push_back(linex);
		vx++;
	}
	while(i<f.size()){
		char tb[15];
		strcpy(tb,f.at(i).c_str());
		
		int cpt=0;	
		obstacle d;
		otab.push_back(d);
		for(int j=0;j<13;j++){
			string x="",y="",radius="";
			if(tb[j]==' ' &&cpt==0){
				x.append(1,tb[j-3]);
				x.append(1,tb[j-2]);
				x.append(1,tb[j-1]);
				otab.at(i).x1=  ::atof(x.c_str());
				cpt++;
			}else if(tb[j]==' ' &&cpt==1){
				y.append(1,tb[j-3]);
				y.append(1,tb[j-2]);
				y.append(1,tb[j-1]);
				otab.at(i).y1=  ::atof(y.c_str());
				
				radius.append(1,tb[j+1]);
				radius.append(1,tb[j+2]);
				radius.append(1,tb[j+3]);
				otab.at(i).radius=  ::atof(radius.c_str());
				cpt++;
			}
		}
		i++;
	}
	return otab;
	}
	
		
		bool inCollision(cercle c, obstacle o){
			if(sqrt((c.x1-o.x1)*(c.x1-o.x1) + (c.y1-o.y1)*(c.y1-o.y1))<= c.radius+o.radius){
				return true;
			}else return false;
		}
		
		bool inCollision(cercle c, target o){
			if(sqrt((c.x1-o.x1)*(c.x1-o.x1) + (c.y1-o.y1)*(c.y1-o.y1))<= c.radius+o.radius){
				return true;
			}else return false;
		}

		bool inCollision(target c, obstacle o){
			if(sqrt((c.x1-o.x1)*(c.x1-o.x1) + (c.y1-o.y1)*(c.y1-o.y1))<= c.radius+o.radius){
				return true;
			}else return false;
		}

		bool inCollision(collider c, obstacle o){
			if(sqrt((c.x1-o.x1)*(c.x1-o.x1) + (c.y1-o.y1)*(c.y1-o.y1))<= c.radius+o.radius){
				return true;
			}else return false;
		}
		
		
	
	template <typename T> class Vector2D{
private:
    T x;
    T y;

public:
    explicit Vector2D(const T& x=0, const T& y=0) : x(x), y(y) {}
    Vector2D(const Vector2D<T>& src) : x(src.x), y(src.y) {}
    virtual ~Vector2D() {}

    // Accessors
    inline T X() const { return x; }
    inline T Y() const { return y; }
    inline T X(const T& x) { this->x = x; }
    inline T Y(const T& y) { this->y = y; }

    // Vector arithmetic
    inline Vector2D<T> operator-() const
        { return Vector2D<T>(-x, -y); }

    inline Vector2D<T> operator+() const
        { return Vector2D<T>(+x, +y); }

    inline Vector2D<T> operator+(const Vector2D<T>& v) const
        { return Vector2D<T>(x+v.x, y+v.y); }

    inline Vector2D<T> operator-(const Vector2D<T>& v) const
        { return Vector2D<T>(x-v.x, y-v.y); }

    inline Vector2D<T> operator*(const T& s) const
        { return Vector2D<T>(x*s, y*s); }

    // Dot product
    inline T operator*(const Vector2D<T>& v) const
        { return x*v.x + y*v.y; }

    // l-2 norm
    inline T norm() const { return sqrt(x*x + y*y); }

    // inner angle (radians)
    static T angle(const Vector2D<T>& v1, const Vector2D<T>& v2)
    {
        return acos( (v1 * v2) / (v1.norm() * v2.norm()) );
    }
};	

	
