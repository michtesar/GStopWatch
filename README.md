# GStopWatch

A small playground for start of **How to develop GUI applications in Linux** with GTK3+ and C programming language.

This little repository shows how to setup CMakeLists.txt to compile against C99 and GTK3+ for C on Ubuntu 20.04.

GUI is made in Glade and GTK3+ loads the XML definition at runtime.

## Dependencies

```bash
sudo apt install cmake libgtk-3-dev
```

Optionally for development also:

```bash
sudo apt install glade
```

## Instal lfrom source

CD into repository and then:

```bash
mkdir ./build
cd ./build
cmake ..
make
```

## Run 

In build folder run:
`./gsw`

Usually it should be possible to make it executable 

`chmod +x ./gsw` 

but there is an issue with GNOME 3 file browser (Nautilus), that does not recognize build file as executable but text file.
