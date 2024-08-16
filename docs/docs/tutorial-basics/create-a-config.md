---
sidebar_position: 2
---

import Tabs from "@theme/Tabs"
import TabItem from "@theme/TabItem"

import Admonition from "@theme/Admonition"

# Create a Config

To create a config simply run:

<Tabs>
 <TabItem value="linux" label="Linux">

```bash
./el conf
```

**or**

```bash
touch config.lua
```

 </TabItem>

 <TabItem value="windows" label="Windows">

```powershell
type nul >> "config.lua"
```

</TabItem>

</Tabs>

After that you should end up with the `config.lua` file.

If you didnt create it with the `conf` argument then you would need to do this:

```lua title="config.lua"
conf = {

}
```

So you have a valid empty config.

# Config attributes

Here is an example of how a config file could look like:

```lua title="config.lua"
conf = {
    -- highlight-start
    name = "Best Game", -- Default set to Game
    fps = 60, -- Default set to 60
    terminal = false, -- Default set to false
    -- highlight-end
}
```

And what the default value is if you dont set it.
