# Description of the TGJGE api

## Initialization

The engine is initialized by calling the function

```c
void TG_init(const char *window_title, int res_x, int res_y, _Bool fullscreen_toggle);
```


You can set various parameters to let the created window fit your needs. But because of the _Bool you need to have a compiler that can compile C99. Although this shouldn't be an issue today anymore.


## Updating the window

Once you drew everything into the framebuffer then you may wish to see your result. You can do this by calling

```c 
void TG_flip(float r, float g, float b); 
```

The TG_flip function takes in three floats as parameters. They are used to set the background color of the screen.

## Objects

In TGJGE quads are used to render everything on the screen. They are
simply called TG_object;

The basic structure of the usage of a TG_object object is to create,
doing some stuff and destroy it.

```c
TG_object* TG_new_object();
void TG_render_object(const TG_object *object);
void TG_destroy_object(TG_object *object);
```