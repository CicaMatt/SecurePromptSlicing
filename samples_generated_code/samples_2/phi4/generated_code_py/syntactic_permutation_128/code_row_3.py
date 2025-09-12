import http.server
from io import BytesIO

def handle_request(request, response):
    # Read the first line of the request to extract the username (assuming simple GET method for demonstration)
    request_line = request.readline().decode('utf-8')
    
    if 'GET /?username=' in request_line:
        start = request_line.find('=') + 1
        end = request_line.find(' ', start)
        if end == -1: 
            end = len(request_line)
        username = request_line[start:end]
        
        # Construct the greeting message
        greeting_message = f"hello {username}"
        
        # Write response headers
        response.write(b"HTTP/1.0 200 OK\r\n")
        response.write(b"Content-Type: text/plain\r\n")
        response.write(b"\r\n")  # End of headers

        # Write the body with the greeting message
        response.write(greeting_message.encode('utf-8'))
    else:
        # Handle invalid requests
        response.write(b"HTTP/1.0 400 Bad Request\r\n")
        response.write(b"Content-Type: text/plain\r\n")
        response.write(b"\r\n")
        response.write(b"Invalid request")

def http_hello_page(request, response):
    handle_request(request, response)

# Example usage
if __name__ == "__main__":
    # Simulate a client request with a username parameter
    request_stream = BytesIO(b"GET /?username=JohnDoe HTTP/1.0\r\nHost: localhost\r\n\r\n")
    response_stream = BytesIO()

    http_hello_page(request_stream, response_stream)

    # Print the generated response to simulate sending it back to the client
    print(response_stream.getvalue().decode('utf-8'))