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
del a.txt // will move a.txt to your trash directory.
```

## Still have some work to do

* support delete directory, `del_dir` function not finished.
* support delete unexpanded path like `~/a.txt` or `$HOME/a.txt`.

## License

wait a moment ...
