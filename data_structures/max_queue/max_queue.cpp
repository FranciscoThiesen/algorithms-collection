struct MaxQueue {
	vector<pair<ll, int> > d;
	int l, r;
	int cnt;
	int size;
	
	MaxQueue(){
		l = r = cnt = size = 0;
	}
	
	ll max() {
		return d[l].first;
	}
	
	void push(ll v) {
		int sum = 0;
		// aqui estamos contanto quantas caras sao menores que o novo valor v
		while (r > l && d[r - 1].first < v) {
			r--;
			sum += d[r].second;
		}
		if(r == d.size()) {
			d.push_back({0, 0});
		}
		d[r++] = pair<ll, int>(v, sum + 1);
		size++;
	}
	
	void pop() {
		d[l].second--;
		if (d[l].second == 0) l++;
		size--;
	}
	
	void clear() {
		l = 0, r = 0, cnt = 0, size = 0;
	}
};

const int ms = 2e6 + 20;

ll acc[ms];
int n, d;
ll p;
