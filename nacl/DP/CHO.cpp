struct line {
    int a, b;
    int y(int x) { return a * x + b; }
};

struct CHO {
    deque<line> dq;
    int intersect(line x, line y) {
        int d1 = x.b - y.b;
        int d2 = y.a - x.a;
        return d1 / d2;
    }
    bool check(line x, line y, line z) {
        int I12 = intersect(x, y);
        int I23 = intersect(y, z);
        return I12 < I23;
    }
    void insert(int a, int b) {
        if(!dq.empty() && a == dq.back().a) return;
        while(dq.size() >= 2 &&
              !check(dq[dq.size() - 2], dq[dq.size() - 1],
                     {a, b})) {
            dq.pop_back();
        }
        dq.push_back({a, b});
    }
    void update(int x) {
        while(dq.size() >= 2 && dq[0].y(x) >= dq[1].y(x)) {
            dq.pop_front();
        }
    }
    int query(int x) {
        update(x);
        return dq.front().y(x);
    }
};
