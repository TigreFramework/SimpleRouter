//
// Created by pedrosoares on 4/29/18.
//

#ifndef TIGREFRAMEWORK_SIMPLEROUTER_H
#define TIGREFRAMEWORK_SIMPLEROUTER_H

#include <TigreFramework/Core/Kernel/Router.h>
#include <TigreFramework/Core/Kernel/Application/Configurable.h>
#include <TigreFramework/Core/Kernel/Response.h>
#include <TigreFramework/Core/Kernel/Request.h>
#include <functional>
#include <vector>

class SimpleRouter : public Router, public Configurable {

    public:
        void boot() override;
        Response handle(Request *request) override;

        static void post(std::string uri, std::function<Response(void)>);
        static void get(std::string uri, std::function<Response(void)>);

        template<typename Result, typename Cls>
        static std::function<Response(void)> bind(Result (Cls::*func)(), Cls (*clone)()){
            return [=](){
                return ((clone()).*(func))();
            };
        }

    private:
        Response find(Request *request);
        bool matchRouteName(std::string uri, std::string route);
        static std::vector<std::map<std::string, std::map<std::string, std::function<Response(void)>>>> routes;

};

#endif //TIGREFRAMEWORK_ROUTER_H
