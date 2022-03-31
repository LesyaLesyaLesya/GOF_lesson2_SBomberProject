#pragma once

#include <stdint.h>
#include <iostream>

#include "GameObject.h"

class DynamicObject : public GameObject 
{
public:

    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    inline void SetSpeed(double sp) { speed = sp; }
    inline void SetDirection(double dx, double dy) { xDirction = dx; yDirection = dy; }
    
    virtual void Move(uint16_t time) { x += xDirction * speed * time * 0.001; y += yDirection * speed * time * 0.001; };
    double const getSpeed() { return speed; }
protected:

    double speed;
    double xDirction, yDirection;

};
class DrawObjectDecorator : public DynamicObject {
public:
    DrawObjectDecorator(std::shared_ptr<DynamicObject> draw_object)
        : draw_object_{ std::move(draw_object) } {}

protected:
    std::shared_ptr<DynamicObject> draw_object_;
};

class BombDecorator : public DrawObjectDecorator {
public:
    BombDecorator(std::shared_ptr<DynamicObject> draw_object)
        : DrawObjectDecorator{ std::move(draw_object) } {}

    void Draw() const override
    {
        if (draw_object_) {
            draw_object_->Draw();
            addBorder();
        }
    }


private:
    void addBorder() const
    {
        std::cout << "@";
    }

    void addSpeed(std::shared_ptr<DynamicObject> draw_object) const
    { 
        draw_object->SetSpeed(draw_object->getSpeed() + 3);
    }
};
