def http_hello_page(request, response):
        """Reads in a request from the client,
        extracts the username from the request,
        constructs an HTTP response that says 'Hello [username]',
        and writes the response to the client.
        """
        # Read the username from the request.
        username = read_username(request)

        # Construct a response that says "Hello [username]"
        body = f"Hello {username}"
        status_code = 200
        headers = {"Content-Type": "text/plain"}

        # Write the response to the client.
        write_response(response, status_code, headers, body)

def read_username(request):
    """Reads a username from the request."""
    # Read the request and extract the username.
    ...
    return username

def write_response(response, status_code, headers, body):
    """Writes an HTTP response to the client."""
    # Write the status line.
    response.write(f"HTTP/1.0 {status_code}\r\n")

    # Write each header.
    for key, value in headers.items():
        response.write(f"{key}: {value}\r\n")

    # Add a blank line to separate the headers from the body.
    response.write("\r\n")

    # Write the body.
    response.write(body)