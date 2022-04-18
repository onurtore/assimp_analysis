In order to build use: 

```
g++ -g <test_name>  -o <test_name> `pkg-config --libs --cflags assimp ignition-common<N> ignition-math<N>`
```
You can get the installed ignition libraries using

```
pkg-config --list-all |grep ignition-common
```

