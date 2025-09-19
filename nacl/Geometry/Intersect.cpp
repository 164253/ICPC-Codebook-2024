struct point {
    int x, y;
    point operator+(point b) { return {x + b.x, y + b.y}; }
    point operator-(point b) { return {x - b.x, y - b.y}; }
    int operator*(point b) { return x * b.x + y * b.y; }
    int operator^(point b) { return x * b.y - y * b.x; }
};

bool onseg(point x, point y, point z) {
    return ((x - z) ^ (y - z)) == 0 && (x - z) * (y - z) <= 0;
}

int dir(point x, point y) {
    int k = x ^ y;
    if(k == 0) return 0;
    if(k > 0) return 1;
    return -1;
}

bool intersect(point x, point y, point z, point w) {
    if(onseg(x, y, z) || onseg(x, y, w)) return 1;
    if(onseg(z, w, x) || onseg(z, w, y)) return 1;
    if(dir(y - x, z - x) * dir(y - x, w - x) == -1 &&
       dir(z - w, x - w) * dir(z - w, y - w) == -1) {
        return 1;
    }
    return 0;
}
