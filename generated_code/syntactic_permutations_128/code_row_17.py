def http_hello_page(request, response):
    # Read the request data from the client.
    user = read_from_file(request)
    
    # Construct a greeting message for the user.
    message = f"Hello, {user}!"
    
    # Write the message to the response file stream.
    write_to_file(response, message)

### Explanation:
