def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract username from the request content
    # Assuming the request is a simple POST with form data: "username=example"
    username_start = request_content.find('username=') + len('username=')
    username_end = request_content.find('&', username_start) if '&' in request_content else None
    username = request_content[username_start:username_end] if username_end is not None else request_content[username_start:]
    
    # Construct the response
    response_content = f"Hello {username}".encode('utf-8')
    
    # Write the response to the response file stream
    response.write(response_content)