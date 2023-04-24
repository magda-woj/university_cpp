#include <string>
#include <iostream>
#include <vector>
#define COUT(x) std::cout << x << std::endl;

class Item {
public:
    Item(double width, double weight, std::string name) : 
        width(width), weight(weight), name(name), type("item") {
        COUT("Item");
    }

    double get_width() const { return width; }
    double get_weight() const { return weight; }
    std::string get_name() const {
        return name;
    }

    std::string get_type() const {
        return type;
    }
protected:
    // so we can fill other type in inheriting classes
    // protected because we do not want to show it to the user
    Item(double width, double weight, std::string name, std::string type) : 
        width(width), weight(weight), name(name), type(type) {
        COUT("Item protected");
    }
private:
    std::string name;
    std::string type;
    double width, weight;
};

class Book : public Item {
public:
    Book(double width, double weight, std::string name, int no_of_pages) 
            : Item(width, weight, name, "book"), no_of_pages(no_of_pages){
        COUT("Book");
    }

    int get_no_of_pages() const { return no_of_pages; }

    std::string get_name() const {
        return "book " + Item::get_name();
    }
protected:
    // so we can change type in inheriting objects
    Book(double width, double weight, std::string name, int no_of_pages, std::string type) 
            : Item(width, weight, name, type), no_of_pages(no_of_pages){
        COUT("Book protected");
    }

private:
    int no_of_pages;
};

class Drive : public Item {
public:
    Drive(double width, double weight, std::string name, double space) 
            : Item(width, weight, name, "drive"), space(space){
        COUT("Drive");
    }

    std::string get_name() const {
        return "drive " + Item::get_name();
    }
protected:
    Drive(double width, double weight, std::string name, double space, std::string type) 
            : Item(width, weight, name, type), space(space){
        COUT("Drive protected");
    }
private:
    double space;
};


class CD : public Drive {
public:
    CD(double width, double weight, std::string name, double space, int no_of_pieces) 
            : Drive(width, weight, name, space, "CD"), no_of_pieces(no_of_pieces){
        COUT("CD");
    }

    std::string get_name() const {
        return "cd " + Drive::get_name();
    }
protected:
    CD(double width, double weight, std::string name, double space, int no_of_pieces, std::string type) 
                : Drive(width, weight, name, space, type), no_of_pieces(no_of_pieces){
        COUT("CD protected");
    }
private:
    int no_of_pieces;
};


class DVD : public Drive {
public:
    DVD(double width, double weight, std::string name, double space, int no_of_pieces) 
            : Drive(width, weight, name, space, "DVD"), no_of_pieces(no_of_pieces){
        COUT("DVD");
    }

    std::string get_name() const {
        return "dvd " + Drive::get_name();
    }
protected:
    DVD(double width, double weight, std::string name, double space, int no_of_pieces, std::string type) 
                    : Drive(width, weight, name, space, type), no_of_pieces(no_of_pieces){
            COUT("CD protected");
        }
private:
    int no_of_pieces;
};


class WrongShelf {
public:
    WrongShelf(double max_width, double max_weight) : max_width(max_width), max_weight(max_weight) {}

    bool add(Item it) {
        if(cur_weight + it.get_weight() > max_weight) return false;
        if(cur_width + it.get_width() > max_width) return false;
        
        cur_weight += it.get_weight();
        cur_width += it.get_width();
        
        items.push_back(it);
        return true;
    }

    const Item& operator[](int i) const {
        return items[i];
    }
private:
    std::vector<Item> items;
    double cur_width = 0, cur_weight = 0;
    double max_width, max_weight;
};


class GoodShelf {
public:
    GoodShelf(double max_width, double max_weight) : max_width(max_width), max_weight(max_weight) {}

    bool add(Item *it) {
        if(cur_weight + it->get_weight() > max_weight) return false;
        if(cur_width + it->get_width() > max_width) return false;
        
        cur_weight += it->get_weight();
        cur_width += it->get_width();
        
        items.push_back(it);
        return true;
    }

    const Item* operator[](int i) const {
        return items[i];
    }
private:
    std::vector<Item*> items;
    double cur_width = 0, cur_weight = 0;
    double max_width, max_weight;
};


// naive polymorphism example
std::ostream& operator<<(std::ostream &o, const Item &it){
    if(it.get_type() == "item"){
        o << it.get_name();
    }
    else if(it.get_type() == "book"){
        o << ((const Book&)it).get_name();
    }
    else if(it.get_type() == "drive"){
        o << ((const Drive&)it).get_name();
    }
    else if(it.get_type() == "CD"){
        o << ((const CD&)it).get_name();
    }
    else if(it.get_type() == "DVD"){
        o << ((const DVD&)it).get_name();
    }
    return o;
}


int main(int argc, char const *argv[])
{
    // take a look at called constructors and their order
    COUT("BOOK CONSTRUCTION");
    Book b(1, 1, "analiza", 10);
    COUT("DVD CONSTRUCTION")
    DVD dvd(1, 1, "gothic", 1, 1);
    

    // Wrong shelf implementation
    WrongShelf s(100, 100);
    // it casts Book to Item - cuts out the data whic is not in Item!
    s.add(b);
    
    // we reinterpret item as the book again
    const Book *bp = (const Book*)(&s[0]);
    COUT("WRONG SHELF");
    COUT(bp->get_weight());
    COUT(bp->get_width());
    // whoops! no_of_pages got cut out, returns some junk (probably 0)
    COUT(bp->get_no_of_pages());
    

    // Good shelf implementation
    GoodShelf s2(100, 100);
    // we give a pointer, no data is cut
    s2.add(&b);

    // we again reinterpret Item* as Book*, this time successfully
    bp = (const Book*)(s2[0]);
    COUT("GOOD SHELF");
    COUT(bp->get_weight());
    COUT(bp->get_width());
    // data is not cut out
    COUT(bp->get_no_of_pages());


    // checking naive polymorphism
    std::cout << b << "\n";
    std::cout << dvd << "\n";

    return 0;
}
