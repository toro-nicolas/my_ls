# my_ls 🗂️



### Table of contents 📑
- [Project goal](https://github.com/toro-nicolas/my_ls#project-goal-)
- [How to compile it ?](https://github.com/toro-nicolas/my_ls#how-to-compile-it--)
- [How to use it ?](https://github.com/toro-nicolas/my_ls#how-to-use-it--)
- [Final result on my.epitech.eu](https://github.com/toro-nicolas/my_ls#final-result-on-myepitecheu-)

### Project goal 🎯
Reproduction of the linux command "ls" in C.    
This program lists the files in a folder.    
The following flags are supported:    
- **a :** to display hidden files    
- **l :** to display all file information (size, date, ...)    
- **R :** to display all files recursively    
- **d :** to display only selected files and folders    
- **t :** to sort by order of modification    
- **r :** to sort in reverse order    

### How to compile it ? 🛠️
Make the game :
```shell
make
```

Make the libs :
```shell
make libs
```

Re make the game :
```shell
# This command will deleted all the compiled files
make re
```

Remove all compiled files (*.o) :
```shell
make clean
```

<p>Remove all compiled files (*.o), all compiled libs (*.a), all unit tests and program executable  :</p>

```shell
make fclean
```

Make a unit_tests file :
```shell
make unit_tests
```

Make and run a unit_tests file with the coverage :
```shell
make tests_run
```

### How to use it ? 💻
Usage :
```Shell
./my_ls [-alRdrt] [FILE]
```

### Final result on my.epitech.eu 🚩
|                             Test name                              | Status |
|:------------------------------------------------------------------:|:------:|
|                      Empty directory listing                       |   ✅    |
|                       Multiple file listing                        |   ✅    |
|                  Sanity check 2 - error handling                   |   ✅    |
|                  Sanity check 2 - error handling                   |   ✅    |
|                        Single file listing                         |   ✅    |
|                     Access rights on directory                     |   ✅    |
|                   Access rights on regular file                    |   ✅    |
|                                Date                                |   ✅    |
|                             File size                              |   ✅    |
|                  No access right on regular file                   |   ✅    |
|                             Sticky bit                             |   ✅    |
|                           UID resolving                            |   ✅    |
|                       Recursive file listing                       |   ✅    |
|          Recursive listing (-lR) , testing access rights           |   ✅    |
| Recursive listing including hidden file (-l -R), separated options |   ✅    |
|           Recursive listing including hidden file (-lR)            |   ✅    |
|                          Time sorting #1                           |   ✅    |
|                          Time sorting #2                           |   ✅    |
|                    Testing device type & major                     |   ✅    |

I obtained **100%** with **99% lines** and **90%** branches in the last test.
