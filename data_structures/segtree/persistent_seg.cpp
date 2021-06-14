constexpr int ms = 200'013; 
 
struct node
{
    int val;
    node *l, *r;
    node() {}
    node(int val = 0, node* l = NULL, node* r = NULL) : val(val), l(l), r(r){}
 
};
 
node* roots[ms];
 
node* build(int left, int right)
{
    if(left == right - 1) return new node(0, NULL, NULL);
    int mid = (left + right) >> 1;
    node* l = build(left, mid);
    node* r = build(mid, right);
    return new node(l->val + r->val, l, r);
}
 
node* buildCopy(node* current, int left, int right, int upd, int add) {
	if(left == right - 1) return new node(add, NULL, NULL);
	int mid = (left + right) >> 1;
	node *l, *r;
	if( upd < mid ) {
		l = buildCopy(current->l, left, mid, upd, add);
		r = current->r;
	}
	else {
		l = current->l;
		r = buildCopy(current->r, mid, right, upd, add);
	}
	return new node(l->val + r->val, l, r);
}

// queries também vão ser semi-abertas
int query(node* root, int arvL, int arvR, int L, int R)
{
    if(root == nullptr) return 0;
    if(arvL >= R || arvR < L) return 0;
    if(arvL >= L && arvR <= R) return root->val;
    int mid = (arvR + arvL) / 2;
    return query(root->l, arvL, mid, L, R) + query(root->r, mid, arvR, L, R); 
}
