def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request (assuming it's in the format "username=[name]")
    parts = request_content.split('=')
    if len(parts) == 2 and parts[0].strip() == 'username':
        username = parts[1].strip()
    else:
        username = 'Guest'
    
    # Construct the response
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))