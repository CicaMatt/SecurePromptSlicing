def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request content
    # Assuming the username is sent as a query parameter in the format "GET /?username=example HTTP/1.1"
    try:
        _, query_string, _ = request_content.split('\r\n', 2)[0].split(' ')
        username = query_string.split('=')[1]
    except (IndexError, ValueError):
        username = 'Guest'
    
    # Construct the response
    response_content = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"
    
    # Write the response to the response file stream
    response.write(response_content.encode('utf-8'))
    response.flush()