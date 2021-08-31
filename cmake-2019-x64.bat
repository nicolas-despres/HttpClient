set GENERATE_PROJECT_NAME=.build-2019-x64

cd %~dp0
mkdir %GENERATE_PROJECT_NAME%
cd %GENERATE_PROJECT_NAME%
call cmake -G "Visual Studio 16 2019" -A x64 "%~dp0"

call cmake --build "." --config Release --target testHttp --clean-first

cd..
