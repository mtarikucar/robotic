#include<iostream>
#include<string>
#include<vector>
#include<math.h>


class Point_features{
    std::string name;
    int influence;
    //constructer
    public:
    Point_features(std::string name, int inf){
        this->name = name;
        this->influence = inf;
    }
    Point_features(std::string name){
        this->name = name;
        this->influence = 0;
    }
    Point_features(){
        this->name = "";
        this->influence = 0;
    }
    
    //getters
    std::string get_name(){
        return this->name;
    }
    int get_influence(){
        return this->influence;
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
    Point_features f;
    //constructer
    public:
    Point(int x, int y, Point_features f){
        this->x = x;
        this->y = y;
        this->f = f;
    }
    Point(int x, int y){
        this->x = x;
        this->y = y;
        this->f = Point_features();
    }
    Point(){
        this->x = 0;
        this->y = 0;
        this->f = Point_features();
    }
    
    //getters
    int get_x(){
        return this->x;
    }
    int get_y(){
        return this->y;
    }
    Point_features get_f(){
        return this->f;
    }
    
    //show function
    void show(){
        std::cout << "Point: (" << this->x << ", " << this->y << ")" << std::endl;
        this->f.show();
    }
};

class Map{
    std::vector<Point> points;
    int square_size = 100; //per square represents 20 cm
    int grid[100][100]; //? default grid size is 100x100 it's not given square size ı don't know why look at this line later
    //constructer
    public:
    Map(){
        for(int i = 0; i < square_size; i++){
            for(int j = 0; j < square_size; j++){
                this->grid[i][j] = 0;
            }
        }
    }

    //setters
    
    void set_points(std::vector<Point> points){
        this->points = points;
        for(int i = 0; i < square_size; i++){
            for(int j = 0; j < square_size; j++){
                this->grid[i][j] = 0;
            }
        }
        for(int i = 0; i < this->points.size(); i++){
            //! edge case is should be limited to square_size
            for(int j = 0; j <this->points[i].get_f().get_influence();j++){
                this->grid[this->points[i].get_x() - int(ceilf(this->points[i].get_f().get_influence()/2))][this->points[i].get_y() - int(ceilf(this->points[i].get_f().get_influence()/2))] = 1;
            }
        }
    }
    
    //show function
    void show_points(){
        for(int i = 0; i < this->points.size(); i++){
            this->points[i].show();
            std::cout << "=================" << std::endl;
        }
    }
    void show_grid(){
        for(int i = 0; i < square_size; i++){
            for(int j = 0; j < square_size; j++){
                std::cout << this->grid[i][j] << " ";
            }
            std::cout << std::endl;
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

class Possible_state:public Vehicle{
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


int main(){

    Point_features line("line", 1);
    Point_features obstacle("obstacle", 20);
    
    Point pointA(1,1,line);
    Point pointB(2,2,line);
    Point pointC(3,3,line);
    Point pointD(4,4,obstacle);
    Point pointE(5,5,obstacle);
    Point pointF(6,6,obstacle);
    Point pointG(5,95,obstacle);
    Point pointH(5,96,obstacle);
    Point pointI(5,97,obstacle);
    Point pointJ(5,98,obstacle);

    std::vector<Point> points;

    points.push_back(pointA);
    points.push_back(pointB);
    points.push_back(pointC);
    points.push_back(pointD);
    points.push_back(pointE);
    points.push_back(pointF);
    points.push_back(pointG);
    points.push_back(pointH);
    points.push_back(pointI);
    points.push_back(pointJ);

    //inner for loop 10 times
    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            Point p(50+i,50+j,obstacle);
            points.push_back(p);
        }
    }

    Map map;

    map.set_points(points);
    
    Vehicle vehicle(0,50,50,0);
    
    Estimeted_state est_stt;
    
    Possible_state pos_stt;

    map.show_grid();
    

    return 0;
}