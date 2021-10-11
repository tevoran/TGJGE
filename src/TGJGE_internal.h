#ifndef TGJGE_INTERNAL_H
#define TGJGE_INTERNAL_H

//shader types
#define TG_VERTEX 0
#define TG_FRAGMENT 1

void TG_load_shader(const int shader_type, const char *shader_location);
void TG_set_anim_frame(TG_object *object);

#endif