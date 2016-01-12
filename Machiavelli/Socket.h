#pragma once
//=============================================================================
// socket.h
// (c) 8-12-2010, Frans Spijkerman, Avans Hogeschool
// enhanced for cross-platform use by Bob Polis (c) 2013, 2014
//
// Definition of classes Socket, ServerSocket and CientSocket
//
// Socket:
//	Abstraction of tcp-socket using Windows Sockets API (WSA)
//
// ServerSocket:
//  Socket to listen to clients on a tcp-port
//
// ClientSocket:
//	Socket to connect to a server on a tcp-port
//=============================================================================

#if defined(__APPLE__) || defined(__linux__)
	#include <sys/socket.h>
	typedef int SOCKET;
#else // Windows
	#include <winsock2.h>
	typedef long ssize_t;
#endif

#include <iostream>
#include <string>
#include <memory>

//=============================================================================
class Socket
//=============================================================================
{
protected:
    SOCKET sock {0};
	struct sockaddr_storage addr;

public:
    Socket() {}
    Socket(SOCKET sock, const struct sockaddr& address);
	Socket(const Socket& other) = delete;
	Socket(Socket&& other);
	virtual ~Socket();

	Socket& operator=(const Socket& other) = delete;
	Socket& operator=(Socket&& other);

	SOCKET get_socket() const { return sock; }
	void set_socket(SOCKET sock) { this->sock = sock; }
	void close();
	bool is_open() const { return sock > 0; }
	std::string get_dotted_ip() const;

	ssize_t read(char *buf, size_t maxlen) const;
    char read() const;
	std::string readline() const;

	void write(const std::string& msg) const;
	void write(const char *buf, size_t len) const;
    void write(char c) const;
	
	const Socket& operator<<(const char c) const;
	const Socket& operator<<(const char* message) const;
	const Socket& operator<<(const std::string& message) const;
	
	template <typename T> const Socket& operator<<(T value) const {
		write(std::to_string(value));
		return *this;
	}
};

//=============================================================================
class ServerSocket : public Socket
//=============================================================================
{
public:
	ServerSocket(int port);
	std::unique_ptr<Socket> accept();
};

//=============================================================================
class ClientSocket : public Socket
//=============================================================================
{
public:
    ClientSocket(const std::string& host, int port);
};

