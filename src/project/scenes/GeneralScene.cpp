//
// Created by madrent on 29/11/2022.
//

#include <iostream>
#include "src/project/Object.h"
#include "GeneralScene.h"
#include "src/project/LightSource.h"

std::list<std::unique_ptr<Object>>* GeneralScene::getObjects() {
    return (&objects);
}

std::list<std::unique_ptr<LightSource>>* GeneralScene::getLights() {
    return (&lights);
}
