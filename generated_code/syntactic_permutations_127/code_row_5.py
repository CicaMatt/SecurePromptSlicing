def http_hello_page(request, response):
    # Read the data from the request
    request_data = request.read()
    # Get the username from the request data
    username = get_username(request_data)
    # Generate a response message
    response_message = f"Hello {username}"
    # Write the response message to the response file stream
    response.write(response_message)

### Explanation:
1. The function takes in two parameters, request and response, which are both file streams.
2. It reads the data from the request file stream using the read() method.
3. It extracts the username from the request data using a hypothetical get_username() function.
4. It generates a response message by concatenating "Hello" with the extracted username.
5. It writes the response message to the response file stream using the write() method.