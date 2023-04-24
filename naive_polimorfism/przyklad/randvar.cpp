#include <vector>
#include <math.h>
#include <numeric>
#include <iostream>
#define COUT(x) std::cout << x << std::endl;


class DiscreteProbabilitySpace : private std::vector<double> {
public:
    using Base = std::vector<double>;
    using Base::size;
    using Base::empty;

    // we cannot do this by using, because it would give
    // us non-const operator[] too
    const double operator[](int i) const {
        return Base::operator[](i);
    }

    DiscreteProbabilitySpace& operator=(const std::vector<double> &v){        
        if(std::abs(std::accumulate(v.begin(), v.end(), 0.) - 1.) < eps){
            Base::operator=(v);   
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream &o, const DiscreteProbabilitySpace &dps){
        for(auto x: dps){
            o << x << " ";
        }
        return o;
    }

private:
    static constexpr double eps = 1e-8;
};


class DiscreteRandomVariable : private std::vector<double> {
public:
    using Base = std::vector<double>;
    using Base::size;
    using Base::empty;
    using Base::operator[];
    using Base::at;

    DiscreteRandomVariable(const DiscreteProbabilitySpace &dps, const std::vector<double> &v) 
        : Base(v), dps(dps) {}
    
    double expected_value() const {
        double ret = 0;
        for(int i = 0; i < size(); ++i){
            ret += this->operator[](i) * dps[i];
        }
        return ret;
    }

    friend std::ostream& operator<<(std::ostream &o, const DiscreteRandomVariable &drv){
        for(auto x: drv){
            o << x << " ";
        }
        return o;
    }

private:
    DiscreteProbabilitySpace dps;
};


int main(int argc, char const *argv[])
{
    // DiscreteProbabilitySpace dps;
    // dps = {0.25, 0.25, 0.5};
    // COUT(dps[0]);
    
    // // we want it not to work 
    // // dps[0] = 1;

    // COUT(dps);

    DiscreteProbabilitySpace dice;
    dice = std::vector<double>(6, 1. / 6);
    COUT(dice);

    auto ev = DiscreteRandomVariable(dice, {1, 2, 3, 4, 5, 6}).expected_value();
    COUT(ev);


    return 0;
}
