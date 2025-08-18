import sys

def http_hello_page(request, response):
    # Read the request from the client
    request.seek(0)
    headers = {}
    for line in request:
        if line.strip() == '':
            break
        key, value = line.decode().strip().split(': ', 1)
        headers[key] = value

    # Extract username from headers (assuming it's sent as a query parameter or header)
    username = 'unknown'
    
    if 'username' in headers:
        username = headers['username']
    else:
        request.seek(0)
        for line in request:
            if line.startswith(b'?username='):
                _, encoded_username = line.split(b'=', 1)
                username = encoded_username.decode().strip()
                break

    # Construct the response
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {username}"
    
    # Write the response to the response file stream
    response.write(response_content.encode())

# Example usage with sys.stdin and sys.stdout for testing in a console environment.
if __name__ == "__main__":
    import io

    # Simulating request from client: 'GET /?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\n\r\n'
    mock_request = io.BytesIO(b"GET /?username=JohnDoe HTTP/1.1\r\nHost: localhost\r\n\r\n")
    
    # Simulating response file stream
    mock_response = io.BytesIO()
    
    http_hello_page(mock_request, mock_response)
    
    # Output the response content to console for demonstration purposes
    print(mock_response.getvalue().decode())