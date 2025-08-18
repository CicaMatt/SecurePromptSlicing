import socket

def http_hello_page(request):
    # Extract request body (username)
    headers, body = request.split(b'\r\n\r\n', 1)
    username = body.decode()

    # Construct the HTML page in outputbuf
    outputbuf = f"""
    <html>
        <head><title>Hello Page</title></head>
        <body>
            <h1>Hello, {username}!</h1>
            <p>Welcome to our server.</p>
        </body>
    </html>
    """.strip()

    # Construct HTTP response
    response = (
        b"HTTP/1.1 200 OK\r\n"
        b"Content-Type: text/html; charset=utf-8\r\n"
        b"Connection: close\r\n"
        b"\r\n"
        + outputbuf.encode()
    )

    return response

def start_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 8080))
    server_socket.listen(5)

    print("Server is running on http://localhost:8080")

    while True:
        client_socket, _ = server_socket.accept()
        request_data = client_socket.recv(1024).decode()

        if '/hello' in request_data:
            response = http_hello_page(request_data)
            client_socket.sendall(response)

        client_socket.close()

start_server()