--[[
Lua entry point for script extender.
Allows you to type require("ExtraUtilities2")
and returns the dll module
--]]

local exu2
do
    local dll_loader = require("dll_loader")
    dll_loader.require("3515140097", "Bin")
    local old_path = package.path
    package.path = ""
    exu2 = require("ExtraUtilities2")
    package.path = old_path
end
return exu2