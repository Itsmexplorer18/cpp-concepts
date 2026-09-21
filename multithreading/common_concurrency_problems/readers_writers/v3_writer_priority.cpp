#include <semaphore>
class Gate {
public:
    void enter(std::binary_semaphore& roomEmpty) {
        mutex_.acquire();
        count_ += 1;
        if (count_ == 1) {
            roomEmpty.acquire();
        }
        mutex_.release();
    }

    void leave(std::binary_semaphore& roomEmpty) {
        mutex_.acquire();
        count_ -= 1;
        if (count_ == 0) {
            roomEmpty.release();
        }
        mutex_.release();
    }

private:
    int count_ = 0;
    std::binary_semaphore mutex_{1};
};
/------------USAGE--------------------------/
std::binary_semaphore roomEmptyOfReaders(1);
std::binary_semaphore roomEmptyOfWriters(1);
Gate readerGroup;
Gate writerGroup;

void reader() {
    roomEmptyOfReaders.acquire();
    readerGroup.enter(roomEmptyOfWriters);
    roomEmptyOfReaders.release();

    // --- critical section for readers ---

    readerGroup.leave(roomEmptyOfWriters);
}

void writer() {
    writerGroup.enter(roomEmptyOfReaders);
    roomEmptyOfWriters.acquire();

    // --- critical section for writers ---

    roomEmptyOfWriters.release();
    writerGroup.leave(roomEmptyOfReaders);
}
