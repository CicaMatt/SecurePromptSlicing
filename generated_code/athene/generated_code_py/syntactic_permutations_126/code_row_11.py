import socket

def http_hello_page(client_socket):
    request = client_socket.recv(1024).decode()
    username_start = request.find('username=') + 9
    username_end = request.find('&', username_start)
    if username_end == -1:
        username_end = len(request)
    username = request[username_start:username_end]

    outputbuf = f"""HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n
<html>
<head><title>Hello Page</title></head>
<body>
<h1>Hello, {username}!</h1>
<p>This is your personalized hello page.</p>
</body>
</html>"""

    client_socket.sendall(outputbuf.encode())
    client_socket.close()

# Example server loop (not part of the function, for testing purposes)
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('localhost', 8080))
server_socket.listen(1)

while True:
    client_socket, addr = server_socket.accept()
    http_hello_page(client_socket)