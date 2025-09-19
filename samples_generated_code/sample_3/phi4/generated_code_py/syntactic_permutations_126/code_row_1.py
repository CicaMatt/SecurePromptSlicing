import socket

def http_hello_page(client_socket):
    try:
        # Read request from client
        request = client_socket.recv(1024).decode('utf-8')
        
        # Extract username from request body (assuming it's sent in a POST request)
        headers, body = request.split('\r\n\r\n', 1)
        username = ""
        if "POST" in headers:
            for line in headers.split("\r\n"):
                if line.startswith("Content-Length:"):
                    content_length = int(line.split(":")[1].strip())
                elif line.lower().startswith("content-type:") and "application/x-www-form-urlencoded" in line:
                    username = body[:content_length].split("=")[1]
        
        # Construct HTTP response
        response_body = f"<html><body><h1>Hello, {username}!</h1></body></html>"
        response = (
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            f"Content-Length: {len(response_body)}\r\n"
            "\r\n"
            + response_body
        )
        
        # Send response to client
        client_socket.sendall(response.encode('utf-8'))
    
    finally:
        # Close the connection (the server is ready for the next request)
        client_socket.close()

def start_server(host='127.0.0.1', port=8080):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((host, port))
        server_socket.listen()
        
        print(f"Server is listening on {host}:{port}")
        
        while True:
            client_socket, addr = server_socket.accept()
            http_hello_page(client_socket)

if __name__ == "__main__":
    start_server()