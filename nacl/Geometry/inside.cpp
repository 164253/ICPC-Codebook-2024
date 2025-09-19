int inside(point p) {
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        if(onseg(a[i], a[i + 1], {p.x, p.y})) {
            return -1;
        }
        if(intersect({p.x, p.y}, {INF, p.y}, a[i], a[i + 1])) {
            ans ^= 1;
        }
        point temp = a[i].y > a[i + 1].y ? a[i] : a[i + 1];
        if(temp.y == p.y && temp.x > p.x) {
            ans ^= 1;
        }
    }
    return ans;
}
