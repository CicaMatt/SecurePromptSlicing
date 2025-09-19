def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Extract username from the request data
    # Assuming the request format is "GET /?username=[username] HTTP/1.1"
    parts = request_data.split()
    if len(parts) > 1:
        query_string = parts[1]
        if '?' in query_string:
            query_params = dict(qc.split('=') for qc in query_string.split('?')[1].split('&'))
            username = query_params.get('username', 'Guest')
        else:
            username = 'Guest'
    else:
        username = 'Guest'
    
    # Construct the response
    response_message = f"HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))