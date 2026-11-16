# FileSkin
Edit info, data, metadata and other info of file in 1 app!
Lightweight and fast file utility written in C using GTK. No bloat, just simple file manipulation.

# Project Status
- [x] Linux support
- [ ] Windows support (in progress / maybe later)
- [x] View file size
- [ ] Basic stat info
- [ ] "Touch" button (update file timestamps)
- [ ] Edit file metadata & permissions (chmod)
- [ ] Batch file renaming & numbering (regex)
- [ ] Custom themes / minimal UI tweaks

# How to use?
Drug any file into the "fileskin" app or type in the linux terminal:
```bash
./fileskin (any path of file you want)
```

# Build from source
Make sure you have `gcc` and `gtk3` installed and use
```bash
gcc main.c -o fileskin `pkg-config --cflags --libs gtk+-3.0`
```
or
```bash
gcc main.c -o fileskin (pkg-config --cflags --libs gtk+-3.0 | string split " ")
```
if GTK is not detected by gcc
