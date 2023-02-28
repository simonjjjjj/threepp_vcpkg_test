//
// Created by sijoj on 21/02/2023.
//

#ifndef THREEPP_VCPKG_TEST_DOODSCENE_HPP
#define THREEPP_VCPKG_TEST_DOODSCENE_HPP

#include "threepp/threepp.hpp"
#include <iostream>
#include <unordered_map>

using namespace threepp;

class DoodScene : public Scene, public KeyListener {
public:


    explicit DoodScene(int gridSize) {


        scene_ = Scene::create();
        //scene->position.set(OrigoX_, OrigoY_, 0);
        gridSize_ = gridSize;
        setCoordSystem(gridSize);

        camera_ = OrthographicCamera::create(-gridSize_ / 2, gridSize_ / 2, -gridSize_ / 2, gridSize_ / 2);
        camera_->position.z = 1;    //Creates camera, and sets it to grid size



        {
            auto grid = GridHelper::create(gridSize_, gridSize_, 0x444444, 0x444444);
            grid->rotation.x = math::PI / 2;

            scene_->add(grid);

        }




    }

//    void shootDood(float angle){
//    for(int i = 0; i < gridSize_; i++){
//
//    }
//    }
//
float angle = math::PI/8;   //for testing, plz remove...

    void update(float dt) {
        // Use the point to position an object in the scene
        if (HitDectX(doodMap_[1])) {angle = math::PI - angle;
        std::printf("balls");
        }
        std::cout << (angle) << "  ";
        if (!HitDectY(doodMap_[1])) {shootDood(angle, doodMap_[1], dt);
        std::printf("cock");
        }
        else {
            setDoodPos(getDoodPosX(doodMap_[1]), getDoodPosY(doodMap_[1]), doodMap_[1]);
        }

        std::cout << "X: " << getDoodPosX(doodMap_[1]) << "  ";
        std::cout << "Y: " << getDoodPosY(doodMap_[1]) << std::endl;

    }

    void setCoordSystem(int gridSize) {
        gridSize_ = gridSize;   //gridSize is specifiable by function
        OrigoX_ = -gridSize_ / 2 + 0.5; //Making the x and y origo for a coordinate system
        OrigoY_ = gridSize_ / 2 - 0.5;
    }


    void makeDood(int i) {  //Just for testing, needs implementing
        {
            std::shared_ptr<BoxGeometry> boxGeometry_ = BoxGeometry::create(1, 1, 0);

            auto doodMaterial = MeshBasicMaterial::create();
            if (i%2 != 0) {doodMaterial->color = Color::red;}
            else{doodMaterial->color = Color::green;}

            doodMap_[i] = Mesh::create(boxGeometry_, doodMaterial);
            scene_->add(doodMap_[i]);
        }
    }

    int getGridSize() {
        return gridSize_;
    }

    std::shared_ptr<Scene> getScene() {
        return scene_;
    }

    std::shared_ptr<OrthographicCamera> getCamera() {
        return camera_;
    }

    std::shared_ptr<Mesh> getDood(int doodKey) {
        return doodMap_[doodKey];
    }

    void setDoodPos(float x, float y, std::shared_ptr<Mesh> body){
        auto position = body->position;
        position.setX(OrigoX_ + round(x));
        position.setY(OrigoY_ - round(y));

        std::cout << round(OrigoX_ + x);
        std::cout << round(OrigoY_ - y) << std::endl;
        body->position = position;
    }

    float getDoodPosX(std::shared_ptr<Mesh> body) {
        return body->position.x - OrigoX_;
    }

    float getDoodPosY(std::shared_ptr<Mesh> body) {
        return -(body->position.y - OrigoY_);
    }



    void shootDood(float angle, std::shared_ptr<Mesh> body, float dt){

        float deltaDist = shootSpeed_*dt;
        auto position = body->position;
        position.setX(position.x + deltaDist * cos(angle));
        position.setY(position.y - deltaDist * sin(angle));
        body->position = position;
    }

    bool HitDectY (std::shared_ptr<Mesh> body) {
        auto position = body->position;
        if(getDoodPosY(body) >= gridSize_-1) {
            return true;
        }
        return false;
    }

    bool HitDectX (std::shared_ptr<Mesh> body) {
        auto position = body->position;
        if((getDoodPosX(body) >= gridSize_-1) || (getDoodPosX(body) < 0)) {
            return true;
        }
        return false;
    }





private:
    std::shared_ptr<OrthographicCamera> camera_;
    std::shared_ptr<Scene> scene_;
    int gridSize_;
    std::shared_ptr<Mesh> dood_;
    std::shared_ptr<Mesh> dood2_;
    float OrigoX_;
    float OrigoY_;
    float shootSpeed_ = 2;
    std::unordered_map<int, std::shared_ptr<Mesh>> doodMap_;



};


#endif //THREEPP_VCPKG_TEST_DOODSCENE_HPP
