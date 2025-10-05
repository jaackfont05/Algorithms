//AUTHOR: Jack Fontenot
//Assignment Title: Program 2
//Assignment Description: Maxima Set
//Due Date: 9/7/2025
//Date Created: 9/7/2025
//Date Last Modified: 9/7/2025

#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED
#include <iostream>

using namespace std;

struct point{
    int x;
    int y;

    point operator=(point m){
        this->x = m.x;
        this->y = m.y;
        return *this;
    }

    void print(){
        cout << "(" << x << ", " << y << ")";
    }
};

class Set{
private:
    point* p;
    int size;
    int cap;
public:
    Set(){
        size = 0;
        cap = 10;
        p = new point[cap];
    }

    Set operator=(Set a){
        delete [] p;
        this->size = 0;
        this->cap = a.cap;
        p = new point[cap];
        for(int i = 0; i < a.Size(); ++i){
            this->push(a.at(i));
        }

        return *this;
    }

    void push(point t){
        if(this->size >= this->cap){
            resize();
        }

        insert(t);
        this->size += 1;
    }

    void resize(){
        this->cap *= 2;
        point* temp = new point[cap];

        for(int i = 0; i < cap/2; ++i){
            temp[i] = this->p[i];
        }

        delete [] this->p;
        p = temp;
    }

    point& at(int i){
        return p[i];
    }

    int Size(){
        return this->size;
    }

    void shiftR(int b){
        for(int i = size; i > b; --i){
            p[i] = p[i-1];
        }
    }

    void insert(point t){
        bool flag = false;
        int i = 0;

        if(size == 0){
            p[i] = t;
        }else{
            while(!flag && i <= size){
                if(p[i].x == t.x){
                    if(p[i].y < t.y){
                        flag = true;
                        shiftR(i);
                    }
                    else if(p[i].y == t.y){
                        size--;
                        return;
                    }
                }
                else if(p[i].x < t.x){
                    flag = true;
                    shiftR(i);
                }
                ++i;
            }

            i--;
            p[i] = t;
        }
    }

    point median(){
        return p[(this->size)/2];
    }

    Set low(point m){
        Set res;

        for(int i = 0; i < size; ++i){

            if(m.x > p[i].x){
                res.push(p[i]);
            }
        }

        return res;
    }

    Set high(point m){
        Set res;



        for(int i = 0; i < size; ++i){
            if(m.x == p[i].x){
                if(m.y <= p[i].y){
                    res.push(p[i]);
                }
            }
            else if(m.x < p[i].x){
                res.push(p[i]);
            }
        }


        return res;
    }

    void pop(point r){
        int index;
        for(int i = 0; i < this->size; ++i){
            if(r.x == p[i].x && r.y == p[i].y){
                index = i;
            }
        }

        shiftL(index);
        this->size = this->size - 1;
    }

    void shiftL(int n){
        for(int i = n; i < this->size -1; ++i){
            p[i] = p[i+1];
        }
    }
};
#endif // POINT_H_INCLUDED
