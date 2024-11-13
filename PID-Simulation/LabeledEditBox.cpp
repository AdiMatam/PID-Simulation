#include "LabeledEditBox.hpp"

// ideally, control should be a weak pointer... in case it dies
LabeledEditBox::LabeledEditBox(BaseScreen* parent, Lay2d position, const tg::String& prefix, float* control) {
    this->parent = parent;
    this->text = tgui::Label::create();
    this->edit = tgui::EditBox::create();

    this->text->setSize(REL_GUI(0.1f, 0.05f));
    this->text->setPosition(position);
    this->text->setText(prefix);

    this->edit->setSize(REL_GUI(0.1f, 0.05f));
    this->edit->setPosition(this->text->getPosition() + REL_GUI(0.07f, -0.005f));
    this->edit->onReturnKeyPress([this, control]() {
        float out;
        bool worked = this->edit->getText().attemptToFloat(out);
        if (worked) {
            *control = out;
        }
    });

	CallbackManager::Get().Add(
		Callback(
			parent, control, CallbackTrigger::OnChange,
			[this, control]() { 
				char str[16];
				sprintf(str, "%.2f", *control);
				this->edit->setText(tg::String(str));
			},
			true
		)
	);


}
void LabeledEditBox::addToRenderer(tg::Gui* gui) {
    gui->add(this->text);
    gui->add(this->edit);
}
