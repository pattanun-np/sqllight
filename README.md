# SQL LIGHT

This is project making simple sql lite from scratch with `C`. It is a simple project to understand how sql lite works.

## Few step of sql lite

- tokenizer
- parser
- code generator

The input to the front-end is a SQL query. the output is sqlite virtual machine `bytecode (essentially a compiled program that can operate on the database).

The back-end consists of the:

- virtual machine
- B-tree
- pager
- os interface

## How to run

### With Bash

```bash
make
./sqlight
```

### With Docker

```bash
    docker build -t sqlight .
    docker run -it sqlight
```

## Available make commands

- `make` - build the project
- `make clean` - clean the project
- `make run` - run the project
- `make format` - format the project

## References

- [SQLite Architecture](https://www.sqlite.org/arch.html)
- [The SQLite Bytecode Engine](https://www.sqlite.org/opcode.html)  
- [SQLite B-Tree](https://www.sqlite.org/fileformat2.html)
- [SQLite Pager](https://www.sqlite.org/fileformat2.html)

## License

MIT License

## Author

Pattanan Numpong Lodash (Thailand) Co., Ltd.

Team StandUpCode

```citation
@misc{sqlight,
  author = {Pattanan Numpong},
  title = {SQL Light},
  year = {2024},
  
  company = {Lodash (Thailand) Co., Ltd.},
  publisher = {GitHub},
  journal = {GitHub repository},
}


```
