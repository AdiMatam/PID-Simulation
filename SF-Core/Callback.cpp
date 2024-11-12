#include "Callback.hpp"

Callback::Callback(BaseScreen* owner, float* reference, CallbackTrigger triggerType, CallbackFunc func, bool immediateInvoke)
    : owner(owner),
        reference(reference),
        referenceVal(*reference),
        triggerType(triggerType),
        func(func),
        immediateInvoke(immediateInvoke) {}

CallbackManager& CallbackManager::Get() {
    static CallbackManager instance;
    return instance;
}

const Callback* CallbackManager::Add(Callback cb) {
    mCallbacks[cb.owner].emplace_back(cb);
    if (cb.immediateInvoke)
        cb.func();

    return &mCallbacks[cb.owner].back();
}

void CallbackManager::Poll(BaseScreen* owner) {
    if (!mapContains(mCallbacks, owner)) {
        return;
    }

    for (Callback& cb : mCallbacks[owner]) {
        if (cb.triggerType == CallbackTrigger::OnChange) {
            if(*cb.reference != cb.referenceVal) {
                cb.referenceVal = *cb.reference;
                cb.func();
            }
        }
    }
}
