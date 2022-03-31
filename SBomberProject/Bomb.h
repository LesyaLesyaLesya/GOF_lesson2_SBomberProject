#pragma once

#include "DynamicObject.h"

class Bomb : public DynamicObject
{
public:
    Bomb() {};
    Bomb(const Bomb&) {};
    Bomb& operator=(const Bomb&) = delete;
    Bomb(Bomb&&) {};
    Bomb& operator=(const Bomb&&) = delete;


	static const uint16_t BombCost = 10; // стоимость бомбы в очках

	void Draw() const override;

private:

};

