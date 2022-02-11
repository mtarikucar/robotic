#include<iostream>
#include<string>
#include<vector>

class Features{
    std::string name;
    int influence;
    //constructer
    public:
    Features(std::string name, int inf){
        this->name = name;
        this->influence = inf;
    }
    Features(std::string name){
        this->name = name;
        this->influence = 0;
    }
    Features(){
        this->name = "";
        this->influence = 0;
    }
    
    //setters
    void set_name(std::string name){
        this->name = name;
    }
    void set_influence(int inf){
        this->influence = inf;
    }
    
    //show function
    void show(){
        std::cout << "Name: " << this->name << std::endl;
        std::cout << "Influence: " << this->influence << std::endl;
    }

};

class Point{
    int x;
    int y;
    Features f;
    //constructer
    public:
    Point(int x, int y, Features f){
        this->x = x;
        this->y = y;
        this->f = f;
    }
    Point(int x, int y){
        this->x = x;
        this->y = y;
        this->f = Features();
    }
    Point(){
        this->x = 0;
        this->y = 0;
        this->f = Features();
    }
    
    //setters
    void set_x(int x){
        this->x = x;
    }
    void set_y(int y){
        this->y = y;
    }
    void set_f(Features f){
        this->f = f;
    }
    
    //show function
    void show(){
        std::cout << "Point: (" << this->x << ", " << this->y << ")" << std::endl;
        this->f.show();
    }
};

class Map{
    std::vector<Point> points;
    //constructer
    public:
    Map(){
        this->points = std::vector<Point>();
    }
    Map(std::vector<Point> points){
        this->points = points;
    }
    
    //setters
    void set_points(std::vector<Point> points){
        this->points = points;
    }
    
    //show function
    void show(){
        for(int i = 0; i < this->points.size(); i++){
            this->points[i].show();
            std::cout << "=================" << std::endl;
        }
    }
};

class Vehicle{
    protected:
        int id;
        int x;
        int y;
        float dir; //direction type is radian
        float radianToDegree(float radian){
            return radian * 180 / 3.14159265;
        }
    //constructer
    public:
        Vehicle(int id, int x, int y, float dir){
            this->id = id;
            this->x = x;
            this->y = y;
            this->dir = dir;
        }
        Vehicle(){
            this->id = 0;
            this->x = 0;
            this->y = 0;
            this->dir = 0;
        }
        //show function
        void show(){
            std::cout << "Vehicle: " << this->id << std::endl;
            std::cout << "Position: (" << this->x << ", " << this->y << ")" << std::endl;
            std::cout << "Direction: " << this->radianToDegree(this->dir) << std::endl;
        }
    
};

class Estimeted_state:public Vehicle{
    //constructer
    int time_stamp;
    public:
    Estimeted_state(int id, int time_stamp, int x, int y, float dir){
        this->id = id;
        this->time_stamp = time_stamp;
        this->x = x;
        this->y = y;
        this->dir = dir;
    }

    Estimeted_state(){
        this->id = 0;
        this->time_stamp = 0;
        this->x = 0;
        this->y = 0;
        this->dir = 0;
    }

    //show function
    void show(){
        std::cout << "Vehicle ID: " << this->id << std::endl;
        std::cout << "Time Stamp: " << this->time_stamp << std::endl;
        std::cout << "Position: (" << this->x << ", " << this->y << ")" << std::endl;
        std::cout << "Direction: " << radianToDegree(this->dir) << " degree" << std::endl;
    }

    //estimate reachable better waypoint
};

class Possible_states:public Vehicle{
    //constructer
    int layer;
    int time_stamp;
    public:
    Possible_state(int id, int time_stamp, int x, int y, float dir){
        this->id = id;
        this->time_stamp = time_stamp;
        this->x = x;
        this->y = y;
        this->dir = dir;
    }

    Possible_state(){
        this->id = 0;
        this->time_stamp = 0;
        this->x = 0;
        this->y = 0;
        this->dir = 0;
    }

    //show function
    void show(){
        std::cout << "Vehicle ID: " << this->id << std::endl;
        std::cout << "Time Stamp: " << this->time_stamp << std::endl;
        std::cout << "Position: (" << this->x << ", " << this->y << ")" << std::endl;
        std::cout << "Direction: " << radianToDegree(this->dir) << " degree" << std::endl;
    }

    //calculate posiable states
};

