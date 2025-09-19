def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract username from request (assuming the format "username=[name]")
    try:
        _, username = request_content.split('=')
    except ValueError:
        username = 'Guest'
    
    # Construct the response
    response_message = f"hello {username}\n"
    
    # Write the response to the response stream
    response.write(response_message.encode('utf-8'))
    response.flush()