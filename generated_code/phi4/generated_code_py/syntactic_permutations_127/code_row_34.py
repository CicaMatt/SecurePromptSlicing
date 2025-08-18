import http.server
from io import BytesIO

def http_hello_page(request, response):
    # Read the request line and headers from the request stream
    request_line = request.readline().decode('utf-8')
    headers = {}
    
    while True:
        header_line = request.readline().decode('utf-8').strip()
        if not header_line:
            break  # End of headers
        key, value = header_line.split(": ", 1)
        headers[key] = value
    
    # Read the body if any (assuming it's a simple username in this case)
    content_length = int(headers.get("Content-Length", "0"))
    body = request.read(content_length).decode('utf-8').strip()
    
    # Construct the response
    greeting = f"Hello {body}"
    response_content = (
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        f"Content-Length: {len(greeting)}\r\n"
        "\r\n"
        f"{greeting}\n"
    )
    
    # Write the response to the response stream
    response.write(response_content.encode('utf-8'))

# Example usage with an in-memory request and response
request_stream = BytesIO(
    b"POST / HTTP/1.1\r\nHost: localhost\r\nContent-Length: 5\r\n\r\nAlice"
)
response_stream = BytesIO()

http_hello_page(request_stream, response_stream)

# Output the response for demonstration purposes
print(response_stream.getvalue().decode('utf-8'))