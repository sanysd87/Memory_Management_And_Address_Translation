Project Title: Memory Management And Address Translation

Language: C++

Description: The purpose of this project is to demonstrate memory management and address translation. The program accepts logical addresses as inputs and translates the logical addresses to physical addresses based on the page/frame table. 
It also handles page faults from there not being a page number in the page/frame table.
The output contains the original logical address and provides corresponding physical addresses, along with page numbers and offsets, as output(s).

When you download the project, you can run it on basically any IDE. Many popular ones are Visual Studio, Visual Studio code, Online IDE, and Online GDB. 
If you want to try to put new logical addresses, simply put "translate_logical_address("0xXXXX");", where "XXXX" can be any hexadecimal number. 
If you want to change the page/frame table, it will be in "std::unordered_map<int, int> pageFrameTable = {...}", in line 6 of the code.
