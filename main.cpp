#include <iostream>
#include <Windows.h>
#include <vector>

int main() {
    std::vector<std::pair<char*, size_t>> allocatedMemory;
    while (true) {
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(memoryStatus);
        GlobalMemoryStatusEx(&memoryStatus);
        DWORDLONG availablePhysicalMemory = memoryStatus.ullAvailPhys;
        std::cout << "trying to allocate " << availablePhysicalMemory / (1024 * 1024) << " MB\n";

        try {
            char* allocatedMemoryBlock = new char[availablePhysicalMemory];
            allocatedMemory.push_back(std::make_pair(allocatedMemoryBlock, availablePhysicalMemory));
        }
        catch (const std::bad_alloc& e) {
            std::cerr << "oops: " << e.what() << '\n';


            for (const auto& allocation : allocatedMemory) {
                delete[] allocation.first;
                std::cout << "freed " << allocation.second / (1024 * 1024) << " MB\n";
            }
            allocatedMemory.clear();
        }
        Sleep(100);
    }
    return 0;
}
