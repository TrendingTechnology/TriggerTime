Trigger Time (https://github.com/Sheph/TriggerTime)
=========================

**1. About**
-------------------
Trigger Time is a story-driven, top-down shoot'em up with a fun gravity gun and physics puzzles to solve.
Blast your way through 9 levels filled with enemies, hazards and bizarre bosses.
Along the way you'll take control of vehicles, pick up weapons, items and boosters.

Check out Trigger Time steam trailer on youtube:

[![Trigger Time Steam trailer](https://img.youtube.com/vi/u9Aoe5sreEg/0.jpg)](https://www.youtube.com/watch?v=u9Aoe5sreEg)

You can also get Trigger Time on Steam for free here: https://store.steampowered.com/app/512920

**2. Status**
-------------------
This is 100% full source code for the game. However, due to some legal stuff it's not possible to publish some of the in-game
music here on github. Those music files were replaced by "5 minutes of silence" dummy ogg files. If you want to have the
music in game you'll have to install the game from Steam (for free), locate music files and overwrite those dummy oggs. More
on that later.

**3. Building on windows**
-------------------

#### Install CMake

Download latest stable (not RC) .exe installer at http://www.cmake.org/download/

Version 3.2.3+ will do.

Run it, choose "Add CMake to the system PATH for all users", accept other defaults.

#### Install Visual Studio Express 2013 for Windows Desktop

Go to https://visualstudio.microsoft.com/vs/older-downloads/
find "Visual Studio Express 2013 for Windows Desktop" and press "download"

You'll need microsoft account, if you don't have one, create it and use it to download the installer.

Run the installer, accept all defaults (You may uncheck "experience improvement program" however).

Launch visual studio, don't select "sign in now", it's not necessary. Wait for first time setup to complete, you
can now exit visual studio if you like.

#### Generate visual studio solution

Open cmd shell (i.e. win key + R, type "cmd"), inside the shell run:

<pre>
cmake_Win32_VS2013.bat
</pre>

If everything was done right, you'll see CMake generating the solution and output:

<pre>
-- Build files have been written to: C:/Projects/TriggerTime/build_Win32_VS2013
</pre>

#### Build and run the game

Open visual studio if you haven't done so already, open
C:\Projects\TriggerTime\build_Win32_VS2013\AIRFORCE.sln solution.

* Set "tt" project as active project, i.e. right-click "tt" project and select "Set as StartUp project"
* Open "tt" project properties, i.e. right-click "tt" project and select "Properties"
* Set "Configuration" to "All Configurations"
* Go to "Configuration Properties -> Debugging" and change "Working Directory" to $(ProjectDir)..\out\bin\$(Configuration)
* Press "Ok"

Now you can build and run the game in different configurations, i.e. to build in release mode
choose "Release" in the topmost combox box and press "ctrl + F5"

Once the game is built you can also run it outside of IDE by simply
running "C:\Projects\TriggerTime\build_Win32_VS2013\out\bin\Release\tt.exe"

**4. Building on linux**
-------------------

<pre>
./cmake_x64_release.sh
cd ../TriggerTime-x64-release
make -j4
</pre>

Then:

<pre>
cd ./out/bin
./tt
</pre>

You can also use other cmake_xxx.sh scripts to generate debug, i386 and steam runtime version of the game.

**5. Building for android**
-------------------

Originally there was also an android build, but at some point the game became "PC only". There're still android makefiles
here and there, the game code still contains touchscreen control code, android platform code, etc. So technically, with some effort, one can get the game running on android again... But for now, the **build is broken**, so you were warned :)

#### Build commands

<pre>
cd ./android
echo "sdk.dir=/home/user/android-sdk-linux/sdk" > local.properties
/home/user/android-ndk-rxx/ndk-build
ant debug
</pre>

Then:

<pre>
adb install ./bin/AirForce-debug.apk
</pre>

#### Other NDK build options

Multithreaded build:
<pre>
/home/user/android-ndk-rxx/ndk-build -j8
</pre>

Build for one arch only:
<pre>
/home/user/android-ndk-rxx/ndk-build APP_ABI=x86
</pre>

Build for native debugging:
<pre>
/home/user/android-ndk-rxx/ndk-build NDK_DEBUG=1 APP_OPTIM=debug
</pre>

Start native debugging:
<pre>
bash /home/user/android-ndk-rxx/ndk-gdb --start
</pre>

**6. Replacing in-game music**
-------------------

Due to some legal stuff it's not possible to publish some of the in-game
music here on github. Those music files were replaced by "5 minutes of silence" dummy ogg files. If you want to have the
music in game you'll have to:

* Go to Steam and install the game: https://store.steampowered.com/app/512920
* If you're on windows, go to C:/Program Files (x86)/Steam/SteamApps/common/Trigger Time/assets
* If you're on linux, go to /home/user/.steam/steam/SteamApps/common/Trigger Time/assets
* Copy all action*.ogg and ambient*.ogg files to ./game/assets with overwriting

**7. Developer mode**
-------------------

TODO
