#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <range/v3/all.hpp>
#include "ip_filter2.h"

using ip = std::vector<std::string>;
// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
ip split(const std::string& str, char d)
{
    ip r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

bool ip_comp(ip a, ip b)
{
    for (int i = 0; i < a.size(); ++i)
        if (std::stoi(a.at(i)) == std::stoi(b.at(i)))
            continue;
        else return std::stoi(a.at(i)) > std::stoi(b.at(i));
    return false;
}

int main(int argc, char const* argv[])
{
    try
    {
        std::vector<ip> ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }
        
        ranges::sort(ip_pool, ip_comp);

        for (auto ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        {
            for (auto ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
            {
                if (ip_part != ip->cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // Filter by first byte and output 
        std::vector<ip> filter1;
        ranges::for_each(ip_pool, [&filter1](auto a) 
            {if (stoi(a.at(0)) == 1) 
                { filter1.push_back(a); 
                    for (const auto& i : a) std::cout << i << ".";
                        std::cout << std::endl; } });
        std::cout << std::endl;
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // Filter by first and second bytes and output
        std::vector<ip> filter2;
        ranges::for_each(ip_pool, [&filter2](auto a) 
            {if (stoi(a.at(0)) == 46 && stoi(a.at(1)) == 70) 
                { filter2.push_back(a); 
                    for (const auto& i : a) std::cout << i << ".";
                        std::cout << std::endl;
                } });
        std::cout << std::endl;
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // Filter by any byte and output  
        std::vector<ip> filter3;
        ranges::for_each(ip_pool, [&filter3](auto a) 
            {for(const auto& i : a)
                if(i == "46"){
                    filter3.push_back(a);
                        for (const auto& i : a) std::cout << i << ".";
                            std::cout << std::endl; break;
                } });
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

