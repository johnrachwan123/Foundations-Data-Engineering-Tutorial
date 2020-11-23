## The Thing King
### Paging Game
This "Paging Game" rules were written by Jeff Berryman, University of British Columbia, 1972.

1. Each player gets several million *things*.
2. Things are kept in *crates* that hold 4096 things each. Things in the same crate are called *crate-mates*.
3. Crates are stored either in the *workshop* or in the *warehouse*. The workshop is almost always too small to hold all the crates.
4. There is only one workshop, but there may be several warehouses. Everybody shares them.
5. Each thing has its own *thing number*.
6. What you do with a thing is to *zark* it. Everybody takes turns zarking.
7. You can only zark your own things, not anybody else's.
8. Things may only be zarked when they are in the workshop.
9. Only the *Thing King* knows whether a thing is in the workshop or in a warehouse.
10. The longer a thing goes without being zarked, the *grubbier* it is said to become.
11. The way to get things is to ask the Thing King. He only gives out things in crates. This is to keep royal overhead down.
12. The way to zark a thing is to give its thing number. If you give the number of a thing that happens to be in the workshop, it gets zarked right away. If it is in a warehouse, the Thing King moves the crate containing your thing into the workshop. If there is no room in the workshop, he first finds the grubbiest crate in the workshop, whether it be yours or somebody else's, and packs it off with all its crate-mates to a warehouse. In its place he puts the crate containing your thing. Your thing gets zarked and you never even know that it wasn't in the workshop all along.
Each player's stock of things has the same numbers as everybody else's. The Thing King always knows who owns what thing and whose turn it is, so you can't ever accidentally zark somebody else's thing even if it has the same number as one of yours.
 

*** NOTES ***

1. Traditionally, the Thing King sits at a large, segmented table and is attended by pages (the so-called "table pages") whose jobs it is to help the king remember where all the things are and to whom they belong.
2. One consequence of Rule 13 is that everybody's thing numbers will be similar from game to game, regardless of the number of players.
3. The Thing King has a few things of his own, some of which move back and forth between workshop and warehouse just like anybody else's, but some of which are just too heavy to move out of the workshop.
4. With the given set of rules, oft-zarked things tend to get kept mostly in the workshop, while little-zarked things stay mostly in a warehouse.
5. Sometimes even the warehouses get full. The Thing King then has to start piling things on the dump out back. This makes the game slow because it takes a long time to get things off the dump when they are needed in the workshop. A forthcoming change in the rules will allow the Thing King to select the grubbiest things in the warehouses and send them to dump in his spare time, thus keeping the warehouses from getting too full. This means that the most infrequently-zarked things will end up in the dump so the Thing King won't have to get things from the dump so often. This should speed up the game when there are lots of users and the warehouses are getting full.


This short set of rules should give you some intuition regarding how memory works. Note that it was written in 1972! 
Many things changed since then, and in reality whole process is much, much more complex. However, the general rules remained the same. 

### Paging Game - VM Manager Version

Here is an explanation using technical terminology 

1. Each process gets several million *bytes*.
2. Bytes are kept in *pages* that hold 4096 bytes each. Bytes on the same page have *locality of reference*.
3. Pages are stored either in *memory* or on the *disk*. The memory is almost always too small to hold all the pages.
4. There is only one memory, but there may be several disks. Everybody shares them.
5. Each byte has its own *virtual address*.
6. What you do with a byte is to *reference* it. Everybody takes turns referencing.
7. You can only reference your own bytes, not anybody else's.
8. Bytes may only be referenced when they are in the memory.
9. Only the *VM Manager* knows whether a byte is in the memory or on a disk.
10. The longer a byte goes without being referenced, the *older* it is said to become.
11. The way to get bytes is to ask the VM Manager. He only gives out bytes in pages. This is to keep overhead down.
12. The way to reference a byte is to give its virtual address. If you give the address of a byte that happens to be in the memory, it gets referenced right away. If it is on a disk, the VM Manager moves the page containing your byte into the memory. If there is no room in the memory, he first finds the oldest page in the memory, whether it be yours or somebody else's, and packs it off with the rest of the page to a disk. In its place he puts the page containing your byte. Your byte gets referenced and you never even know that it wasn't in the memory all along.
13. Each process's stock of bytes has the same virtual addresses as everybody else's. The VM Manager always knows who owns what byte and whose turn it is, so you can't ever accidentally reference somebody else's byte even if it has the same virtual address as one of yours.
 

*** NOTES ***

1. Traditionally, the VM Manager uses a large, segmented table and "page tables" whose jobs it is to help the king remember where all the bytes are and to whom they belong.
2. One consequence of Rule 13 is that everybody's virtual address will be similar from game to game, regardless of the number of processs.
3. The VM Manager has a few bytes of his own, some of which move back and forth between memory and disk just like anybody else's, but some of which are just too heavyily used to move out of the memory.
4. With the given set of rules, oft-referenced bytes tend to get kept mostly in the memory, while little-referenced bytes stay mostly on a disk.
5. Sometimes even the disks get full. The VM Manager then has to start piling bytes on the dump out back. This makes the computer slow because it takes a long time to get bytes off the dump when they are needed in the memory. A forthcoming change in the rules will allow the VM Manager to select the grubbiest bytes in the disks and send them to dump in his spare time, thus keeping the disks from getting too full. This means that the most infrequently-referenceed bytes will end up in the dump so the VM Manager won't have to get bytes from the dump so often. This should speed up the game when there are a lot of processs and the disks are getting full.

## Process memory layout

([source](https://manybutfinite.com/post/anatomy-of-a-program-in-memory/))
![memory schema](linuxFlexibleAddressSpaceLayout.png) 

In the schema above we can see how process memory is divided in 32-bit system. 

Very important thing to realize it that, this is **Virtual Memory**. From process perspective, there is 3GB of exclusive continuous RAM to use. However, those are virtual addresses and
whenever they are accessed Operating System (**OS**) *translates* them into **Physical Memory**. Moreover it doesn't mean that system reserved 3GB of space for this process, it just means that
at some point in time the process can request memory from this pool. 

The sum of all virtual memory spaces (of all running processes) can be (and usually is) much bigger than physical memory (RAM) available. 
But because not all processes are executed simultaneously and OS can store some content of ram on the hard drive, 
it can "trick" processes to "think" they actually have all the memory available for themselves. 
  
There are 7 memory areas in the diagram above, let's take a look at each of them.

* Kernel space: This space is not available for the process and points to the same physical memory for each process. 
This does not mean the kernel uses that much physical memory, only that it has that portion of address space available to map whatever physical memory it wishes.
* Stack stores local variables and function parameters in most programming languages. Calling a method or function pushes a new stack frame onto the stack. The stack frame is destroyed when the function returns. 
* Below the stack, we have the memory mapping segment. Here the kernel maps contents of files directly to memory. Any application can ask for such a mapping via the Linux mmap() system call.
* The heap provides runtime memory allocation, like the stack, meant for data that must outlive the function doing the allocation, unlike the stack. Most languages provide heap management to programs. Satisfying memory requests is thus a joint affair between the language runtime and the kernel. In C, the interface to heap allocation is malloc() and friends.
* BSS, Data and Text segments store "static" content of the process.

## Loading a file: read vs map

(NOTE: The description below is very simplified and does not take into the account many of modern development in this area. However, it should give you enough information to proceed with next exercises.)

Regardless which option you choose, the file loading operation **always** goes through the **Page Cache**. As the name suggest, Page Cache stores data pages 
(chunks of memory, usually 4KB). The pages are the smallest unit of memory for OS. Even if you request to read one byte (e.g. only first character from the file)
whole page will be loaded into the Page Cache. 

### Read
(Assumption: the file hasn't been read yet and isn't present in RAM)
* Process ask the OS to load X bytes of the file.
* OS reads the Y pages (where Y contains all X bytes and possibly more, so that the page system preserved)
* The data are read into the **Page Cache** 
* The data are **copied** from Page Cache into the process **User Space**
* The data are mapped to the **heap** address pool of the process.
* Process can use the data

If other process requests the same data, the OS will realize that it already loaded them into the Page Cache and no I/O will be perfromed.
However OS will **copy** the data from Page Cache into the other process User Space again.

There are two main downsides of this approach.

1. The data has to be copied inside of RAM for each process, which influences the process performance.
2. The data is duplicated, we are "wasting" RAM.

However, in this case each process has exclusive data copy. Write operations are very easy, as the don't have to be synchronized with other processes. 
The data is flushed back to the file at *some point* in the future.

### Map
 (Assumption: the file hasn't been read yet and isn't present in RAM)
 * Process ask the OS to load X bytes of the file.
 * **Memory Mapping Segment** addresses of the process are mapped into the Page Cache physical addresses (**Nothing is read from disk!**)
 * The process tries to read data from file, goes to the Page Cache which doesn't contain any data yet.
 * **Page Fault** exception is thrown and only now OS read a single page from the disk - this is called **lazy loading**.
 * Process can use the data
 
 If other process requests the same data, the OS will simply map its virtual memory into existing pages in Page Cache - **no copying or I/O!**.
 
 In this way we solved two main disadvantages of buffered read. However, we have complicated the write operation.
 
 There are two options for writes.
 
 1. Shared mapping - processes write back to the same address in Page Cache - synchronization is required! The data is flushed back to the file at *some point* in the future.
 2. Private mapping (Copy-on-write) - whenever process wants to write something, the contend of the Page is **copied** to a different location. Thus we do not required to synchronize
 however file opened in this way **cannot be flushed back into the file**. The changes will remain only visible to the process and will be gone after process is finished.
