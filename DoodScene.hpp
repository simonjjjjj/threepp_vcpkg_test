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


    void update(float time) {
        // Use the point to position an object in the scene
        int y = 0;
        int x = 0;
        for (int i = 0; i < doodMap_.size(); i++) {
            if (x > gridSize_) {y++; x = 0;}
                setDoodPos(x, y, doodMap_[i]);
            x++;
        }
       // setDoodPos(abs(round(5 * sin(i / 50))), abs(round(5 * cos(i / 50))), dood_);
    }

    void setCoordSystem(int gridSize) {
        gridSize_ = gridSize;   //gridSize is specifiable by function
        OrigoX_ = -gridSize_ / 2 + 0.5; //Making the x and y origo for a coordinate system
        OrigoY_ = gridSize_ / 2 - 0.5;
        std::cout << OrigoX_ << std::endl;
    }

    void makeDood(int i) {
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

    void setDoodPos(float x, float y, std::shared_ptr<Mesh> body){
        auto position = body->position;
        position.setX(OrigoX_ + x);
        position.setY(OrigoY_ - y);
        std::cout << position << std:: endl;
        body->position = position;
    }



void shootDood(float angle, std::shared_ptr<Mesh> body){
        auto position = body->position;
        position.setX(OrigoX_);
        position.setY(OrigoY_);
        body->position = position;
    }




private:
    std::shared_ptr<OrthographicCamera> camera_;
    std::shared_ptr<Scene> scene_;
    int gridSize_;
    std::shared_ptr<Mesh> dood_;
    std::shared_ptr<Mesh> dood2_;
    float OrigoX_;
    float OrigoY_;
    std::unordered_map<int, std::shared_ptr<Mesh>> doodMap_;



};


#endif //THREEPP_VCPKG_TEST_DOODSCENE_HPP
