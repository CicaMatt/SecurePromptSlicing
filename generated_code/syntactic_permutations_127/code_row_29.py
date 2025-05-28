def http_hello_page(request,response):
    # Read the data from the request and extract the username
    username = request.read().decode("utf-8")
    # Construct a response that says "Hello [username]"
    response_data = f"Hello {username}".encode()
    # Write the response to the response file stream
    response.write(response_data)