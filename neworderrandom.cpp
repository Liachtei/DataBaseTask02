#include <cstdint>
#include "Types.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include "GeneratedSchema.hpp"
#include <algorithm>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

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

// int64_t randomnumeric62(Numeric<6, 2> min, Numeric<6, 2> max) {
// return (random() % (max.value - min.value + 1)) + min;
// }
// char* genName(int32_t id) {
// char parts = { 'BAR', 'OUGHT', 'ABLE', 'PRI', 'PRES', 'ESE', 'ANTI',
// 'CALLY', 'ATION', 'EING' };
// return parts[(id / 100) % 10] + parts[(id / 10) % 10] + parts[id % 10];
// }

// void paymentRandom(uint64_t now, int32_t w_id)
// {
// int32_t d_id =urand(1,10);
// int32_t c_w_id, c_d_id;
// if (urand(1,100)<=85) {
// c_w_id=w_id;
// c_d_id=d_id;
// } else {
// c_w_id= urandexcept(1,warehouses,w_id);
// c_d_id= urand(1,10);
// }
// Numeric<6,2> h_amount = randomnumeric62(1.00,5000.00);
// uint64_t h_date=now;
//
// if (urand(1,100)<=60) {
// //paymentByName(w_id,d_id,c_w_id,c_d_id,genName(nurand(255,0,999)),h_date,h_amount,now);
// } else {
// //paymentById(w_id,d_id,c_w_id,c_d_id,nurand(1023,1,3000),h_date,h_amount,now);
// }
// }
//
// void ostatRandom(int32_t w_id)
// {
// int32_t d_id=urand(1,10);
//
// if (urand(1,100)<=60) {
// //ostatByName(w_id,d_id,genName(nurand(255,0,999)));
// } else {
// //ostatById(w_id,d_id,nurand(1023,1,3000));
// }
// };
//
// void deliveryRandom(uint64_t now,int32_t w_id)
// {
// int32_t carrier_id=urand(1,10);
// //delivery(w_id,carrier_id,now);
// };
//
// void slevRandom(int32_t w_id)
// {
// int32_t d_id=urand(1,10);
// int32_t threshold=urand(10,20);
//
// //slev(w_id,d_id,threshold);
// };
//
// int32_t partitionedOltp(uint64_t now,int32_t w_id)
// {
// int32_t choice=urand(1,1000);
//
// //Payment?
// if (choice<=430) {
// paymentRandom(now,w_id);
// return 1;
// }
// choice=choice-430;
//
// //Order status?
// if (choice<=40) {
// ostatRandom(w_id);
// return 2;
// }
// choice=choice-40;
//
// //Delivery?
// if (choice<=45) {
// deliveryRandom(now,w_id);
// return 3;
// }
// choice=choice-45;
//
// //Stock level?
// if (choice<=40) {
// slevRandom(w_id);
// return 40;
// }
//
// //Default to new order
// newOrderRandom(now,w_id);
// return 0;
// };
//
// int32_t oltp(uint64_t now)
// {
// return partitionedOltp(now,urand(1,warehouses));
// };

void newOrder(Integer w_id, Integer d_id, Integer c_id, int32_t items,
		Integer* supware, Integer* itemid, Integer* qty, Timestamp datetime) {

	Integer o_id;
	Numeric<4, 4> w_tax, c_discount, d_tax;
	//select w_tax from warehouse w where w.w_id=w_id;
	auto warehouseKey = make_tuple(w_id);
	warehouse w = getwarehouse(findwarehouse(warehouseKey));
	w_tax = w.w_tax;

	//select c_discount from customer c where c_w_id=w_id and c_d_id=d_id and c.c_id=c_id;
	auto customerKey = make_tuple(w_id, d_id, c_id);
	customer c = getcustomer(findcustomer(customerKey));
	c_discount = c.c_discount;
	//select d_next_o_id as o_id,d_tax from district d where d_w_id=w_id and d.d_id=d_id;
	//update district set d_next_o_id=o_id+1 where d_w_id=w_id and district.d_id=d_id;
	auto districtKey = make_tuple(w_id, d_id);
	district d = getdistrict(finddistrict(districtKey));
	o_id = d.d_next_o_id;
	d_tax = d.d_tax;
	d.d_next_o_id = o_id + 1;

	int32_t all_local = 1;
	for (auto index = 0; index < items; index++) {
		if (w_id != supware[index])
			all_local = 0;
	}
	//insert into "order" values (o_id,d_id,w_id,c_id,datetime,0,items,all_local);
	order o = { o_id, d_id, w_id, c_id, datetime, 0, items, all_local };
	auto orderKey = make_tuple(o.o_w_id, o.o_d_id, o.o_id);
	if (!insertorder(orderKey, o)) {
		cout << "Insert of order failed!" << endl;
		return;
	}
	//insert into neworder values (o_id,d_id,w_id);
	neworder no = { o_id, d_id, w_id };
	auto neworderKey = make_tuple(no.no_w_id, no.no_d_id, no.no_o_id);
	if (!insertneworder(neworderKey, no)) {
		cout << "Insert of new order failed";
		return;

	}

	Numeric<5, 2> i_price;
	Numeric<4, 0> s_quantity;
	Numeric<4, 0> s_remote_cnt;
	Numeric<4, 0> s_order_cnt;
	char s_dist[24];
	//select i_price from item where i_id=itemid[index];
	for (auto index = 0; index < items; index++) {
		auto itemKey = make_tuple(itemid[index]);
		item i = getitem(finditem(itemKey));
		i_price = i.i_price;
		//select s_quantity,s_remote_cnt,s_order_cnt,case d_id when 1 then s_dist_01 when 2 then s_dist_02 when 3 then s_dist_03 when 4 then s_dist_04
		//when 5 then s_dist_05 when 6 then s_dist_06 when 7 then s_dist_07 when 8 then s_dist_08 when 9 then s_dist_09
		//when 10 then s_dist_10 end as s_dist from stock where s_w_id=supware[index] and s_i_id=itemid[index];
		auto stockKey = make_tuple(supware[index], itemid[index]);
		stock s = getstock(findstock(stockKey));
		switch (d_id.value) {
		case 1:
			strcpy(s_dist, s.s_dist_01.value);
			break;
		case 2:
			strcpy(s_dist, s.s_dist_02.value);
			break;
		case 3:
			strcpy(s_dist, s.s_dist_03.value);
			break;
		case 4:
			strcpy(s_dist, s.s_dist_04.value);
			break;
		case 5:
			strcpy(s_dist, s.s_dist_05.value);
			break;
		case 6:
			strcpy(s_dist, s.s_dist_06.value);
			break;
		case 7:
			strcpy(s_dist, s.s_dist_07.value);
			break;
		case 8:
			strcpy(s_dist, s.s_dist_08.value);
			break;
		case 9:
			strcpy(s_dist, s.s_dist_09.value);
			break;
		case 10:
			strcpy(s_dist, s.s_dist_10.value);
			break;
		}
		s_quantity = s.s_quantity;
		s_remote_cnt = s.s_remote_cnt;
		s_order_cnt = s.s_order_cnt;
		// if (s_quantity>qty[index]) {
		// update stock set s_quantity=s_quantity-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
		// } else {
		// update stock set s_quantity=s_quantity+91-qty[index] where s_w_id=supware[index] and s_i_id=itemid[index];
		if (s_quantity > qty[index]) {
			s.s_quantity = s_quantity - qty[index];
		} else {
			s.s_quantity = s_quantity + 91 - qty[index];
		}
		//if (supware[index]<>w_id) {
		// update stock set s_remote_cnt=s_remote_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
		//} else {
		//update stock set s_order_cnt=s_order_cnt+1 where s_w_id=w_id and s_i_id=itemid[index];
		if (supware[index] != w_id) {
			s.s_remote_cnt = s_remote_cnt + 1;
		} else {
			s.s_order_cnt = s_order_cnt + 1;
		}

		Numeric<6, 2> ol_amount = Numeric<6, 2>(
				qty[index] * i_price.value * (1.0 + w_tax.value + d_tax.value)
						* (1.0 - c_discount.value));

		//insert into orderline values(o_id, d_id, w_id, index + 1, itemid[index],
		//supware[index], 0, qty[index], ol_amount, s_dist);

		orderline ol = { o_id, d_id, w_id, index + 1, itemid[index],
				supware[index], 0, qty[index], ol_amount };
		strcpy(ol.ol_dist_info.value, s_dist);
		auto orderlineKey = make_tuple(ol.ol_w_id, ol.ol_d_id, ol.ol_o_id,
				ol.ol_number);
		if (!insertorderline(orderlineKey, ol)) {
			cout << "Insert of orderline failed" << endl;
			return;
		}
	}
}

void newOrderRandom(Timestamp now, int w_id) {
	Integer d_id = urand(1, 10);
	Integer c_id = nurand(1023, 1, 3000);
	int ol_cnt = urand(5, 15);

	Integer supware[15];
	Integer itemid[15];
	Integer qty[15];
	for (auto i = 0; i < ol_cnt; i++) {
		if (urand(1, 100) > 1)
			supware[i] = Integer(w_id);
		else
			supware[i] = Integer(urandexcept(1, 5, w_id));
		itemid[i] = nurand(8191, 1, 100000);
		qty[i] = urand(1, 10);
	}
	newOrder(Integer(w_id), d_id, c_id, ol_cnt, supware, itemid, qty, now);
}

void delivery(Integer w_id, Integer o_carrier_id, Timestamp datetime) {
	//forsequence (d_id between 1 and 10) {
	for (auto d_id = 1; d_id <= 10; d_id++) {
		//select min(no_o_id) as o_id from neworder where no_w_id=w_id and no_d_id=d_id order by no_o_id else { continue; } -- ignore this district if no row found
		//TODO: Find min
		neworder no = getneworder(0);
		auto o_id = no.no_o_id;

		//delete from neworder where no_w_id=w_id and no_d_id=d_id and no_o_id=o_id;
		auto neworderKey = make_tuple(no.no_w_id, no.no_d_id, no.no_o_id);
		if(!deleteneworder(neworderKey))
		{
			cout << "Delete new order failed" << endl;
			return;
		}

		// select o_ol_cnt,o_c_id from "order" o where o_w_id=w_id and o_d_id=d_id and o.o_id=o_id;
		auto orderKey = make_tuple(w_id, no.no_d_id, no.no_o_id);
		order o = getorder(findorder(orderKey));
		auto o_ol_cnt = o.o_ol_cnt;
		auto o_c_id = o.o_c_id;
		// update "order" set o_carrier_id=o_carrier_id where o_w_id=w_id and o_d_id=d_id and "order".o_id=o_id;
		o.o_carrier_id = o_carrier_id;
		//var numeric(6,2) ol_total=0;
		Numeric<6, 2> ol_total = 0;
		//forsequence (ol_number between 1 and o_ol_cnt) {
		for (int ol_number = 1; ol_number <= o_ol_cnt.value; ol_number++) {
			//select ol_amount from orderline where ol_w_id=w_id and ol_d_id=d_id and ol_o_id=o_id and orderline.ol_number=ol_number;
			auto orderlineKey = make_tuple(w_id, Integer(d_id), Integer(o_id),
					Integer(ol_number));
			orderline ol = getorderline(findorderline(orderlineKey));
			auto ol_amount = ol.ol_amount;
			//ol_total=ol_total+ol_amount;
			ol_total = ol_total + ol_amount;
			//update orderline set ol_delivery_d=datetime where ol_w_id=w_id and ol_d_id=d_id and ol_o_id=o_id and orderline.ol_number=ol_number;
			ol.ol_delivery_d = datetime;
		}
		//update customer set c_balance=c_balance+ol_total where c_w_id=w_id and c_d_id=d_id and c_id=o_c_id;
		auto customerKey = make_tuple(w_id, Integer(d_id), Integer(o_c_id));
		customer c = getcustomer(findcustomer(customerKey));
		c.c_balance = c.c_balance + Numeric<12, 2>(ol_total.value);
	}
}

void init() {
	warehouseInit();
	districtInit();
	customerInit();
	historyInit();
	neworderInit();
	orderInit();
	orderlineInit();
	itemInit();
	stockInit();
}

int numberOfTransctions = 100;

int main() {
	init();
	//for (int rounds = 0; rounds < 10; rounds++) {
	time_t begin = time(0);
	cout << "Neworder(before): " << getnewordertablesize() << endl;
	cout << "Order(before): " << getordertablesize() << endl;
	cout << "Orderline(before): " << getorderlinetablesize() << endl;
	for (auto i = 0; i < numberOfTransctions; i++) {
		if (urand(1, 10) < 9) {
			int w_id = urand(1, 5);
			Timestamp now = Timestamp(time(0));
			newOrderRandom(now, w_id);
		} else {
			int w_id = urand(1, 5);
			delivery(w_id,Integer(urand(1,10)), Timestamp(time(0)));
		}
	}
	time_t end = time(0);
	cout << "Neworder(after): " << getnewordertablesize() << endl;
	cout << "Order(after): " << getordertablesize() << endl;
	cout << "Orderline(after): " << getorderlinetablesize() << endl;
	float totalTime = end - begin;
	cout << "Total time: " << end - begin << endl;
	cout << "Number of transactions per second: "
			<< numberOfTransctions / totalTime << endl;
	//}
	return 0;
}

