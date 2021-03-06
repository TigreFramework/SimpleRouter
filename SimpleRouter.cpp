//
// Created by pedrosoares on 4/29/18.
//
#include "SimpleRouter.h"
#include <TigreFramework/Core/Kernel/Request.h>
#include <TigreFramework/Core/Kernel/PageNotFoundException.h>
#include <TigreFramework/String/String.h>

std::vector<std::map<std::string, std::map<std::string, std::function<Response(Request *)>>>> SimpleRouter::routes;

void SimpleRouter::boot() {

}

Response SimpleRouter::handle(Request *request) {
    Response response = this->find(request);
    return std::move(response);
}

Response SimpleRouter::find(Request *request) {
    for (auto& item: routes) {
        for (auto& mapa: item) {
            if(this->matchRouteName(request->getUri(), mapa.first)){
                for(auto& mapa_ : mapa.second){
                    if(mapa_.first == request->getMethod()){
                        return mapa_.second(request);
                    }
                }
            }
        }
    }
    throw PageNotFoundException();
}

bool SimpleRouter::matchRouteName(std::string uri, std::string route) {
    if (uri == route){
        return true;
    }

    auto uri_piece = Tigre::String(uri).explode("/");
    auto route_piece = Tigre::String(route).explode("/");

    std::map<std::string, std::string> params;
    for(int i=0; i < uri_piece.size(); i++){
        if(route_piece.size() <= i){
            return false;
        }
        if(uri_piece.size() <= i){
            return false;
        }

        bool is_param = (
            route_piece[i].getValue().find(std::string("{")) != std::string::npos &&
            route_piece[i].getValue().find(std::string("}")) != std::string::npos
        );

        if(route_piece[i] != uri_piece[i] && !is_param){
            return false;
        }else if(is_param && uri_piece[i] == ""){
            return false;
        }else if(is_param){
            Tigre::String param = route_piece[i].getValue();
            param.replace("{", "");
            param.replace("}", "");
            params[param.getValue()] = uri_piece[i].getValue();
        }
    }

    if(route_piece.size() == uri_piece.size()){
        /** TODO Add the Params to the Request Methods */
        return true;
    }
    return false;
}

void SimpleRouter::post(std::string uri, std::function<Response(Request *)> response) {
    routes.push_back({ { uri, {{ "POST", response }} } });
}

void SimpleRouter::get(std::string uri, std::function<Response(Request *)> response) {
    routes.push_back({ { uri, {{ "GET", response }} } });
}