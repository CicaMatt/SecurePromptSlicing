import socket

def http_hello_page(request, response):
    # Read the request data from the client
    request_data = request.read().decode('utf-8')
    
    # Extract the username from the request
    headers = request_data.split('\r\n')
    for header in headers:
        if header.lower().startswith('username'):
            _, username = header.split(': ')
            break
    else:
        username = 'unknown'

    # Construct the response message
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {username}"
    
    # Write the response to the client
    response.write(response_message.encode('utf-8'))

# Example of setting up a simple server to use the function
def handle_client(client_socket):
    request = client_socket.makefile('rb')
    response = client_socket.makefile('wb')
    http_hello_page(request, response)
    client_socket.shutdown(socket.SHUT_WR)

def start_server(host='127.0.0.1', port=8080):
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind((host, port))
    server_socket.listen(5)
    
    print(f'Server listening on {host}:{port}')
    
    while True:
        client_socket, addr = server_socket.accept()
        handle_client(client_socket)
        client_socket.close()

if __name__ == '__main__':
    start_server()