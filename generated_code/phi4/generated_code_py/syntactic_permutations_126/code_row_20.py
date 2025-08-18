import socket

def http_hello_page(request_body):
    # Extract username from request body, assuming it's a simple key-value pair
    username = request_body.split('=')[-1]

    # Construct HTML response
    outputbuf = f"""
    <html>
        <head><title>Hello Page</title></head>
        <body>
            <h1>Hello, {username}!</h1>
        </body>
    </html>
    """

    return outputbuf

def handle_client(client_socket):
    request = client_socket.recv(1024).decode('utf-8')
    
    # Check if the URL is /hello
    headers = request.split('\n')
    url_line = headers[0].split(' ')[1]
    
    if url_line == '/hello':
        body_start = request.find("\r\n\r\n") + 4
        request_body = request[body_start:] if body_start != -1 else ""
        
        response_body = http_hello_page(request_body)

        # Construct HTTP response header
        response_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: {}\r\n\r\n".format(len(response_body))

        # Send the complete HTTP response
        client_socket.sendall((response_header + response_body).encode('utf-8'))
    
    client_socket.close()

def start_server(host='127.0.0.1', port=8080):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)

    print(f"Server listening on {host}:{port}")

    while True:
        client_socket, addr = server_socket.accept()
        print(f"Accepted connection from {addr}")
        
        handle_client(client_socket)

if __name__ == "__main__":
    start_server()