#include <iostream>

// Compile with TWO commands to see the difference:
//
// BEFORE C++17:  g++ -std=c++14 -fno-elide-constructors photo.cpp -o photo14 && ./photo14
//   -fno-elide-constructors forces compiler to show every move (disables silent optimization)
//   You will see: constructor → move → move → destructors
//
// C++17:         g++ -std=c++17 photo.cpp -o photo17 && ./photo17
//   C++17 mandatory RVO — prvalue is constructed directly in myPhoto's memory
//   You will see: constructor → destructor (move constructor never called)

struct Photo {
    int w, h;

    // Step 1: always fires once — creates the actual Photo{100,200}
    Photo(int w, int h) : w(w), h(h) {
        std::cout << "Photo(int,int) — constructor\n";
    }

    // C++14: fires TWICE — once moving out of createPhoto(), once into myPhoto
    // C++17: never fires — object is built directly in myPhoto, no middleman
    Photo(Photo&& o) : w(o.w), h(o.h) {
        std::cout << "Photo(Photo&&) — move constructor\n";
    }

    // C++14: fires 3 times — temp + return slot + myPhoto all destroyed separately
    // C++17: fires once  — only myPhoto is destroyed at end of main
    ~Photo() {
        std::cout << "~Photo() — destructor\n";
    }
};

// The return type is a prvalue (Photo{100,200} has no name, no address)
// C++14: compiler creates it, then moves it to return slot, then moves to myPhoto
// C++17: compiler sees prvalue and constructs it directly in myPhoto — zero moves
Photo createPhoto() {
    return Photo{100, 200};
}

int main() {
    Photo myPhoto = createPhoto();
    std::cout << "--- end of main ---\n";
    return 0;
}

// -------------------------------------------------------
// EXPECTED OUTPUT — C++14 with -fno-elide-constructors:
// -------------------------------------------------------
// Photo(int,int) — constructor
// Photo(Photo&&) — move constructor      <- moving out of createPhoto()
// Photo(Photo&&) — move constructor      <- moving into myPhoto
// ~Photo() — destructor                  <- destroying return slot
// ~Photo() — destructor                  <- destroying temp inside createPhoto()
// --- end of main ---
// ~Photo() — destructor                  <- destroying myPhoto
//
// -------------------------------------------------------
// EXPECTED OUTPUT — C++17:
// -------------------------------------------------------
// Photo(int,int) — constructor           <- built directly in myPhoto, no moves
// --- end of main ---
// ~Photo() — destructor                  <- only myPhoto to destroy
