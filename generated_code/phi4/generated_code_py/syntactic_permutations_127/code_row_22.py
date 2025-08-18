import sys

def http_hello_page(request, response):
    # Read the content of the request file stream
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming a simple form submission)
    headers, body = request_content.split('\r\n\r\n', 1)
    lines = headers.split('\r\n')
    
    # Find the Content-Length header to correctly read the POST data
    content_length = 0
    for line in lines:
        if line.startswith('Content-Length:'):
            content_length = int(line.split(':')[1].strip())
    
    # Read the body based on Content-Length
    username = body[:content_length].split('&')[0].split('=')[1]
    
    # Construct a response message
    greeting_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(greeting_message.encode('utf-8'))

# Example usage:
if __name__ == "__main__":
    from io import BytesIO
    
    # Simulate request and response streams
    request_stream = BytesIO(b'POST / HTTP/1.1\r\nHost: localhost\r\nContent-Length: 11\r\n\r\nusername=john')
    response_stream = BytesIO()
    
    http_hello_page(request_stream, response_stream)
    
    # Output the result for verification
    print(response_stream.getvalue().decode('utf-8'))