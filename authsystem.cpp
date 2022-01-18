#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <conio.h>
#include <algorithm>

class auth {

protected:
	std::string key = "n2r5u8x/A?D(G+KbPeShVkYp3s6v9y$B&E)H@McQfTjWnZq4t7w!z%C*F-JaNdRgUkXp2s5u8x/A?D(G+KbPeShVmYq3t6w9y$B&E)H@McQfTjWnZr4u7x!A%C*F-JaNdRgUkXp2s5v8y/B?E(G+KbPeShVmYq3t6w9z$C&F)J@McQfTjWnZr4u7x!A%D*G-KaPdRgUkXp2s5v8y/B?E(H+MbQeThVmYq3t6w9z$C&F)J@NcRfUjXn2r4u7x!A%D*G-KaPdSgVkYp3s6v8y/B?E(H+MbQeThWmZq4t7w!z$C&F)J@NcRfUjXn2r5u8x/A?D*G-KaPdSgVkYp3s6v9y$B&E)H+MbQeThWmZq4t7w!z%C*F-JaNcRfUjXn2r5u8x/A?D(G+KbPeSgVkYp3s6v9y$B&E)H@McQfTjWmZq4t7w!z%C*F-JaNdRgUkXp2r5u8x/A?D(G+KbPeShVmYq3t6v9y$B&E)H@McQfTjWnZr4u7x!z%C*F-JaNdRgUk";
	const std::string file = "login.txt";
	const bool encryption = true;

private:
	std::string encrypt(std::string msg)
	{
		std::string tmp(key);
		while (key.size() < msg.size())
			key += tmp;

		for (std::string::size_type i = 0; i < msg.size(); ++i) {
			msg[i] ^= key[i];
		}
		std::string::size_type pos = 0;
		while ((pos = msg.find("\r\n", pos)) != std::string::npos)
		{
			msg.erase(pos, 2);
		}
		return msg;
	}

	std::string decrypt(std::string msg)
	{
		return encrypt(msg);
	}

public:
	bool checkLogin(std::string user, std::string pass) {
		if (encryption) {
			std::string user_dec = decrypt(user);
			std::string pass_dec = decrypt(pass);

			std::ifstream in(file);
			std::string tp;
			std::vector <std::string> vector;

			while (std::getline(in >> std::ws, tp)) {
				if (tp.size() > 0) {
					vector.push_back(tp);
				}
			}

			in.close();

			if (vector[0] == user_dec && vector[1] == pass_dec) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			std::ifstream in(file);
			std::string tp;
			std::vector <std::string> vector;

			while (std::getline(in >> std::ws, tp)) {
				if (tp.size() > 0) {
					vector.push_back(tp);
				}
			}

			in.close();

			if (vector[0] == user && vector[1] == pass) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	bool registerLogin(std::string user, std::string pass) {
		if (encryption) {
			std::string user_enc = encrypt(user);
			std::string pass_enc = encrypt(pass);

			try {
				std::ofstream output(file);
				output << user_enc << "\n" << pass_enc;
				output.close();
			}
			catch (...) {
				std::cout << "File output error. (w/enc)";
				return false;
			}
			return true;
		}
		else {
			try {
				std::ofstream output(file);
				output << user << "\n" << pass;
				output.close();
			}
			catch (...) {
				std::cout << "File output error. (wo/enc)";
				return false;
			}
		}
	}
};

int main()
{
Main:
	system("cls");
	std::string some;
	std::cout << "[+] Would you like to login or register?\n1. Login\n2. Register\n=> ";
	std::getline(std::cin, some);

	int a;
	std::stringstream ss(some);
	ss >> a;

	system("cls");

	switch(a) {
	case 1: {
		std::string username;
		std::string password;
		auth auth;

		std::cout << "[+] Please enter your username: ";
		std::getline(std::cin, username);

		std::cout << "[+] Please enter your password: ";
		std::getline(std::cin, password);

		if (auth.checkLogin(username, password)) {
			system("cls");
			std::cout << "Successfully logged in!" << "\n";
			_getch();
		}
		else {
			system("cls");
			std::cout << "Incorrect login!" << "\n";
			_getch();
		}
		break;
	}
	case 2: {
		std::string username;
		std::string password;
		auth auth;

		std::cout << "[+] Please enter your desired username: ";
		std::getline(std::cin, username);

		for (std::string::size_type i = 0; i < username.size(); ++i) {
			if (username[i] == ' ') {
				std::cout << "Your username cannot contain spaces!";
				_getch();
				goto Main;
			}
			else {
				continue;
			}
		}
		
		if (username.length() > 15) {
			system("cls");
			std::cout << "Your username cannot be more than 15 characters.";
			_getch();
			goto Main;
		}

		std::cout << "[+] Please enter your desired password: ";
		std::getline(std::cin, password);

		for (std::string::size_type i = 0; i < password.size(); ++i) {
			if (password[i] == ' ') {
				std::cout << "Your password cannot contain spaces!";
				_getch();
				goto Main;
			}
			else {
				continue;
			}
		}

		if (password.length() > 15) {
			system("cls");
			std::cout << "Your password cannot be more than 15 characters.";
			_getch();
			goto Main;
		}

		auth.registerLogin(username, password);
		system("cls");
		std::cout << "Sucessfully registered!" << "\n";
		_getch();
		goto Main;
	}
	default:
		std::cout << "[+] Invalid input, please try again." << "\n";
		_getch();
		goto Main;
	}

}