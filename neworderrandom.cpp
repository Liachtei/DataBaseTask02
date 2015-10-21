#include <cstdint>
#include "Types.hpp"
#include <iostream>
#include <fstream>
#include <ctime>

const int32_t warehouseCount = 5;
const int32_t districtCount = 50;
const int32_t itemCount = 100000;
const int32_t customerCount = 150000;
const int32_t stockCount = 500000;

using namespace std;

struct Warehouse {
	int32_t w_id;
	Numeric<4, 4> w_tax;
};

struct Customer {
	int32_t c_id;
	int32_t c_d_id;
	int32_t c_w_id;
	Numeric<4, 4> c_discount;
};

struct District {
	int32_t d_id;
	int32_t d_w_id;
	Numeric<4, 4> d_tax;
	int32_t d_next_o_id;
};

struct Item {
	int32_t i_id;
	Numeric<5, 2> i_price;
};

struct Stock {
	int32_t s_i_id;
	int32_t s_w_id;
	Numeric<4, 0> s_quantity;
	char s_dist_01[24];
	char s_dist_02[24];
	char s_dist_03[24];
	char s_dist_04[24];
	char s_dist_05[24];
	char s_dist_06[24];
	char s_dist_07[24];
	char s_dist_08[24];
	char s_dist_09[24];
	char s_dist_10[24];
	Numeric<4, 0> s_order_cnt;
	Numeric<4, 0> s_remote_cnt;

};

struct Orderline {
	int32_t ol_o_id;
	int32_t ol_d_id;
	int32_t ol_w_id;
	int32_t ol_number;
	int32_t ol_i_id;
	int32_t ol_supply_w_id;
	uint64_t ol_delivery_d;
	Numeric<2, 0> ol_quantity;
	Numeric<6, 2> ol_amount;
	char ol_dist_info[24];
};

struct Order {
	int32_t o_id;
	int32_t o_d_id;
	int32_t o_w_id;
	int32_t o_c_id;
	uint64_t o_entry_d;
	int32_t o_carrier_id;
	Numeric<2, 0> o_ol_cnt;
	Numeric<1, 0> o_all_local;
};

struct Neworder {
	int32_t no_o_id;
	int32_t no_d_id;
	int32_t no_w_id;
};

const int32_t neworderMax = 1045000;
const int32_t orderMax = 1150000;
const int32_t orderlineMax = 2500000;
int32_t neworderCount = 0;
int32_t orderCount = 0;
int32_t orderlineCount = 0;

Warehouse warehouseArray[warehouseCount];
District districtArray[districtCount];
Customer customerArray[customerCount];
Item itemArray[itemCount];
Stock stockArray[stockCount];

Neworder newOrderArray[neworderMax];
Order orderArray[orderMax];
Orderline orderlineArray[orderlineMax];

void warehouseInit() {
	ifstream warehouseFile;
	warehouseFile.open("tpcc_warehouse.tbl");
	int i = 0;
	string line;
	while (getline(warehouseFile, line)) {
		int32_t w_id;
		int32_t garbageSize = line.length();
		char garbage[garbageSize];
		int32_t w_tax;
		w_id = 0;
		w_tax = 0;
		sscanf(line.c_str(), "%d|%s|%s|%s|%s|%s|%s|%d|%s", &w_id, garbage,
				garbage, garbage, garbage, garbage, garbage, &w_tax, garbage);
		Warehouse w = { w_id, Numeric<4, 4>(w_tax) };
		warehouseArray[w_id - 1] = w;
		i++;
	}
	warehouseFile.close();
}

void districtInit() {
	ifstream districtFile;
	districtFile.open("tpcc_district.tbl");
	int i = 0;
	string line;
	while (getline(districtFile, line)) {
		int32_t d_id, d_w_id, d_tax, d_next_o_id;
		int32_t garbageSize = line.length();
		char garbage[garbageSize];
		sscanf(line.c_str(), "%d|%d|%s|%s|%s|%s|%s|%s|%d|%s|%d|", &d_id,
				&d_w_id, garbage, garbage, garbage, garbage, garbage, garbage,
				&d_tax, garbage, &d_next_o_id);
		District d = { d_id, d_w_id, Numeric<4, 4>(d_tax), d_next_o_id };
		districtArray[i] = d;
		i++;
	}
	districtFile.close();
}

void customerInit() {
	ifstream customerFile;
	customerFile.open("tpcc_customer.tbl");
	int i = 0;
	string line;
	while (getline(customerFile, line)) {
		int32_t c_id, c_d_id, c_w_id, c_discount;
		int32_t garbageSize = line.length();
		char garbage[garbageSize];
		sscanf(line.c_str(),
				"%d|%d|%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%d|%s", &c_id,
				&c_d_id, &c_w_id, garbage, garbage, garbage, garbage, garbage,
				garbage, garbage, garbage, garbage, garbage, garbage, garbage,
				&c_discount, garbage);
		Customer c = { c_id, c_d_id, c_w_id, Numeric<4, 4>(c_discount) };
		customerArray[i] = c;
		i++;
	}
	customerFile.close();
}

void neworderInit() {
	ifstream neworderFile;
	neworderFile.open("tpcc_neworder.tbl");
	int i = 0;
	string line;
	while (getline(neworderFile, line)) {
		int32_t no_o_id, no_d_id, no_w_id;
		sscanf(line.c_str(), "%d|%d|%d|", &no_o_id, &no_d_id, &no_w_id);
		Neworder no = { no_o_id, no_d_id, no_w_id };
		newOrderArray[i] = no;
		neworderCount++;
		i++;
	}
	neworderFile.close();
}

void orderInit() {
	ifstream orderFile;
	orderFile.open("tpcc_order.tbl");
	int i = 0;
	string line;
	while (getline(orderFile, line)) {
		int32_t o_id, o_d_id, o_w_id, o_c_id, o_carrier_id, o_ol_cnt,
				o_all_local;
		uint64_t o_entry_d;
		sscanf(line.c_str(), "%d|%d|%d|%d|%d|%d|%d|%d|", &o_id, &o_d_id,
				&o_w_id, &o_c_id, &o_entry_d, &o_carrier_id, &o_ol_cnt,
				&o_all_local);
		Order o = { o_id, o_d_id, o_w_id, o_c_id, o_entry_d, o_carrier_id,
				Numeric<2, 0>(o_ol_cnt), Numeric<1, 0>(o_all_local) };
		orderArray[i] = o;
		orderCount++;
		i++;
	}
	orderFile.close();
}

void orderlineInit() {
	ifstream orderlineFile;
	orderlineFile.open("tpcc_orderline.tbl");
	int i = 0;
	string line;
	while (getline(orderlineFile, line)) {
		int32_t garbageSize = line.length();
		char garbage[garbageSize];
		int32_t ol_o_id, ol_d_id, ol_w_id, ol_number, ol_i_id, ol_supply_w_id,
				ol_quantity, ol_amount;
		uint64_t ol_delivery_d;
		char ol_dist_info[24];
		sscanf(line.c_str(), "%d|%d|%d|%d|%d|%d|%d|%d|%d|%s|", &ol_o_id,
				&ol_d_id, &ol_w_id, &ol_number, &ol_i_id, &ol_supply_w_id,
				&ol_delivery_d, &ol_quantity, &ol_amount, ol_dist_info);
		Orderline ol = { ol_o_id, ol_d_id, ol_w_id, ol_number, ol_i_id,
				ol_supply_w_id, ol_delivery_d, ol_quantity, ol_amount };
		std::strcpy(ol.ol_dist_info, ol_dist_info);
		orderlineArray[i] = ol;
		orderlineCount++;
		i++;
	}
	orderlineFile.close();
}

void itemInit() {
	ifstream itemFile;
	itemFile.open("tpcc_item.tbl");
	int i = 0;
	string line;
	while (getline(itemFile, line)) {
		int32_t i_id, i_price;
		int32_t garbageSize = line.length();
		char garbage[garbageSize];
		sscanf(line.c_str(), "%d|%s|%s|%d|%s", &i_id, garbage, garbage,
				&i_price, garbage);
		Item item = { i_id, Numeric<5, 2>(i_price) };
		itemArray[i] = item;
		i++;
	}
	itemFile.close();
}

void stockInit() {
	ifstream stockFile;
	stockFile.open("tpcc_stock.tbl");
	int i = 0;
	string line;
	//while (stockFile.getline(line, 400, '\n')) {
	while (getline(stockFile, line)) {
		Stock s = Stock();
		//int32_t lineSize = line.length();
		char garbage01[10];
		char garbage02[60];
		int32_t s_i_id, s_w_id, s_quantity, s_order_cnt, s_remote_cnt;
		char district0 [24];
		char district1 [24];
		char district2 [24];
		char district3 [24];
		char district4 [24];
		char district5 [24];
		char district6 [24];
		char district7 [24];
		char district8 [24];
		char district9 [24];
		sscanf(line.c_str(),
				"%d|%d|%d|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%d|%d|%s", &s_i_id,
				&s_w_id, &s_quantity, district0, district1, district2,
				district3, district4, district5, district6,
				district7, district8, district9, garbage01, &s_order_cnt,
				&s_remote_cnt, garbage02);
		s.s_i_id = s_i_id;
		s.s_w_id = s_w_id;
		s.s_quantity = Numeric<4, 0>(s_quantity);
		std::strncpy(s.s_dist_01, district0, 24);
		std::strncpy(s.s_dist_02, district1, 24);
		std::strncpy(s.s_dist_03, district2, 24);
		std::strncpy(s.s_dist_04, district3, 24);
		std::strncpy(s.s_dist_05, district4, 24);
		std::strncpy(s.s_dist_06, district5, 24);
		std::strncpy(s.s_dist_07, district6, 24);
		std::strncpy(s.s_dist_08, district7, 24);
		std::strncpy(s.s_dist_09, district8, 24);
		std::strncpy(s.s_dist_10, district9, 24);
		s.s_order_cnt = Numeric<4, 0>(s_order_cnt);
		s.s_remote_cnt = Numeric<4, 0>(s_remote_cnt);
		stockArray[i] = s;
		i++;
	}
	stockFile.close();
}

void init() {
	warehouseInit();
	districtInit();
	customerInit();
	neworderInit();
	orderInit();
	orderlineInit();
	itemInit();
	stockInit();
}

int32_t urand(int32_t min, int32_t max) {
	return (random() % (max - min + 1)) + min;
}

int32_t nurand(int32_t A, int32_t x, int32_t y) {
	return ((((random() % A) | (random() % (y - x + 1) + x)) + 42) % (y - x + 1))
			+ x;
}

int32_t urandexcept(int32_t min, int32_t max, int32_t v) {
	if (max <= min)
		return min;
	int32_t r = (random() % (max - min)) + min;
	if (r >= v)
		return r + 1;
	else
		return r;
}

/*
 *
 int64_t randomnumeric62(Numeric<6, 2> min, Numeric<6, 2> max) {
 return (random() % (max.value - min.value + 1)) + min;
 }
 char* genName(int32_t id) {
 char parts = { 'BAR', 'OUGHT', 'ABLE', 'PRI', 'PRES', 'ESE', 'ANTI',
 'CALLY', 'ATION', 'EING' };
 return parts[(id / 100) % 10] + parts[(id / 10) % 10] + parts[id % 10];
 }


 void paymentRandom(uint64_t now, int32_t w_id)
 {
 int32_t d_id =urand(1,10);
 int32_t c_w_id, c_d_id;
 if (urand(1,100)<=85) {
 c_w_id=w_id;
 c_d_id=d_id;
 } else {
 c_w_id= urandexcept(1,warehouses,w_id);
 c_d_id= urand(1,10);
 }
 Numeric<6,2> h_amount = randomnumeric62(1.00,5000.00);
 uint64_t h_date=now;

 if (urand(1,100)<=60) {
 //paymentByName(w_id,d_id,c_w_id,c_d_id,genName(nurand(255,0,999)),h_date,h_amount,now);
 } else {
 //paymentById(w_id,d_id,c_w_id,c_d_id,nurand(1023,1,3000),h_date,h_amount,now);
 }
 }

 void ostatRandom(int32_t w_id)
 {
 int32_t d_id=urand(1,10);

 if (urand(1,100)<=60) {
 //ostatByName(w_id,d_id,genName(nurand(255,0,999)));
 } else {
 //ostatById(w_id,d_id,nurand(1023,1,3000));
 }
 };

 void deliveryRandom(uint64_t now,int32_t w_id)
 {
 int32_t carrier_id=urand(1,10);
 //delivery(w_id,carrier_id,now);
 };

 void slevRandom(int32_t w_id)
 {
 int32_t d_id=urand(1,10);
 int32_t threshold=urand(10,20);

 //slev(w_id,d_id,threshold);
 };

 int32_t partitionedOltp(uint64_t now,int32_t w_id)
 {
 int32_t choice=urand(1,1000);

 //Payment?
 if (choice<=430) {
 paymentRandom(now,w_id);
 return 1;
 }
 choice=choice-430;

 //Order status?
 if (choice<=40) {
 ostatRandom(w_id);
 return 2;
 }
 choice=choice-40;

 //Delivery?
 if (choice<=45) {
 deliveryRandom(now,w_id);
 return 3;
 }
 choice=choice-45;

 //Stock level?
 if (choice<=40) {
 slevRandom(w_id);
 return 40;
 }

 //Default to new order
 newOrderRandom(now,w_id);
 return 0;
 };

 int32_t oltp(uint64_t now)
 {
 return partitionedOltp(now,urand(1,warehouses));
 };
 */

void newOrder(int32_t w_id, int32_t d_id, int32_t c_id, int32_t items,
		int32_t* supware, int32_t* itemid, int32_t* qty, Timestamp datetime) {

	int32_t o_id;
	Numeric<4, 4> w_tax, c_discount, d_tax;
	//select w_tax from warehouse w where w.w_id=w_id;
	w_tax = warehouseArray[w_id].w_tax;

	//select c_discount from customer c where c_w_id=w_id and c_d_id=d_id and c.c_id=c_id;
	for (auto cIndex = c_id; cIndex < customerCount; cIndex = cIndex + 3000) {
		//for (auto c : customerArray) {
		Customer c = customerArray[cIndex];
		if (c.c_w_id == w_id && c.c_d_id == d_id) {
			//if (c.c_id == c_id && c.c_w_id == w_id && c.c_d_id == d_id) {
			c_discount = c.c_discount;
			break;
		}
	}
	//select d_next_o_id as o_id,d_tax from district d where d_w_id=w_id and d.d_id=d_id;
	//update district set d_next_o_id=o_id+1 where d_w_id=w_id and district.d_id=d_id;
	for (auto d : districtArray) {
		if (d.d_id == d_id && d.d_w_id == w_id) {
			d_tax = d.d_tax;
			o_id = d.d_next_o_id;
			d.d_next_o_id = o_id++;
			break;
		}
	}

	int32_t all_local = 1;
	for (auto index = 0; index < items; index++) {
		if (w_id != supware[index])
			all_local = 0;
	}
	//insert into "order" values (o_id,d_id,w_id,c_id,datetime,0,items,all_local);
	Order order =
			{ o_id, d_id, w_id, c_id, datetime.value, 0, items, all_local };
	orderArray[orderCount] = order;
	orderCount++;
	//insert into neworder values (o_id,d_id,w_id);
	Neworder neworder = { o_id, d_id, w_id };
	newOrderArray[neworderCount] = neworder;
	neworderCount++;

	Numeric<5, 2> i_price;
	Numeric<4, 0> s_quantity;
	Numeric<4, 0> s_remote_cnt;
	Numeric<4, 0> s_order_cnt;
	char s_dist[24];
	//select i_price from item where i_id=itemid[index];
	for (auto index = 0; index < items; index++) {
		i_price = itemArray[itemid[index]].i_price;
		//for (auto item : itemArray) {
		//if (item.i_id == itemid[index]) {
		//i_price = item.i_price;
		//}
		//}
		//select s_quantity,s_remote_cnt,s_order_cnt,case d_id when 1 then s_dist_01 when 2 then s_dist_02 when 3 then s_dist_03 when 4 then s_dist_04
		//when 5 then s_dist_05 when 6 then s_dist_06 when 7 then s_dist_07 when 8 then s_dist_08 when 9 then s_dist_09
		//when 10 then s_dist_10 end as s_dist from stock where s_w_id=supware[index] and s_i_id=itemid[index];
		for (auto sIndex = 0; sIndex < stockCount; sIndex++) {
			//for (auto stock : stockArray) {
			Stock stock = stockArray[sIndex];
			if (stock.s_w_id != supware[index]) {
				sIndex += 99999;
				continue;
			}
			if (stock.s_i_id == itemid[index]) {
				switch (d_id) {
				case 1:
					strcpy(s_dist, stock.s_dist_01);
					break;
				case 2:
					strcpy(s_dist, stock.s_dist_02);
					break;
				case 3:
					strcpy(s_dist, stock.s_dist_03);
					break;
				case 4:
					strcpy(s_dist, stock.s_dist_04);
					break;
				case 5:
					strcpy(s_dist, stock.s_dist_05);
					break;
				case 6:
					strcpy(s_dist, stock.s_dist_06);
					break;
				case 7:
					strcpy(s_dist, stock.s_dist_07);
					break;
				case 8:
					strcpy(s_dist, stock.s_dist_08);
					break;
				case 9:
					strcpy(s_dist, stock.s_dist_09);
					break;
				case 10:
					strcpy(s_dist, stock.s_dist_10);
					break;
				}
				s_quantity = stock.s_quantity;
				s_remote_cnt = stock.s_remote_cnt;
				s_order_cnt = stock.s_order_cnt;
// if (s_quantity>qty[index]) {
// update stock set s_quantity=s_quantity-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
// } else {
// update stock set s_quantity=s_quantity+91-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
				if (s_quantity > qty[index]) {
					stock.s_quantity = s_quantity - qty[index];
				} else {
					stock.s_quantity = s_quantity + 91 - qty[index];
				}
//if (supware[index]<>w_id) {
// update stock set s_remote_cnt=s_remote_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
//} else {
//update stock set s_order_cnt=s_order_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
				if (supware[index] != w_id) {
					stock.s_remote_cnt = s_remote_cnt + 1;
				} else {
					stock.s_order_cnt = s_order_cnt + 1;
				}

				Numeric<6, 2> ol_amount = Numeric<6, 2>(
						qty[index] * i_price.value
								* (1.0 + w_tax.value + d_tax.value)
								* (1.0 - c_discount.value));

//insert into orderline values(o_id, d_id, w_id, index + 1, itemid[index],
//supware[index], 0, qty[index], ol_amount, s_dist);

				Orderline orderline =
						{ o_id, d_id, w_id, index + 1, itemid[index],
								supware[index], 0, qty[index], ol_amount };
				strcpy(orderline.ol_dist_info, s_dist);
				orderlineArray[orderlineCount] = orderline;
				orderlineCount++;
			}
		}
	}
}

void newOrderRandom(Timestamp now, int32_t w_id) {
	int32_t d_id = urand(1, 1);
	int32_t c_id = nurand(1023, 1, 3000);
	int32_t ol_cnt = urand(5, 15);

	int32_t supware[15];
	int32_t itemid[15];
	int32_t qty[15];
	for (int32_t i = 0; i < ol_cnt; i++) {
		if (urand(1, 100) > 1)
			supware[i] = w_id;
		else
			supware[i] = urandexcept(1, warehouseCount, w_id);
		itemid[i] = nurand(8191, 1, 100000);
		qty[i] = urand(1, 10);
	}
	newOrder(w_id, d_id, c_id, ol_cnt, supware, itemid, qty, now.value);
}

int numberOfTransctions = 1000;

int main() {
	init();
	//for (int rounds = 0; rounds < 10; rounds++) {
	time_t begin = time(0);
	cout << "Neworder(before): " << neworderCount << endl;
	cout << "Order(before): " << orderCount << endl;
	cout << "Orderline(before): " << orderlineCount << endl;
	for (auto i = 0; i < numberOfTransctions; i++) {
		int32_t w_id = urand(1, 5);
		Timestamp now = Timestamp(time(0));
		newOrderRandom(now, w_id);
	}
	time_t end = time(0);
	cout << "Neworder(after): " << neworderCount << endl;
	cout << "Order(after): " << orderCount << endl;
	cout << "Orderline(after): " << orderlineCount << endl;
	float totalTime = end - begin;
	cout << "Total time: " << end - begin << endl;
	cout << "Number of transactions per second: "
			<< numberOfTransctions / totalTime << endl;
	//}
	return 0;
}

