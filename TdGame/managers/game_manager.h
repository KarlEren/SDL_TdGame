#pragma once
#include "manager.h"


class GameManager:public Manager<GameManager>
{
    friend class Manager<GameManager>;//使父类GameManager可以访问子类构造函数
public:
protected:
    GameManager(){}
    ~GameManager(){}
};
