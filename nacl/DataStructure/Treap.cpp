#define pii pair<int, int>
struct node {
    int tag = 0;
    int sum = 0;
    int prio = rand();
    int lson = 0;
    int rson = 0;
    int si = 0;
    int val = 0;
};
node treap[400005];
int cnt = 0;
int root = 0;

void update(int index) {
    int lson = treap[index].lson;
    int rson = treap[index].rson;
    treap[index].si = treap[lson].si + treap[rson].si + 1;
    treap[index].sum = treap[lson].sum;
    treap[index].sum += treap[rson].sum;
    treap[index].sum += treap[index].val;
}
void push(int index) {
    if(!treap[index].tag) return;
    swap(treap[index].lson, treap[index].rson);
    int lson = treap[index].lson;
    int rson = treap[index].rson;
    treap[lson].tag ^= 1;
    treap[rson].tag ^= 1;
    treap[index].tag = 0;
}

pii split(int rk, int index) {
    if(!index) return {0, 0};
    push(index);
    int lson = treap[index].lson;
    int rson = treap[index].rson;
    if(rk <= treap[lson].si) {
        pii temp = split(rk, lson);
        treap[index].lson = temp.second;
        update(index);
        return {temp.first, index};
    } else {
        pii temp = split(rk - treap[lson].si - 1, rson);
        treap[index].rson = temp.first;
        update(index);
        return {index, temp.second};
    }
}

int merge(int x, int y) {
    if(!x && !y) return 0;
    if(!x && y) return y;
    if(x && !y) return x;
    push(x);
    push(y);
    if(treap[x].prio < treap[y].prio) {
        treap[x].rson = merge(treap[x].rson, y);
        update(x);
        return x;
    } else {
        treap[y].lson = merge(x, treap[y].lson);
        update(y);
        return y;
    }
}

void insert(int x, int v) {
    pii temp = split(x - 1, root);
    cnt++;
    treap[cnt].val = v;
    update(cnt);
    temp.first = merge(temp.first, cnt);
    root = merge(temp.first, temp.second);
}

int query(int l, int r) {
    pii R = split(r, root);
    pii L = split(l - 1, R.first);
    int ret = treap[L.second].sum;
    R.first = merge(L.first, L.second);
    root = merge(R.first, R.second);
    return ret;
}

void modify(int l, int r) {
    pii R = split(r, root);
    pii L = split(l - 1, R.first);
    treap[L.second].tag ^= 1;
    R.first = merge(L.first, L.second);
    root = merge(R.first, R.second);
}
