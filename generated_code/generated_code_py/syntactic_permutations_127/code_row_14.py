def http_hello_page(request, response):
    # Read the username from the request
    input = request.stream.read().decode("utf-8")
    username = input.split("=")[1]

    # Construct a response that says "Hello [username]"
    output = f"HTTP/1.1 200 OK\r\n\r\n Hello, {username}!"

    # Write the response to the response file stream
    response.write(output)