def http_hello_page(request, response):
    import io

    # Read the request content
    request_content = request.read().decode('utf-8')

    # Extract the username from the request (assuming it's in plain text)
    username = request_content.strip()

    # Construct the response message
    response_message = f"Hello {username}\n"

    # Write the response to the response file stream
    response.write(response_message.encode('utf-8'))