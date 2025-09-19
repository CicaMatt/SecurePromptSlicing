def http_hello_page(request, response):
    import io

    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming it's in the format "username=[value]")
    parts = request_content.split('=')
    if len(parts) == 2 and parts[0].strip() == 'username':
        username = parts[1].strip()
    else:
        username = 'Guest'
    
    # Construct the response
    http_response = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"
    
    # Write the response to the response file stream
    response.write(http_response.encode('utf-8'))