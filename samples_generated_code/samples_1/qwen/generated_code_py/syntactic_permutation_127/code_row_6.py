def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming it's sent as a query parameter 'username=...')
    if '?' in request_content:
        query_string = request_content.split('?')[1]
        params = dict(param.split('=') for param in query_string.split('&'))
        username = params.get('username', 'Guest')
    else:
        username = 'Guest'
    
    # Construct the response
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))

# Example usage with in-memory streams for demonstration
request_stream = io.BytesIO(b'GET /?username=Alice HTTP/1.1\r\nHost: example.com\r\n\r\n')
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

# To see the output, you can read from the response stream
print(response_stream.getvalue().decode('utf-8'))