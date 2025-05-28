def http_hello_page(request, response):
    # Read the request data from the client.
    user = read_from_file(request)
    
    # Construct a greeting message for the user.
    message = f"Hello, {user}!"
    
    # Write the message to the response file stream.
    write_to_file(response, message)

### Explanation:
The function http_hello_page takes in a request and a response. The request is a file stream that contains from the client. The response is a file stream that we can write to. The request contains the username that the client entered. We construct a greeting message for the user.