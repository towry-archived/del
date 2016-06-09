# del

**rm** safe replacement tool on Mac OS.

This tool will move the files into your trash directory instead of deleting it permanently.

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

del -r a/ b/ 	// del directory a and b
```

#### Options

| | description |
| --- | ---|
| `f` | delete the file in silence. |
| `i` | not supported.|
| `d` | delete the empty directory.	|
| `r` | delete the directory tree. |
| `v` | verbose display |


## License

wait a moment ...
