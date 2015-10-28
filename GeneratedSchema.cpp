#include "GeneratedSchema.hpp"
vector<warehouse> warehouseTable;
vector<tuple<tuple<Integer>, int>> warehouseIndexTable;

vector<district> districtTable;
vector<tuple<tuple<Integer,Integer>, int>> districtIndexTable;

vector<customer> customerTable;
vector<tuple<tuple<Integer,Integer,Integer>, int>> customerIndexTable;

vector<history> historyTable;
vector<tuple<tuple<Integer>, int>> historyIndexTable;

vector<neworder> neworderTable;
vector<tuple<tuple<Integer,Integer,Integer>, int>> neworderIndexTable;

vector<order> orderTable;
vector<tuple<tuple<Integer,Integer,Integer>, int>> orderIndexTable;

vector<orderline> orderlineTable;
vector<tuple<tuple<Integer,Integer,Integer,Integer>, int>> orderlineIndexTable;

vector<item> itemTable;
vector<tuple<tuple<Integer>, int>> itemIndexTable;

vector<stock> stockTable;
vector<tuple<tuple<Integer,Integer>, int>> stockIndexTable;


// Find functions
int findwarehouse(tuple<Integer> key) {
	for(auto entry : warehouseIndexTable){
	if(get<0>(entry) == key){
		return get<1>(entry);
		}
	}
	return -1;
}

int finddistrict(tuple<Integer,Integer> key) {
	for(auto entry : districtIndexTable){
	if(get<0>(entry) == key){
		return get<1>(entry);
		}
	}
	return -1;
}

int findcustomer(tuple<Integer,Integer,Integer> key) {
	for(auto entry : customerIndexTable){
	if(get<0>(entry) == key){
		return get<1>(entry);
		}
	}
	return -1;
}

int findneworder(tuple<Integer,Integer,Integer> key) {
	for(auto entry : neworderIndexTable){
	if(get<0>(entry) == key){
		return get<1>(entry);
		}
	}
	return -1;
}

int findorder(tuple<Integer,Integer,Integer> key) {
	for(auto entry : orderIndexTable){
	if(get<0>(entry) == key){
		return get<1>(entry);
		}
	}
	return -1;
}

int findorderline(tuple<Integer,Integer,Integer,Integer> key) {
	for(auto entry : orderlineIndexTable){
	if(get<0>(entry) == key){
		return get<1>(entry);
		}
	}
	return -1;
}

int finditem(tuple<Integer> key) {
	for(auto entry : itemIndexTable){
	if(get<0>(entry) == key){
		return get<1>(entry);
		}
	}
	return -1;
}

int findstock(tuple<Integer,Integer> key) {
	for(auto entry : stockIndexTable){
	if(get<0>(entry) == key){
		return get<1>(entry);
		}
	}
	return -1;
}

warehouse& getwarehouse(int i) {
	return warehouseTable[i];
}
district& getdistrict(int i) {
	return districtTable[i];
}
customer& getcustomer(int i) {
	return customerTable[i];
}
neworder& getneworder(int i) {
	return neworderTable[i];
}
order& getorder(int i) {
	return orderTable[i];
}
orderline& getorderline(int i) {
	return orderlineTable[i];
}
item& getitem(int i) {
	return itemTable[i];
}
stock& getstock(int i) {
	return stockTable[i];
}
// Delete functions
bool deletewarehouse(tuple<Integer> key) {
	for(auto indexEntry : warehouseIndexTable){
		if(get<0>(indexEntry) == key){
			int indexToDelete = get<1>(indexEntry);
			if(indexToDelete < 0)
				return false;
			iter_swap(warehouseTable.begin() + indexToDelete, warehouseTable.end());
			warehouseTable.pop_back();
			get<1>(indexEntry) = -1;
			return true;}}
	return false;
}

bool deletedistrict(tuple<Integer,Integer> key) {
	for(auto indexEntry : districtIndexTable){
		if(get<0>(indexEntry) == key){
			int indexToDelete = get<1>(indexEntry);
			if(indexToDelete < 0)
				return false;
			iter_swap(districtTable.begin() + indexToDelete, districtTable.end());
			districtTable.pop_back();
			get<1>(indexEntry) = -1;
			return true;}}
	return false;
}

bool deletecustomer(tuple<Integer,Integer,Integer> key) {
	for(auto indexEntry : customerIndexTable){
		if(get<0>(indexEntry) == key){
			int indexToDelete = get<1>(indexEntry);
			if(indexToDelete < 0)
				return false;
			iter_swap(customerTable.begin() + indexToDelete, customerTable.end());
			customerTable.pop_back();
			get<1>(indexEntry) = -1;
			return true;}}
	return false;
}

bool deleteneworder(tuple<Integer,Integer,Integer> key) {
	for(auto indexEntry : neworderIndexTable){
		if(get<0>(indexEntry) == key){
			int indexToDelete = get<1>(indexEntry);
			if(indexToDelete < 0)
				return false;
			iter_swap(neworderTable.begin() + indexToDelete, neworderTable.end());
			neworderTable.pop_back();
			get<1>(indexEntry) = -1;
			return true;}}
	return false;
}

bool deleteorder(tuple<Integer,Integer,Integer> key) {
	for(auto indexEntry : orderIndexTable){
		if(get<0>(indexEntry) == key){
			int indexToDelete = get<1>(indexEntry);
			if(indexToDelete < 0)
				return false;
			iter_swap(orderTable.begin() + indexToDelete, orderTable.end());
			orderTable.pop_back();
			get<1>(indexEntry) = -1;
			return true;}}
	return false;
}

bool deleteorderline(tuple<Integer,Integer,Integer,Integer> key) {
	for(auto indexEntry : orderlineIndexTable){
		if(get<0>(indexEntry) == key){
			int indexToDelete = get<1>(indexEntry);
			if(indexToDelete < 0)
				return false;
			iter_swap(orderlineTable.begin() + indexToDelete, orderlineTable.end());
			orderlineTable.pop_back();
			get<1>(indexEntry) = -1;
			return true;}}
	return false;
}

bool deleteitem(tuple<Integer> key) {
	for(auto indexEntry : itemIndexTable){
		if(get<0>(indexEntry) == key){
			int indexToDelete = get<1>(indexEntry);
			if(indexToDelete < 0)
				return false;
			iter_swap(itemTable.begin() + indexToDelete, itemTable.end());
			itemTable.pop_back();
			get<1>(indexEntry) = -1;
			return true;}}
	return false;
}

bool deletestock(tuple<Integer,Integer> key) {
	for(auto indexEntry : stockIndexTable){
		if(get<0>(indexEntry) == key){
			int indexToDelete = get<1>(indexEntry);
			if(indexToDelete < 0)
				return false;
			iter_swap(stockTable.begin() + indexToDelete, stockTable.end());
			stockTable.pop_back();
			get<1>(indexEntry) = -1;
			return true;}}
	return false;
}


// Insert functions
bool insertwarehouse(tuple<Integer>key, const warehouse& value) {
	if (findwarehouse(key) != -1)
		return false;
	warehouseTable.push_back(value);
	warehouseIndexTable.push_back(make_tuple(value.primaryKey, warehouseTable.size()));
	return true;
}

bool insertdistrict(tuple<Integer,Integer>key, const district& value) {
	if (finddistrict(key) != -1)
		return false;
	districtTable.push_back(value);
	districtIndexTable.push_back(make_tuple(value.primaryKey, districtTable.size()));
	return true;
}

bool insertcustomer(tuple<Integer,Integer,Integer>key, const customer& value) {
	if (findcustomer(key) != -1)
		return false;
	customerTable.push_back(value);
	customerIndexTable.push_back(make_tuple(value.primaryKey, customerTable.size()));
	return true;
}

bool insertneworder(tuple<Integer,Integer,Integer>key, const neworder& value) {
	if (findneworder(key) != -1)
		return false;
	neworderTable.push_back(value);
	neworderIndexTable.push_back(make_tuple(value.primaryKey, neworderTable.size()));
	return true;
}

bool insertorder(tuple<Integer,Integer,Integer>key, const order& value) {
	if (findorder(key) != -1)
		return false;
	orderTable.push_back(value);
	orderIndexTable.push_back(make_tuple(value.primaryKey, orderTable.size()));
	return true;
}

bool insertorderline(tuple<Integer,Integer,Integer,Integer>key, const orderline& value) {
	if (findorderline(key) != -1)
		return false;
	orderlineTable.push_back(value);
	orderlineIndexTable.push_back(make_tuple(value.primaryKey, orderlineTable.size()));
	return true;
}

bool insertitem(tuple<Integer>key, const item& value) {
	if (finditem(key) != -1)
		return false;
	itemTable.push_back(value);
	itemIndexTable.push_back(make_tuple(value.primaryKey, itemTable.size()));
	return true;
}

bool insertstock(tuple<Integer,Integer>key, const stock& value) {
	if (findstock(key) != -1)
		return false;
	stockTable.push_back(value);
	stockIndexTable.push_back(make_tuple(value.primaryKey, stockTable.size()));
	return true;
}

void warehouseInit() {
	ifstream file;
	file.open("tpcc_warehouse.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		warehouse rel;
		 elements = split(line, "|");
	rel.w_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.w_name = Varchar<10>::castString(elements[1].c_str(), elements[1].size());
	rel.w_street_1 = Varchar<20>::castString(elements[2].c_str(), elements[2].size());
	rel.w_street_2 = Varchar<20>::castString(elements[3].c_str(), elements[3].size());
	rel.w_city = Varchar<20>::castString(elements[4].c_str(), elements[4].size());
	rel.w_state = Char<2>::castString(elements[5].c_str(), elements[5].size());
	rel.w_zip = Char<9>::castString(elements[6].c_str(), elements[6].size());
	rel.w_tax = 	Numeric<4,4>::castString(elements[7].c_str(), elements[7].size());
	rel.w_ytd = 	Numeric<12,2>::castString(elements[8].c_str(), elements[8].size());
		warehouseTable.push_back(rel);
	rel.primaryKey = make_tuple(rel.w_id);
		warehouseIndexTable.push_back(make_tuple(rel.primaryKey, warehouseTable.size()));
	}
sort(warehouseIndexTable.begin(), warehouseIndexTable.end());
	file.close();
}

void districtInit() {
	ifstream file;
	file.open("tpcc_district.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		district rel;
		 elements = split(line, "|");
	rel.d_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.d_w_id = Integer::castString(elements[1].c_str(), elements[1].size());
	rel.d_name = Varchar<10>::castString(elements[2].c_str(), elements[2].size());
	rel.d_street_1 = Varchar<20>::castString(elements[3].c_str(), elements[3].size());
	rel.d_street_2 = Varchar<20>::castString(elements[4].c_str(), elements[4].size());
	rel.d_city = Varchar<20>::castString(elements[5].c_str(), elements[5].size());
	rel.d_state = Char<2>::castString(elements[6].c_str(), elements[6].size());
	rel.d_zip = Char<9>::castString(elements[7].c_str(), elements[7].size());
	rel.d_tax = 	Numeric<4,4>::castString(elements[8].c_str(), elements[8].size());
	rel.d_ytd = 	Numeric<12,2>::castString(elements[9].c_str(), elements[9].size());
	rel.d_next_o_id = Integer::castString(elements[10].c_str(), elements[10].size());
		districtTable.push_back(rel);
	rel.primaryKey = make_tuple(rel.d_w_id,rel.d_id);
		districtIndexTable.push_back(make_tuple(rel.primaryKey, districtTable.size()));
	}
sort(districtIndexTable.begin(), districtIndexTable.end());
	file.close();
}

void customerInit() {
	ifstream file;
	file.open("tpcc_customer.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		customer rel;
		 elements = split(line, "|");
	rel.c_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.c_d_id = Integer::castString(elements[1].c_str(), elements[1].size());
	rel.c_w_id = Integer::castString(elements[2].c_str(), elements[2].size());
	rel.c_first = Varchar<16>::castString(elements[3].c_str(), elements[3].size());
	rel.c_middle = Char<2>::castString(elements[4].c_str(), elements[4].size());
	rel.c_last = Varchar<16>::castString(elements[5].c_str(), elements[5].size());
	rel.c_street_1 = Varchar<20>::castString(elements[6].c_str(), elements[6].size());
	rel.c_street_2 = Varchar<20>::castString(elements[7].c_str(), elements[7].size());
	rel.c_city = Varchar<20>::castString(elements[8].c_str(), elements[8].size());
	rel.c_state = Char<2>::castString(elements[9].c_str(), elements[9].size());
	rel.c_zip = Char<9>::castString(elements[10].c_str(), elements[10].size());
	rel.c_phone = Char<16>::castString(elements[11].c_str(), elements[11].size());
	rel.c_since = Timestamp(0);
	rel.c_credit = Char<2>::castString(elements[13].c_str(), elements[13].size());
	rel.c_credit_lim = 	Numeric<12,2>::castString(elements[14].c_str(), elements[14].size());
	rel.c_discount = 	Numeric<4,4>::castString(elements[15].c_str(), elements[15].size());
	rel.c_balance = 	Numeric<12,2>::castString(elements[16].c_str(), elements[16].size());
	rel.c_ytd_paymenr = 	Numeric<12,2>::castString(elements[17].c_str(), elements[17].size());
	rel.c_payment_cnt = 	Numeric<4,0>::castString(elements[18].c_str(), elements[18].size());
	rel.c_delivery_cnt = 	Numeric<4,0>::castString(elements[19].c_str(), elements[19].size());
	rel.c_data = Varchar<500>::castString(elements[20].c_str(), elements[20].size());
		customerTable.push_back(rel);
	rel.primaryKey = make_tuple(rel.c_w_id,rel.c_d_id,rel.c_id);
		customerIndexTable.push_back(make_tuple(rel.primaryKey, customerTable.size()));
	}
sort(customerIndexTable.begin(), customerIndexTable.end());
	file.close();
}

void historyInit() {
	ifstream file;
	file.open("tpcc_history.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		history rel;
		 elements = split(line, "|");
	rel.h_c_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.h_c_d_id = Integer::castString(elements[1].c_str(), elements[1].size());
	rel.h_c_w_id = Integer::castString(elements[2].c_str(), elements[2].size());
	rel.h_d_id = Integer::castString(elements[3].c_str(), elements[3].size());
	rel.h_w_id = Integer::castString(elements[4].c_str(), elements[4].size());
	rel.h_date = Timestamp(0);
	rel.h_amount = 	Numeric<6,2>::castString(elements[6].c_str(), elements[6].size());
	rel.h_data = Varchar<24>::castString(elements[7].c_str(), elements[7].size());
		historyTable.push_back(rel);
}
	file.close();
}
void neworderInit() {
	ifstream file;
	file.open("tpcc_neworder.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		neworder rel;
		 elements = split(line, "|");
	rel.no_o_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.no_d_id = Integer::castString(elements[1].c_str(), elements[1].size());
	rel.no_w_id = Integer::castString(elements[2].c_str(), elements[2].size());
		neworderTable.push_back(rel);
	rel.primaryKey = make_tuple(rel.no_w_id,rel.no_d_id,rel.no_o_id);
		neworderIndexTable.push_back(make_tuple(rel.primaryKey, neworderTable.size()));
	}
sort(neworderIndexTable.begin(), neworderIndexTable.end());
	file.close();
}

void orderInit() {
	ifstream file;
	file.open("tpcc_order.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		order rel;
		 elements = split(line, "|");
	rel.o_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.o_d_id = Integer::castString(elements[1].c_str(), elements[1].size());
	rel.o_w_id = Integer::castString(elements[2].c_str(), elements[2].size());
	rel.o_c_id = Integer::castString(elements[3].c_str(), elements[3].size());
	rel.o_entry_d = Timestamp(0);
	rel.o_carrier_id = Integer::castString(elements[5].c_str(), elements[5].size());
	rel.o_ol_cnt = 	Numeric<2,0>::castString(elements[6].c_str(), elements[6].size());
	rel.o_all_local = 	Numeric<1,0>::castString(elements[7].c_str(), elements[7].size());
		orderTable.push_back(rel);
	rel.primaryKey = make_tuple(rel.o_w_id,rel.o_d_id,rel.o_id);
		orderIndexTable.push_back(make_tuple(rel.primaryKey, orderTable.size()));
	}
sort(orderIndexTable.begin(), orderIndexTable.end());
	file.close();
}

void orderlineInit() {
	ifstream file;
	file.open("tpcc_orderline.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		orderline rel;
		 elements = split(line, "|");
	rel.ol_o_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.ol_d_id = Integer::castString(elements[1].c_str(), elements[1].size());
	rel.ol_w_id = Integer::castString(elements[2].c_str(), elements[2].size());
	rel.ol_number = Integer::castString(elements[3].c_str(), elements[3].size());
	rel.ol_i_id = Integer::castString(elements[4].c_str(), elements[4].size());
	rel.ol_supply_w_id = Integer::castString(elements[5].c_str(), elements[5].size());
	rel.ol_delivery_d = Timestamp(0);
	rel.ol_quantity = 	Numeric<2,0>::castString(elements[7].c_str(), elements[7].size());
	rel.ol_amount = 	Numeric<6,2>::castString(elements[8].c_str(), elements[8].size());
	rel.ol_dist_info = Char<24>::castString(elements[9].c_str(), elements[9].size());
		orderlineTable.push_back(rel);
	rel.primaryKey = make_tuple(rel.ol_w_id,rel.ol_d_id,rel.ol_o_id,rel.ol_number);
		orderlineIndexTable.push_back(make_tuple(rel.primaryKey, orderlineTable.size()));
	}
sort(orderlineIndexTable.begin(), orderlineIndexTable.end());
	file.close();
}

void itemInit() {
	ifstream file;
	file.open("tpcc_item.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		item rel;
		 elements = split(line, "|");
	rel.i_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.i_im_id = Integer::castString(elements[1].c_str(), elements[1].size());
	rel.i_name = Varchar<24>::castString(elements[2].c_str(), elements[2].size());
	rel.i_price = 	Numeric<5,2>::castString(elements[3].c_str(), elements[3].size());
	rel.i_data = Varchar<50>::castString(elements[4].c_str(), elements[4].size());
		itemTable.push_back(rel);
	rel.primaryKey = make_tuple(rel.i_id);
		itemIndexTable.push_back(make_tuple(rel.primaryKey, itemTable.size()));
	}
sort(itemIndexTable.begin(), itemIndexTable.end());
	file.close();
}

void stockInit() {
	ifstream file;
	file.open("tpcc_stock.tbl");
	string line;
	vector<string> elements;
	while (getline(file, line)) {
		stock rel;
		 elements = split(line, "|");
	rel.s_i_id = Integer::castString(elements[0].c_str(), elements[0].size());
	rel.s_w_id = Integer::castString(elements[1].c_str(), elements[1].size());
	rel.s_quantity = 	Numeric<4,0>::castString(elements[2].c_str(), elements[2].size());
	rel.s_dist_01 = Char<24>::castString(elements[3].c_str(), elements[3].size());
	rel.s_dist_02 = Char<24>::castString(elements[4].c_str(), elements[4].size());
	rel.s_dist_03 = Char<24>::castString(elements[5].c_str(), elements[5].size());
	rel.s_dist_04 = Char<24>::castString(elements[6].c_str(), elements[6].size());
	rel.s_dist_05 = Char<24>::castString(elements[7].c_str(), elements[7].size());
	rel.s_dist_06 = Char<24>::castString(elements[8].c_str(), elements[8].size());
	rel.s_dist_07 = Char<24>::castString(elements[9].c_str(), elements[9].size());
	rel.s_dist_08 = Char<24>::castString(elements[10].c_str(), elements[10].size());
	rel.s_dist_09 = Char<24>::castString(elements[11].c_str(), elements[11].size());
	rel.s_dist_10 = Char<24>::castString(elements[12].c_str(), elements[12].size());
	rel.s_ytd = 	Numeric<8,0>::castString(elements[13].c_str(), elements[13].size());
	rel.s_order_cnt = 	Numeric<4,0>::castString(elements[14].c_str(), elements[14].size());
	rel.s_remote_cnt = 	Numeric<4,0>::castString(elements[15].c_str(), elements[15].size());
	rel.s_data = Varchar<50>::castString(elements[16].c_str(), elements[16].size());
		stockTable.push_back(rel);
	rel.primaryKey = make_tuple(rel.s_w_id,rel.s_i_id);
		stockIndexTable.push_back(make_tuple(rel.primaryKey, stockTable.size()));
	}
sort(stockIndexTable.begin(), stockIndexTable.end());
	file.close();
}

int getordertablesize() {
	return orderTable.size();
}
int getnewordertablesize() {
	return neworderTable.size();
}
int getorderlinetablesize() {
	return orderlineTable.size();
}
