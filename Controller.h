//
// Created by pedrosoares on 5/2/18.
//

#ifndef TIGREFRAMEWORK_CONTROLLER_H
#define TIGREFRAMEWORK_CONTROLLER_H

#include <iostream>

#define Controller(Class)                                                \
public:                                                                  \
    static Class instance() {                                               \
        return Class();                                                  \
    }


class Controller {

};


#endif //TIGREFRAMEWORK_CONTROLLER_H
