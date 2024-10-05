# my_ls

Submit directory	. 
Submit files	Makefile - *.c - *.h

Description
Write a programm called my_ls. Following the specifications of this page.

SPECIFICATIONS
NAME
my_ls -- list directory contents

SYNOPSIS
my_ls [-at] [file ...]

# DESCRIPTION
For each operand that names a file of a type other than directory, my_ls displays its name as well as any requested, associated information. 
For each operand that names a file of type directory, my_ls displays the names of files contained within that directory, as well as any requested, 
associated information.

If no operands are given, the contents of the current directory are displayed. If more than one operand is given, non-directory operands are displayed first; directory and non-directory operands are sorted separately and in lexicographical order.

The following options are available:
```
-a Include directory entries whose names begin with a dot (.).
-t Sort by time modified (most recently modified first) before sorting the operands by lexicographical order.
```

# Requirements
Your code must be compiled with the flags -Wall -Wextra -Werror.

Hint(s)
Watch out for memory leaks !
You can test your code against memory errors by compiling with the debugging flags -g3 -fsanitize=address
Global variables are strictly FORBIDDEN
tv_sec AND tv_nsec are used for the -t options ;-)
st_mtime is not what you want to use. You want to use st_mtim
Technical information
you must create a Makefile, and the ouput is the command itself

You can use:
malloc(3)
free(3)
printf(3)
write(2)
stat(2)
lstat(2)
opendir(2)
closedir(2)
readdir(2)

You can NOT use:
Any functions / syscalls which does not appear in the previous list
Yes, it includes exit, errno, qsort, strdup, snprintf, strrchr, perror, realloc, and getopt.
Multiline macros are forbidden
Include another .c is forbidden
Macros with logic (while/if/variables/...) are forbidden

Your output needs to be respecting the "sorting" criteria and in one column. It will be compared with: ls -1.
```
$>./my_ls > my_ls.output
$>ls -1 > ls.output
$>diff my_ls.output ls.output
$>
```
Tips
Check /dev What is the difference between stat and lstat?

# Tests to pass
```
Test 1: ./my_ls
MY LS CAN YOU RUN  /MY LS AND IT PRINTS THE CONTENT OF THE CURRENT DIRECTORY?
Test 2: ./my_ls .
 MY LS CAN YOU RUN  /MY LS . AND IT PRINTS THE CONTENT OF THE CURRENT DIRECTORY?
Test 3: ./my_ls /tmp/
MY LS CAN YOU RUN  /MY LS /TMP/ AND IT PRINTS THE CONTENT OF THE DIRECTORY? 
Test 4: ./my_ls -t
MY LS CAN YOU RUN  /MY LS -T AND IT PRINTS THE CONTENT OF THE CURRENT DIRECTORY (SORTED BY TIME)? 
Test 5: ./my_ls -a
MY LS CAN YOU RUN  /MY LS -A AND IT PRINTS THE CONTENT OFTHE CURRENT DIRECTORY WITH . FILES?   
Test 6: ./my_ls -ta
MY LS CAN YOU RUN  /MY LS -TA AND IT PRINTS THE CONTENT OF THE MARVEL DIRECTORY (SORTED BY TIME) + HIDDEN FILES? 
Test 7: ./my_ls DIR1 DIR2
MY LS CAN YOU RUN  /MY LS DIR1 DIR2 AND IT PRINTS THE CONTENT OF THE TWO DIRECTORIES? 
Test 8: ./my_ls -t -a 
MY LS CAN YOU RUN  /MY LS -T -A AND IT PRINTS THE CONTENT OF THE MARVEL DIRECTORY (SORTED BY TIME SEC + NSEC + ALPHANUM ) + HIDDEN FILES?
```

currently the code fails ./my_ls -t -a , ./my_ls -ta, ./my_ls DIR1 DIR2
