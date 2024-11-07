#pragma once

#include "Pch.hpp"

#define CAT2(a,b) a##b
#define CAT(a,b) CAT2(a,b)
#define UNIQUE_ID CAT(rend_,__LINE__)

#define tgConfig(object, attr1, attr2, arg) \
    auto UNIQUE_ID = object->getRenderer()->get##attr1(); \
    UNIQUE_ID.set##attr2(arg); \
    button->getRenderer()->set##attr1(UNIQUE_ID)


