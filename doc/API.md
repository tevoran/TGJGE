# Description of the TGJGE api

## Initialization

The engine is initialized by calling the function

```c
void TG_init(const char *window_title, int res_x, int res_y, _Bool fullscreen_toggle);
```


You can set various parameters to let the created window fit your needs.
But because of the _Bool you need to have a compiler that can compile C99.




