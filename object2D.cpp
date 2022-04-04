#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreatePlayer(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
   // glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        //corp
        VertexFormat(corner, glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(length, 0, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(1, 1, 0)),
        //ureche stanga
        VertexFormat(corner + glm::vec3(length / 10, length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(4 * length / 10, length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(4 * length / 10, 3 * length / 10 + length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(length / 10, 3 * length / 10 + length, 0), glm::vec3(1, 1, 1)),
        //ureche dreapta
        VertexFormat(corner + glm::vec3(6 * length / 10,  length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(9 * length / 10,  length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(6 * length / 10, 3 * length / 10 + length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(9 * length / 10, 3 * length / 10 + length, 0), glm::vec3(1, 1, 1)),
        //ochi stanga
         VertexFormat(corner + glm::vec3(2 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(3 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(2 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(3 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
        //ochi dreapta
         VertexFormat(corner + glm::vec3(7 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(8 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(7 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(8 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0))
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 
                                         12, 13, 14,
                                         15, 13, 14,
                                         16, 17, 18,
                                         19, 17, 18,
                                         0, 1, 2,
                                         3,  0, 2,
                                         4, 5, 6,
                                         7, 4, 6,
                                          8, 9, 10,
                                          11, 9 , 10,
                                           };

   
    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateInamic(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    //std::vector<VertexFormat> vertices =
    //{
    //    //corp
    //    VertexFormat(corner, glm::vec3(0.4f, 0, 0)),
    //    VertexFormat(corner + glm::vec3(length, 0, 0), glm::vec3(0.4f, 0, 0)),
    //    VertexFormat(corner + glm::vec3(length, length, 0),  glm::vec3(0.4f, 0, 0)),
    //    VertexFormat(corner + glm::vec3(0, length, 0),  glm::vec3(0.4f, 0, 0)),

    //    //ochi stanga
    //    VertexFormat(corner + glm::vec3(2 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
    //    VertexFormat(corner + glm::vec3(3 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
    //    VertexFormat(corner + glm::vec3(2 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
    //    VertexFormat(corner + glm::vec3(3 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
    //    //ochi dreapta
    //    VertexFormat(corner + glm::vec3(7 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
    //    VertexFormat(corner + glm::vec3(8 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
    //    VertexFormat(corner + glm::vec3(7 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
    //    VertexFormat(corner + glm::vec3(8 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0))
    //};

    //Mesh* square = new Mesh(name);
    //std::vector<unsigned int> indices = { 0, 1, 2,
    //                                      3, 0, 2,
    //                                      4, 5, 6,
    //                                      7, 4, 6,
    //                                      8, 9, 10,
    //                                      11, 8, 9

    //};
    //
     std::vector<VertexFormat> vertices =
    {
        //corp
        VertexFormat(corner, glm::vec3(0.4f, 0, 0)),
        VertexFormat(corner + glm::vec3(length, 0, 0), glm::vec3(0.4f, 0, 0)),
        VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(0.4f, 0, 0)),
        VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(0.4f, 0, 0)),
        //ureche stanga
        VertexFormat(corner + glm::vec3(length / 10, length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(4 * length / 10, length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(4 * length / 10, 3 * length / 10 + length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(length / 10, 3 * length / 10 + length, 0), glm::vec3(1, 1, 1)),
        //ureche dreapta
        VertexFormat(corner + glm::vec3(6 * length / 10,  length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(9 * length / 10,  length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(6 * length / 10, 3 * length / 10 + length, 0), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(9 * length / 10, 3 * length / 10 + length, 0), glm::vec3(1, 1, 1)),
        //ochi stanga
         VertexFormat(corner + glm::vec3(2 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(3 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(2 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(3 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
        //ochi dreapta
         VertexFormat(corner + glm::vec3(7 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(8 * length / 10, 7 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(7 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0)),
         VertexFormat(corner + glm::vec3(8 * length / 10, 6 * length / 10 , 0), glm::vec3(0, 0, 0))
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 
                                         12, 13, 14,
                                         15, 13, 14,
                                         16, 17, 18,
                                         19, 17, 18,
                                         0, 1, 2,
                                         3,  0, 2,
                                        };

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateObstacle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, glm::vec3(0, 0.5f, 0)),
        VertexFormat(corner + glm::vec3(length, 0, 0),glm::vec3(0, 0.5f, 0)),
        VertexFormat(corner + glm::vec3(length, length, 0), glm::vec3(0, 0.5f, 0)),
        VertexFormat(corner + glm::vec3(0, length, 0), glm::vec3(0, 0.5f, 0))
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 
        3, 0, 2 };
    

    square->InitFromData(vertices, indices);
    return square;
}