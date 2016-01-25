//
//  main.cpp
//  socketexample
//
//  Created by Bob Polis on 16/09/14.
//  Copyright (c) 2014 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include <thread>
#include <iostream>
#include <exception>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

#include "Socket.h"
#include "Sync_queue.h"
#include "ClientCommand.h"
#include "Player.h"

#include "Game.h"

shared_ptr<Game> m_g;

namespace machiavelli {
    const int tcp_port {1080};
    const string prompt {"machiavelli> "};
}

static Sync_queue<ClientCommand> queue;


void consume_command() // runs in its own thread
{
    try {
        while (true) {
			ClientCommand command {queue.get()}; // will block here unless there are still command objects in the queue
			shared_ptr<Socket> client {command.get_client()};
			shared_ptr<Player> player {command.get_player()};
			try {
 				m_g->handleCommand(player, command.get_cmd());

				// TODO handle command here
				//*client << player->get_name() << ", you wrote: '" << command.get_cmd() << "', but I'll ignore that for now.\r\n" << machiavelli::prompt;
			} catch (const exception& ex) {
				cerr << "*** exception in consumer thread for player " << player->get_name() << ": " << ex.what() << '\n';
				if (client->is_open()) {
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			} catch (...) {
				cerr << "*** exception in consumer thread for player " << player->get_name() << '\n';
				if (client->is_open()) {
					client->write("Sorry, something went wrong during handling of your request.\r\n");
				}
			}
        }
    } catch (...) {
        cerr << "consume_command crashed\n";
    }
}

void handle_client(shared_ptr<Socket> client) // this function runs in a separate thread
{
	try {
		client->write("Welcome to Server 1.0! To quit, type 'quit'.\r\n");
		if (m_g->isGameStarted()) {
			client->write("Game already in progress, please try again later.\r\n");
		}
		else {
			client->write("What's your name?\r\n");
			client->write(machiavelli::prompt);
			string name{ client->readline() };

			if (m_g->getCurrentPlayers().size() >= 2) {
				client->write("Lobby full, please try again later.\r\n");
			}
			else {
				shared_ptr<Player> player{ new Player {name, m_g, client} };
				m_g->AddPlayer(player);

				*client << machiavelli::prompt << "Welcome, " << name << ", have fun playing our game!\r\n";
				
				m_g->handleCommand(player, "join");

				while (true) { // game loop
					try {
						// read first line of request
						string cmd{ client->readline() };
						cerr << '[' << client->get_dotted_ip() << " (" << client->get_socket() << ") " << player->get_name() << "] " << cmd << '\n';

						std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

						if (cmd == "quit") {
							m_g->RemovePlayer(player);
							m_g->handleCommand(player, "quit");
							client->write("Bye!\r\n");
							break; // out of game loop, will end this thread and close connection
						}

						ClientCommand command{ cmd, client, player };
						queue.put(command);

					}
					catch (const exception& ex) {
						cerr << "*** exception in client handler thread for player " << player->get_name() << ": " << ex.what() << '\n';
						if (client->is_open()) {
							*client << "ERROR: " << ex.what() << "\r\n";
						}
					}
					catch (...) {
						cerr << "*** exception in client handler thread for player " << player->get_name() << '\n';
						if (client->is_open()) {
							client->write("ERROR: something went wrong during handling of your request. Sorry!\r\n");
						}
					}
				}
				if (client->is_open()) client->close();

			}
		}
	}
	catch (...) {
		cerr << "handle_client crashed\n";
	}	
}

int main(int argc, const char * argv[])
{
	m_g = make_shared<Game>(Game());

    // start command consumer thread
    thread consumer {consume_command};

	// keep client threads here, so we don't need to detach them
	vector<thread> handlers;
	    
	// create a server socket
	ServerSocket server {machiavelli::tcp_port};

	while (true) {
		try {
			while (true) {
				// wait for connection from client; will create new socket
				cerr << "server listening" << '\n';
				unique_ptr<Socket> client {server.accept()};

				// communicate with client over new socket in separate thread
                thread handler {handle_client, move(client)};
				handlers.push_back(move(handler));
			}
		} catch (const exception& ex) {
			cerr << ex.what() << ", resuming..." << '\n';
        } catch (...) {
            cerr << "problems, problems, but: keep calm and carry on!\n";
        }
	}
    return 0;
}

