class TrieNode {
    int end;
    vector<TrieNode *> next;
public:
    TrieNode() {
        end = 0;
        for (int i = 0; i < 26; i++) {
            next.push_back(nullptr);
        }
    }

    bool has_next(char c) {
        return next[c - 'a'] != nullptr ;
    }

    TrieNode *get_next(char c) {
        assert(has_next(c));
        return next[c - 'a'];
    }

    void set_next(char c) {
        assert(!has_next(c));
        next[c - 'a'] = (new TrieNode()); // EPIC
    }

    void mark() {
        end += 1;
    }

    bool is_marked() {
        return end != 0;
    }
};
class Trie {
public:
    /** Initialize your data structure here. */
    TrieNode start;

    Trie() {
        start = TrieNode();
    }

    /** Inserts a word into the trie. */
    void insert(string s) {
        int n = (int) s.size();
        int i = 0;
        TrieNode *cur = &(start);
        while (i < n && (*cur).has_next(s[i])) {
            cur = (cur->get_next(s[i]));
            i += 1;
        }
        while (i < n) {
            assert(cur != nullptr);
            (*cur).set_next(s[i]);
            cur = cur->get_next(s[i]);
            i += 1;
        }
        (*cur).mark();// mark as the end of a string

    }

    /** Returns if the word is in the trie. */
    bool search(string s) {
        int i = 0;
        int n = (int) s.size();
        TrieNode *cur = &start;
        while ((i < n) && (cur->has_next(s[i]))) {
            cur = cur->get_next(s[i]);
            i += 1;
        }
        return (i == n) && cur->is_marked();
    }

    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string s) {
        int i = 0;
        int n = (int) s.size();
        TrieNode *cur = &start;
        while ((i < n) && (cur->has_next(s[i]))) {
            cur = cur->get_next(s[i]);
            i += 1;
        }
        return (i == n) ;
    }
};