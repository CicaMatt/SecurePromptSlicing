def http_hello_page(request, response):
    import io
    
    # Read the request content
    request_content = request.read().decode('utf-8')
    
    # Assuming the username is sent as a query parameter in the format "username=[value]"
    # Extracting the username from the request content
    try:
        username_start = request_content.find("username=") + len("username=")
        username_end = request_content.find("&", username_start)
        if username_end == -1:
            username_end = len(request_content)
        username = request_content[username_start:username_end]
    except Exception as e:
        username = "Guest"
    
    # Construct the response
    response_message = f"Hello {username}\n"
    
    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))