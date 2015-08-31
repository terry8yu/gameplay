/*
* Copyright (C) 2010 The Android Open Source Project
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#include "android_native_app_glue.h"
#include <gameplay.h>

using namespace gameplay;

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "AdsFrame.NativeActivity", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "AdsFrame.NativeActivity", __VA_ARGS__))

extern struct android_app* __state;

/**
* This is the main entry point of a native application that is using
* android_native_app_glue.  It runs in its own thread, with its own
* event loop for receiving input events and doing other things.
*/
void android_main(struct android_app* state)
{
    // Android specific : Dummy function that needs to be called to 
    // ensure that the native activity works properly behind the scenes.
    app_dummy();

    __state = state;
    Game* game = Game::getInstance();
    Platform* platform = Platform::create(game);
    GP_ASSERT(platform);
    platform->enterMessagePump();
    delete platform;

    // Android specific : the process needs to exit to trigger
    // cleanup of global and static resources (such as the game).
    exit(0);
}
