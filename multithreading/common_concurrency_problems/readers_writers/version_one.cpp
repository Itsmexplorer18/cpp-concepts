
#include <semaphore>

class ReaderGate {
public:
    void enter(std::binary_semaphore& roomEmpty) {
        mutex_.acquire();
        readers_ += 1;
        if (readers_ == 1) {
            roomEmpty.acquire();   // first reader: lock out writers
        }
        mutex_.release();
    }

    void leave(std::binary_semaphore& roomEmpty) {
        mutex_.acquire();
        readers_ -= 1;
        if (readers_ == 0) {
            roomEmpty.release();   // last reader: let writers back in
        }
        mutex_.release();
    }

private:
    int readers_ = 0;
    std::binary_semaphore mutex_{1};
};
int main(){
std::binary_semaphore roomEmpty(1);
ReaderGate readerGate;

void reader() {
    readerGate.enter(roomEmpty);
    // --- critical section for readers ---
    readerGate.leave(roomEmpty);
}

void writer() {
    roomEmpty.acquire();
    // --- critical section for writers ---
    roomEmpty.release();
}
};
