//
// Created by pedrosoares on 4/29/18.
//

#ifndef TIGREFRAMEWORK_SIMPLEROUTER_H
#define TIGREFRAMEWORK_SIMPLEROUTER_H

#include <TigreFramework/Core/Kernel/Router.h>
#include <TigreFramework/Core/Kernel/Response.h>
#include <TigreFramework/Core/Kernel/Request.h>
#include <functional>
#include <vector>

class SimpleRouter : public Router {

    public:
        void boot() override;
        Response handle(Request *request) override;

        static void post(std::string uri, std::function<Response(Request *)>);
        static void get(std::string uri, std::function<Response(Request *)>);

        template<typename Result, typename Cls>
        static std::function<Response(Request *)> bind(Result (Cls::*func)(), Cls (*clone)()){
            return [=](Request * request){
                return ((clone()).*(func))();
            };
        }
        template<typename Result, typename Cls>
        static std::function<Response(Request *)> bind(Result (Cls::*func)(Request *), Cls (*clone)()){
            return [=](Request * request){
                return ((clone()).*(func))(request);
            };
        }

    private:
        Response find(Request *request);
        bool matchRouteName(std::string uri, std::string route);
        static std::vector<std::map<std::string, std::map<std::string, std::function<Response(Request *)>>>> routes;

};

#endif //TIGREFRAMEWORK_ROUTER_H
