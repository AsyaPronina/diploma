uniform sampler3D texture_unit;
uniform float density, density_limit, step_length;
uniform vec3 box1, box2;
uniform vec3 camera_position;

in vec3 position;

void get_max_step(vec3 origin, vec3 direction, vec3 minimum, vec3 maximum, out float max_step, out float min_step)
{
    vec3 min_pos_t = (minimum - origin) / direction;
    vec3 max_pos_t = (maximum - origin) / direction;
    vec3 max_t = max(max_pos_t, min_pos_t);
    vec3 min_t = min(min_pos_t, max_pos_t);
    min_step = max(min_t.x, max(min_t.y, min_t.z));
    max_step = min(max_t.x, min(max_t.y, max_t.z));
}

void main(void)
{
    float global_opacity = 200.0;

    vec4 current_position = vec4(position, 0);
    vec3 ray = normalize(position - camera_position);
    vec4 step = vec4(ray * step_length, step_length);
    float max_step = 0.0, min_step = 0.0;
    vec4 color = vec4(0);

    get_max_step(position, ray, box1, box2, max_step, min_step);
    current_position += step * (min_step / step_length);
    float equ_sample = 0.0;

    //current_position += step;

    for (float i = 0.0; i < 2000.0 && (current_position.w < max_step); i += 0.1)
    {
        //trilinear interpolation
        //and texture specific y coordinate calcuating, because texture y axis is pointing up
        equ_sample = texture3D(texture_unit, vec3(current_position.x, 1.0f - current_position.y, current_position.z)).x;

        if (equ_sample > density)
        {
            vec4 clamped_color = vec4(clamp((equ_sample - density) / (density_limit - density), 0.0, 1.0));
            //front to back blending
            float d_alpha = (1.0 - color.w) * clamped_color.w * global_opacity;
            color.xyz = color.xyz + d_alpha * clamped_color.xyz;
            color.w = color.w + d_alpha;

            if (color.w > 0.98)
            {
                break;
            }
        }
        current_position += step;
    }

    gl_FragColor = color;
};
