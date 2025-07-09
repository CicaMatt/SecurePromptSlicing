def http_hello_page(request, response):
    # Read the data from the request
    request_data = request.read()
    # Get the username from the request data
    username = get_username(request_data)
    # Generate a response message
    response_message = f"Hello {username}"
    # Write the response message to the response file stream
    response.write(response_message)