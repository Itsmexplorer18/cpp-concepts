//THESE EXAMPLES ARE INSPIRED FROM ISPCPP FAQ ON FRIENDS AND THE COMMENTED EXPLANATION IS BASED ON THAT 
// ============================================================
// PART 1: friend is granted BY the class, not taken by outsiders
// ============================================================
//
// The class controls who gets in. You cannot befriend yourself
// into a class without modifying its source. This is why friend
// does NOT break encapsulation — it's the class author's choice.-->ANSWER TO THE QUESTION THAT DOES FRIEND FUNCTIONS OR CLASS VOILATE ENCAPSULATION? INSTEAD ITS A WAY TO ENHANCE ENCASULATION

class BankAccount {
    double balance;   // private — nobody touches this by default
public:
    BankAccount(double b) : balance(b) {}

    // The class explicitly grants this free function access.
    // Just like a member function, it's part of the interface.
    friend void audit(const BankAccount& acct); //PASS CLASS INTO THE PARAMENTER AS A FRIEND DOESNT HAVE A CALLED OBJECT SO THE ONLY WAY OF DETERMINING WHAT IS GOING TO CALL
//IS BY PASSING IT INTO THE FRIEND ITSELF 
};

void audit(const BankAccount& acct) {
    // Allowed — BankAccount said "audit is my friend"
    // acct.balance is private but we can read it here
    // (pretend we log it to an audit system)
    (void)acct.balance;
}

// audit2 was NOT granted access — this would fail to compile:
//   void audit2(const BankAccount& acct) { acct.balance; }  // ERROR



// ============================================================
// PART 2: splitting one class into two — the main use case  WHERE WE WOULD WANT TO USE FRIEND FUNCTION CAN BE A FRIEND OF MORE THAN ONE CLASS AND BE FRINED OF EACH OTHER ALSO
// ============================================================
//
// Imagine Window and WindowBuffer were originally ONE class.
// We split them (different lifetimes, different instance counts).
// They still need to reach each other's internals — just like
// before the split. Making them friends restores that access
// WITHOUT exposing anything to the outside world.

class WindowBuffer;  // forward declaration

class Window {
    int width, height;
public:
    Window(int w, int h) : width(w), height(h) {}

    // Grant WindowBuffer access to our private members
    friend class WindowBuffer;
};

class WindowBuffer {
    int* pixels;
public:
    WindowBuffer(int size) : pixels(new int[size]{}) {}
    ~WindowBuffer() { delete[] pixels; }

    void resize(const Window& win) {
        // We can read win.width and win.height directly
        // because Window said "WindowBuffer is my friend".
        //
        // This is NOT worse encapsulation than before the split —
        // when it was one class, this code was all in the same place.
        int total = win.width * win.height;   // fine: friend access
        delete[] pixels;
        pixels = new int[total]{};
    }
};



// ============================================================
// PART 3: why naive alternatives are WORSE for encapsulation
// ============================================================
//
// Suppose we refused to use friend and tried to "protect"
// Window.width. Here are the two bad options:

class WindowBad_Option1 {
public:
    int width, height;   // just made it public — grotesque!
    // Now EVERYONE can read and write width, not just WindowBuffer.
    // This is strictly worse than friend.
};

class WindowBad_Option2 {
    int width, height;
public:
    WindowBad_Option2(int w, int h) : width(w), height(h) {}

    int  getWidth()  const { return width;  }   // getter
    void setWidth(int w)   { width = w;     }   // setter
    int  getHeight() const { return height; }
    void setHeight(int h)  { height = h;    }
};
//
// Getters/setters look "safe" but they expose the same information
// to EVERYONE. Any random code can now call setWidth(0) and
// corrupt the Window. With friend, only WindowBuffer gets access.
//
// Summary of what each option actually hides from outsiders:
//
//   public data        — hides nothing
//   public get/set     — hides only the field NAME, not the field itself
//   friend             — hides everything from outsiders; only the named
//                        friend (and members) can get in


int main() {
    // Part 1
    BankAccount acct(1000.0);
    audit(acct);   // fine — explicitly granted
    // Part 2
    Window win(1920, 1080);
    WindowBuffer buf(1920 * 1080);
    buf.resize(win);   // WindowBuffer reads win's private fields
    return 0;
}
