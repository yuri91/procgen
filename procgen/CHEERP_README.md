# Compile the project with Cheerp

```
cd procgen
cmake -B jsbuild -DCMAKE_TOOLCHAIN_FILE=/opt/cheerp/share/cmake/Modules/CheerpToolchain.cmake .
cmake --build jsbuild
cmake --install jsbuild
```

Now just serve the directory `jsbuild/dist` with a web server.

