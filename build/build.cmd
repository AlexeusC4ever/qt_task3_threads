set PATH=D:\Qt5\Tools\CMake_64\bin;%PATH%
set PATH=D:\Qt5\Tools\Ninja;%PATH%
set PATH=C:\Qt\Tools\mingw810_64\bin;%PATH%

cmake^
 -G "Ninja"^
 -D CMAKE_PREFIX_PATH="D:\Qt5\5.13.2\msvc2015_64"^
 ..

pause	
	
cmake --build .

pause

cmake --build .