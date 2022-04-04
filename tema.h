#pragma once

#include "components/simple_scene.h"
struct corp {
    float x;
    float y;
    float width;
    float height;

    corp() {

    }
    corp(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->height = height;
        this->width = width;
    }

    friend std::ostream& operator<< (std::ostream& o, const corp& r) {
        return o << r.x << " " << r.y << " " << r.width << " " << r.height << std::endl;
    }
};
struct glont1 {
    float x;
    float y;
    float angular;
    int click;
    corp glont;
    glont1() {
        x = 0;
        y = 0;
        angular = 0;
        click = 0;
        this->glont = corp(0, 0, 4, 4);
    }
    glont1(float x, float y, float angular, int click) {
        this->x = x;
        this->y = y;
        this->angular = angular;
        this->click = click;
        this->glont = corp(x, y, 4, 4);
    }
};
struct inamic1 {
    float x;
    float y;
    float angular;
    float speed;
    float time;
    int coliziune;
    corp inamic;
    inamic1() {
        this->inamic = corp(0, 0, 40, 40);
        coliziune = 0;
    }
    inamic1(float x, float y, float angular, float speed, float time, int coliziune) {
        this->x = x;
        this->y = y;
        this->angular = angular;
        this->speed = speed;
        this->inamic = corp(x, y, 4, 4);
        this->coliziune = coliziune;
        this->time = time;
    }
};
struct coordObj {
    float scaleX;
    float scaleY;
    float x;
    float y;

    coordObj() {

    }
    coordObj(float scaleX, float scaleY, float x, float y) {
        this->scaleX = scaleX;
        this->scaleY = scaleY;
        this->x = x;
        this->y = y;
    }
};
namespace m1
{
    class tema : public gfxc::SimpleScene
    {
     public:
        tema();
        ~tema();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        bool Collision(corp a, corp b);

     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        int player_length;
        float scaleX, scaleY;
        float angularStep;
        float angularInc;
        float mapX, mapY;
        float pozX, pozY;
        float speed;
        float speed_glont;
        float nr_glont;
        float time_glont;
        corp playerDef;
        corp obstacolDef;
        coordObj obj;
        std::vector<coordObj> coordonate;
        std::vector<corp> obstacole;
        std::vector<glont1> gloante;
        std::vector<inamic1> inamici;
        float time = 0;
        float scor = 0;
        float viata = 100000;
    };
}
