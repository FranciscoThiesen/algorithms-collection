#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define mp make_pair

struct node{
    int key, prior;
    node* l, r;
    node() {}
    node(int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) {}
};
typedef node* pnode;

void split(pnode t, int key, pnode& l, pnode& r){
    if(t == NULL) l = r = NULL;
    else if(key < t->key){
        split(t->l, key, l, t->l);
        r = t;
    }
    else{
        split(t->r, key, t->r, r);
        l = t;
    }
}

void insert(pnode& t, pnode it){
    if(t == NULL) t = it;
    else if(it->prior > t->prior)
        split(t, it->key, it->l, it->r), t = it;
    else
        insert(it->key < t->key ? t->l : t->r, it);
}

void merge(pnode& t, pnode l, pnode r){
    if(!l || !r) t = l ? l : r;
    else if(l->prior > r->prior)
        merge(l->r, l->r, r), t = l;
    else
        merge(r->l, l, r->l), t = r;
}

void erase(pnode& t, int key){
    if(t->key == key) merge(t, t->l, t->r);
    else erase(key < t->key ? t->l : t->r, key);
}

pnode unite(pnode l, pnode r){
    if(!l || !r) return l ? l : r;
    if(l->prior < r->prior) swap(l, r);
    pitem lt, rt;
    split(r, l->key, lt, rt);
    l->l = unite(l->l, lt);
    l->r = unite(l->r, rt);
    return l;
}
