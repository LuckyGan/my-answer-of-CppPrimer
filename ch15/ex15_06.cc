 ///
 /// @file    ex15_05.cc
 /// @author  zack(18357154046@163.com)
 /// @date    2017-08-01 10:26:21
 ///
#include <iostream>
class Quote{
public:
	Quote()=default;
	Quote(const std::string &book,double sales_price):
		bookNo(book),price(sales_price){}
	std::string isbn() const {
		return bookNo;
	}
	virtual double net_price(std::size_t n) const{
		return n*price;
	}
	virtual ~Quote()=default;
private:
	std::string bookNo;
protected:
	double price=0.0;
};
double print_total(std::ostream &os,Quote const &item,size_t n){
	double ret=item.net_price(n);
	os<<"ISBN:"<<item.isbn()<<" # sold:"<<n<<" total due:"<<ret<<std::endl;
	return ret;
}

class Bulk_quote:public Quote{
public:
	Bulk_quote()=default;
	Bulk_quote(const std::string& book,double p,std::size_t qty,double disc):
		Quote(book,p),min_qty(qty),discount(disc){
	}
	double net_price(std::size_t cnt) const override{
		if(cnt>=min_qty)
			return cnt*(1-discount)*price;
		else
			return cnt*price;
	}
private:
	std::size_t min_qty=0;
	double discount=0.0;
};

int main(){
	Quote quote("0-201-78345-X",23.8);
	print_total(std::cout,quote,3);
	Bulk_quote bulk_quote("0-201-78345-X",23.8,3,0.5);
	print_total(std::cout,bulk_quote,3);
	return 0;
}
