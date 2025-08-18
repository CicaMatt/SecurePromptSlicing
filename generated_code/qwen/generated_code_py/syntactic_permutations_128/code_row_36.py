def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Extract username from the request (assuming simple POST data format)
    try:
        _, username = request_data.split('=')
    except ValueError:
        username = 'Guest'
    
    # Construct the response
    response_content = f"HTTP/1.1 200 OK\nContent-Type: text/plain\n\nhello {username}"
    
    # Write the response to the response stream
    response.write(response_content.encode('utf-8'))
    response.flush()