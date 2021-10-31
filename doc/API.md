# Description of the TGJGE api

## Initialization

The engine is initialized by calling the function

```c
void TG_init(const char *window_title, int res_x, int res_y, _Bool fullscreen_toggle);
```

You can set various parameters to let the created window fit your
needs. But because of the bool data type you need to have a compiler
that can compile C99. Although this shouldn't be an issue today
anymore.

## Quitting the engine

The engine can be quitted by calling the TG_quit
function.

```c
void TG_quit();
```

It will end SDL and the related OpenGL stuff. But it
is still necessary to destroy all objects and
textures on your own if you want to have a clean end
of execution.

## Updating the window

Once you drew everything into the framebuffer then you may wish to see your result. You can do this by calling

```c 
void TG_new_frame(float r, float g, float b); 
```

The TG_new_frame function takes in three floats as parameters. They are used to set the background color of the screen.

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

## Input

### Keyboard

Keyboard input can be read with a function called TG_is_key_pressed.
It returns a false if this particular key is not currently pressed
and true if it is pressed.

As its input the function currently processes SDL2 Scancodes.
A collection of all of them can be found here at
https://wiki.libsdl.org/SDL_Scancode

```c
_Bool TG_is_key_pressed(unsigned char key);
``` 

### Mouse

The mouse input is split into two parts. The first one is the position
of the mouse cursor on the screen. This is described by two floats
with values between 0.0f and 1.0f. 0.0f is the left side of the screen
for the X-axis and the bottom side of the screen for the Y-axis;

```c
void TG_mouse_position(float *x, float *y);
```

The second part are the buttons on the mouse. There are a few
functions to get the state of certain buttons on the mouse.

```c
_Bool TG_mouse_is_left_pressed();
_Bool TG_mouse_is_right_pressed();
```

They return true if the respective button is pressed and false if it
isn't.

### Mouse Cursor

As your OS or your window manager provides you with a default
cursor, you may not want this cursor visible in your game. This is
why there is a function to be able to disable the cursor and to
enable it, if you wish to do so.

```c
	void TG_show_cursor(_Bool toggle);
```

Use true to enable the cursor or false to disable the cursor.


## Objects

In TGJGE quads are used to render everything on the screen. They are
simply called TG_object;

The basic structure of the usage of a TG_object object is to create,
doing some stuff and destroy it.

```c
TG_object* TG_new_object(
	float size_x,
	float size_y,
	float pos_x,
	float pos_y);
void TG_render_object(const TG_object *object);
void TG_destroy_object(TG_object *object);
```

During the object's creation it is necessary to give some information
about it.

The size and position are screen relative, i.e. a screen filling 
sprite has the size (1.0f, 1.0f) and a sprite with a quarter of the
screen's size is (0.5f, 0.5f). For the sprite's positioning it is
important to note that the screen's origin is always the left bottom
corner of the screen.

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

#### Rotation

It is possible to rotate an object with the function TG_rotate_object.

```c
void TG_rotate_object(TG_object *object, float radians);
```

This function will rotate an object around its center in a clockwise
manner. It is also important to note that the rotation angle is an
absolute one and is given in radians. Therefore a full rotation equals
2 * PI. 

### Textures/Sprites

Textures can be loaded from images in the following formats JPEG, PNG, BMP,
GIF, PSD, HDR, PIC and PNM. The textures can be attached to TG_objects and
will be displayed with them and turn them effectively into sprites.

The num_frames input is especially important if a sprite
needs to be animated later on. If it's not animated then one can leave
the value at 1.
Animations are always stored in image files that store all the ani-
mations in a horizontal strip. Therefore the num_frames input is used
to divide the strip into displayable frames.

TG_new_texture is used to create a new texture from a file located in path.
An interesting feature is the linear interpolation toggle. If it's false then
the texels are clearly visible with sharp borders while it's completely differen
when it's activated with true. Then low res textures can become quite blurry
with very loosely visible borders.

```c
TG_texture* TG_new_texture(
	const char *path,
	int num_frames,
	_Bool linear_interpolation_toggle);
```

The function to assign a texture to an object. If the texture doesn't exist at
the time of drawing then the object will most likely not be rendered although
the exact behaviour depends on the local OpenGL implementation.

```c
void TG_object_use_texture(TG_object *object, TG_texture *texture);
```

After the texture is not used anymore then it should be destroyed by calling

```c
void TG_destroy_texture(TG_texture *texture);
```

but this should only happen when the texture isn't used on any object anymore.

### Animations

To be able to use the animation system it is important to have an
active texture that is used with an object. But once an object and a
texture are connected it is easy to start an animation sequence with

```c
void TG_object_start_animation(
	TG_object *object,
	int start_frame, 
	int end_frame, 
	int duration_ms,
	_Bool loop);
```

This function starts an animation sequence and uses the animation
frame strip in the texture to get from the start frame to the end
frame in the duration provided by the user.

The loop toggle is true for infinitely looping the animation until a
TG_object_stop_animation() is getting called. If it's false then it
will be executed only once.

If it is necessary to stop an animation then there is the function

```c
void TG_object_stop_animation(TG_object *object);
```

### Collision

In games it is often necessary to detect the collision between two
objects. Therefore TGJGE can detect if two objects overlap. In this
case the two objects are treated as simple quads. This might be very
accurate or not, depending on your used sprite.

```c
_Bool TG_is_colliding(TG_object *a, TG_object *b);
```

The function above is returns true if the two objects overlap and is
false if they don't overlap.

## Text

If text needs to be rendered on the screen then you will need a
TG_text object and a TG_font object.

The font acts in a similar way like a texture acts to a 2D object in
TGJGE.

### Font

A TG_font needs to be loaded from a file. Supported file types are TTF
and FON.

```c
TG_font* TG_new_font(const char *path, unsigned int font_size_pt);
```

It creates a font with a specific size. It can be streached and so on
but it will determine how pixelated the text will look. So if you need
different point sizes then you need to create different fonts.

At the of the game's runtime it is advised to destroy all the used
fonts.

```c
void TG_destroy_font(TG_font *font);
```

### Text objects

Once a font is created, it can be used to generate a TG_text object.
This kind of object contains all the data that is necessary to display
a given text.

```c
TG_text* TG_new_text(
	TG_font *font, 
	const char *text, 
	float size_x, 
	float size_y, 
	float pos_x, 
	float pos_y,
	float color_r,
	float color_g,
	float color_b);
```

The color values are also between 0.0f and 1.0f. So a text with the
color 0.0f, 0.0f, 0.0f will be black.

```c
void TG_render_text(TG_text *text);
void TG_destroy_text(TG_text *text);
```

## Audio

