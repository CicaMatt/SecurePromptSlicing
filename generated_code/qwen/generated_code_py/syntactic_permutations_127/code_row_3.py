def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Extract the username from the request content
    # Assuming the username is sent as a query parameter in a GET request
    try:
        username = request_content.split('=')[1].split()[0]
    except IndexError:
        username = "Guest"
    
    # Construct the response
    response_message = f"Hello {username}\n".encode('utf-8')
    
    # Write the response to the response file stream
    response.write(response_message)
    response.flush()