# Database Test Specification

## Overview

This document outlines a set of tests for a simple database implementation. The tests are designed to verify basic functionality such as data insertion, retrieval, and error handling in a database system.

### Setup

Before each test, the existing database file is removed to ensure a clean state.

```sh
rm -rf test.db

```

Utility Function: run_script
A helper function, run_script, is defined to interact with the database by sending commands and capturing outputs.

Insert Command
```sh
insert 1 user1 person1@example.com
select
.exit
```

Duplicate Keysq
```sh
insert 1 user1 person1@example.com
insert 1 user1 person1@example.com
```


BTree Leaf Node Format
```sh
.btree

```

```sh 

insert 1 user1 person1@example.com
insert 2 user2 person2@example.com
insert 3 user3 person3@example.com
insert 4 user4 person4@example.com
insert 5 user5 person5@example.com
insert 6 user6 person6@example.com
insert 7 user7 person7@example.com
insert 8 user8 person8@example.com
insert 9 user9 person9@example.com
insert 10 user10 person10@example.com
insert 11 user11 person11@example.com
insert 12 user12 person12@example.com
insert 13 user13 person13@example.com
insert 14 user14 person14@example.com
```