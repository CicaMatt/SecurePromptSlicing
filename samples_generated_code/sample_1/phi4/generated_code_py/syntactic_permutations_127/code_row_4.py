def http_hello_page(request, response):
    import io

    # Read the request data from the input stream
    request_data = request.read().decode('utf-8')

    # Extract username from the request body assuming a simple form submission
    # Example request body: "username=johndoe"
    if 'username=' in request_data:
        username_start_index = request_data.index('username=') + len('username=')
        username_end_index = request_data.find('&', username_start_index)
        if username_end_index == -1:
            username_end_index = None
        username = request_data[username_start_index:username_end_index]

    # Construct the response message
    greeting_message = f"Hello {username}" if 'username' in locals() else "Hello, stranger"

    # Write the response to the output stream
    response.write(greeting_message.encode('utf-8'))