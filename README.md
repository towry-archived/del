# del

**rm** safe replacement tool on Mac OS.

## Install

This will install binary `del` into `/usr/local/bin`.

```bash
git clone https://github.com/towry/del.git /tmp/del
cd /tmp/del
make install
```

## Usage

```bash
del [-f | -i] [-dPRrvW] file ...

del a.txt // will move a.txt to your trash directory.

del a.txt b.txt // del a.txt and b.txt and ...

del -v a.txt b.txt // del a.txt and b.txt and show verbose display.
```

#### Options

| | description |
| --- | ---|
| `f` | delete the file in silence. |
| `i` | not supported.|
| `d` | delete the empty directory.	|
| `r` | delete the directory tree. (not supported currently). |
| `v` | verbose display |


## Still have some work to do

* support delete directory, `del_dir` function not finished.
* support delete unexpanded path like `~/a.txt` or `$HOME/a.txt`.

## License

wait a moment ...
