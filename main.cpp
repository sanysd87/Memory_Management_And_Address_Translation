#include <iostream>
#include <unordered_map>
#include <string>
#include <iomanip>  //for setw

std::unordered_map<int, int> pageFrameTable = {     //function that defines an unordered_map that represents the page/frame table
    // The keys (first set) are the logical page numbers, and the values (second set) are the corresponding frame's base addresses.
    {0x3A, 0x0D},
    {0xAB, 0x2B},
    {0x56, 0x15},
};

//This function takes a string and reference representing a hexadecimal logical address
void translate_logical_address(const std::string& logical_address_hexadecimal) {
    if (logical_address_hexadecimal.size() != 6) {  //if condition that check if strings are more than 6; "0x" is part of the string, so that is why it is 6 and not 4
        std::cerr << "Invalid logical address format: " << logical_address_hexadecimal << std::endl;
        return;
    }

    //Extract the page number and offset from the logical address
    std::string page_str = logical_address_hexadecimal.substr(2, 2);    //extracts the page number part(two characters after the "0x" prefix) of the logical address as a string.
    std::string offset_str = logical_address_hexadecimal.substr(4, 2);  //extracts the offset part (the last two characters) of the logical address as a string

    //stoi turns string into integer
    int page_number = std::stoi(page_str, nullptr, 16);
    int offset = std::stoi(offset_str, nullptr, 16);

    auto it = pageFrameTable.find(page_number);     //searches the pageFrameTable for the extracted page number.
    if (it != pageFrameTable.end()) {       //if condition that checks if page number is found
        //If found...
        int frame_base_address = it->second;    //... retrieves the frame's base address associated with that page number
        int physical_address = (frame_base_address << 8) | offset;  //... calculate the physical address by left-shifting the frame's base address by 8 bits (to make room for the offset)... 
        //...and then performs a bitwise OR with the offset

        //Outputs the result in the format of the sample output with the physical address
        std::cout << "Logical Address: " << logical_address_hexadecimal
            << " => Page Number: 0x" << std::setw(2) << std::setfill('0') << std::hex << it->first
            << ", Offset: 0x" << std::setw(2) << std::setfill('0') << std::hex << offset
            << ", Physical Address: 0x" << std::setw(4) << std::setfill('0') << physical_address << std::endl;
    }
    else {
        //If the page number is not found, it is a page fault...
        std::cout << "Logical Address: " << logical_address_hexadecimal     //...and prints in the format of the sample output with the page fault 
            << " => Page Number: 0x" << page_str
            << ", Offset: 0x" << offset_str
            << ", Page Fault!" << std::endl;
    }
}

int main() {
    //Translate the logical addresses and check for page faults
    translate_logical_address("0x3A7F");
    translate_logical_address("0xABCD");
    translate_logical_address("0x5678");
    //because "0x12" is not a key in the pageFrameTable.
    translate_logical_address("0x1234"); //This should cause a page fault

    return 0;
}