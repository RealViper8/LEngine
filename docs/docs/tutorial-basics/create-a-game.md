---
sidebar_position: 1
---

# Create a Game

Add **el** executable file to your desired location make sure it is in an empty directory to create a **standalone page**:

- `init.lua` → Entrypoint
- `config.lua` → A config file

## Create your first Game

Create a file at the game directory called `init.lua`.

This is an example of how a `init.lua` file **could** look:

:::note Note
This example shows how to use it with autocompletion !
:::

```lua title="/init.lua"
_G.run = true
_G.status_code = 0

_G.start = start
_G.update = update
_G.exit = exit

-- Console Functions
_G.exit_game = exit_game
_G.clear = clear
_G.log = log
_G.log_bold = log_bold

-- GUI Functions
_G.set_rect_position = set_rect_position
_G.draw_rect = draw_rect
_G.render_window = render_window
_G.clear_render = clear_render
_G.draw = draw

_G.pressed_key = pressed_key
_G.on_specific_key = on_specific_key

local player = { x = 15, y = 15, w = 50, h = 50 }
local move_speed = 5

-- This function is executed 60 times every frame (if default).
function _G.update(deltaTime)
    print("DeltaTime: " .. deltaTime)
end

function _G.on_specific_key(key)
	if key == "right" then
		player.x = player.x + move_speed
	elseif key == "left" then
		player.x = player.x - move_speed
	elseif key == "up" then
		player.y = player.y - move_speed
	elseif key == "down" then
		player.y = player.y + move_speed
	end
end

-- This function is executed one time.
function _G.start(game_name)
	print("Starting " .. game_name)
	return 0
end

-- This function is executed when the game exits.
function _G.exit(exit_code)
	_G.run = false
	print("Exiting with Exit Code: " .. exit_code)
end
```

Just start the executable `el` and you should be ready to go !

If any errors show up then it will be stored in the `status_code` variable and the `exit(status_code)` function will be executed with the status code as parameter.
