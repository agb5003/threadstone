How OpenGL interprets the vertices depends entirely on the primitive type you specify in your draw call:

# GL_TRIANGLES

OpenGL takes every consecutive group of 3 vertices as an independent triangle.

Example: If you have vertices v0, v1, v2, v3, v4, v5, OpenGL forms triangles: (v0,v1,v2), (v3,v4,v5).

So with 8 vertices, only the first 6 would form 2 triangles; the last 2 vertices wouldn't form a triangle at all.

# GL_TRIANGLE_STRIP

After the first two vertices, each new vertex forms a triangle with the previous two.

Example: v0,v1,v2,v3 → triangles (v0,v1,v2) and (v1,v2,v3)

This is useful for making connected meshes efficiently.

# GL_TRIANGLE_FAN

The first vertex is the "center," and each subsequent pair of vertices forms a triangle with it.

Example: v0,v1,v2,v3 → triangles (v0,v1,v2) and (v0,v2,v3)