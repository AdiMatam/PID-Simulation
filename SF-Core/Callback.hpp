#pragma once
#include "Pch.hpp"
#include "Animation.hpp"
#include "Helpers.hpp"
#include "BaseScreen.hpp"

enum class CallbackTrigger {
	OnChange
};

using CallbackFunc = std::function<void()>;

struct Callback {
    BaseScreen* owner;
    float* reference;
	float referenceVal;

    CallbackTrigger triggerType;
    CallbackFunc func;
    bool immediateInvoke;

    Callback(BaseScreen* owner, float* reference, CallbackTrigger triggerType, CallbackFunc func, bool immediateInvoke);
};

class CallbackManager {
public:
    static CallbackManager& Get();

	const Callback* Add(Callback cb) ;
    void Poll(BaseScreen* owner);

private:
    CallbackManager() = default;
    CallbackManager(const CallbackManager&) = delete;
    CallbackManager& operator=(const CallbackManager&) = delete;

    // Map to store callbacks based on trigger type
    std::unordered_map<BaseScreen*, std::vector<Callback>> mCallbacks;
};


