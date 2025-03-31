/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 06:27:50 by pc                #+#    #+#             */
/*   Updated: 2025/03/31 05:35:30 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main (int argc, char **argv)
{
    std::vector<int> vector;
    if (argc != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    check_arg (argv[1]);
    fill_vector (vector, argv[1]);
    if (vector.size() != 1)
        error_exit ("Error: Too many operands, extra tokens detected");
    std::cout << vector[0] << std::endl;
}