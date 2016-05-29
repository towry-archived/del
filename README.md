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

`del [-f | -i] [-dPRrvW] file ...`

```bash
del a.txt // will move a.txt to your trash directory.
```

#### Options

| | description |
| --- | ---|
| `f` | delete the file in silence. |
| `i` | not supported.|
| `d` | delete the empty directory.	|
| `r` | delete the directory tree. (not supported currently). |


## Still have some work to do

* support delete directory, `del_dir` function not finished.
* support delete unexpanded path like `~/a.txt` or `$HOME/a.txt`.

## License

wait a moment ...
