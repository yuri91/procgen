# Compile the project with Cheerp

```
cd procgen
cmake -B jsbuild -DCMAKE_TOOLCHAIN_FILE=/opt/cheerp/share/cmake/Modules/CheerpToolchain.cmake .
cmake --build jsbuild
cmake --install jsbuild
```

Now just serve the directory `jsbuild/dist` with a web server.

# Try it

The master branch is automatically deployed to Github Pages, and it is reachable at https://yuri91.github.io/procgen/ .

You can pass options by encoding them in the query string.

Example: https://yuri91.github.io/procgen/?env_name="miner"&rand_seed=13423

This runs the "miner" environment with seed 13423. The available options are the same as the native version.
