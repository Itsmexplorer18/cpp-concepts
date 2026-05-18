//refer to notes 
class Widget {
  private:
    int         i  { 0 };
    std::string s  {};
    int*        pi { nullptr };   // raw owning pointer — forces Rule of Five

  public:
/*    ~Widget()                            { delete pi; }
    Widget( const Widget& w )
        : i(w.i), s(w.s)
        , pi( w.pi ? new int(*w.pi) : nullptr ) {}
    Widget& operator=( const Widget& w ) {
        if (this != &w) {
            i = w.i;  s = w.s;
            delete pi;
            pi = w.pi ? new int(*w.pi) : nullptr;
        }
        return *this;
    }
    */

    Widget( Widget&& w ) noexcept
        : i ( std::move(w.i) )
        , s ( std::move(w.s) )
        , pi( std::exchange(w.pi, nullptr) )  // move + null in one expression

    {}
    Widget& operator=( Widget&& w ) noexcept {
        delete pi;                           // Phase 1: free our resource

        i  = std::move(w.i);
        s  = std::move(w.s);                 // Phase 2: member-wise move
        pi = std::exchange(w.pi, nullptr);  // Phase 3: steal + null source

        return *this;
    }
//move() explicitly is important because pi=w.pi again calls copy ctor as within that fucntion it has a name hence is an lvalue so we convert it into  a rvalue reference to make sure move ctor is called
   //noexcept importance
};

// ─── If you replace int* with unique_ptr<int> ────────────────────────────
// All five special member functions collapse back to = default.
// unique_ptr handles delete, move, and nulling automatically.
// That is the Rule of Zero — the goal to aim for.
