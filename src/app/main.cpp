#include "application.h"
#include <imgui.h>

#include <iostream>
#include <math.h>
#include <deque>
#include <chrono>

#include <Eigen/Core>
using Eigen::Vector2f;

class TestApp : public Application
{
#define COLOR_OUT    nvgRGBA(220,50,50,255)
#define COLOR_IN     nvgRGBA(50,50,220,255)
#define COLOR_SOLVED nvgRGBA(50,220,50,255)

public:
    TestApp(int w, int h, const char * title) : Application(title, w, h) {
        lastFrame = std::chrono::high_resolution_clock::now();

        circleKey = {{w/2-200, h/2-100}, 30, COLOR_OUT, nvgRGBA(50, 50, 50, 100)};
        circleMouse = {{w/2-200, h/2+100}, 20, COLOR_OUT, nvgRGBA(50, 50, 50, 100)};
        rect = Box{{w/2+200, h/2}, Vector2f(100, 150), nvgRGBA(50, 50, 50, 100), nvgRGBA(50, 50, 50, 200)};

    }

    void process() override {
        std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
        if(std::chrono::duration_cast<std::chrono::microseconds>(now-lastFrame).count() >= 1./60. * 1.e6){
            Vector2f vel(0, 0);
            if(keyDown[GLFW_KEY_LEFT])
                vel[0] -= 1;
            if(keyDown[GLFW_KEY_RIGHT])
                vel[0] += 1;
            if(keyDown[GLFW_KEY_UP])
                vel[1] -= 1;
            if(keyDown[GLFW_KEY_DOWN])
                vel[1] += 1;
            circleKey.pos += vel/(vel.norm()+1e-10) * 10;

            bool isInsideKey = rect.isInside(circleKey.pos, circleKey.radius);
            bool isInsideMouse = rect.isInside(circleMouse.pos, circleMouse.radius);
            circleKey.colorFill = (isInsideKey) ? (isInsideMouse ? COLOR_SOLVED : COLOR_IN) : COLOR_OUT;
            circleMouse.colorFill = (isInsideMouse) ? (isInsideKey ? COLOR_SOLVED : COLOR_IN) : COLOR_OUT;

            if(draggingCircle)
                circleMouse.pos = Vector2f(mouseState.lastMouseX, mouseState.lastMouseY) - draggingCircleOffset;

            if(isInsideKey && isInsideMouse){
                float randX = (20.f*((float) rand() / (RAND_MAX)) + .1f) * ((rand()%2) ? -1 : 1);
                float randY = (20.f*((float) rand() / (RAND_MAX)) + .1f) * ((rand()%2) ? -1 : 1);
                float randR = 30.f*((float) rand() / (RAND_MAX)) + 10.f;
                int r = rand() % 255;
                int g = rand() % 255;
                int b = rand() % 255;
                int a = rand() % 255;
                circles.push_back({Vector2f(randX, randY), Circle{rect.center, randR, nvgRGBA(r, g, b, a), nvgRGBA(r, g, b, (2*a)%255)}});

                if(circles.size() > 400)
                    circles.erase(circles.begin(), circles.begin()+100);

                for(auto &c : circles)
                    c.second.pos += c.first;
            }
            else{
                circles.clear();
            }
            lastFrame = now;
        }
    }

    void drawImGui() override {

        using namespace ImGui;

        Begin("Hello World!");
        TextWrapped("Use the arrow keys to move the first circle.");
        TextWrapped("Drag the other circle with the mouse.");
        TextWrapped("Put them both in the Box!");
        End();

        BeginMainMenuBar();
        if(BeginMenu("debug")){
            Checkbox("draw cursor", &drawCursor);
            Checkbox("draw circles", &drawCircles);
            EndMenu();
        }
        Text("| window size: %d x %d", width, height);
        Text("| pixel ratio: %f", pixelRatio);
        EndMainMenuBar();
    }

    void drawNanoVG() override {
        // draw Box
        nvgBeginPath(vg);
        nvgRect(vg, rect.center[0]-rect.size[0]/2.f, rect.center[1]-rect.size[1]/2.f, rect.size[0], rect.size[1]);
        nvgFillColor(vg, rect.colorFill);
        nvgFill(vg);
        nvgStrokeColor(vg, rect.colorStroke);
        nvgStrokeWidth(vg, 10.0f);
        nvgStroke(vg);

        if(drawCircles)
        {
            auto drawCircle = [this](const Circle &circle){
                nvgBeginPath(vg);
                nvgCircle(vg, circle.pos[0], circle.pos[1], circle.radius);
                nvgFillColor(vg, circle.colorFill);
                nvgFill(vg);
                nvgStrokeColor(vg, circle.colorStroke);
                nvgStrokeWidth(vg, 10.0f);
                nvgStroke(vg);
            };

            for(const auto &c : circles)
                drawCircle(c.second);

            // draw circle key
            drawCircle(circleKey);
            drawCircle(circleMouse);
        }

        if(drawCursor){
            nvgBeginPath(vg);
            nvgCircle(vg, mouseState.lastMouseX, mouseState.lastMouseY, 10.f);
            nvgFillColor(vg, rect.colorStroke);
            nvgFill(vg);
        }
    }

protected:
    void mouseButtonPressed(int button, int mods) override {
        Vector2f x = Vector2f(mouseState.lastMouseX, mouseState.lastMouseY);
        if(button == GLFW_MOUSE_BUTTON_LEFT && circleMouse.isInside(x)) {
            draggingCircle = true;
            draggingCircleOffset = x - circleMouse.pos;
        }
    }

    void mouseButtonReleased(int button, int mods) override {
        draggingCircle = false;
    }

private:
    int loadFonts(NVGcontext* vg)
    {
        int font;
        font = nvgCreateFont(vg, "sans", "../example/Roboto-Regular.ttf");
        if (font == -1) {
            printf("Could not add font regular.\n");
            return -1;
        }
        font = nvgCreateFont(vg, "sans-bold", "../example/Roboto-Bold.ttf");
        if (font == -1) {
            printf("Could not add font bold.\n");
            return -1;
        }
        return 0;
    }

private:
    bool drawCursor = false;
    bool drawCircles = true;
    struct Circle
    {
        bool isInside(const Vector2f &x){
            return (x-pos).squaredNorm() <= radius*radius;
        }

        Vector2f pos;
        float radius;
        NVGcolor colorFill, colorStroke;
    } circleKey, circleMouse;
    struct Box {
        bool isInside(const Vector2f &x, float slack = 0.f) {
            for (int i = 0; i < 2; ++i)
                if(x[i]-slack < center[i]-size[i]/2 || x[i]+slack > center[i]+size[i]/2)
                    return false;
            return true;
        }

        Vector2f center;
        Vector2f size;
        NVGcolor colorFill, colorStroke;
    } rect;

    bool draggingCircle = false;
    Vector2f draggingCircleOffset;
    std::deque<std::pair<Vector2f, Circle>> circles;
    std::chrono::high_resolution_clock::time_point lastFrame;
};

int main(int, char**)
{
    TestApp app(720, 560, "Assignment 0");
    app.run();

    return 0;
}
