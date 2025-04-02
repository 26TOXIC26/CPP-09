/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:50:27 by pc                #+#    #+#             */
/*   Updated: 2025/04/02 04:02:25 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void error_exit(const char *error)
{
    std::cout << error << std::endl;
    exit(1);
}

void check_argv (int argc, char **argv)
{
    if (argc > 3001)
        error_exit ("Error: Too many Argument");
    for (int i = 1; i < argc; i++)
    {
        for (int j = 0; argv[i][j]; j++)
            if (!isdigit(argv[i][j]))
                error_exit ("Error: Argument is not a number");
    }
}

void fill_continers (std::list<size_t> &f_continer, std::deque<size_t> &s_continer, int argc, char **argv)
{
    size_t tmp;
    for (int i = 1; i < argc; i++)
    {
        tmp = std::strtoul (argv[i], NULL, 10);
        f_continer.push_back (tmp);
        s_continer.push_back (tmp);
    }
}

void check_dup (std::deque<size_t> &continer)
{
    std::deque<size_t>::iterator it = continer.begin();
    while (it != continer.end() - 1)
    {
        if (std::find(it + 1, continer.end(), *it) != continer.end())
            error_exit ("Error: Duplicate numbers are not allowed");
        it++;
    }
}

void merge(std::list<size_t>& left, std::list<size_t>& right, std::list<size_t>& merged) {
    std::list<size_t>::iterator itL = left.begin();
    std::list<size_t>::iterator itR = right.begin();
    while (itL != left.end() && itR != right.end()) {
        if (*itL < *itR)
            merged.push_back(*itL++);
        else
            merged.push_back(*itR++);
    }
    while (itL != left.end())
        merged.push_back(*itL++);
    while (itR != right.end())
        merged.push_back(*itR++);
}

void mergeSort(std::list<size_t>& lst) {
    if (lst.size() <= 1)
        return;
    std::list<size_t> left, right;
    std::list<size_t>::iterator it = lst.begin();
    for (size_t i = 0; i < lst.size() / 2; i++)
        it++;
    left.splice(left.begin(), lst, lst.begin(), it);
    right.splice(right.begin(), lst, lst.begin(), lst.end());
    mergeSort(left);
    mergeSort(right);
    merge(left, right, lst);
}

void put_s_b(std::list<size_t> &big, size_t value)
{
    std::list<size_t>::iterator it = big.begin();
    for (; it != big.end(); it++)
        if (*it > value)
            break;
    big.insert (it, value);
}

void sort_list (std::list<size_t> &continer)
{
    if (continer.size() < 2)
        return ;
    std::list<size_t> small, big;
    std::list<size_t>::iterator it = continer.begin();
    
    while (it != continer.end())
    {
        size_t a = *it;
        it++;
        if (it != continer.end())
        {
            size_t b = *it;
            it++;
            if (a > b)
                std::swap(a, b);
            small.push_back(a);
            big.push_back(b);
        }
        else
            big.push_back(a);
    }
    mergeSort(big);
    for (std::list<size_t>::iterator s_it = small.begin(); s_it != small.end(); s_it++)
        put_s_b(big, *s_it);
    continer = big;
}

int main (int argc, char **argv)
{
    std::list<size_t> f_continer;
    std::deque<size_t> s_continer;

    check_argv(argc, argv);
    fill_continers (f_continer, s_continer, argc, argv);
    check_dup (s_continer);
    std::cout << "Before:";
    for (std::list<size_t>::iterator it = f_continer.begin(); it != f_continer.end(); it++)
        std::cout << " " << *it;
    std::cout << std::endl;
    clock_t start1 = clock();
    sort_list (f_continer);
    clock_t end1 = clock();
    double time1 = static_cast<double>(end1 - start1) / CLOCKS_PER_SEC * 1000;
    std::cout << "After: ";
    for (std::list<size_t>::iterator it = f_continer.begin(); it != f_continer.end(); it++)
        std::cout << " " << *it;
    std::cout << std::endl;
    std::cout << "Time to process a range of " << f_continer.size() << " elements with std::list container: " << time1 << " us" << std::endl;
}