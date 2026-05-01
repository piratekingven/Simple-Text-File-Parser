This is a custom text file parser built in C, implementing efficient memory management.

We parse the words using ' ' and '\n' as delimiters.

We parse the words and store the words and their lengths in an extendable array of structs. The words are stored using a pointer in the struct, so we can keep allocating memory to the pointer incase the word becomes too long. 

The extendable array is created using a pointer and malloc, so we can accommodate an increasing number of words.

We don't allocate memory each time for each byte/array slot when it is required (which is very inefficient) and instead, allocate multiple bytes/array slots of memory at once when needed, and then cut the memory that is not used using realloc(), so we only use memory that we truly use. 

Once the parsing is over, we print the stored words and their lengths, and then free the memory allocated using free().

If we pass an empty file to the program, or don't even pass a file to the program, it will print the appropriate message and exit the program.

Syntax to use : a.exe [filename] [ for Windows ]

Syntax to use : ./a.out [filename] [ for Linux ]
(Too broke for Mac)
