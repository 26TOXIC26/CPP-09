/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pc <pc@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 06:27:50 by pc                #+#    #+#             */
/*   Updated: 2025/03/30 06:37:12 by pc               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

void check_arg (char *argv)
{
    for (size_t i = 0; argv[i]; i++)
    {
        if (!isdigit(argv[i]) && argv[i] != '+' && argv[i] != '-' && argv[i] != '/' && argv[i] != '*')
        {
            std::cout << "Error" << std::endl;
            exit (1);
        }
    }
}

int main (int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }
    check_arg (argv[1]);
}