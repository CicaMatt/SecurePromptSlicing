def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request content
    # Assuming the request format is "username=[username]"
    parts = request_content.split('=')
    if len(parts) == 2 and parts[0].strip() == 'username':
        username = parts[1].strip()
    else:
        username = 'Guest'
    
    # Construct the response content
    response_content = f"hello {username}"
    
    # Write the response content to the response stream
    response.write(response_content.encode('utf-8'))

# Example usage with in-memory streams for demonstration
request_stream = io.BytesIO(b'username=Alice')
response_stream = io.BytesIO()

http_hello_page(request_stream, response_stream)

# To see the result, we read from the response stream
response_stream.seek(0)
print(response_stream.read().decode('utf-8'))