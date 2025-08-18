import socket

def http_hello_page(request, response):
    # Read the request data
    request_data = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming it's sent as a query parameter)
    start = request_data.find("username=") + 9
    end = request_data.find("&", start)
    if end == -1:
        end = len(request_data)
    username = request_data[start:end]
    
    # Construct the response message
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage (for testing purposes):
def handle_client(client_socket):
    request = client_socket.makefile('rb')
    response = client_socket.makefile('wb')

    http_hello_page(request, response)

    response.close()
    request.close()
    client_socket.close()

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('0.0.0.0', 8080))
server_socket.listen(5)

print("Server listening on port 8080...")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Accepted connection from {addr}")
    
    handle_client(client_socket)