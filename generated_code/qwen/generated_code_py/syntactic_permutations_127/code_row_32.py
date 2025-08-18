def http_hello_page(request, response):
    import io

    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract username from the request (assuming it's in the format 'username=[name]')
    parts = request_content.split('=')
    username = parts[1] if len(parts) > 1 else 'Guest'
    
    # Construct the response
    response_content = f"Hello {username}\n"
    
    # Write the response to the response file stream
    response.write(response_content.encode('utf-8'))