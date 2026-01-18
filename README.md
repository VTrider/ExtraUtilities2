# Extra Utilities 2

Extra Utilities 2 is a script extender for Battlezone Combat Commander that provides more script utilities with high interoperability with stock. 
This mod targets the bleeding edge build of BZCC and should be able to update to a new build within hours if time permits. 

## Features
- First class support for LuaMission and DLL Missions
- Follows stock conventions: ie. functions that take a position are overloaded for handle, matrix, and vector
- Plug and play as an asset pack

## Tutorial

Before using this mod you should have very advanced knowledge of your desired platform (either Lua or C++), and BZCC modding in general.
If you are an experienced modder and are looking for certain features that the stock game doesn't provide, you've come to the right place.
This mod has both a Lua and C++ API. Before going into the platform dependent instructions, there are a few things to do.

- Add the [workshop item](https://steamcommunity.com/sharedfiles/filedetails/?id=3515140097) as an asset dependency for your mod. ID: 3515140097.
- Ensure you are running the latest private beta build of BZCC.

Using this mod as a vendored dependency where you make a copy of the library to use in your mod is HIGHLY discouraged. You will not get automatic
updates, you waste space, and having multiple copies of the library in your filesystem could potentially cause major issues. You will not receive support
if you use Extra Utilities 2 as a vendored dependency. Please use the library as an asset dependency with the [official steam workshop item](https://steamcommunity.com/sharedfiles/filedetails/?id=3515140097).

### LuaMission

This mod only supports stock LuaMission i.e. the one that lives in the BZCC game folder. This is because Extra Utilities 2 relies on the Lua API
that this LuaMission exports. It is also the most up to date with the latest BZCC version. Custom LuaMissions such as "LuaMission Update" on the workshop,
or the LuaMission integrated into VSR are not supported. If you have a custom LuaMission and would like to provide support, see the advanced usage section.

Next, copy the `ExtraUtils.lua` file from this repo or from the workshop folder. This file is a definition file for the Lua Language Server. Other protocols like 
EmmyLua are not supported. Add this to your workspace in your editor of choice that supports the Lua Language Server like VSCode or Neovim, and this will
provide code completion and documentation for the Lua API.

Once you have your mod and workspace configured properly, using the library is very simple:

```lua
-- Call at the beginning of your script with other imports
local exu2 = require("ExtraUtilities2)

-- You're now ready to use the library!
print(exu2.GetSteam64())
```

### DLL Mission

Integration with DLL missions is slightly more complex so you should be comfortable with C++ before attempting.
You will need the following files: `ExtraUtils.h`, `ExtraUtilities2.lib`, and optionally `ExtraUtilities2.pdb` for
debugging symbols.

In Visual Studio:

- Copy `ExtraUtils.h` into your include directory
- Copy `ExtraUtilities2.lib` into your lib directory
- In your project settings go to `Linker -> input` and under `Delay Loaded Dlls` add `ExtraUtilities2.dll`
- Then go to `Linker -> Advanced` and under `Unload delay loaded DLL` select `Yes (/DELAY:UNLOAD)`

Once the project is configured, go to `dllmain.cpp` and make sure the following code is in place:

```cpp
#include <ExtraUtils.h>
#include <Windows.h>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        exu2::ProcessAttach(); // Critical function
        break;
    case DLL_PROCESS_DETACH:
        exu2::ProcessDetach(); // Critical function
        break;
    }
    return TRUE;
}
```

Ensure that `exu2::ProcessAttach` and `exu2::ProcessDetach` are called in their respective locations.
Take caution when working inside the DllMain switch statement to not allow for case fallthroughs. I recommend
removing the cases for thread attach/detach unless you specifically need them.

You are now ready to `#include <ExtraUtils.h` and call the functions!

## Updating the Mod

If all goes well the workshop build should be updated within 1 day of a new patch release. If there are serious architectural
changes to the game it may take longer. In the case that functions become obsolete due to being implemented in the stock game,
the exu2 api will simply forward the call to the stock function to maintain compatibility as long as the effects are identical.

For developers, there are a few steps to updating the mod:

- Extract a .def file from LuaMission.dll, and use it to create a LuaMission.lib import library.
- Use the list of pattern scans in `exu2.json` to resolve the offsets needed for the library. They follow the IDA pattern format and should work with most pattern scanning tools.
- Replace the old `LuaMission.lib` and `Offsets.h` with the new ones.
- Update the version string, and the version stamp in the `ExtraUtilities2.rc` file.

## Advanced Usage

If you are only interested in using the library in your mods you can stop here.

### Custom or Development Build

If you want to use the latest development build from source, or use your own custom version, you will need to handle
the dll loader search path. This mod relies on delay loaded dlls to make usage seamless for the user, and by default it
targets the dll in the workshop folder which will be the latest stable release. For a custom build you need to make the following
modifications:

```cpp
// ExtraUtils.h

inline void ProcessAttach()
{
	SetDefaultDllDirectories(LOAD_LIBRARY_SEARCH_APPLICATION_DIR |
							 LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | 
							 LOAD_LIBRARY_SEARCH_SYSTEM32 |
							 LOAD_LIBRARY_SEARCH_USER_DIRS
	);
	// AddDllDirectory(GetWorkshopPath().append("3515140097").append("Bin").c_str());
  // Call AddDllDirectory() with the path to your custom ExtraUtilities2.dll to
  // ensure it gets loaded instead of the workshop build.
}
```

You should also modify the `versionString` and the resource files to indicate that the build is custom.
Putting your name and custom version number in `ExtraUtilities2.rc` will do well do differentiate it from
the workshop build.

### Custom LuaMission

If you really want to use a custom LuaMission you can, but you need to provide exports for all of the Lua C API. This mod
targets Lua 5.2.0, so your LuaMission must remain compatible. After that, you should be able to `require()` this mod as a C library
in Lua like normal. If your LuaMission has a different name, make sure to change all references of LuaMission in the project to 
use your custom name. So this includes the unloading logic in `exu2::ProcessDetach` and the linker settings.
the mod should be able to load properly. 
