#ifndef RENDERER
#define RENDERER

#include <vector>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>

#include "file-ops.hpp"

namespace RachitEngine {
    bgfx::ShaderHandle createShader(const std::string& shader, const char* name);
    struct Vertex {
        float x;
        float y;
        float z;
        uint32_t abgr;
    };

    struct Mesh { // a mesh is just vertices, indices/triangles, and link to a vertex shader and fragment shader.
                  // in the future, a mesh will contain things like a position, rotation, texture, ect.
        std::vector<Vertex> vertices;
        std::vector<uint16_t> triangles;
        std::string vertexShaderPath;
        std::string fragmentShaderPath;
    };

    struct RenderObject { // a render object is essentially a mesh with all the components needed to render is, including compiled shaders, a vertex buffer, index buffer, ect.
        bgfx::ShaderHandle vertexShader;
        bgfx::ShaderHandle fragmentShader;
        bgfx::ProgramHandle program;
        bgfx::VertexLayout vertexLayout;
        bgfx::VertexBufferHandle vertexBuffer;
        bgfx::IndexBufferHandle indexBuffer;

        void createFromMesh(Mesh mesh); // this function generates the above components using the basic information of the mesh
    };


    class Renderer {
    public:
        void Draw(RenderObject object); // the renderer will than take in all the components (vertex buffer, index buffer, ect.) of a render object and then bind and use them
    };
    // essentially renderering an object is done like this:
    // first create a mesh, then turn that mesh into a render object using createFromMesh object, than use the draw method to render the final output
};

#endif