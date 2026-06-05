// #include <iostream>
// #include <cstring>

// void causeBufferOverflow() {
//     char smallBuffer[5];
//     // Security Flaw: copy 12 bytes into a 5-byte buffer array
//     std::strcpy(smallBuffer, "UnsafeString"); 
//     std::cout << "Buffer contents: " << smallBuffer << std::endl;
// }

// void causeMemoryLeak() {
//     // Performance Flaw: Allocating memory but never running delete[] to free it
//     int* leakedArray = new int[100];
//     leakedArray[0] = 42;
//     std::cout << "Memory allocated at address: " << leakedArray << std::endl;
// }

// int main() {
//     std::cout << "--- Starting Application Tests ---" << std::endl;
//     causeBufferOverflow();
//     causeMemoryLeak();
//     std::cout << "--- Execution Finished Safely ---" << std::endl;
//     return 0;
// }


#include <iostream>
#include <cstring>
#include <string>

void causeBufferOverflow() {
    // FIX: Using std::string dynamically manages memory to prevent buffer boundaries issues
    std::string safeBuffer = "UnsafeString"; 
    std::cout << "Buffer contents: " << safeBuffer << std::endl;
}

void causeMemoryLeak() {
    // FIX: Match the allocation pointer with a corresponding 'delete' statement
    int* leakedArray = new int[5];
    leakedArray[0] = 42;
    std::cout << "Memory allocated at address: " << leakedArray << std::endl;
    
    // Crucial cleanup step for Valgrind
    delete[] leakedArray; 
}

int main() {
    std::cout << "--- Starting Application Tests ---" << std::endl;
    causeBufferOverflow();
    causeMemoryLeak();
    std::cout << "--- Execution Finished Safely ---" << std::endl;
    return 0;
}
