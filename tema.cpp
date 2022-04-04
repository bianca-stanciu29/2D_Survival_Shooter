#include "lab_m1/tema/tema.h"

#include <vector>
#include <iostream>
#include <stdlib.h>
#include "lab_m1/tema/transform2D.h"
#include "lab_m1/tema/object2D.h"
#define PI 3.14159265
using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema::tema()
{
}


tema::~tema()
{
}



void tema::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    
    player_length = 40;
    speed = 1000;
    speed_glont = 1000;
    nr_glont = 0;
    time_glont = 0;
    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = corner.x + player_length / 2;
    cy = corner.y + player_length / 2;
    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    pozX = resolution.x / 2;
    pozY = resolution.y / 2;

    // Initialize sx and sy (the scale factors)
    scaleX = -15;
    scaleY = 5;

    // Initialize angularStep
    angularStep = 0;

    //player
    Mesh* player = object2D::CreatePlayer("square", corner, player_length, true);
    AddMeshToList(player);
    //caracetristici player
    playerDef.x = pozX;
    playerDef.y = pozY;
    playerDef.height = player_length;
    playerDef.width = player_length;
   
    //inamic
    Mesh* inamic = object2D::CreateInamic("inamic", corner, player_length, true);
    AddMeshToList(inamic);


    for (int i = 0; i < 5; i++) {
       // inamici.push_back(inamic1());
        inamici.push_back(inamic1());
        inamici[i].x = rand() % 1513 + 42;
        inamici[i].y = rand() % 1464 + 43;
        inamici[i].inamic.x = inamici[i].x;
        inamici[i].inamic.y = inamici[i].y;
        inamici[i].speed = rand() % 300 + 50;
        inamici[i].time = (i == 0) ? 5 : -i*5;
        inamici[i].coliziune = 1;
    }
    
       
    
   
    //cout << "inamici poz" << inamici[0].x << " " << inamici[0].y << endl;

    //mapa
    Mesh* mapa = object2D::CreateSquare("mapa", corner, player_length, glm::vec3(0.2f, 0.2f, 0), true);
    AddMeshToList(mapa);
    coordonate.push_back(coordObj(1, player_length, 0, 0));
    obstacole.push_back(corp(0, 0, (float)player_length * 1, (float)player_length * player_length));

    coordonate.push_back(coordObj(player_length, 1, 0, 0));
    obstacole.push_back(corp(0, 0, (float)player_length * player_length, (float)player_length));

    coordonate.push_back(coordObj (player_length, 1, 0, player_length * player_length - player_length));
    obstacole.push_back(corp(0, player_length * player_length - player_length, (float)player_length * player_length, (float)player_length));

    coordonate.push_back(coordObj(1, player_length, player_length * player_length, 0));
    obstacole.push_back(corp(player_length * player_length, 0, (float)player_length , (float)player_length * player_length));

    //obstacole
    coordonate.push_back(coordObj(1, 25, 360, 227));
    obstacole.push_back(corp(360, 227, (float)player_length * 1, (float)player_length * 25));

    coordonate.push_back(coordObj(25, 1, 150, 1360));
    obstacole.push_back(corp(150, 1360, (float)player_length * 25, (float)player_length * 1));

    coordonate.push_back(coordObj(1, 20, 1400, 230));
    obstacole.push_back(corp(1400, 230, (float)player_length * 1, (float)player_length * 20));

    coordonate.push_back(coordObj(12.5, 1, 930, 230));
    obstacole.push_back(corp(930, 230, (float)player_length * 12.5, (float)player_length * 1));

    //glont
    Mesh* glont = object2D::CreateSquare("glont", corner, 4, glm::vec3(1, 1, 1), true);
    for (int i = 0; i < 5; i++)
    {
        gloante.push_back(glont1());
    }
    AddMeshToList(glont);
    
    //obstacol
    Mesh* obstacol = object2D::CreateObstacle("obstacol", glm::vec3(0, 0, 0), player_length, glm::vec3(0, 0.5f, 0), true);
    AddMeshToList(obstacol);
    obstacolDef = {0, 0, (float)player_length * 10,(float) player_length * 1};
    //healthbar
    Mesh* viata = object2D::CreateSquare("viata", glm::vec3(0, 0, 0), 10, glm::vec3(1, 0, 0), true);
    AddMeshToList(viata);
    //healthbar contur
    Mesh* contur = object2D::CreateSquare("contur", glm::vec3(0, 0, 0), 10, glm::vec3(1, 0, 0), false);
    AddMeshToList(contur);
}


void tema::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void tema::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(pozX - resolution.x/2, -resolution.y/2 + pozY, 50));
    //healthbar contur
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x / 2 + pozX - 200, resolution.y / 2 + pozY - 100)
                *transform2D::Scale(-15, 5);
    RenderMesh2D(meshes["contur"], shaders["VertexColor"], modelMatrix);
    //healthbar
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(resolution.x / 2 + pozX - 200, resolution.y / 2 + pozY - 100)
        * transform2D::Scale(scaleX, scaleY);
    RenderMesh2D(meshes["viata"], shaders["VertexColor"], modelMatrix);
   
     //player
    modelMatrix = glm::mat3(1);
    modelMatrix *=  transform2D::Translate(pozX + cx, pozY + cy)
        * transform2D::Rotate(angularStep - PI / 2)
        * transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["square"], shaders["VertexColor"], modelMatrix);

    //glont
    for (int i = 0; i < 5; i++) {
        //cout << "click: " << gloante[i].click << endl;
        if (gloante[i].click == 1) {
            gloante[i].x += deltaTimeSeconds * cos(gloante[i].angular) * speed_glont;
            gloante[i].y += deltaTimeSeconds * sin(gloante[i].angular) * speed_glont;

            //cout << gloante[i].x << " glont " << gloante[i].y << endl;
            gloante[i].glont.x = gloante[i].x;
            gloante[i].glont.y = gloante[i].y;
            // cout << gloante[i].glont.x << " glont2 " << gloante[i].glont.y <<"h= " 
                // << gloante[i].glont.height <<"w = "<<gloante[i].glont.width<<endl;

            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(gloante[i].x, gloante[i].y);// *transform2D::Scale(1, 1);
            RenderMesh2D(meshes["glont"], shaders["VertexColor"], modelMatrix);
        }
    }

    //inamic
    for (int i = 0; i < inamici.size(); i++) {
       
        if (inamici[i].coliziune == 0) {
            
            angularInc = atan2((pozY - inamici[i].y), (pozX - inamici[i].x));

            inamici[i].angular = angularInc;

            inamici[i].x += deltaTimeSeconds * cos(inamici[i].angular) * inamici[i].speed;
            inamici[i].y += deltaTimeSeconds * sin(inamici[i].angular) * inamici[i].speed;
            inamici[i].inamic.x = inamici[i].x;
            inamici[i].inamic.y = inamici[i].y;
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(inamici[i].x + cx, inamici[i].y + cy)
                * transform2D::Rotate(inamici[i].angular - PI / 2)
                * transform2D::Translate(-cx, -cy);
            RenderMesh2D(meshes["inamic"], shaders["VertexColor"], modelMatrix);
        }
        else {
            inamici[i].time += deltaTimeSeconds;

            if (inamici[i].time >= 5) {
                inamici[i].time = 0;
                inamici[i].coliziune = 0;
                inamici[i].x = rand() % 1513 + 42;
                inamici[i].y = rand() % 1464 + 43;
                inamici[i].inamic.x = inamici[i].x;
                inamici[i].inamic.y = inamici[i].y;
                inamici[i].speed = rand() % 300 + 50;
            }
        }
    }

    //obstacol pentru margine
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0) * transform2D::Scale(1, player_length);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0) * transform2D::Scale(player_length, 1);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, player_length * player_length - player_length) * transform2D::Scale(player_length, 1);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(player_length * player_length, 0) * transform2D::Scale(1, player_length);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);


    //obstacole in harta
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(360, 227) * transform2D::Scale(1, 25);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(150, 1360) * transform2D::Scale(25, 1);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1400, 230) * transform2D::Scale(1, 20);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(930, 230) * transform2D::Scale(12.5, 1);
    RenderMesh2D(meshes["obstacol"], shaders["VertexColor"], modelMatrix);

    //mapa
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0) 
        *transform2D::Scale(40,40);
    RenderMesh2D(meshes["mapa"], shaders["VertexColor"], modelMatrix);

   
}


void tema::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void tema::OnInputUpdate(float deltaTime, int mods)
{
    float lastX = pozX;
    float lastY = pozY;


    float lastColX = playerDef.x;
    float lastColY = playerDef.y;

    if (window->KeyHold(GLFW_KEY_W)) {

       
            pozY += deltaTime * speed;
            playerDef.y += deltaTime * speed;
           

    }
    if (window->KeyHold(GLFW_KEY_A)) {

        
            pozX -= deltaTime * speed;
            playerDef.x -= deltaTime * speed;
           

    }
    if (window->KeyHold(GLFW_KEY_S)) {

            pozY -= deltaTime * speed;
            playerDef.y -= deltaTime * speed;
           

    }
    if (window->KeyHold(GLFW_KEY_D)) {

       
            pozX += deltaTime * speed;
            playerDef.x += deltaTime * speed;
           
    }

    //player-obstacole
    for (int i = 0; i < obstacole.size(); i++) {
        //daca exista coliziune intre player si obstacol
        if (Collision(playerDef, obstacole[i])) {
            //se atribuie vechile pozitii inainte de coliziune
            //se schimba coordonatele la care se randeaza player-ul
            pozX = lastX;
            pozY = lastY;
            //se schimba collider-ul
            playerDef.x = lastColX;
            playerDef.y = lastColY;
        }
    }

     //glont - inamic 
    for (int i = 0; i < gloante.size(); i++) {
        for (int j = 0; j < obstacole.size(); j++) {
            //daca glontul exista si loveste un obstacol
            if (gloante[i].click == 1 && Collision(gloante[i].glont, obstacole[j])) {
                //dispare glontul de pe ecran
                gloante[i].click = 0;
            }    
        }
        for (int k = 0; k < inamici.size(); k++) {
            //daca exista glont si inamicul nu e mort si glontul nimereste inamicul
            if (gloante[i].click == 1 && inamici[k].coliziune == 0 && Collision(gloante[i].glont, inamici[k].inamic)) {
                //dispare inamicul, nu se mai randeaza
                inamici[k].coliziune = 1;
                //disparul glontul, nu se mai randeaza
                gloante[i].click = 0;
                //creste scorul
                scor++;
                //scade viata
                viata -= 10;
                cout << "Scorul este " << scor << endl;
            }
        }
    }
    

    //inamic si obstacole
    for (int j = 0; j < inamici.size(); j++) {
        for (int i = 0; i < 4; i++) {
            //daca inamicul loveste peretii mapei
            if (Collision(inamici[j].inamic, obstacole[i])) {
                //nu se mai randeaza 
                inamici[j].coliziune == 1;
            }
        }
    }
    
    //player si inamici
    for (int i = 0; i < inamici.size(); i++) {
        //daca exista coliziune intre player si inamic
        if (Collision(playerDef, inamici[i].inamic)) {
            //scade 
            if (scaleX < 0 && inamici[i].coliziune == 0) {
                scaleX++;
            } else if (scaleX >= 0) {
                cout << "Scorul este " << scor << endl;
                exit(0);
            }
            inamici[i].coliziune = 1;
        }
    }
}


void tema::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void tema::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void tema::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    //cout << "poz= " << pozX<< " " << pozY << endl;

    // Add mouse move event
    glm::ivec2 resolution = window->GetResolution();
    angularStep = atan2((resolution.y - mouseY - resolution.y / 2), (mouseX - resolution.x / 2));

}


void tema::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
        if (nr_glont < 5) {
            gloante[nr_glont].click = 1;
            gloante[nr_glont].x = pozX;
            gloante[nr_glont].y = pozY;

            gloante[nr_glont].glont.x = pozX;
            gloante[nr_glont].glont.y = pozY;

            gloante[nr_glont].angular = angularStep;
            nr_glont++;
            
        }
        else {
            nr_glont = 0;
        }
        
    }
}


void tema::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if (IS_BIT_SET(button, GLFW_MOUSE_BUTTON_LEFT)) {
       
        
    }
}


void tema::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void tema::OnWindowResize(int width, int height)
{
}

bool tema::Collision(corp a, corp b) {
    return (a.x <= (b.x + b.width) && (a.x + a.width)>= b.x &&
        a.y <= (b.y + b.height) && (a.y + a.height) >= b.y);
}
