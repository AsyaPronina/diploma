in vec3 vertex;
out vec3 position;
uniform mat4 mvp_matrix;
void main(void)
{
     position = vertex;
     vec4 vertex4 = vec4(vertex, 1);
     gl_Position = mvp_matrix * vertex4;
}
