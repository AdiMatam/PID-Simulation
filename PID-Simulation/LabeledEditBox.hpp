#pragma once

#include "SF-Core/Core.hpp"

struct LabeledEditBox {
    BaseScreen* parent;
    tg::Label::Ptr text;
    tg::EditBox::Ptr edit;

    LabeledEditBox(BaseScreen* parent, Lay2d position, const tg::String& prefix, float* control);
    void addToRenderer(tg::Gui* gui);
};
