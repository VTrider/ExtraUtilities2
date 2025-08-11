--[[
Example DLL Loader by VTrider

There's probably a better way to do it that I
Don't know about
--]]

local dll_loader = {}
do
    -- The following two functions are by DivisionByZero -VT
    local function splitAtSemicolon(str)
        local results = {}
        for substr in string.gmatch(str, '([^;]+)') do
            table.insert(results, substr)
        end
        return results
    end

    local function getGameDirectory()
        local path = splitAtSemicolon(package.cpath)[1]
        return string.match(path, "(.*)\\%?")
    end

    local function getSteamWorkshopDirectory()
        local gameDirectory = getGameDirectory()
        local workshopRelativePath = "steamapps\\workshop\\content\\624970"

        local commonDirectory = "steamapps\\common\\BZ2R"
        local commonDirectoryIndex = string.find(gameDirectory, commonDirectory)

        if commonDirectoryIndex then
            gameDirectory = gameDirectory:sub(1, commonDirectoryIndex - 2)
        end

        return gameDirectory .. "\\" .. workshopRelativePath
    end

    function dll_loader.require(workshop_id, ...)
        local path = getSteamWorkshopDirectory()
        path = path .. "\\" .. workshop_id
        for _, folder in ipairs({...}) do
            path = path .. "\\" .. folder
        end
        package.cpath = package.cpath .. ";" .. path .. "\\" .. "?.dll"
    end
end
return dll_loader

