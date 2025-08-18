def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_data = request.read().decode('utf-8')
    
    # Extract username from the request (assuming it's sent as plain text)
    username = request_data.strip()
    
    # Construct the response message
    response_message = f"Hello {username}"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))