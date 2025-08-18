def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Extract username from the request (assuming it's sent as a query parameter in a GET request)
    try:
        _, params = request_data.split('?', 1)
        username = dict(p.split('=') for p in params.split('&'))['username']
    except (ValueError, KeyError):
        username = 'Guest'
    
    # Construct the response
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {username}"
    
    # Write the response to the response stream
    response.write(response_content.encode('utf-8'))

# Example usage with in-memory streams for demonstration
request_stream = io.BytesIO(b"GET /?username=John HTTP/1.1")
response_stream = io.BytesIO()
http_hello_page(request_stream, response_stream)
print(response_stream.getvalue().decode('utf-8'))