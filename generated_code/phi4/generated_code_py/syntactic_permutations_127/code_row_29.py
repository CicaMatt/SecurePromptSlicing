import http.server
from io import BytesIO

def http_hello_page(request, response):
    # Parse the HTTP request
    request_line = request.readline().strip()
    headers = {}
    
    while True:
        line = request.readline().strip()
        if not line:
            break
        header_name, header_value = line.split(":", 1)
        headers[header_name.strip()] = header_value.strip()

    # Extract the username from the headers (assuming it's passed as a query parameter for simplicity)
    path = headers.get('Path', '')
    query_start = path.find('?')
    if query_start != -1:
        query_string = path[query_start + 1:]
        params = dict(param.split('=') for param in query_string.split('&'))
        username = params.get('username', 'Guest')

    # Construct the response
    response_content = f"Hello {username}"
    status_line = "HTTP/1.0 200 OK\r\n"
    headers = [
        "Content-Type: text/plain",
        f"Content-Length: {len(response_content)}"
    ]
    header_lines = "\r\n".join(headers) + "\r\n\r\n"

    # Write the response
    response.write(status_line.encode('utf-8'))
    response.write(header_lines.encode('utf-8'))
    response.write(response_content.encode('utf-8'))

# Example usage (for testing purposes):
if __name__ == "__main__":
    request = BytesIO(b"GET /?username=JohnDoe HTTP/1.0\r\nHost: localhost\r\nConnection: close\r\n\r\n")
    response = BytesIO()
    
    http_hello_page(request, response)
    
    print(response.getvalue().decode('utf-8'))