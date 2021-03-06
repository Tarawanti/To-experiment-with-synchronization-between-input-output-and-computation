﻿// HCI_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#pragma warning(disable : 4996)
#include <atomic>
#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include <math.h>
void ReadCin(std::atomic<bool>& run)

{
	char ch;
	int buffer;
	// while the variable 'run' is true waiting some symbol 
	// if it is the 's' symbol set the 'run' variable the false value
	while (run.load())

	{

		if (getch() == int('s'))

		{

			// set the 'run' variable the false value

			run.store(false);

		}
	}
}
int main()
{
	// defining the number PI
	double PI = 3.1415926;
	// defining an operation number variable
	int operationsCount;
	// infinite loop for square root calculation procedure <operationsCount> times
	while (true)
	{
		// loop for getting <operationsCount> from the user
		while (true)
		{
			// the first message
			std::cout << "Enter an integer or q to quit." << std::endl;
			// the variable for symbols sequence from the console
			std::string inSymbols;
			// getting symbols fron the console
			std::cin >> inSymbols;
			// if the user has entered 'q' exit the program
			if (inSymbols == "q")
			{
				return 0;
			}

			// check the correctness of the number of operations of calculation of the square root, 
			// it is required that it was a number without other characters
			try

			{

				// stoi - this function converts the string to an number
				operationsCount = std::stoi(inSymbols);
			}

			catch (...)

			{

				// if you entered not a number, but something else, ask again

				std::cout << "Wrong input of the operations' count" << std::endl;

				continue;

			}



			// if the input is correct, exit this loop

			break;

		}



		// defining the variable 'run' to True

		// Atomic types are types that encapsulate a value whose access is guaranteed to not cause data races 

		// and can be used to synchronize memory accesses among different threads

		// We use this variable in this thread(here we calculate square roots) and in the thread cinThread(where we can get the symbol 's' to stop calculating)

		std::atomic<bool> run(true);



		// defining the thread cinThread in which the function ReadCin works, and we also pass the 'run' variable reference to this function 

		std::thread cinThread(ReadCin, std::ref(run));



		// square root operation counter

		int opCounter = 0;



		// while the variable 'run' is true do the square root operation and print the result to console

		while (run.load()) // (***)

		{

			// getting the square root

			double result = sqrt(PI);



			// printing to console

			std::cout << (opCounter + 1) << std::endl;



			// if we got <operationCount> operations then stop and go the message "Enter an integer or q to quit." at the start of the cycle

			if (++opCounter == operationsCount)

			{

				std::cout << "The square root of PI is " << result << std::endl;

				break;

			}

		}



		// set the 'run' varuable to false, stopping the cicle (***)

		run.store(false);



		// waiting when cinThread ends

		cinThread.join();

	}



	return 0;

}

#pragma warning(disable : 4996)

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
