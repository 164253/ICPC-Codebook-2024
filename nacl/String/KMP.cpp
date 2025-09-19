string s, t;
int pmt[1000005];

void init() {
    for(int i = 1, j = 0; i < t.size(); i++) {
        while(j && t[j] ^ t[i]) {
            j = pmt[j - 1];
        }
        if(t[j] == t[i]) j++;
        pmt[i] = j;
    }
}

int kmp(string s) {
    int ret = 0;
    for(int i = 0, j = 0; i < s.size(); i++) {
        while(j && s[i] ^ t[j]) {
            j = pmt[j - 1];
        }
        if(s[i] == t[j]) {
            j++;
        }
        if(j == t.size()) {
            ret++;
            j = pmt[j - 1];
        }
    }
    return ret;
}
