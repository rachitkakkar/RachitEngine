#include "Window.h"
#include "Renderer.h"
#include "file-ops.hpp"

int main() {
    RachitEngine::Window win("RachitEngine", 800, 600);
    
    RachitEngine::Mesh cube;
    cube.vertices = {
        {-1.0f, 1.0f, 1.0f, 0xff000000},   {1.0f, 1.0f, 1.0f, 0xff0000ff},
        {-1.0f, -1.0f, 1.0f, 0xff00ff00},  {1.0f, -1.0f, 1.0f, 0xff00ffff},
        {-1.0f, 1.0f, -1.0f, 0xffff0000},  {1.0f, 1.0f, -1.0f, 0xffff00ff},
        {-1.0f, -1.0f, -1.0f, 0xffffff00}, {1.0f, -1.0f, -1.0f, 0xffffffff},
    };

    cube.triangles = {
        0, 1, 2, 1, 3, 2, 4, 6, 5, 5, 6, 7, 0, 2, 4, 4, 2, 6,
        1, 5, 3, 5, 7, 3, 0, 4, 1, 4, 5, 1, 2, 3, 6, 6, 3, 7,
    };

    cube.vertexShaderPath = "shader/v_simple.bin";
    cube.fragmentShaderPath = "shader/f_simple.bin";

    bgfx::setViewClear(0,
                     BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH,
                     0x443355FF, 1.0f, 0);
    bgfx::VertexLayout pcvDecl;
    pcvDecl.begin()
        .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
        .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
    .end();
    bgfx::VertexBufferHandle vbh = bgfx::createVertexBuffer(bgfx::makeRef(cube.vertices.data(), sizeof(RachitEngine::Vertex) * cube.vertices.size()), pcvDecl);
    bgfx::IndexBufferHandle ibh = bgfx::createIndexBuffer(bgfx::makeRef(cube.triangles.data(), sizeof(uint16_t) * cube.triangles.size()));

    std::string vshader;
    if (!fileops::read_file("shader/v_simple.bin", vshader)) {
        printf("Error reading shader v_simple!");
    }

    std::string fshader;
    if (!fileops::read_file("shader/f_simple.bin", fshader)) {
        printf("Error reading shader f_simple!");
    }

    bgfx::ShaderHandle vsh = RachitEngine::createShader(vshader, "vshader");
    bgfx::ShaderHandle fsh = RachitEngine::createShader(fshader, "fshader");
    bgfx::ProgramHandle program = bgfx::createProgram(vsh, fsh, true);
    
    RachitEngine::RenderObject cubeObject;
    cubeObject.createFromMesh(cube);
    
    // Main Loop
    bool quit = false;
    SDL_Event currentEvent;
    float counter = 0.0f;
    while (!quit) {
        while (SDL_PollEvent(&currentEvent) != 0) {
            if (currentEvent.type == SDL_QUIT) {
                quit = true;
            }
        }

        const bx::Vec3 at = {0.0f, 0.0f,  0.0f};
        const bx::Vec3 eye = {0.0f, 0.0f, -5.0f};
        float view[16];
        bx::mtxLookAt(view, eye, at);
        float proj[16];
        bx::mtxProj(proj, 60.0f, float(win.getWidth()) / float(win.getHeight()), 0.1f, 100.0f, bgfx::getCaps()->homogeneousDepth);
        bgfx::setViewTransform(0, view, proj);
        float mtx[16];
        bx::mtxRotateXY(mtx, counter * 0.01f, counter * 0.01f);
        bgfx::setTransform(mtx);        

        bgfx::setVertexBuffer(0, vbh);
        bgfx::setIndexBuffer(ibh);

        bgfx::setViewTransform(0, view, proj);

        bgfx::submit(0, cubeObject.program);
        bgfx::frame();

        counter += 2.0f;
    }
}