//
// Created by pedrosoares on 4/29/18.
//

#ifndef TIGREFRAMEWORK_ROUTERSERVICEPROVIDER_H
#define TIGREFRAMEWORK_ROUTERSERVICEPROVIDER_H


#include <TigreFramework/Core/Kernel/Application/Configurable.h>
#include <TigreFramework/Core/Kernel/Application/ServiceProvider.h>

class RouterServiceProvider : public ServiceProvider, public Configurable {

    public:
        void boot();

};


#endif //TIGREFRAMEWORK_ROUTERSERVICEPROVIDER_H
