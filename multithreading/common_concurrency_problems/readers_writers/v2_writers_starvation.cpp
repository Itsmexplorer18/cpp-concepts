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
//------------------------------USAGE------------------------//
std::binary_semaphore roomEmpty(1);
std::binary_semaphore writer_turnstile(1); //in notes this is writer prioirty initially but this is just writer starvation avoidance not priority so better name can be writer_turnsile
ReaderGate readGroup;   // from before — readers_ + mutex_, no roomEmpty stored

void reader() {
    writer_turnstile.acquire();
    writer_turnstile.release();          // pass straight through, don't hold it

    readGrouph.enter(roomEmpty);
    // --- critical section for readers ---
    readGroup.leave(roomEmpty);
}

void writer() {
    writer_turnstile.acquire();          // held like a normal mutex
    roomEmpty.acquire();          // checked while still holding turnstile

    // --- critical section for writers ---

    roomEmpty.release();
    writer_turnstile.release();          // only now does anyone else get through
}
