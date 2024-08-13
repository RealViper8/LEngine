const std = @import("std");
const clua = @import("lib/zlua.zig");

const Types = enum {
    TRUE,
    FALSE,
    DEBUG,
    NONE,
};

const Engine = struct {
    debug: bool,
    line: u32,
    pwd: bool,
};

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    const stdin = std.io.getStdIn().reader();

    var buffered_writer = std.io.bufferedWriter(stdout);

    var running: bool = true;

    var buffer: [1024]u8 = undefined;

    var engine = Engine{
        .line = 0,
        .debug = false,
        .pwd = true,
    };

    // var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    // defer arena.deinit();
    // const allocator = arena.allocator();

    //var args = std.ArrayList(Types).init(allocator);
    //defer allocator.free(args);

    try stdout.writeAll("\n\x1b[1;32m--- \x1b[0;36mLENGINE \x1b[1;32m---\n");
    try stdout.writeAll("  \x1b[0;32mVERSION \x1b[1;36m1.0  \n\x1b[0m\n");

    while (running) {
        if (engine.pwd) try stdout.print("[{}] lengine -> ", .{engine.line});

        const line = try stdin.readUntilDelimiter(&buffer, '\n');

        var it = std.mem.splitSequence(u8, line, " ");

        if (engine.debug) _ = try buffered_writer.write("\x1b[0;32mArgs: \n");
        if (engine.debug) try buffered_writer.flush();
        while (it.next()) |item| {
            if (engine.debug) try stdout.print("  {s} ", .{item});

            const arg = item;

            if (std.mem.eql(u8, arg, "break") or std.mem.eql(u8, arg, "exit")) running = false;
            if (std.mem.eql(u8, arg, "help")) {
                try stdout.writeAll("\n\x1b[1;36mLEngine \x1b[1;35m- \x1b[0;32mLightweight Game Engine\n");
                try stdout.writeAll("\n\x1b[0;32mCommands:\n");
                try stdout.writeAll("\x1b[1;35mrun            \x1b[0;36m- runs a lua file\n");
                try stdout.writeAll("\x1b[1;35mbreak          \x1b[0;36m- exits out of this cli\n");
                try stdout.writeAll("\x1b[1;35mhelp           \x1b[0;36m- shows this menu\n");
                try stdout.writeAll("\x1b[1;35mdebug <bool>   \x1b[0;36m- sets the debug property\n\x1b[0m");
            }

            const arg2 = it.peek();

            if (std.mem.eql(u8, arg, "debug") and arg2 != null and std.mem.eql(u8, arg2.?, "true")) {
                engine.debug = true;
            }

            if (std.mem.eql(u8, arg, "debug") and arg2 != null and std.mem.eql(u8, arg2.?, "false")) {
                engine.debug = false;
            }
            // try args.append(toType(item));
        }
        try stdout.print("\x1b[0m\n", .{});

        engine.line += 1;
        buffer = undefined;
    }
}
