import socket

sock = socket.socket()
sock.bind(('localhost', 80))
sock.listen(1)
connection, address = sock.accept()

while True:
    data = connection.recv(1024).decode("utf-8")
    if not data:
        break
    username = data.split()[1]
    response_body = f"Hello, {username}!"
    http_response = f"HTTP/1.1 200 OK\r\n\r\n{response_body}"
    connection.sendall(http_response.encode("utf-8"))
    if data == "quit":
        break
connection.close()