
#include "threepp/threepp.hpp"
#include "threepp/extras/imgui/imgui_context.hpp"
#include "DoodScene.hpp"

using namespace threepp;

int main() {

DoodScene scene(10);

    Canvas canvas;

    GLRenderer renderer(canvas);
    renderer.setClearColor(Color::black);


    canvas.onWindowResize([&](WindowSize size) { //Resizes the canvas, but keeps the grid in a locked aspect ratio

        float aspectRatio = static_cast<float>(size.width) / static_cast<float>(size.height);
        scene.getCamera()->left = (-scene.getGridSize() / 2) * aspectRatio;
        scene.getCamera()->right = (scene.getGridSize() / 2) * aspectRatio;
        scene.getCamera()->bottom = -scene.getGridSize() / 2;
        scene.getCamera()->top = scene.getGridSize() / 2;
        scene.getCamera()->updateProjectionMatrix();
        renderer.setSize(size);

    });

for (int i = 0; i < 30; i++) { scene.makeDood(i);}

float time = 0;
    canvas.animate([&](float dt) {
        time += dt;
        if(time > 1) {time = 0;}
            scene.update(time);
            renderer.render(scene.getScene(), scene.getCamera());



    });
    }







