const std = @import("std");

const lua = @cImport({
    @cInclude("lua.h");
    @cInclude("lualib.h");
    @cInclude("lauxlib.h");
});

pub fn run_file(file: []const u8) void {
    const L = lua.LuaL_newstate();
    lua.luaL_openlibs(L);

    if (check(L, lua.lua_dofile(file))) {
        std.io.getStdOut().writer().print("[*] File {s} was executed successfully !", .{file});
    }

    lua.lua_close(L);
}

fn check(L: lua.lua_State, result: i8) bool {
    var works: bool = false;

    if (result != 0) {
        const errmsg = lua.lua_tostring(L, -1);
        std.debug.print("Lua error: {}\n", .{errmsg});
    } else works = true;

    return works;
}
