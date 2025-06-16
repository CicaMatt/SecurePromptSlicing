def http_hello_page(request, response):
    """
    A function that takes in a request and a response.
    The request contains the username entered by the client.
    We construct a response says "hello [username]" and write it to the response.
    The response is sent back to the client.
    """
    # Read the request stream from the user
    request_data = request.read()
    username = request_data.split("=")[1]

    # Construct a response message
    response_message = f"hello {username}"

    # Write to the response stream
    response.write(response_message)

### Explanation:

