# directories
## about directories

This is a program I wrote to get more familiar with C and writing platform dependent code. 
Currently the project supports linux and Win32. The program lists out the content of the user's
current working directory and allows them to traverse through their filesystem. It is by no means
fool proof, but it is intended as more of an exercise. I hope you enjoy playing around with it!

## Getting started

The project is built using cmake, a CMakeLists.txt file is included.
Once you've cloned the repository, you can build it by doing the following:

```bash
  $ mkdir build
  $ cmake -B build/
  $ make -C build/
  $ ./directories
```


