# Building Assimp

You can use the link [here](https://github.com/assimp/assimp/blob/master/Build.md) Be aware that not all the parts of the assimp is required for the Phase 2.

This reporsitory uses release 5.1.1 of the assimp. Final release (5.2.3) gives compilation errors on fresh Ubuntu 20.04. 

In order to build use: 

```
g++ <test_name>  -o <test_name> `pkg-config --libs --cflags assimp`
```
