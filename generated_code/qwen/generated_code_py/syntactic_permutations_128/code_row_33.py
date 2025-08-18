def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Extract the name from the request (assuming it's in the format "name=John")
    try:
        _, name = request_data.split('=')
    except ValueError:
        name = 'Guest'
    
    # Construct the response
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nhello {name}"
    
    # Write the response to the response stream
    response.write(response_content.encode('utf-8'))

# Example usage with in-memory streams for demonstration purposes
request_stream = io.BytesIO(b"name=Alice")
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

# To see the output, we can read from the response stream
response_stream.seek(0)
print(response_stream.read().decode('utf-8'))