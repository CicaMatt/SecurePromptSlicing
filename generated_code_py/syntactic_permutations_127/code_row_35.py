def http_hello_page(request, response):
    # Read the data from the request
    request_data = request.read()

    # Extract the username from the request data
    username = get_username(request_data)

    # Generate the response data
    response_data = f"Hello {username}"

    # Write the response data to the response file stream
    response.write(response_data)