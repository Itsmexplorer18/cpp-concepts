#include <iostream>
#include <vector>
#include <chrono>
//refer notes code taken for sagar medium article 

const int PAGE_SIZE = 4096; // Standard memory page size in bytes
const int INTS_PER_PAGE = PAGE_SIZE / sizeof(int); // 1024 integers fit in one page

// This function performs 'totalAccesses' memory reads. 
// It cycles continuously through a 'workingSetPages' number of distinct memory pages.
void testTLB_Capacity(int workingSetPages, int totalAccesses) {
    // Allocate enough memory to hold our working set of pages
    std::vector<int> memory(workingSetPages * INTS_PER_PAGE, 0);

    // Calculate how many times we need to loop to hit our totalAccesses target
    int iterations = totalAccesses / workingSetPages;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i) {
        // Loop through our working set of pages.
        // We touch exactly ONE integer per page.
        for (int p = 0; p < workingSetPages; ++p) {
            // Indexing by (p * INTS_PER_PAGE) forces the CPU to jump exactly 4096 bytes,
            // landing on a completely different memory page every single loop iteration.
            memory[p * INTS_PER_PAGE]++; 
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;
    
    std::cout << "Working Set: " << workingSetPages << " Pages (" 
              << (workingSetPages * 4) << " KB)\t | Time: " 
              << elapsed.count() << " ms\n";
}

int main() {
    // We will do exactly 10 Million memory accesses in both scenarios.
    const int TOTAL_WORK = 10000000; 

    std::cout << "Starting TLB Capacity Benchmark...\n";
    std::cout << "------------------------------------------------------\n";

    // Scenario 1: Small working set. 
    // 32 Pages easily fits inside a standard L1 TLB (usually 64+ entries).
    // The TLB grabs the mappings once and keeps them. Extremely fast!
    testTLB_Capacity(32, TOTAL_WORK);

    // Scenario 2: Large working set.
    // 2048 Pages greatly exceeds the TLB capacity.
    // By the time the inner loop finishes reading page 2047, the TLB has already 
    // evicted the mapping for page 0 to make room. When the outer loop restarts 
    // and asks for page 0 again, it suffers a TLB Miss. (TLB Thrashing!)
    testTLB_Capacity(2048, TOTAL_WORK);
        testTLB_Capacity(4096, TOTAL_WORK);
        testTLB_Capacity(8192, TOTAL_WORK);
        testTLB_Capacity(16384, TOTAL_WORK);



    return 0;
}
