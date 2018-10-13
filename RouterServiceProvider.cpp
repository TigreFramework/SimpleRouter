//
// Created by pedrosoares on 4/29/18.
//

#include <TigreFramework/Core/Kernel/Application/Configuration.h>
#include "RouterServiceProvider.h"
#include "SimpleRouter.h"

void RouterServiceProvider::boot() {
    Configuration::set("Router", new SimpleRouter());
}