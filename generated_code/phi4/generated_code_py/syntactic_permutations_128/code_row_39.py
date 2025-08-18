import io

def http_hello_page(request: io.BytesIO, response: io.BytesIO) -> None:
    # Read the request content as UTF-8 text
    request_content = request.getvalue().decode('utf-8')
    
    # Extract username from request content assuming it's a simple GET request with 'username' in query string
    # Example request line: "GET /?username=johndoe HTTP/1.1"
    if "username=" in request_content:
        start = request_content.find("username=") + len("username=")
        end = request_content.find(" ", start)
        username = request_content[start:end]
        
        # Construct the response message
        greeting_message = f"Hello {username}"
    else:
        greeting_message = "Hello stranger"
    
    # Write the HTTP response headers and body to the response stream
    response.write(b"HTTP/1.1 200 OK\r\n")
    response.write(b"Content-Type: text/plain; charset=UTF-8\r\n")
    response.write(b"\r\n")  # End of headers
    
    # Write the greeting message as response body
    response.write(greeting_message.encode('utf-8'))