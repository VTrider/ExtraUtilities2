--- @meta exu2
--- This file provides the lua definitions for Extra Utilities 2
--- This depends on AI Unit's BZCC Lua Function Sigs. 
--- If you are missing definitions for stock symbols, make sure it is
--- added to your lua language server workspace. You can find this on
--- the Battlezone Scrap Field GitHub organization.

error("This is a definition file, use require(\"ExtraUtilities2\")")

--- @class exu2
--- @field VERSION string
local exu2 = {}

--- Camera

-- Perspective functions warning: don't use the built in matrix functions,
-- they only work on the 3x3 portion of the matrix. Perspective transformations
-- require 4x4, and you need vec4's with a W component.

--- Returns the current perspective projection matrix.
--- @return Matrix
function exu2.GetPerspectiveMatrix() end

--- Returns the current view matrix.
--- @return Matrix
function exu2.GetViewMatrix() end

--- Returns true if the local player is in satellite mode.
--- This is triggered by using the terminal of a comm bunker, antenna, eyes of xyr, etc.
--- @return boolean
function exu2.InSatellite() end

--- Wrapper over WorldToScreen if you only want to know if something is visible.
--- Note that this only determines if a point is within the camera's view,
--- it doesn't account for map geometry or line of sight.
--- @param h Handle
--- @return boolean
function exu2.IsVisible(h) end

--- Wrapper over WorldToScreen if you only want to know if something is visible.
--- @param m Matrix
--- @return boolean
function exu2.IsVisible(m) end

--- Wrapper over WorldToScreen if you only want to know if something is visible.
--- @param v Vector
--- @return boolean
function exu2.IsVisible(v) end

--- Returns a vector with normalized screen coordinates [0,1].
--- The z component is the depth, larger values are closer to the camera.
--- Returns nil if the position is not visible.
--- @param h Handle
--- @return Vector | nil
function exu2.WorldToScreen(h) end

--- Returns a vector with normalized screen coordinates [0,1].
--- The z component is the depth, larger values are closer to the camera.
--- Returns nil if the position is not visible.
--- @param worldMat Matrix
--- @return boolean visible
function exu2.WorldToScreen(worldMat) end

--- Returns a vector with normalized screen coordinates [0,1].
--- The z component is the depth, larger values are closer to the camera.
--- Returns nil if the position is not visible.
--- @param worldPos Vector
--- @return boolean visible
function exu2.WorldToScreen(worldPos) end

--- Console

--- Gets the count of arguments supplied to the current command.
--- Note: Includes the command name (minimum 1).
--- @return integer
function exu2.IFace_GetArgCount() end

--- Gets a float value at the given position if it exists.
--- @param arg integer
--- @return number | nil
function exu2.IFace_GetArgFloat(arg) end

--- Gets an integer value at the given position if it exists.
--- @param arg integer
--- @return integer | nil
function exu2.IFace_GetArgInteger(arg) end

--- Gets a string value at the given position if it exists.
--- @param arg integer
--- @return string | nil
function exu2.IFace_GetArgString(arg) end

--- Filesystem

--- Returns the root BZCC directory where the executable is.
--- @return string
function exu2.GetBZCCPath() end

--- Returns the BZCC steam workshop directory.
--- @return string
function exu2.GetWorkshopPath() end

--- Graphics

--- Gets the current viewport size in pixels (X, Y).
--- @return number x
--- @return number y
function exu2.GetViewportSize() end

--- Steam

--- Gets the Steam 64 ID of the local user.
--- Note that it's a string because lua 5.2 doesn't support
--- 64 bit integers
--- @return string
function exu2.GetSteam64() end

--- VarSys

--- Deletes an IFace item and all its subdirectories.
--- @param name string
--- @return boolean success
function exu2.IFace_DeleteItem(name) end

return exu2
