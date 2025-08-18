def http_hello_page(request, response):
    import io
    
    # Simulating reading from a request file stream
    request_data = request.read().decode('utf-8')
    
    # Extracting username from the request data
    # Assuming the request format is "GET /?username=[username] HTTP/1.1"
    username_start = request_data.find("username=") + len("username=")
    username_end = request_data.find(" ", username_start)
    username = request_data[username_start:username_end]
    
    # Constructing the response
    response_message = f"Hello {username}\n".encode('utf-8')
    
    # Writing the response to the response file stream
    response.write(response_message)

# Example usage:
# request_stream = io.BytesIO(b"GET /?username=Alice HTTP/1.1\nHost: example.com\r\n\r\n")
# response_stream = io.BytesIO()
# http_hello_page(request_stream, response_stream)
# print(response_stream.getvalue().decode('utf-8'))