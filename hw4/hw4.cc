#include <cstdio>
#include <vector>
using std::vector;
#include <algorithm>
using std::pop_heap;	using std::push_heap;

/* bidId	clientId	action			price		shareCount */
/* transId	buyClientId	sellClientId	transPrice	transShareCount */

struct Stock {
	int bidId, clientId, price;
};
bool buycmp(const Stock a, const Stock b) {
	if(a.price == b.price)
		return a.bidId > b.bidId;
	return a.price < b.price;
}
bool sellcmp(const Stock a, const Stock b) {
	if(a.price == b.price)
		return a.bidId > b.bidId;
	return a.price > b.price;
}

vector<Stock> buy, sell;
int count[1048576];	// count[bidId] = shareCount

int main()
{
	int bidId, clientId, action, price, shareCount;
	int transID = 0;
	while(scanf("%d%d%d%d%d", &bidId, &clientId, &action, &price, &shareCount) != EOF)
	{
		count[bidId] = shareCount;		// can shareCount == 0 ???
		if(action == 0) {
			buy.push_back( (Stock){bidId, clientId, price} );
			push_heap(buy.begin(), buy.end(), buycmp);
		} else if(action == 1) {
			sell.push_back( (Stock){bidId, clientId, price} );
			push_heap(sell.begin(), sell.end(), sellcmp);
		} else {	// action == 2
			count[price] = 0;
		}
		
		while(!buy.empty() && !count[buy.begin()->bidId]) {
			pop_heap(buy.begin(), buy.end(), buycmp);
			buy.pop_back();
		}
		while(!sell.empty() && !count[sell.begin()->bidId]) {
			pop_heap(sell.begin(), sell.end(), sellcmp);
			sell.pop_back();
		}
		
		while(!buy.empty() && !sell.empty() && buy.begin()->price >= sell.begin()->price)
		{
			printf("%d\t%d\t%d\t%d\t", transID++, buy.begin()->clientId, sell.begin()->clientId, sell.begin()->price);
			if( count[buy.begin()->bidId] > count[sell.begin()->bidId] ) {
				printf("%d\n", count[sell.begin()->bidId]);
				count[buy.begin()->bidId] -= count[sell.begin()->bidId];
				count[sell.begin()->bidId] = 0;
			} else if( count[buy.begin()->bidId] < count[sell.begin()->bidId] ) {
				printf("%d\n", count[buy.begin()->bidId]);
				count[sell.begin()->bidId] -= count[buy.begin()->bidId];
				count[buy.begin()->bidId] = 0;
			} else {	// sell_count == buy_count
				printf("%d\n", count[buy.begin()->bidId]);
				count[buy.begin()->bidId] = 0;
				count[sell.begin()->bidId] = 0;
			}
			
			while(!buy.empty() && !count[buy.begin()->bidId]) {
				pop_heap(buy.begin(), buy.end(), buycmp);
				buy.pop_back();
			}
			while(!sell.empty() && !count[sell.begin()->bidId]) {
				pop_heap(sell.begin(), sell.end(), sellcmp);
				sell.pop_back();
			}
		}
		
	}	// end while (scanf() != EOF)
	
	return 0;
}
