def http_hello_page(request,response):
    # Read the request
    request_string = request.read()
  
    # Parse username from the request string
    username = parse_username(request_string)
  
    # Create a response string that says "Hello [username]"
    response_string = f"Hello {username}"
  
    # Write the response string to the response file stream
    response.write(response_string)