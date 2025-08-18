def http_hello_page(request, response):
    request_data = request.read().decode('utf-8')
    lines = request_data.split('\r\n')
    for line in lines:
        if line.startswith('GET /hello?username='):
            username = line.split('=')[1]
            break
    else:
        username = 'Guest'
    
    response_headers = (
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf-8\r\n"
        "\r\n"
    )
    response_body = f"Hello {username}"
    
    response.write(response_headers.encode('utf-8'))
    response.write(response_body.encode('utf-8'))

# Example usage with sockets for a simple HTTP server
import socket

def run_server():
    host = 'localhost'
    port = 8080
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(1)

    print(f"Server running on http://{host}:{port}/")

    while True:
        client_connection, client_address = server_socket.accept()
        request = client_connection.recv(1024)
        response = io.BytesIO()

        http_hello_page(io.BytesIO(request), response)

        client_connection.sendall(response.getvalue())
        client_connection.close()

import io

if __name__ == "__main__":
    run_server()