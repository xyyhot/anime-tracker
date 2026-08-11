@echo off
rem =====================================================
rem  anime-tracker one-click build script (MinGW g++)
rem =====================================================
where g++ >nul 2>nul
if errorlevel 1 (
    echo [ERROR] g++ not found. Install MinGW-w64 or Visual Studio first.
    pause
    exit /b 1
)
if not exist build mkdir build
g++ -std=c++17 -Wall -O2 src\main.cpp src\storage.cpp src\http.cpp src\anilist.cpp -Iinclude -o build\anime_tracker.exe -lwininet
if errorlevel 1 (
    echo [ERROR] Build failed. Check the messages above.
    pause
    exit /b 1
)
echo.
echo Build OK: build\anime_tracker.exe
echo Run it:   build\anime_tracker.exe
pause
