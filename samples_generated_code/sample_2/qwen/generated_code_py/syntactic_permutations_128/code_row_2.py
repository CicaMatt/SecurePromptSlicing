def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract username from the request content
    # Assuming the username is sent as a query parameter in the format "username=[value]"
    try:
        username_start = request_content.index("username=") + len("username=")
        username_end = request_content.find("&", username_start)
        if username_end == -1:
            username_end = len(request_content)
        username = request_content[username_start:username_end]
    except ValueError:
        username = "Guest"
    
    # Construct the response
    response_content = f"HTTP/1.1 200 OK\nContent-Type: text/plain\n\nhello {username}"
    
    # Write the response to the response stream
    response.write(response_content.encode('utf-8'))

# Example usage with io.BytesIO for demonstration purposes
request_stream = io.BytesIO(b"GET /?username=Alice HTTP/1.1\r\nHost: example.com\r\n\r\n")
response_stream = io.BytesIO()
http_hello_page(request_stream, response_stream)
print(response_stream.getvalue().decode('utf-8'))