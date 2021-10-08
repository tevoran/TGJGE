# Description of the TGJGE api

## Initialization

The engine is initialized by calling the function

```c
void TG_init(const char *window_title, int res_x, int res_y, _Bool fullscreen_toggle);
```

You can set various parameters to let the created window fit your
needs. But because of the _Bool you need to have a compiler that can
compile C99. Although this shouldn't be an issue today anymore.


## Updating the window

Once you drew everything into the framebuffer then you may wish to see your result. You can do this by calling

```c 
void TG_flip(float r, float g, float b); 
```

The TG_flip function takes in three floats as parameters. They are used to set the background color of the screen.

This function also updates the timers for each frame. This enables the
engine's user to get the current delta time.

## Time

As mentioned in "Updating the window" the TG_flip() function updates
all the timers that are used by the engine itself.

To get the current delta time you can use these two functions.
But beware they only have a ms resolution which should be enough for
almost anything game related.

```c
int TG_delta_time();
float TG_delta_time_f();
```

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

### Transformations

There are several transformations that can be applied to the basic quad.
You can set it at any position and can scale it.

It is important to note that the origin of the engine's coordinate system is
the left bottom corner. It's the same for both the root window and the used
quads.

```c

void TG_resize_object(TG_object *object, float size_x, float size_y);
void TG_set_position_object(TG_object *object, float pos_x, float pos_y);
```

### Textures

