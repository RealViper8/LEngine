---
sidebar_position: 3
---

# Functions

So as you know there are plenty functions and I will later implement more.

## Console functions

:::note
if the function has an comment with param for Example test(status_code) -- param

It means that the function gives you the parameter
::::

```lua
exit_game(status_code) --param
    ^ -> global function if it exits

log(text, code)
    ^ -> the text should be a string.
    | -> the code:
      |  0 for info
      |  1 for error
      |  2 for warning

log_bold(text, code)
    -> Same as log it just prints it out bold

update(delta_time) -- param
    ^ -> global function runs every frame and stores the deltaTime (is controlled by fps)

draw(renderer) -- param
    ^ -> global function runs every millisecond (not controlled by fps)

start(game_name) -- param
    ^ -> global function runs only one time at the start of the game with the game_name

key_pressed(key) -- param
    ^ -> global function stores the key.
      -> wich can be checked with this in the key_pressed function:
            if key == 'w' then print("PRESSED W") end
```

Yes thats it these are the console functions and more are coming in the future !

:::danger
Experimental GUI functions may cause some issues !
:::

To **use** this set `terminal = false` in `config.lua`:

```lua
draw(render) -- param
    ^ -> global function which gives you the render.

draw_rect(x, y, w, h)
    ^ -> Position: x, y
    | -> w: Width, h: Height

render_window(render)
    ^ -> To render the window.
    | -> The render in the draw function

clear_render(render)
    ^ -> To clear the window.
    | -> The render in the draw function
```

Thats it for the GUI functions be careful since it is **experimental**.
