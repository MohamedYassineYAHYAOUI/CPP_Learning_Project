#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>
#include <type_traits>


template<std::size_t dimension, typename PointType>
class Point
{

private:
 
    
    std::size_t size() const { return dimension;}


public:

    std::array<PointType, dimension > values;
   
    Point()=default;
   
    template <typename... Qs, std::enable_if_t<std::is_arithmetic_v<PointType>,bool> = true>
    Point(const PointType& first, Qs... others): values{first, static_cast<PointType>(others) ...}{
        static_assert(dimension-1 == sizeof...(Qs));
    };
    
   

    PointType& x() { 
        static_assert(dimension >=2);
        return values[0]; 
    }
    PointType x() const {
        static_assert(dimension >=2);
        return values[0]; 
    }

    PointType& y() { 
        static_assert(dimension >=2);
        return values[1]; 
    }
    PointType y() const { 
        static_assert(dimension >=2);
        return values[1];
        }
     
    PointType& z() {
        static_assert(dimension >2);
        return values[2];
        }
    PointType z() const { 
        static_assert(dimension >2);
        return values[2];
        }


    PointType& value(int dim) 
    {
        assert(dim >=0 && dim < dimension);
        return values[dim]; 
    }
    PointType value(int dim) const 
    {
        assert(dim >=0 && dim < dimension);
        return values[dim]; 
    }

    Point& operator+=(const Point& other)
    {
        assert(other.size() == size());
        int i=0;
        std::transform(values.begin(), values.end(), values.begin(), [&other, &i](PointType v){return v+other.values[i++];});
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        assert(other.size() == size());

        int i=0;
        std::transform(values.begin(), values.end(), values.begin(), [&other, &i](PointType v){return v-other.values[i++];});
        return *this;
    }

    Point& operator*=(const PointType scalar)
    {

        std::transform(values.begin(), values.end(), values.begin(), [scalar](PointType v){return v*scalar;});
        return *this;
    }

    Point& operator*=(const Point& other)
    {
        int i=0;
        std::transform(values.begin(), values.end(), values.begin(), [&other, &i](PointType v){return v * other.values[i++];});

        return *this;
    }


    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const PointType scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }




    Point operator-() const 
    {
        Point point = *this;
        std::transform(values.begin(), values.end(), point.values.begin() ,[&point](PointType v){return -v; });
        return point;
    }


    bool operator!=(const Point& other)
    {
        
        return std::all_of(values.begin(), values.end(), [&other](PointType v1, PointType v2){ return v1 != v2;});
    }


    PointType length() const 
    { 
        return std::sqrt(std::inner_product(values.begin(), values.end(), values.begin(), 0.f));
    }

    PointType distance_to(const Point& other) const { return (*this - other).length(); }


    Point& normalize(const PointType target_len = 1.0f)
    {
        const PointType current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("cannot normalize vector of length 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }    

    Point& cap_length(const PointType max_len)
    {
        assert(max_len > 0);

        const PointType current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }
};