/* User code: This file will not be overwritten by TASTE. */

#include "signal_handler.h"
#include <iostream>
#include <csignal>
#include <unistd.h>

void handle_signal( int signum )
{
	std::cout << "Interrupt signal (" << signum << ") received.\n"<<std::endl;
	signal_handler_RI_sigint();
	signal_handler_RI_sigint1();
	signal_handler_RI_sigint2();
	sleep(1);
	std::cout << "Terminating..."<<std::endl;
	exit(0);
}

void signal_handler_startup()
{
    //Register signal handler for SIGINT to close log file
    signal(SIGINT, handle_signal);
}

void signal_handler_PI_trigger()
{
    /* Write your code here! */
}

