#include "Renderer.h"

namespace RachitEngine {
    bgfx::ShaderHandle createShader(const std::string& shader, const char* name) {
        const bgfx::Memory* mem = bgfx::copy(shader.data(), shader.size());
        const bgfx::ShaderHandle handle = bgfx::createShader(mem);
        bgfx::setName(handle, name);
        return handle;
    };

    void RenderObject::createFromMesh(Mesh mesh) {
        vertexLayout.begin()
            .add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
            .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
        .end();
        vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(mesh.vertices.data(), sizeof(RachitEngine::Vertex) * mesh.vertices.size()), vertexLayout);
        indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(mesh.triangles.data(), sizeof(uint16_t) * mesh.triangles.size()));
        
        std::string vshader;
        if (!fileops::read_file(mesh.vertexShaderPath, vshader)) {
            printf("Error reading shader v_simple!");
        }

        std::string fshader;
        if (!fileops::read_file(mesh.fragmentShaderPath, fshader)) {
            printf("Error reading shader f_simple!");
        }

        vertexShader = createShader(vshader, "vshader");
        fragmentShader = createShader(fshader, "fshader");
        program = bgfx::createProgram(vertexShader, fragmentShader, true);
    }
};