def http_hello_page(request, response):
    import io

    # Simulate reading from a file-like object
    request_data = request.read().decode('utf-8')
    
    # Assuming the username is sent as plain text in the request
    username = request_data.strip()
    
    # Construct the response
    response_message = f"Hello {username}\n"
    
    # Write the response to the file-like object
    response.write(response_message.encode('utf-8'))