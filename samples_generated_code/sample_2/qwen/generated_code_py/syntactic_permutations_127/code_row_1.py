def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request content
    # Assuming the request content is simply the username
    username = request_content.strip()
    
    # Construct the response
    response_content = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_content.encode('utf-8'))